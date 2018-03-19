/*************************************************
* <:copyright-BRCM:2013:proprietary:standard
*
*    Copyright (c) 2013 Broadcom
*    All Rights Reserved
*
*  This program is the proprietary software of Broadcom and/or its
*  licensors, and may only be used, duplicated, modified or distributed pursuant
*  to the terms and conditions of a separate, written license agreement executed
*  between you and Broadcom (an "Authorized License").  Except as set forth in
*  an Authorized License, Broadcom grants no license (express or implied), right
*  to use, or waiver of any kind with respect to the Software, and Broadcom
*  expressly reserves all rights in and to the Software and all intellectual
*  property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE
*  NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY
*  BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
*
*  Except as expressly set forth in the Authorized License,
*
*  1. This program, including its structure, sequence and organization,
*     constitutes the valuable trade secrets of Broadcom, and you shall use
*     all reasonable efforts to protect the confidentiality thereof, and to
*     use this information only in connection with your use of Broadcom
*     integrated circuit products.
*
*  2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
*     AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
*     WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
*     RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND
*     ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT,
*     FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
*     COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE
*     TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE OR
*     PERFORMANCE OF THE SOFTWARE.
*
*  3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR
*     ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
*     INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY
*     WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN
*     IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES;
*     OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE
*     SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS
*     SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY
*     LIMITED REMEDY.
:>
*/
/**
 *	@file	 wlcsm_lib_nvram.c
 *	@brief	 wlcsm nvram related functions
 *
 *	wlcsm nvram acts as middleware between user application and
 *	nvram storage in kernel.Nvram item value change is closely
 *	monitored in a seperated thread and broadcasted to user applications
 *	which are using nvram middleware. User application register its hook
 *	to respond to nvram varibble changes.It is Application's sole responsibility
 *	to react to the change.Nvram middle ware has no knowldge of App's intersts.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <asm/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <bcmnvram.h>
#include <linux/netlink.h>
#include <linux/in.h>
#include <linux/if.h>
#include <errno.h>
#include  <pthread.h>
#include <sys/time.h>
#include  <sys/prctl.h>
#include  <stdarg.h>
#include "wlcsm_linux.h"
#include "wlcsm_lib_api.h"
#include "wlcsm_lib_netlink.h"
#include "wlcsm_lib_nvram.h"

#ifdef WLCSM_DEBUG
#include <sys/time.h>
unsigned int g_WLCSM_TRACE_LEVEL = 1;
char g_WLCSM_TRACE_PROC[32] = {0};

typedef struct t_wlcsm_trace_match {
    char name[16];
    unsigned char level;
} t_WLCSM_TRACE_MATCH;

t_WLCSM_TRACE_MATCH trace_matches[]= {
    { "clr", WLCSM_TRACE_NONE  },
    { "dbg", WLCSM_TRACE_DBG  },
    { "err", WLCSM_TRACE_ERR  },
    { "log", WLCSM_TRACE_LOG  },
    { "func", WLCSM_TRACE_FUNC  },
    { "pkt", WLCSM_TRACE_PKT  }
};
#endif

#define m_NO_CREATE 0
#define m_CREATE_NEW 1

WLCSM_EVENT_HOOK_FUNC g_WLCSM_EVENT_HOOKS[WLCSM_EVT_LAST]; 	/**< specic event hook as some apps only intersted in specific event */
WLCSM_EVENT_HOOK_GENERICFUNC  g_WLCSM_EVENT_GENERIC_HOOK=NULL;	/**< generic hook for listening to all wlcsm events */
extern int _wlcsm_init(int is_daemon);

pthread_mutex_t g_WLCSM_NVRAM_MUTEX= PTHREAD_MUTEX_INITIALIZER; /**< mutex for protecting nvram manipulation */

#define _NVRAM_UNLOCK() pthread_mutex_unlock(&g_WLCSM_NVRAM_MUTEX)
#define _NVRAM_LOCK()  pthread_mutex_lock(&g_WLCSM_NVRAM_MUTEX)
#define  _LOCAL_SYNC_ENABLED_  (g_WLCSM_IS_DAEMON==m_AS_DAEMON)
#define  _STR_VALUE_EQUAL(v1,v2) ((v1 && v2 && !strcmp(v1,v2)) || (!v1 && !v2))

static char g_temp_buf[MAX_NLRCV_BUF_SIZE];

/* internal structure */
struct wlcsm_nvram_tuple {
    char *name;
    char *value;
    struct wlcsm_nvram_tuple *next,*prev;
    short vlen;
    char referred;
};

static struct wlcsm_nvram_tuple * wlcsm_local_nvram_hash[32] = { NULL }; /**< hashtable for local nvram cache  */
static struct wlcsm_nvram_tuple * wlcsm_local_nvram_deadlist= NULL; /**< tuples with exported value pointers */

/*Differennt Nvram variable has different value length. To keep the Hash table static and sequence,
when one nvrma variable is inserted into hash table, the location will not dynamic change.
This structure is used to keep nvram name and value length*/
/* When new nvram variable is defined and max length is more than WL_DEFAULT_VALUE_SIZE_MAX,
the name and max length should be added into var_len_tab*/

struct   nvram_var_len_table {
    char *name;
    unsigned int  max_len;
};

/*nvram variable vs max length table*/
struct nvram_var_len_table var_len_tab[] = {
    {"wsc_ssid",     WL_SSID_SIZE_MAX+1},
    {"wsc_uuid",    WL_UUID_SIZE_MAX+1},
    {"wps_ssid",     WL_SSID_SIZE_MAX+1},
    {"wps_uuid",    WL_UUID_SIZE_MAX+1},
    {"radius_key",  WL_DEFAULT_VALUE_SIZE_MAX * 3},
    {"wpa_psk",    WL_WPA_PSK_SIZE_MAX+1},
    {"key1",          WL_MID_SIZE_MAX+1 },
    {"key2",          WL_MID_SIZE_MAX+1 },
    {"key3",          WL_MID_SIZE_MAX+1 },
    {"key4",          WL_MID_SIZE_MAX+1 },
    {"wds",            WL_WDS_SIZE_MAX },
    {"maclist",        WL_SINGLEMAC_SIZE * WL_MACFLT_NUM },
    {"lan_ifnames",  WL_DEFAULT_VALUE_SIZE_MAX * 3},
    {"lan1_ifnames",  WL_DEFAULT_VALUE_SIZE_MAX * 3},
    {"lan2_ifnames",  WL_DEFAULT_VALUE_SIZE_MAX * 3},
    {"lan3_ifnames",  WL_DEFAULT_VALUE_SIZE_MAX * 3},
    {"lan4_ifnames",  WL_DEFAULT_VALUE_SIZE_MAX * 3},
    {"br0_ifnames",  WL_DEFAULT_VALUE_SIZE_MAX * 3},
    {"br1_ifnames",  WL_DEFAULT_VALUE_SIZE_MAX * 3},
    {"br2_ifnames",  WL_DEFAULT_VALUE_SIZE_MAX * 3},
    {"br3_ifnames",  WL_DEFAULT_VALUE_SIZE_MAX * 3},
    {"wldbg",           1024 },
    {"netauthlist",     128 },
    {"oplist",          128 },
    {"osu_frndname",    51 },
    {"osu_icons",       36 },
    {"osu_uri",         128 },
    {"realmlist",       128 },
    {"venuelist",       320 },
    {"3gpplist",       	128},
    {"osu_servdesc",   	128},
    {"concaplist",   	128},
    {"qosmapie",   	80},
    {"radarthrs",   	128},
    {"toa-sta-1",    WL_DEFAULT_VALUE_SIZE_MAX * 2},
    {"toa-sta-2",    WL_DEFAULT_VALUE_SIZE_MAX * 2},
    {"toa-sta-3",    WL_DEFAULT_VALUE_SIZE_MAX * 2},
    {"toa-sta-4",    WL_DEFAULT_VALUE_SIZE_MAX * 2},
#ifdef BCA_HNDROUTER
    /* pa nvram parameters */
    {"pa5ga0",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5ga1",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5ga2",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5ga3",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5g40a0",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5g40a1",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5g40a2",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5g40a3",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5g80a0",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5g80a1",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5g80a2",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"pa5g80a3",    WL_DEFAULT_VALUE_SIZE_MAX * 4},
    {"vifs",    WL_DEFAULT_VALUE_SIZE_MAX * 2},
#endif /* BCA_HNDROUTER */
};

#define VAR_LEN_COUNT (sizeof(var_len_tab) /sizeof(struct nvram_var_len_table))



static char *wl_prefix_check(char *name)
{
    char *prefix = g_temp_buf;
    int buf_size = sizeof(g_temp_buf);
    int i, j;

    /* check for wl_ */
    snprintf(prefix, buf_size, "wl_");
    if (!strncmp(name, prefix, strlen(prefix)))
        goto found;

    for (i = 0; i < WL_MAX_NUM_RADIO; i++) {
        /* check wl prefix for devpath%d */
        snprintf(prefix, buf_size, "%d:", i);
        if (!strncmp(name, prefix, strlen(prefix)))
            goto found;

        /* check for wlX_*/
        snprintf(prefix, buf_size, "wl%d_", i);
        if (!strncmp(name, prefix, strlen(prefix)))
            goto found;

        for (j = 0; j < WL_MAX_NUM_SSID; j++) {
            /* check for wlX.Y_*/
            snprintf(prefix, buf_size, "wl%d.%d_", i, j);
            if (!strncmp(name, prefix, strlen(prefix)))
                goto found;
        }
    }

    /* not found */
    prefix[0] = '\0';

found:

    return prefix;
}

/*Check nvram variable and return itsmax  value length*/
static int var_maxlen(char *name,uint32 len)
{
    int idx =0;
    char short_name[64];
    char *prefix;
    int ret_len= WL_DEFAULT_VALUE_SIZE_MAX ;
    WLCSM_TRACE(WLCSM_TRACE_NVRAM,"Check_var name=[%s]\n", name );
    memset(short_name, 0, sizeof(short_name));

    if(len>WL_NVRAM_VALUE_MAX_LEN) {
        fprintf(stderr, "nvram%s value length is  bigger than allowed \
				max length:%d\r\n",name, WL_NVRAM_VALUE_MAX_LEN);
        return -1;
    }

    prefix = wl_prefix_check(name);
    if (prefix[0] != '\0')
        strcpy(short_name, name + strlen(prefix));
    else
        strcpy(short_name, name);
    for ( idx=0; idx < VAR_LEN_COUNT && var_len_tab[idx].name[0] !='\0'; idx++ ) {
        if ( !strcmp( var_len_tab[idx].name, short_name) ) {
            WLCSM_TRACE(WLCSM_TRACE_NVRAM, "[%s] Max Len [%d]\n", name, var_len_tab[idx].max_len );
            ret_len = var_len_tab[idx].max_len;
        }
    }
    if(len>ret_len) {
        /* giving the exceptional string extra room */
        ret_len=len+WL_DEFAULT_VALUE_SIZE_MAX;
        if(ret_len>WL_NVRAM_VALUE_MAX_LEN)
            ret_len=WL_NVRAM_VALUE_MAX_LEN;
    }
    return ret_len;
}

static inline unsigned int _hash(char *s)
{
    unsigned int hash = 0;
    while (*s) {
        hash = 31 * hash + *s++;
    }
    return hash% ARRAYSIZE(wlcsm_local_nvram_hash);
}

static inline struct wlcsm_nvram_tuple *_find_local_nvram( char *name  )
{
    int i=_hash(name);
    struct wlcsm_nvram_tuple *tuple=wlcsm_local_nvram_hash[i];
    while(tuple) {
        if(tuple->name && !strcmp(tuple->name,name))
            return tuple;
        tuple=tuple->next;
    }
    return NULL;
}

static inline void _nvram_remove_tuple_(struct wlcsm_nvram_tuple *tuple,int index) {
    /*remove the tuple from the link list */
    if(tuple == wlcsm_local_nvram_hash[index])
        /* if the tuple is at head */
        wlcsm_local_nvram_hash[index]= tuple->next;
    else {
        if(tuple->next)
            tuple->next->prev=tuple->prev;
        if(tuple->prev)
            tuple->prev->next=tuple->next;
    }
    free(tuple);
}

static inline void _nvram_local_unset(struct wlcsm_nvram_tuple *tuple)
{
    if( ! tuple->referred && ! _LOCAL_SYNC_ENABLED_  ) {
        /*if this nvram is not referred,it can be freed*/
        _nvram_remove_tuple_(tuple,_hash(tuple->name));
    } else {
        /*limitation is whichever refer to this will get a zero length
         * string instead of real NULL */
        if(tuple->value) {
            tuple->value[0]='\0';
            tuple->value=NULL;
        }
    }
}

static struct wlcsm_nvram_tuple *_nvram_local_new(char *name, char *value)
{
    int len,vlen,nlen;
    struct wlcsm_nvram_tuple *t;
    int index=_hash(name);
    /* when coming into here, value will not be NULL
     * var_max will return the max allowed value if
     * value is short or strlen if the value is longer than
     * its maximum, no limit since it is new */
    vlen=var_maxlen(name,strlen(value)+1);
    if(vlen<0) return NULL;
    nlen=strlen(name)+1;
    len =  nlen + vlen;
    if (!(t = _MALLOC_(sizeof(struct wlcsm_nvram_tuple) +len ))) {
        fprintf(stderr,"---:%s:%d  Relocated failed name:%s,value:%s\r\n",\
                __FUNCTION__,__LINE__,name,value );
        return NULL;
    }
    memset( &t[1], 0, len );
    t->name = (char *) &t[1];
    strncpy(t->name, name,nlen);
    t->value = t->name + nlen;
    strncpy(t->value, value,strlen(value));
    t->vlen=vlen;
    t->referred=0;
    /* put it into list */
    if(!wlcsm_local_nvram_hash[index])
    {
        t->next=t->prev=NULL;
    } else {
        wlcsm_local_nvram_hash[index]->prev=t;
        t->next=wlcsm_local_nvram_hash[index];
    }
    wlcsm_local_nvram_hash[index]=t;
    return t;
}


static inline void  _nvram_change_notifciation(char *name, char *value,char *tuplevalue)
{

    if(g_WLCSM_EVENT_GENERIC_HOOK||g_WLCSM_EVENT_HOOKS[WLCSM_EVT_NVRAM_CHANGED]) {

        WLCSM_TRACE(WLCSM_TRACE_NVRAM,"----:%s:%d  notify the other process about nvram change \r\n",__FUNCTION__,__LINE__ );

        if(g_WLCSM_EVENT_GENERIC_HOOK)
            g_WLCSM_EVENT_GENERIC_HOOK(WLCSM_EVT_NVRAM_CHANGED,name,value,tuplevalue);

        if(g_WLCSM_EVENT_HOOKS[WLCSM_EVT_NVRAM_CHANGED])
            g_WLCSM_EVENT_HOOKS[WLCSM_EVT_NVRAM_CHANGED](name,value,tuplevalue);

    }
}

static int _nvram_local_update(struct wlcsm_nvram_tuple *tuple,char *name, char *value)
{
    int vlen;
    if(!value) {
        _nvram_local_unset(tuple);
        return WLCSM_SUCCESS;
    }
    vlen=strlen(value)+1;
    if(!tuple->value)
        tuple->value=tuple->name+strlen(tuple->name)+1;
    if(vlen<=tuple->vlen) {
        strncpy(tuple->value,value,strlen(value)+1);
        return WLCSM_SUCCESS;
    } else {
        /* if incoming var length is bigger than available memeory and was referred */
        if(tuple->referred) {
            fprintf(stderr,"nvram/value pair: %s='%s'is bigger than its max length\r\n",name,value);
            /* put it into dead list */
            if(!wlcsm_local_nvram_deadlist)
            {
                tuple->next=tuple->prev=NULL;
            } else {
                wlcsm_local_nvram_deadlist->prev=tuple;
                tuple->next=wlcsm_local_nvram_deadlist;
            }
            wlcsm_local_nvram_deadlist = tuple;
        } else {
            _nvram_local_unset(tuple);
        }
        if( _nvram_local_new(name,value))
            return WLCSM_SUCCESS;
    }
    return WLCSM_GEN_ERR;
}



int wlcsm_nvram_commit (void)
{

    int ret=WLCSM_GEN_ERR;
#if defined(NAND_SYS) && !defined(BRCM_CMS_BUILD)
    char  *name,*buf;
    FILE *fp;
	int fd;
    buf=malloc(MAX_NVRAM_SPACE);
    if(!buf) {
        fprintf(stderr,"Could not allocate memory\n");
        return WLCSM_GEN_ERR;
    }
    wlcsm_nvram_getall(buf,MAX_NVRAM_SPACE);
    fp=fopen(KERNEL_NVRAM_FILE_NAME,"w+");
    if(!fp) {
        fprintf(stderr,"%s:%d could not open nvram file  \r\n",__FUNCTION__,__LINE__ );
        free(buf);
        return WLCSM_GEN_ERR;
    }
    for (name = buf; *name; name += strlen(name) + 1) {
        fputs(name,fp);
        fputc('\n',fp);
    }
    if((fd=fileno(fp)) > 0){
        fsync(fd);
    }
    fclose(fp);
    free(buf);
#endif
    if(wlcsm_netlink_send_mesg(WLCSM_MSG_NVRAM_COMMIT,NULL,0)== WLCSM_SUCCESS) {
        t_WLCSM_MSG_HDR *hdr=wlcsm_unicast_recv_mesg(g_temp_buf);
        if(hdr!=NULL && hdr->type==WLCSM_MSG_NVRAM_COMMIT) ret=WLCSM_SUCCESS;

    }
    return ret;
}

int wlcsm_nvram_unset (char *name)
{
    int buflen=_get_valuepair_total_len(name,NULL,0);
    t_WLCSM_NAME_VALUEPAIR *buf;
    struct wlcsm_nvram_tuple *tuple;
    _NVRAM_LOCK();
    tuple=_find_local_nvram(name);
    if(tuple)
        _nvram_local_unset(tuple);
    buf=wlcsm_get_namevalue_buf(name,NULL,0);
    if(buf!=NULL) {
        if(wlcsm_netlink_send_mesg(WLCSM_MSG_NVRAM_UNSET,(char *)buf,buflen)== WLCSM_SUCCESS) {
            t_WLCSM_MSG_HDR *hdr=wlcsm_unicast_recv_mesg(g_temp_buf);
            if(hdr!=NULL && hdr->type==WLCSM_MSG_NVRAM_UNSET) {
                WLCSM_TRACE(WLCSM_TRACE_NVRAM, "nvram unset successful\n");
                free(buf);
                _NVRAM_UNLOCK();
                return WLCSM_SUCCESS;
            }
        }
        free(buf);
    }
    _NVRAM_UNLOCK();
    return WLCSM_GEN_ERR;
}


void wlcsm_register_event_hook(t_WLCSM_EVENT_TYPE type,WLCSM_EVENT_HOOK_FUNC hook)
{
    _wlcsm_init(m_AS_DAEMON);
    g_WLCSM_EVENT_HOOKS[type]=hook;
}


void wlcsm_register_event_generic_hook(WLCSM_EVENT_HOOK_GENERICFUNC hook)
{
    _wlcsm_init(m_AS_DAEMON);
    g_WLCSM_EVENT_GENERIC_HOOK=hook;
}


void wlcsm_nvram_commit_update()
{
    if(g_WLCSM_EVENT_GENERIC_HOOK)
        g_WLCSM_EVENT_GENERIC_HOOK(WLCSM_EVT_NVRAM_COMMITTED);
    if(g_WLCSM_EVENT_HOOKS[WLCSM_EVT_NVRAM_COMMITTED])
        g_WLCSM_EVENT_HOOKS[WLCSM_EVT_NVRAM_COMMITTED](NULL,NULL,NULL);
}

int wlcsm_nvram_local_update(char *name, char *value)
{
    int ret=WLCSM_SUCCESS;
    struct wlcsm_nvram_tuple *tuple=NULL;
    _NVRAM_LOCK();
    tuple=_find_local_nvram(name);
    WLCSM_TRACE(WLCSM_TRACE_DBG,"name:%s,value:%s\r\n",name ,value?value:"NULL");

    if(tuple) {

        WLCSM_TRACE(WLCSM_TRACE_NVRAM," found local tuple:name:%s,value:%s,invalue:%s \r\n",tuple->name, tuple->value?tuple->value:"NULL" ,value?value:"NULL");
        if(_STR_VALUE_EQUAL(value,tuple->value)) {
            _NVRAM_UNLOCK();
            return ret;
        } else {
            int len=0;
            char *tuplevalue=NULL;
            if(tuple->value) {
                len=strlen(tuple->value)+1;
                tuplevalue=(char *)_MALLOC_(len);
                strcpy(tuplevalue,tuple->value);
            }
            ret=_nvram_local_update(tuple,name,value);
            _NVRAM_UNLOCK();
            if(ret==WLCSM_SUCCESS)
                _nvram_change_notifciation(name,value,tuplevalue);
            if(tuplevalue)
                _MFREE_(tuplevalue);
        }
    } else
        _NVRAM_UNLOCK();
    return ret;
}


#ifdef WLCSM_DEBUG
int  wlcsm_nvram_set_dbg(char *name,char *value,const char *func,int line)
#else
int wlcsm_nvram_set(char *name, char*value)
#endif
{
    struct wlcsm_nvram_tuple *tuple=NULL;
    int buflen;
    t_WLCSM_NAME_VALUEPAIR *buf;
    /* nvram set NULL is the same as unset */
    if(!value) return wlcsm_nvram_unset(name);
#ifdef WLCSM_DEBUG
    {
        char *tobe_debug_nvram=NULL;
        tobe_debug_nvram=wlcsm_nvram_get("nvram_debug");
        if(tobe_debug_nvram && strstr(name,tobe_debug_nvram))
            printf("###%s:%d set %s with %s\r\n",func,line,name,value);
        tobe_debug_nvram=wlcsm_nvram_get("nvram_pid");
        if(tobe_debug_nvram && atoi(tobe_debug_nvram)==getpid())
            fprintf(stderr, "#%d: %s=%s	\n",getpid(),name,value);
    }
#endif
    WLCSM_TRACE(WLCSM_TRACE_DBG, "set:%s=%s\n\n",name,value);
    _NVRAM_LOCK();
    tuple=_find_local_nvram(name);
    if(tuple) {
        WLCSM_TRACE(WLCSM_TRACE_NVRAM," found local tuple:name:%s,value:%s,invalue:%s \r\n",tuple->name, tuple->value?tuple->value:"NULL",value);
        if(_STR_VALUE_EQUAL(value,tuple->value)) {
            if(g_WLCSM_IS_DAEMON==m_AS_DAEMON) {
                _NVRAM_UNLOCK();
                return WLCSM_SUCCESS;
            }
        } else if(_nvram_local_update(tuple,name,value)==WLCSM_GEN_ERR) {
            _NVRAM_UNLOCK();
            return WLCSM_GEN_ERR;
        }
    } else if(_nvram_local_new(name,value)==NULL) {
        _NVRAM_UNLOCK();
        return WLCSM_GEN_ERR;
    }

    buflen=_get_valuepair_total_len(name,value,0);
    buf=wlcsm_get_namevalue_buf(name,value,0);
    if(buf!=NULL) {
        if(wlcsm_netlink_send_mesg(WLCSM_MSG_NVRAM_SET,(char *)buf,buflen)== WLCSM_SUCCESS) {
            t_WLCSM_MSG_HDR *hdr=wlcsm_unicast_recv_mesg(g_temp_buf);
            if(hdr!=NULL && hdr->type==WLCSM_MSG_NVRAM_SET) {
                WLCSM_TRACE(WLCSM_TRACE_NVRAM, "nvram set successful\n");
                free(buf);
                _NVRAM_UNLOCK();
                return WLCSM_SUCCESS;
            }
        }
        free(buf);
    }
    _NVRAM_UNLOCK();
    WLCSM_TRACE(WLCSM_TRACE_NVRAM, "nvram set failed\n");
    return WLCSM_GEN_ERR;
}



char *wlcsm_nvram_get (char *name )
{
    struct wlcsm_nvram_tuple *tuple=NULL;
    char *value=NULL;
    _NVRAM_LOCK();
    tuple=_find_local_nvram(name);
    /* when there is no update daemon or not find in local, go to kernel for the value */

    if((g_WLCSM_IS_DAEMON==m_NOTAS_DAEMON || tuple==NULL) &&
            (wlcsm_netlink_send_mesg(WLCSM_MSG_NVRAM_GET,(char *)name,strlen(name)+1)== WLCSM_SUCCESS)) {

        t_WLCSM_MSG_HDR *hdr=wlcsm_unicast_recv_mesg(g_temp_buf);

        if(hdr!=NULL && hdr->type==WLCSM_MSG_NVRAM_GET ) {

            if(hdr->len) value= VALUEPAIR_VALUE((t_WLCSM_NAME_VALUEPAIR *)(hdr+1));
            if(tuple)
                _nvram_local_update(tuple,name,value);
            else if(value)
                tuple=_nvram_local_new(name,value);
        }
    }
    if(tuple) tuple->referred=1;
    _NVRAM_UNLOCK();
    if(tuple) return tuple->value;
    else return NULL;
}



int wlcsm_nvram_getall(char *buf, int count)
{
    int ret=WLCSM_GEN_ERR;
    t_WLCSM_MSG_HDR *hdr;
    char lenstr[8];
    int len=0;

    memset(buf,'\0',count);
    sprintf(lenstr,"%d",count);
    _NVRAM_LOCK();
    if(wlcsm_netlink_send_mesg(WLCSM_MSG_NVRAM_GETALL,lenstr,strlen(lenstr)+1)== WLCSM_SUCCESS) {
        while(1) {

            hdr=wlcsm_unicast_recv_mesg(g_temp_buf);

            if(!hdr || hdr->len==0) {
                WLCSM_TRACE(WLCSM_TRACE_NVRAM,"----:%s:%d Did not recevie anything?????  \r\n",__FUNCTION__,__LINE__ );
                break;

            }

            if((hdr->type==WLCSM_MSG_NVRAM_GETALL)||hdr->type==WLCSM_MSG_NVRAM_GETALL_DONE) {

                if((count-len)>hdr->len) {
                    memcpy(buf,(char *)(hdr+1),hdr->len);
                    buf+=hdr->len;

                } else  {
                    ret=WLCSM_SUCCESS;
                    break;
                }

                if(hdr->type==WLCSM_MSG_NVRAM_GETALL_DONE) {
                    ret=WLCSM_SUCCESS;
                    break;
                }
            }
        }
    }
    _NVRAM_UNLOCK();
    return ret;
}
void wlcsm_nvram_release_all(void)
{
    uint i;
    struct wlcsm_nvram_tuple *t, *next;
    /* Free hash table */
    _NVRAM_LOCK();
    for (i = 0; i < ARRAYSIZE(wlcsm_local_nvram_hash); i++) {
        for (t = wlcsm_local_nvram_hash[i]; t; t = next) {
            next = t->next;
            free(t);
        }
        wlcsm_local_nvram_hash[i] = NULL;
    }
    for(t=wlcsm_local_nvram_deadlist; t; t=next) {
        next=t->next;
        free(t);
    }
    _NVRAM_UNLOCK();
}

char *wlcsm_prefix_match(char *name)
{
    char *prefix;

    prefix = wl_prefix_check(name);
    if (prefix[0] != '\0')
        return prefix;
    else
        return NULL;
}

char *wlcsm_trim_str(char *value)
{
    char *in_str=value;
    if(!in_str ||strlen(in_str)==0) return in_str;
    else {
        int len=strlen(in_str);
        len--;
        while(len>=0 &&
                (in_str[len]==' '||
                 in_str[len]=='"' ||
                 in_str[len]=='\n'))
            len--;
        in_str[len+1]='\0';
        /*  trim leading space or "*/
        while(*in_str==' '|| *in_str=='"') in_str++;
        return in_str;
    }
}

char *wlcsm_nvram_name_parser(char *name,unsigned int *idx, unsigned int *ssid_idx)
{

    if(name) {
        char *nvram_name=strstr(name,"_");
        if(nvram_name) {
            int ret=sscanf(name,"wl%d.%d",idx,ssid_idx);
            if(ret) {
                if(ret==1) *ssid_idx=0;
                return (char *)(nvram_name+1);
            }
        }
    }
    *idx=0;
    *ssid_idx=0;
    return NULL;
}

#define VALIDATE_BIT(bit) do { if ((bit < 0) || (bit > 31)) return NULL; } while (0)
#define VALIDATE_BIT_INT(bit) do { if ((bit < 0) || (bit > 31)) return 0; } while (0)
#define CODE_BUFF	16
#define HEX_BASE	16

char * wlcsm_nvram_get_bitflag(char *name, int bit)
{
    VALIDATE_BIT(bit);
    char *ptr = wlcsm_nvram_get(name);
    unsigned long nvramvalue = 0;
    unsigned long bitflagvalue = 1;

    if (ptr) {
        bitflagvalue = bitflagvalue << bit;
        nvramvalue = strtoul(ptr, NULL, HEX_BASE);
        if (nvramvalue) {
            nvramvalue = nvramvalue & bitflagvalue;
        }
    }
    return ptr ? (nvramvalue ? "1" : "0") : NULL;
}

int wlcsm_nvram_set_bitflag(char *name, int bit, int value)
{
    VALIDATE_BIT_INT(bit);
    char nvram_val[CODE_BUFF];
    char *ptr = wlcsm_nvram_get(name);
    unsigned long nvramvalue = 0;
    unsigned long bitflagvalue = 1;

    memset(nvram_val, 0, sizeof(nvram_val));

    if (ptr) {
        bitflagvalue = bitflagvalue << bit;
        nvramvalue = strtoul(ptr, NULL, HEX_BASE);
        if (value) {
            nvramvalue |= bitflagvalue;
        } else {
            nvramvalue &= (~bitflagvalue);
        }
    }
    snprintf(nvram_val, sizeof(nvram_val)-1, "%lx", nvramvalue);
    return wlcsm_nvram_set(name, nvram_val);
}

#ifdef WLCSM_DEBUG
void wlcsm_set_trace (char *procname)
{
    char buf[32], *tracelvl;
    snprintf (buf, 32, "%s_trace", procname);
    tracelvl = wlcsm_nvram_get (buf);
    snprintf (g_WLCSM_TRACE_PROC, 32, "%s", procname);
    if (tracelvl) {
        sscanf (tracelvl, "%d", &g_WLCSM_TRACE_LEVEL);
        return;
    } else {
        g_WLCSM_TRACE_LEVEL = 0;
    }
}

void wlcsm_print(const char *fmt, ...)
{
    char msg[MAX_NLRCV_BUF_SIZE]= {'\0'};
    char recv_hdr[sizeof(t_WLCSM_MSG_HDR)+4];
    va_list args;
    int n=0;
    va_start(args,fmt);
    n=vsnprintf(msg,MAX_NLRCV_BUF_SIZE,fmt,args);
    va_end(args);
    if(n>0 && n<MAX_NLRCV_BUF_SIZE && wlcsm_netlink_send_mesg(WLCSM_MSG_DEBUG_LOGMESSAGE,msg,n+1)== WLCSM_SUCCESS) {
        t_WLCSM_MSG_HDR *hdr=wlcsm_unicast_recv_mesg(recv_hdr);
        if(hdr && hdr->type==WLCSM_MSG_DEBUG_LOGMESSAGE && (hdr->len>1))
            return;
        else
            fprintf(stderr,msg);
    }
}

/* default for userspace, otherwize put k ahead, example
 * k+err
 * k-err
 * kclr
 * no+- is to set */
int wlcsm_set_trace_level(char *tl)
{
    char setuser=0;
    char addaction=0;
    if(tl[0]=='+'||tl[0]=='-'||tl[0]=='u') setuser=1;
    if(tl[0]=='u'||tl[0]=='k') tl++;
    if(tl[0]=='+') {
        addaction=2;
        tl++;
    } else if(tl[0]=='-') {
        addaction=1;
        tl++;
    }
    unsigned int i=0;
    unsigned int tracelevel=0;
    for(; i<sizeof(trace_matches)/sizeof(t_WLCSM_TRACE_MATCH); i++) {

        if (!strcmp(trace_matches[i].name,tl)) {
            tracelevel= trace_matches[i].level;
            break;
        }
    }
    if(setuser) {
        if(addaction==2)  g_WLCSM_TRACE_LEVEL|=tracelevel;
        else if(addaction==1)
            g_WLCSM_TRACE_LEVEL &= (~tracelevel);
        else
            g_WLCSM_TRACE_LEVEL=tracelevel;
    } else {
        tracelevel|= (addaction<<30);
        if(wlcsm_netlink_send_mesg(WLCSM_MSG_NVRAM_SETTRACE,(char *)&tracelevel,sizeof(unsigned int))== WLCSM_SUCCESS) {
            t_WLCSM_MSG_HDR *hdr=wlcsm_unicast_recv_mesg(g_temp_buf);
            if(hdr!=NULL && hdr->type==WLCSM_MSG_NVRAM_SETTRACE)
                WLCSM_TRACE(WLCSM_TRACE_NVRAM, "trace set successful\n");
            return 0;
        }
    }
    return -1;
}

/*simple API to evaluate elapsed time beteen instructions */
struct timeval g_TIME_START= {0},g_TIME_CUR= {0},g_TIME_PRE= {0};

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

void wlcsm_restart_time(char *func,int line) {
    gettimeofday(&g_TIME_START,NULL);
    wlcsm_print("%s#%d,reset time\n",func,line);
    g_TIME_PRE.tv_sec=g_TIME_START.tv_sec;
    g_TIME_PRE.tv_usec=g_TIME_START.tv_usec;
}


void wlcsm_delta_time(char *func,int line,char *prompt) {
    struct timeval delta;
    gettimeofday(&g_TIME_CUR,NULL);
    timeval_subtract(&delta,&g_TIME_CUR,&g_TIME_PRE);
    g_TIME_PRE.tv_sec=g_TIME_CUR.tv_sec;
    g_TIME_PRE.tv_usec=g_TIME_CUR.tv_usec;
    if(prompt)
        wlcsm_print("%s:%d: %s: delta:	%lu#%08lu(s#us)\n",func,line,
                    prompt,
                    delta.tv_sec,
                    delta.tv_usec);
}

void wlcsm_total_time(char *func,int line) {
    struct timeval delta;
    gettimeofday(&g_TIME_CUR,NULL);
    timeval_subtract(&delta,&g_TIME_CUR,&g_TIME_START);
    wlcsm_print( "%s:%d:total:	%lu#%08lu(s#us)\n",func,line,
                 delta.tv_sec,
                 delta.tv_usec);
    g_TIME_PRE.tv_sec=g_TIME_CUR.tv_sec;
    g_TIME_PRE.tv_usec=g_TIME_CUR.tv_usec;
}

#endif
