/***********************************************************************
<:copyright-BRCM:2012:proprietary:standard 

   Copyright (c) 2012 Broadcom 
   All Rights Reserved

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
#include <sys/ioctl.h>
#include <net/if.h>
#include <time.h>

#include "stl.h"
#include "cms_util.h"
#include "cms_boardcmds.h"
#include "cms_boardioctl.h"
#include "adslctlapi.h"
#include "bcmxdsl.h"  /* for XdslLinkStat enum */
#include "bcmnet.h"
#include "rut_network.h"
#include "rut_system.h"
#include "tmctl_api.h"
#include "rut_qos.h"
#include "cms_qdm.h"

/* from autogenerated build_timestamp.c */
extern char *build_timestamp;

#if defined(SUPPORT_TMCTL)
tmctl_queueStats_t tmctl_queueStats_wanlan[5][MAX_ETHWAN_TRANSMIT_QUEUES]={};
char ifname[5][6] = {"eth0", "eth1", "eth2", "eth3", "veip0"};
#endif

/* System Status layer handler function go here.
 * Note this file is in the OS dependent sub-directory because
 * all RCL handler functions are likely to be OS dependent.
 */


#ifdef DMP_BASELINE_1
/*
 * The first few objects of TR98 data model: igdObject, DeviceInfo, etc.
 * are obviously dependent on TR98, so only in Legacy TR98 and
 * Hybrid TR98+TR181
 */

CmsRet stl_igdObject(_IGDObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   char deviceSummary[BUFLEN_1024];
   int curLen = 0; 
   int subStrLen = 0;
   /* ) and null character */
   int maxLen = BUFLEN_1024 - 2; 

   // only 1 LANDevice object for now
   obj->LANDeviceNumberOfEntries = 1;
   // only 1 WANDevice object for now
   obj->WANDeviceNumberOfEntries = 1;

   /* these are always built in */
   sprintf(deviceSummary,"InternetGatewayDevice:1.5[](Baseline:1, EthernetLAN:1, USBLAN:1, Time:1, IPPing:1, DeviceAssociation:1, QoS:1");
   curLen = strlen(deviceSummary);

#ifdef DMP_ADSLWAN_1
   subStrLen = strlen(", ADSLWAN:1, ATMLoopback:1, DSLDiagnostics:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", ADSLWAN:1, ATMLoopback:1, DSLDiagnostics:1");
      curLen += subStrLen;
   }
   
#ifdef DMP_PTMWAN_1
   /* PTMWAN:1 */
   subStrLen = strlen(", PTMWAN:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", PTMWAN:1");
      curLen += subStrLen;
   }
#endif /* DMP_PTMWAN_1 */
#endif /* DMP_ADSLWAN_1 */

#ifdef DMP_WIFILAN_1
   subStrLen = strlen(", WiFiLAN:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", WiFiLAN:1");
      curLen += subStrLen;
   }
#endif

#ifdef DMP_DOWNLOAD_1
   subStrLen = strlen(", Download:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", Download:1");
      curLen += subStrLen;
   }
#endif

#ifdef DMP_UPLOAD_1
   subStrLen = strlen(", Upload:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", Upload:1");
      curLen += subStrLen;
   }
#endif

#ifdef DMP_DOWNLOADTCP_1
   subStrLen = strlen(", DownloadTCP:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", DownloadTCP:1");
      curLen += subStrLen;
   }
#endif

#ifdef DMP_UPLOADTCP_1
   subStrLen = strlen(", UploadTCP:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", UploadTCP:1");
      curLen += subStrLen;
   }
#endif

#ifdef DMP_UDPECHO_1
   subStrLen = strlen(", UDPEcho:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", UDPEcho:1");
      curLen += subStrLen;
   }
#endif

#ifdef DMP_UDPECHOPLUS_1
   subStrLen = strlen(", UDPEchoPlus:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", UDPEchoPlus:1");
      curLen += subStrLen;
   }
#endif

#ifdef DMP_PERIODICSTATSBASE_1
   subStrLen = strlen(", PeriodicStatsBase:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", PeriodicStatsBase:1");
      curLen += subStrLen;
   }
#ifdef DMP_PERIODICSTATSADV_1
   subStrLen = strlen(", PeriodicStatsAdv:1");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,", PeriodicStatsAdv:1");
      curLen += subStrLen;
   }
#endif
#endif

   /* the end of data for IGD 1.4*/
   subStrLen = 1;
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary,")");
      curLen += 1;
   }
   
#ifdef BRCM_VOICE_SUPPORT
   subStrLen = strlen(", VoiceService:1.0[1](Endpoint:1, SIPEndpoint:1)");
   if ((subStrLen+ curLen) <= maxLen)
   {
      strcat(deviceSummary," , VoiceService:1.0[1](Endpoint:1, SIPEndpoint:1)");
      curLen += subStrLen;
   }
#endif /* BRCM_VOICE_SUPPORT */


   cmsLog_debug("Device summary string %s, len %d",deviceSummary,curLen);

   REPLACE_STRING_IF_NOT_EQUAL_FLAGS(obj->deviceSummary,deviceSummary,mdmLibCtx.allocFlags);

   return CMSRET_SUCCESS;
}


CmsRet stl_igdDeviceInfoObject(_IGDDeviceInfoObject *obj, const InstanceIdStack *iidStack __attribute__((unused)))
{
   char buf[BUFLEN_64]={0};
   UINT8  macAddr[6];
   CmsRet ret=CMSRET_SUCCESS_OBJECT_UNCHANGED;


   if (obj->additionalHardwareVersion == NULL)
   {
      char boardId[BUFLEN_64]={0};
      char finalString[BUFLEN_64]={0};  /* this is max length of additionalHardwareInfo */


      cmsLog_debug("getting board id now");

      if ((ret = devCtl_boardIoctl(BOARD_IOCTL_GET_ID, 0, boardId, sizeof(boardId), 0, NULL)) != CMSRET_SUCCESS)
      {
         cmsLog_error("Could not get Board Id");
         snprintf(finalString, sizeof(finalString), "BoardId=unknown");
      }
      else
      {
         snprintf(finalString, sizeof(finalString), "BoardId=%s", boardId);
         if (obj->productClass == NULL)
         {
            obj->productClass = cmsMem_strdupFlags(boardId, mdmLibCtx.allocFlags);
         }
         if (obj->modelName == NULL)
         {
            obj->modelName = cmsMem_strdupFlags(boardId, mdmLibCtx.allocFlags);
         }
      }

      if ((obj->additionalHardwareVersion = cmsMem_strdupFlags(finalString, mdmLibCtx.allocFlags)) == NULL)
      {
         cmsLog_error("mem allocation failed");
      }
      else
      {
         cmsLog_debug("set additionalHardwareVersion to ->%s<-", obj->additionalHardwareVersion);
      }

      obj->X_BROADCOM_COM_NumberOfCpuThreads = rutSys_getNumCpuThreads();

      /*
       * Because we changed a parameter, change the return code from
       * CMSRET_SUCCESS_OBJECT_UNCHANGED to CMSRET_SUCCESS.
       */
      ret = CMSRET_SUCCESS;
   }


   if (obj->softwareVersion == NULL)
   {
      cmsLog_debug("getting software version");

      if ((obj->softwareVersion = cmsMem_strdupFlags(CMS_RELEASE_VERSION, mdmLibCtx.allocFlags)) == NULL)
      {
         cmsLog_error("insufficient memory to strdup");
         return CMSRET_RESOURCE_EXCEEDED;
      }

      /*
       * Because we changed a parameter, change the return code from 
       * CMSRET_SUCCESS_OBJECT_UNCHANGED to
       * CMSRET_SUCCESS.
       */
      ret = CMSRET_SUCCESS;
   }


   if (obj->X_BROADCOM_COM_SwBuildTimestamp == NULL)
   {
      cmsLog_debug("getting software build timestamp");

      if ((obj->X_BROADCOM_COM_SwBuildTimestamp = cmsMem_strdupFlags(build_timestamp, mdmLibCtx.allocFlags)) == NULL)
      {
         cmsLog_error("insufficient memory to strdup");
         return CMSRET_RESOURCE_EXCEEDED;
      }

      ret = CMSRET_SUCCESS;
   }


#ifdef DMP_X_BROADCOM_COM_ADSLWAN_1   
   if (obj->X_BROADCOM_COM_DslPhyDrvVersion == NULL)
   {
      char adslPhyVersion[BUFLEN_256]={0};

      cmsLog_debug("getting DSL phy/driver version");

#ifdef DESKTOP_LINUX
      snprintf(adslPhyVersion, sizeof(adslPhyVersion), "desktop phy version");
#else
      cmsAdsl_getPhyVersion(adslPhyVersion, sizeof(adslPhyVersion)-1);
#endif

      if ((obj->X_BROADCOM_COM_DslPhyDrvVersion = cmsMem_strdupFlags(adslPhyVersion, mdmLibCtx.allocFlags)) == NULL)
      {
         cmsLog_error("insufficient memory to strdup");
         return CMSRET_RESOURCE_EXCEEDED;
      }

      ret = CMSRET_SUCCESS;
   }
#endif  /* DMP_X_BROADCOM_COM_ADSLWAN_1 */


#ifdef DMP_X_BROADCOM_COM_PSTNENDPOINT_1

   if (obj->X_BROADCOM_COM_VoiceServiceVersion == NULL)
   {
      cmsLog_debug("getting Voicesoftware version");


      if ((obj->X_BROADCOM_COM_VoiceServiceVersion = cmsMem_strdupFlags("Voice", mdmLibCtx.allocFlags)) == NULL)
      {
         cmsLog_error("insufficient memory to strdup");
         return CMSRET_RESOURCE_EXCEEDED;
      }

      ret = CMSRET_SUCCESS;
   }

#endif /* DMP_X_BROADCOM_COM_ENDPOINT_1 */



   /*
    * In 3.x, this string was hardcoded to "3.0". 
    * You can customize it to whatever you want...
    */
   if (obj->hardwareVersion == NULL)
   {
      if ((obj->hardwareVersion = cmsMem_strdupFlags("tmp_hardware1.0", mdmLibCtx.allocFlags)) == NULL)
      {
         cmsLog_error("insufficient memory to strdup");
         return CMSRET_RESOURCE_EXCEEDED;
      }

      /*
       * Because we changed a parameter, change the return code from 
       * CMSRET_SUCCESS_OBJECT_UNCHANGED to
       * CMSRET_SUCCESS.
       */
      ret = CMSRET_SUCCESS;
   }


   /*
    * This code was taken from sysGetCFEVersion from syscall.c and cgi_main.c
    */
   if (obj->additionalSoftwareVersion == NULL)
   {
      unsigned char cfeVersion[BUFLEN_64]={0};
      char finalString[BUFLEN_64]={0}; /* this is max length of additionalSoftwareInfo */
      
      if ((ret = devCtl_boardIoctl(BOARD_IOCTL_GET_CFE_VER, 0, (char*)cfeVersion, sizeof(cfeVersion), 0, NULL)) != CMSRET_SUCCESS)
      {
         cmsLog_debug("IOCTL_GET_CFE_VER failed, ret=%d, use default string", ret);
         snprintf(finalString, sizeof(finalString), "CFE=(before 1.0.37-5.12)");
      }
      else
      {
         snprintf(finalString, sizeof(finalString), "CFE=%d.%d.%d-%d.%d", cfeVersion[0], cfeVersion[1], cfeVersion[2], cfeVersion[3], cfeVersion[4]);
      }
         
      if ((obj->additionalSoftwareVersion = cmsMem_strdupFlags(finalString, mdmLibCtx.allocFlags)) == NULL)
      {
         cmsLog_error("mem allocation failed");
      }
      else
      {
         cmsLog_debug("set additionalSoftwareVersion to ->%s<-", obj->additionalSoftwareVersion);
      }
   }
    
   /*
    * provisioningCode is something that the ACS sets.  We just report it.
    */


   /*
    * ssk periodically reads this object to for an update of the uptime.
    * But ssk is not interested in the device log, so if ssk is doing the get,
    * don't bother getting the device log.
    * httpd has it own special parsing of the devicelog, so it calls cmsLog_readPartial
    * directly.  So don't bother getting device log when the caller is httpd.
    */
   if ((mdmLibCtx.eid != EID_SSK) && (mdmLibCtx.eid != EID_HTTPD))
   {
#ifdef DESKTOP_LINUX
      obj->deviceLog = cmsMem_strdupFlags("device log not supported on DESKTOP LINUX", mdmLibCtx.allocFlags);
#else
      UINT16 logLen = 0;
      char *log;

      log = rutSys_getDeviceLog(&logLen);

      if (log != NULL && logLen != 0)
      {
         CMSMEM_REPLACE_STRING_FLAGS(obj->deviceLog, log, mdmLibCtx.allocFlags);
         if (obj->deviceLog == NULL)
         {
            cmsLog_error("insufficient memory to strdup");
            return CMSRET_RESOURCE_EXCEEDED;
         }
      }
      else
      {
         CMSMEM_REPLACE_STRING_FLAGS(obj->deviceLog, "", mdmLibCtx.allocFlags);
      }

      /*
       * log may not be NULL, but logLen==0.  So put the free out here to make
       * sure the log buffer is freed.
       */
      CMSMEM_FREE_BUF_AND_NULL_PTR(log);

#endif  /* DESKTOP_LINUX */


      /*
       * Because we changed a parameter, change the return code from 
       * CMSRET_SUCCESS_OBJECT_UNCHANGED to
       * CMSRET_SUCCESS.
       */
      ret = CMSRET_SUCCESS;
   }


   /*
    * The CMS Timestamp API gives us the number of seconds since boot,
    * which is exactly what we want here.
    */
   {
      obj->upTime = cmsTms_getSeconds();

      /*
       * Because we changed a parameter, change the return code from 
       * CMSRET_SUCCESS_OBJECT_UNCHANGED to
       * CMSRET_SUCCESS.
       */
      ret = CMSRET_SUCCESS;
   }

   if (obj->serialNumber == NULL)
   {
      devCtl_getBaseMacAddress(macAddr);

      sprintf(buf, "%02x%02x%02x%02x%02x%02x", 
                (unsigned char) macAddr[0], (unsigned char) macAddr[1],
                (unsigned char) macAddr[2], (unsigned char) macAddr[3],
                (unsigned char) macAddr[4], (unsigned char) macAddr[5]);
      obj->serialNumber = cmsMem_strdupFlags(buf, mdmLibCtx.allocFlags);

      if (obj->manufacturerOUI == NULL)
      {
         sprintf(buf, "%02x%02x%02x", (unsigned char) macAddr[0], 
                       (unsigned char) macAddr[1], (unsigned char) macAddr[2]);
         obj->manufacturerOUI = cmsMem_strdupFlags(buf, mdmLibCtx.allocFlags);
      }

      /*
       * Because we changed a parameter, change the return code from 
       * CMSRET_SUCCESS_OBJECT_UNCHANGED to
       * CMSRET_SUCCESS.
       */
      ret = CMSRET_SUCCESS;
   }
   
   return ret;
}


#endif  /* DMP_BASELINE_1 */

CmsRet stl_syslogCfgObject(_SyslogCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_loginCfgObject(_LoginCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_appCfgObject(_AppCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_httpdCfgObject(_HttpdCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_vectoringCfgObject(_VectoringCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#ifdef DMP_X_ITU_ORG_GPON_1
CmsRet stl_omcidCfgObject(_OmcidCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif /* DMP_X_ITU_ORG_GPON_1 */

CmsRet stl_tr69cCfgObject(_Tr69cCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#ifdef DMP_X_BROADCOM_COM_TR64_1
CmsRet stl_tr64cCfgObject(_Tr64cCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif

CmsRet stl_sshdCfgObject(_SshdCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_telnetdCfgObject(_TelnetdCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_consoledCfgObject(_ConsoledCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_smdCfgObject(_SmdCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_sskCfgObject(_SskCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_snmpdCfgObject(_SnmpdCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_ftpdCfgObject(_FtpdCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_tftpdCfgObject(_TftpdCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_pppdCfgObject(_PppdCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_icmpCfgObject(_IcmpCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#ifdef DMP_X_BROADCOM_COM_EPON_1
CmsRet stl_eponappCfgObject(_EponappCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif

CmsRet stl_cellularappCfgObject(_CellularappCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_interfaceControlObject(_InterfaceControlObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_deviceConfigObject(_DeviceConfigObject *obj, const InstanceIdStack *iidStack __attribute__((unused)))
{
   char *pBuf;

   pBuf = rutSys_getDevicePersistentData();
   if (pBuf != NULL)
   {
      CMSMEM_REPLACE_STRING_FLAGS(obj->persistentData, pBuf, mdmLibCtx.allocFlags);   
      cmsMem_free(pBuf);
   }

   pBuf = rutSys_getRunningConfigFile();
   if (pBuf != NULL)
   {
      CMSMEM_REPLACE_STRING_FLAGS(obj->configFile, pBuf, mdmLibCtx.allocFlags);   
      cmsMem_free(pBuf);
   }

   return CMSRET_SUCCESS;
}

#ifdef DMP_TIME_1
CmsRet stl_timeServerCfgObject(_TimeServerCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   char dateTimeBuf[BUFLEN_64];

   cmsTms_getXSIDateTime(0, dateTimeBuf, sizeof(dateTimeBuf));
   CMSMEM_REPLACE_STRING_FLAGS(obj->currentLocalTime, dateTimeBuf, mdmLibCtx.allocFlags);
   CMSMEM_REPLACE_STRING_FLAGS(obj->daylightSavingsStart, dateTimeBuf, mdmLibCtx.allocFlags);
   CMSMEM_REPLACE_STRING_FLAGS(obj->daylightSavingsEnd, dateTimeBuf, mdmLibCtx.allocFlags);
   obj->daylightSavingsUsed = FALSE;

   return CMSRET_SUCCESS;
}
#endif

#ifdef NOT_SUPPORTED
CmsRet stl_userInterfaceCfgObject(_UserInterfaceCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif

CmsRet stl_l3ForwardingObject(_L3ForwardingObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_l3ForwardingEntryObject(_L3ForwardingEntryObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}


/*
 * These bridging objects should get moved to stl_pmap.c
 */
#ifdef DMP_BRIDGING_1
CmsRet stl_l2BridgingObject(_L2BridgingObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_l2BridgingEntryObject(_L2BridgingEntryObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_l2BridgingFilterObject(_L2BridgingFilterObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#ifdef NOT_SUPPORTED
CmsRet stl_l2BridgingMarkingObject(_L2BridgingMarkingObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif

CmsRet stl_l2BridgingIntfObject(_L2BridgingIntfObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif /* DMP_BRIDGING_1 */


/*
 * These queue objects should get moved to stl_qos.c
 */
#ifdef DMP_QOS_1
CmsRet stl_qMgmtObject(_QMgmtObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_qMgmtClassificationObject(_QMgmtClassificationObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#ifdef DMP_QOSDYNAMIC_FLOW_1
CmsRet stl_qMgmtAppObject(_QMgmtAppObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_qMgmtFlowObject(_QMgmtFlowObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif /* DMP_QOSDYNAMIC_FLOW_1 */

CmsRet stl_qMgmtPolicerObject(_QMgmtPolicerObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_qMgmtQueueObject(_QMgmtQueueObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

void reset_qMgmtQueueStats(void)
{
#if defined(SUPPORT_TMCTL)
   int i, j;
   tmctl_queueStats_t tmctl_queueStats;
   
   for (i = 0; i < 5; i++)
   {
      for (j = 0; j < MAX_ETHWAN_TRANSMIT_QUEUES; j++)
      {
          memset(&tmctl_queueStats, 0, sizeof(tmctl_queueStats));        
          if (rutQos_tmGetQueueStats(ifname[i], j, &tmctl_queueStats) != CMSRET_SUCCESS)
          {
              cmsLog_error("tmctl_getQueueStats failed :port=%d, qid=%d\n", i, j);
              return;
          }
          memcpy(&tmctl_queueStats_wanlan[i][j], &tmctl_queueStats, sizeof(tmctl_queueStats));
      }
   }
#endif
}

#if defined(SUPPORT_TMCTL)
CmsRet stl_qMgmtQueueStatsObject(_QMgmtQueueStatsObject *obj, const InstanceIdStack *iidStack __attribute__((unused)))
{
   tmctl_queueStats_t tmctl_queueStats;
   UINT32 queue = obj->X_BROADCOM_COM_QueueId - 1;
   char intfname[CMS_IFNAME_LENGTH];
   CmsRet ret;
   int i;
            
   memset(&tmctl_queueStats, 0, sizeof(tmctl_queueStats));
   memset(intfname, 0, sizeof(intfname));
   if ((ret = qdmIntf_fullPathToIntfnameLocked(obj->queueInterface, intfname)) != CMSRET_SUCCESS)
   {
      cmsLog_error("qdmIntf_fullPathToIntfnameLocked returns error. ret=%d", ret);
      return CMSRET_SUCCESS_OBJECT_UNCHANGED;
   }


   if ((ret = rutQos_tmGetQueueStats(intfname, queue, &tmctl_queueStats)) != CMSRET_SUCCESS)
   {
      cmsLog_error("tmctl_getQueueStats failed :port=%s, qid=%d, ret=%d\n",
        intfname, queue, ret);
      return CMSRET_SUCCESS_OBJECT_UNCHANGED;
   }
   for (i = 0; i < 5; i++)
   {
      if (strcmp(intfname, ifname[i]) == 0 )
      {
         break;
      }
   }
   if (i >= 5)
   {
      return CMSRET_SUCCESS_OBJECT_UNCHANGED;
   }
   if (tmctl_queueStats.txPackets < tmctl_queueStats_wanlan[i][queue].txPackets)
   {
      memset(&tmctl_queueStats_wanlan[i][queue], 0, sizeof(tmctl_queueStats_wanlan[i][queue]));
   }
   obj->outputPackets = tmctl_queueStats.txPackets - tmctl_queueStats_wanlan[i][queue].txPackets;
   obj->outputBytes = tmctl_queueStats.txBytes - tmctl_queueStats_wanlan[i][queue].txBytes;
   obj->droppedPackets = tmctl_queueStats.droppedPackets - tmctl_queueStats_wanlan[i][queue].droppedPackets;
   obj->droppedBytes = tmctl_queueStats.droppedBytes - tmctl_queueStats_wanlan[i][queue].droppedBytes;
   return CMSRET_SUCCESS;
}
#else
CmsRet stl_qMgmtQueueStatsObject(_QMgmtQueueStatsObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS;
}
#endif /* defined(SUPPORT_TMCTL) */
#endif /* DMP_QOS_1 */



#ifdef NOT_SUPPORTED
CmsRet stl_lanconfigSecurityObject(_LanconfigSecurityObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif


CmsRet stl_wanDebugPortMirroringCfgObject(_WanDebugPortMirroringCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}


CmsRet stl_urlFilterCfgObject(_UrlFilterCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_urlFilterListObject(_UrlFilterListObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}



CmsRet stl_servicesObject(_ServicesObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_snmpCfgObject(_SnmpCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_secDmzHostCfgObject(_SecDmzHostCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#ifdef DMP_X_BROADCOM_COM_SECURITY_1
CmsRet stl_ipFilterCfgObject(_IpFilterCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_macFilterObject(_MacFilterObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_macFilterCfgObject(_MacFilterCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif

CmsRet stl_accessTimeRestrictionObject(_AccessTimeRestrictionObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_dDnsCfgObject(_DDnsCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#ifdef DMP_X_BROADCOM_COM_IPPRINTING_1
/* this function should get moved out into its own file, stl_ipp.c */
CmsRet stl_ippCfgObject(_IppCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif  /* DMP_X_BROADCOM_COM_IPPRINTING_1 */

CmsRet stl_ipSecCfgObject(_IPSecCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_certificateCfgObject(_CertificateCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_networkConfigObject(_NetworkConfigObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}


CmsRet stl_ethernetSwitchObject(_EthernetSwitchObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}


#ifdef DMP_X_BROADCOM_COM_UPNP_1 /* aka SUPPORT_UPNP */

CmsRet stl_upnpCfgObject(_UpnpCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#endif
 
#ifdef DMP_X_BROADCOM_COM_IPV6_1 /* aka SUPPORT_IPV6 */
CmsRet stl_ipTunnelObject(_IPTunnelObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_ipv4inIpv6TunnelObject(_Ipv4inIpv6TunnelObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_ipv6inIpv4TunnelObject(_Ipv6inIpv4TunnelObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_ipv6LanIntfAddrObject(_IPv6LanIntfAddrObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_delegatedAddressObject(_DelegatedAddressObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_ipv6LanHostCfgObject(_IPv6LanHostCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_radvdConfigMgtObject(_RadvdConfigMgtObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_uLAPrefixInfoObject(_ULAPrefixInfoObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_prefixInfoObject(_PrefixInfoObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_ipv6L3ForwardingObject(_IPv6L3ForwardingObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_ipv6L3ForwardingEntryObject(_IPv6L3ForwardingEntryObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#endif 
#ifdef DMP_X_BROADCOM_COM_DNSPROXY_1 /* aka SUPPORT_DNSPROXY */

CmsRet stl_dnsProxyCfgObject(_DnsProxyCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#endif 

#ifdef DMP_X_BROADCOM_COM_PWRMNGT_1 /* aka SUPPORT_PWRMNGT */
CmsRet stl_pwrMngtObject(_PwrMngtObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif /* aka SUPPORT_PWRMNGT */

#ifdef DMP_X_BROADCOM_COM_STANDBY_1
CmsRet stl_standbyCfgObject(_StandbyCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif 


CmsRet stl_vendorConfigFileObject(_VendorConfigFileObject *obj __attribute__((unused)),
                 const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#ifdef DMP_X_BROADCOM_COM_MCAST_1
CmsRet stl_mcastCfgObject(_McastCfgObject *obj __attribute__((unused)),
                     const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif

#ifdef DMP_X_BROADCOM_COM_IGMP_1 /* aka SUPPORT_IGMP */
CmsRet stl_igmpCfgObject(_IgmpCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif /* aka SUPPORT_IGMP*/

#ifdef DMP_X_BROADCOM_COM_MLD_1 /* aka SUPPORT_MLD */
CmsRet stl_mldCfgObject(_MldCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif /* aka SUPPORT_MLD */

#ifdef BRCM_VOICE_SUPPORT
#  ifdef DMP_X_BROADCOM_COM_DECTD_1  /* aka dectd */
CmsRet stl_dectdCfgObject(_DectdCfgObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#  endif
#endif 

#ifdef DMP_X_BROADCOM_COM_EPON_1
CmsRet stl_eponSoftwareImageObject(_EponSoftwareImageObject *obj __attribute__((unused)),
                                    const InstanceIdStack *iidStack __attribute__((unused)))
{
    return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_eponSwUpgradeStatusObject(_EponSwUpgradeStatusObject *obj __attribute__((unused)),
                                    const InstanceIdStack *iidStack __attribute__((unused)))
{
    return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif

CmsRet stl_xmppcCfgObject(_XmppcCfgObject *obj __attribute__((unused)),
                          const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#ifdef DMP_X_BROADCOM_COM_TM_1
CmsRet stl_bCMTrafficManagementObject( _BCMTrafficManagementObject *obj  __attribute__((unused)),
                const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}
#endif
