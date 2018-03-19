/***********************************************************************
 *
 *  Copyright (c) 2010  Broadcom Corporation
 *  All Rights Reserved
 *
<:label-BRCM:2012:proprietary:standard

 This program is the proprietary software of Broadcom and/or its
 licensors, and may only be used, duplicated, modified or distributed pursuant
 to the terms and conditions of a separate, written license agreement executed
 between you and Broadcom (an "Authorized License").  Except as set forth in
 an Authorized License, Broadcom grants no license (express or implied), right
 to use, or waiver of any kind with respect to the Software, and Broadcom
 expressly reserves all rights in and to the Software and all intellectual
 property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE
 NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY
 BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.

 Except as expressly set forth in the Authorized License,

 1. This program, including its structure, sequence and organization,
    constitutes the valuable trade secrets of Broadcom, and you shall use
    all reasonable efforts to protect the confidentiality thereof, and to
    use this information only in connection with your use of Broadcom
    integrated circuit products.

 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
    AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
    WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
    RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND
    ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT,
    FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
    COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE
    TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE OR
    PERFORMANCE OF THE SOFTWARE.

 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR
    ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
    INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY
    WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN
    IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES;
    OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE
    SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS
    SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY
    LIMITED REMEDY.
:>
 *
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <ctype.h>
#include <linux/if_ether.h>
#include <net/if.h>
#include <net/route.h>
#include <fcntl.h>
#include <unistd.h>

#include "bcmnet.h"
#include "cms_core.h"
#include "cms_util.h"
#include "cms_eid.h"
#include "cms_qos.h"
#include "cms_dal.h"
#include "cms_boardcmds.h"
#include "rcl.h"
#include "odl.h"
#include "rut_util.h"
#include "rut_qos.h"
#include "rut_atm.h"
#include "rut_dsl.h"
#include "rut_wan.h"
#include "rut_wanlayer2.h"
#include "rut_xtmlinkcfg.h"
#include "devctl_xtm.h"
#include "skb_defines.h"

#ifdef SUPPORT_QOS

#ifdef SUPPORT_POLICING

typedef enum
{
   CONFORM        = 1,
   PARTIALCONFORM = 2,
   NONCONFORM     = 3

} PolicerConformType;

/** Local functions **/
static void policerClassCommand(QosCommandType cmdType, UINT32 flowid, const char *action);
static void policerFilterCommand(QosCommandType cmdType, UINT32 prio, UINT32 handle,
                                 char *policeStr, UINT32 flowid);
static CmsRet policerAddQdisc(const char *ifname, UINT32 handle);
static CmsRet policerDelQdisc(const char *ifname, UINT32 handle, UINT32 clsKey);


/***************************************************************************
// Function Name: rutQos_policer
// Description  : execute tc commands to add or remove rate limit for a traffic class.
// Parameters   : clsObj - QoS class information.
//                pObj - QoS policer information.
//                queueIfname - egress queue layer 2 interface name.
//                cmdType - command type either config or unconfig.
// Returns      : CmsRet.
****************************************************************************/
CmsRet rutQos_policer(QosCommandType cmdType,
                      const char *queueIfname,
                      UINT32 clsKey,
                      const CmsQosPolicerInfo *pInfo)
{
   char cmd[BUFLEN_1024]={0};
   char policeStr[BUFLEN_64]={0};
   UINT32 clsKeyMark = 0;
   UINT32 tcFlowId;
   CmsRet ret = CMSRET_SUCCESS;

   cmsLog_debug("Entered: cmd=%d queueIfname=%s clsKey=%d policer->meterType=%s",
                cmdType, queueIfname, clsKey, pInfo->meterType);

   if (!pInfo->enable)
   {
      cmsLog_debug("class policer is not enabled. No action is taken.");
      return CMSRET_SUCCESS;
   }

   clsKeyMark = SKBMARK_SET_FLOW_ID(clsKeyMark, clsKey); 

   /* Note that clsKey is always greater than 0. It starts from 1. */
   tcFlowId = (clsKey - 1) * 3;

   rut_doSystemAction("rutQos_policer", "ifconfig ifb0 up 2>/dev/null");

   if (cmdType == QOS_COMMAND_CONFIG)
   {
      sprintf(cmd, "tc qdisc add dev ifb0 root handle 10: dsmark indices %d 2>/dev/null",
              QOS_DSMARK_QDISC_INDICES);
      rut_doSystemAction("rutQos_policer", cmd);

      /* add conforming class */
      policerClassCommand(cmdType, tcFlowId+CONFORM, pInfo->conformingAction);

      if (cmsUtl_strcmp(MDMVS_SIMPLETOKENBUCKET, pInfo->meterType) == 0)
      {
         /* add nonconforming class */
         policerClassCommand(cmdType, tcFlowId+NONCONFORM, pInfo->nonConformingAction);

         if (cmsUtl_strcmp(MDMVS_DROP, pInfo->nonConformingAction) == 0)
         {
            /* add conforming filter and policer to drop if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 drop",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);
         }
         else
         {
            /* add conforming filter and policer to continue if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 continue",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);

            /* add nonconforming filter */               
            policeStr[0] = '\0';
            policerFilterCommand(cmdType, NONCONFORM, clsKeyMark, policeStr, tcFlowId+NONCONFORM);
         }
      }
      else if (cmsUtl_strcmp(MDMVS_SINGLERATETHREECOLOR, pInfo->meterType) == 0)
      {
         /* add partialconforming class */
         policerClassCommand(cmdType, tcFlowId+PARTIALCONFORM, pInfo->partialConformingAction);

         if (cmsUtl_strcmp(MDMVS_DROP, pInfo->partialConformingAction) == 0)
         {
            /* add conforming filter and policer to drop if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 drop",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);
         }
         else
         {
            /* add conforming filter and policer to continue if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 continue",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);
            
            /* add nonconforming class */
            policerClassCommand(cmdType, tcFlowId+NONCONFORM, pInfo->nonConformingAction);

            if (cmsUtl_strcmp(MDMVS_DROP, pInfo->nonConformingAction) == 0)
            {
               /* add partialconforming filter and policer to drop if overlimit */
               sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 drop",
                       pInfo->committedRate/1000, pInfo->excessBurstSize);
               policerFilterCommand(cmdType, PARTIALCONFORM, clsKeyMark, policeStr, tcFlowId+PARTIALCONFORM);
            }
            else
            {
               /* add partialconforming filter and policer to continue if overlimit */
               sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 continue",
                       pInfo->committedRate/1000, pInfo->excessBurstSize);
               policerFilterCommand(cmdType, PARTIALCONFORM, clsKeyMark, policeStr, tcFlowId+PARTIALCONFORM);

               /* add nonconforming filter */               
               policeStr[0] = '\0';
               policerFilterCommand(cmdType, NONCONFORM, clsKeyMark, policeStr, tcFlowId+NONCONFORM);
            }
         }
      }
      else  /* MDMVS_TWORATETHREECOLOR */
      {
         /* add partialconforming class */
         policerClassCommand(cmdType, tcFlowId+PARTIALCONFORM, pInfo->partialConformingAction);

         if (cmsUtl_strcmp(MDMVS_DROP, pInfo->partialConformingAction) == 0)
         {
            /* add conforming filter and policer to drop if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 drop",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);
         }
         else
         {
            /* add conforming filter and policer to continue if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 continue",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);
            
            /* add nonconforming class */
            policerClassCommand(cmdType, tcFlowId+NONCONFORM, pInfo->nonConformingAction);

            if (cmsUtl_strcmp(MDMVS_DROP, pInfo->nonConformingAction) == 0)
            {
               /* add partialconforming filter and policer to drop if overlimit */
               sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 drop",
                       (pInfo->peakRate - pInfo->committedRate)/1000, pInfo->peakBurstSize);
               policerFilterCommand(cmdType, PARTIALCONFORM, clsKeyMark, policeStr, tcFlowId+PARTIALCONFORM);
            }
            else
            {
               /* add partialconforming filter and policer to continue if overlimit */
               sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 continue",
                       (pInfo->peakRate - pInfo->committedRate)/1000, pInfo->peakBurstSize);
               policerFilterCommand(cmdType, PARTIALCONFORM, clsKeyMark, policeStr, tcFlowId+PARTIALCONFORM);

               /* add nonconforming filter */               
               policeStr[0] = '\0';
               policerFilterCommand(cmdType, NONCONFORM, clsKeyMark, policeStr, tcFlowId+NONCONFORM);
            }
         }
      }

      /* add qdisc to interface */
      policerAddQdisc(queueIfname, clsKeyMark);
   }
   else
   {
      if (cmsUtl_strcmp(MDMVS_SIMPLETOKENBUCKET, pInfo->meterType) == 0)
      {
         if (cmsUtl_strcmp(MDMVS_DROP, pInfo->nonConformingAction) == 0)
         {
            /* delete conforming filter and policer to drop if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 drop",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);
         }
         else
         {
            /* delete conforming filter and policer to continue if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 continue",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);

            /* delete nonconforming filter */               
            policeStr[0] = '\0';
            policerFilterCommand(cmdType, NONCONFORM, clsKeyMark, policeStr, tcFlowId+NONCONFORM);
         }
         /* delete nonconforming class */
         policerClassCommand(cmdType, tcFlowId+NONCONFORM, pInfo->nonConformingAction);
      }
      else if (cmsUtl_strcmp(MDMVS_SINGLERATETHREECOLOR, pInfo->meterType) == 0)
      {
         if (cmsUtl_strcmp(MDMVS_DROP, pInfo->partialConformingAction) == 0)
         {
            /* delete conforming filter and policer to drop if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 drop",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);
         }
         else
         {
            /* delete conforming filter and policer to continue if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 continue",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);
            
            if (cmsUtl_strcmp(MDMVS_DROP, pInfo->nonConformingAction) == 0)
            {
               /* delete partialconforming filter and policer to drop if overlimit */
               sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 drop",
                       pInfo->committedRate/1000, pInfo->excessBurstSize);
               policerFilterCommand(cmdType, PARTIALCONFORM, clsKeyMark, policeStr, tcFlowId+PARTIALCONFORM);
            }
            else
            {
               /* delete partialconforming filter and policer to continue if overlimit */
               sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 continue",
                       pInfo->committedRate/1000, pInfo->excessBurstSize);
               policerFilterCommand(cmdType, PARTIALCONFORM, clsKeyMark, policeStr, tcFlowId+PARTIALCONFORM);

               /* delete nonconforming filter */               
               policeStr[0] = '\0';
               policerFilterCommand(cmdType, NONCONFORM, clsKeyMark, policeStr, tcFlowId+NONCONFORM);
            }
            /* delete nonconforming class */
            policerClassCommand(cmdType, tcFlowId+NONCONFORM, pInfo->nonConformingAction);
         }
         /* delete partialconforming class */
         policerClassCommand(cmdType, tcFlowId+PARTIALCONFORM, pInfo->partialConformingAction);
      }
      else  /* MDMVS_TWORATETHREECOLOR */
      {
         if (cmsUtl_strcmp(MDMVS_DROP, pInfo->partialConformingAction) == 0)
         {
            /* delete conforming filter and policer to drop if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 drop",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);
         }
         else
         {
            /* delete conforming filter and policer to continue if overlimit */
            sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 continue",
                    pInfo->committedRate/1000, pInfo->committedBurstSize);
            policerFilterCommand(cmdType, CONFORM, clsKeyMark, policeStr, tcFlowId+CONFORM);
            
            if (cmsUtl_strcmp(MDMVS_DROP, pInfo->nonConformingAction) == 0)
            {
               /* delete partialconforming filter and policer to drop if overlimit */
               sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 drop",
                       (pInfo->peakRate - pInfo->committedRate)/1000, pInfo->peakBurstSize);
               policerFilterCommand(cmdType, PARTIALCONFORM, clsKeyMark, policeStr, tcFlowId+PARTIALCONFORM);
            }
            else
            {
               /* delete partialconforming filter and policer to continue if overlimit */
               sprintf(policeStr, "police rate %dkbit burst %d mtu 2000 continue",
                       (pInfo->peakRate - pInfo->committedRate)/1000, pInfo->peakBurstSize);
               policerFilterCommand(cmdType, PARTIALCONFORM, clsKeyMark, policeStr, tcFlowId+PARTIALCONFORM);

               /* delete nonconforming filter */               
               policeStr[0] = '\0';
               policerFilterCommand(cmdType, NONCONFORM, clsKeyMark, policeStr, tcFlowId+NONCONFORM);
            }
            /* delete nonconforming class */
            policerClassCommand(cmdType, tcFlowId+NONCONFORM, pInfo->nonConformingAction);
         }
         /* delete partialconforming class */
         policerClassCommand(cmdType, tcFlowId+PARTIALCONFORM, pInfo->partialConformingAction);
      }
      /* delete conforming class */
      policerClassCommand(cmdType, tcFlowId+CONFORM, pInfo->conformingAction);
      
      /* delete qdisc from interface */
      policerDelQdisc(queueIfname, clsKeyMark, clsKey);
   }

   return ret;

}  /* End of rutQos_policer() */

void policerClassCommand(QosCommandType cmdType, UINT32 flowid, const char *action)
{
   char cmd[BUFLEN_1024];
   UINT32 mask, dscp;

   if (cmsUtl_strcmp(MDMVS_DROP, action) == 0)
   {
      /* drop */
      return;
   }
   else if (cmsUtl_strcmp(MDMVS_NULL, action) == 0)
   {
      /* continue without dscp re-mark */
      mask = 0xff;   /* preserve all bits */
      dscp = 0;
   }
   else
   {
      /* continue with dscp re-mark */
      mask = 0x3;    /* preserve ECN bits */
      dscp = atoi(action);
   }

   sprintf(cmd, "tc class %s dev ifb0 classid 10:%d dsmark mask 0x%x value 0x%x 2>/dev/null",
           (cmdType == QOS_COMMAND_CONFIG)? "change" : "del",
           flowid, mask, dscp << 2);
   rut_doSystemAction("policerClassCommand", cmd);

   return;

}  /* End of policerClassCommand() */

void policerFilterCommand(QosCommandType cmdType, UINT32 prio, UINT32 handle,
                          char *policeStr, UINT32 flowid)
{
   char cmd[BUFLEN_1024];

   sprintf(cmd, "tc filter %s dev ifb0 parent 10: protocol 0x%x prio %d handle 0x%x/0x%x fw %s flowid :%d 2>/dev/null",
           (cmdType == QOS_COMMAND_CONFIG)? "add" : "del",
           ETH_P_ALL, prio, handle, SKBMARK_FLOW_ID_M, policeStr, flowid);
   rut_doSystemAction("policerFilterCommand", cmd);

   return;

}  /* End of policerFilterCommand() */

CmsRet policerAddQdisc(const char *ifname, UINT32 handle)
{
   char cmd[BUFLEN_1024];

   cmsLog_debug("Enter: ifname=%s handle=0x%x", ifname, handle);

   /* add the qdisc */
   sprintf(cmd, "tc qdisc add dev %s root handle 1: prio 2>/dev/null", ifname);
   rut_doSystemAction("policerAddQdisc", cmd);

   /* add the filter */
   sprintf(cmd, "tc filter add dev %s parent 1: protocol 0x%x prio 1 handle 0x%x/0x%x fw flowid :1 action mirred egress redirect dev ifb0 2>/dev/null",
           ifname, ETH_P_ALL, handle, SKBMARK_FLOW_ID_M);
   rut_doSystemAction("policerAddQdisc", cmd);
   
   return CMSRET_SUCCESS;

}  /* End of policerAddQdisc() */

CmsRet policerDelQdisc(const char *ifname, UINT32 handle, UINT32 excludeClsKey)
{
   char cmd[BUFLEN_1024];

   cmsLog_debug("Enter: ifname=%s handle=0x%x excludeClsKey=%d",
                ifname, handle, excludeClsKey);

   /* delete the filter */
   sprintf(cmd, "tc filter del dev %s parent 1: protocol 0x%x prio 1 handle 0x%x/0x%x fw flowid :1 action mirred egress redirect dev ifb0 2>/dev/null",
           ifname, ETH_P_ALL, handle, SKBMARK_FLOW_ID_M);
   rut_doSystemAction("policerDelQdisc", cmd);


   /* If this was the last one, delete the whole thing */
   if (rutQos_isAnotherClassPolicerExist(excludeClsKey, ifname) == FALSE)
   {
      sprintf(cmd, "tc qdisc del dev %s root handle 1: prio 2>/dev/null", ifname);
      rut_doSystemAction("policerDelQdisc", cmd);
   }

   return CMSRET_SUCCESS;

}  /* End of policerDelQdisc() */

#endif  /* SUPPORT_POLICING */

#endif  /* SUPPORT_QOS */


