/***********************************************************************
 *
 *  Copyright (c) 2006-2011  Broadcom Corporation
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

#ifdef DMP_DEVICE2_BASELINE_1

#include "stl.h"
#include "cms_boardioctl.h"
#include "cms_util.h"
#include "adslctlapi.h"
#include "../rut_system.h"

/* from autogenerated build_timestamp.c */
extern char *build_timestamp;

CmsRet stl_dev2DeviceObject(_Dev2DeviceObject *obj __attribute__((unused)),
                  const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* TODO: not implemented yet */
    return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}


CmsRet stl_dev2ServicesObject(_Dev2ServicesObject *obj __attribute__((unused)),
                  const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* TODO: not implemented yet */
    return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_dev2DeviceInfoObject(_Dev2DeviceInfoObject *obj,
                            const InstanceIdStack *iidStack __attribute__((unused)))
{
   char buf[BUFLEN_64]={0};
   UINT8  macAddr[6];
   CmsRet ret = CMSRET_SUCCESS_OBJECT_UNCHANGED;

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

      obj->processorNumberOfEntries = rutSys_getNumCpuThreads();

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

#ifdef DMP_X_BROADCOM_COM_DSL_1   
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
#endif  /* DMP_X_BROADCOM_COM_DSL_1 */


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


/* XXX TODO: is TR181 has any oject for deviceLog ???  */
#ifdef TR181_IMPLEMENTATION
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
//      obj->deviceLog = cmsMem_strdupFlags("device log not supported on DESKTOP LINUX", mdmLibCtx.allocFlags);
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

#endif   // TR181_IMPLEMENTATION

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

#ifdef DMP_DEVICE2_PROCESSORS_1

CmsRet stl_dev2ProcessorObject(_Dev2ProcessorObject *obj __attribute__((unused)),
                               const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* Nothing to implement here yet */
    return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

#endif  /* DMP_DEVICE2_PROCESSORS_1 */

#endif  /* DMP_DEVICE2_BASELINE_1 */

