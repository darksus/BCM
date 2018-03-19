/***********************************************************************
<:copyright-BRCM:2017:proprietary:standard 

   Copyright (c) 2017 Broadcom 
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

#ifdef DMP_X_BROADCOM_COM_CONTAINER_1

#include "stl.h"
#include "cms_dal.h"
#include "cms_qdm.h"
#include "cms_params_modsw.h"


typedef struct {
   char id[BUFLEN_64];
   char name[BUFLEN_64];
   char status[BUFLEN_32];
   char pid[BUFLEN_32];
   char cpu_use[BUFLEN_32];
   char mem_use[BUFLEN_32];
   char interface[BUFLEN_32];
   char ipv4_addrs[BUFLEN_256];
   char ports[BUFLEN_64];
   char byte_sent[BUFLEN_32];
   char byte_received[BUFLEN_32];
} CONTAINER_INFO, *PCONTAINER_INFO;


static CmsRet container_get_info(const char *container_name, PCONTAINER_INFO info)
{
   CmsRet ret = CMSRET_INTERNAL_ERROR;
   char cmd[BUFLEN_256], buf[BUFLEN_256];
   char name[BUFLEN_64], val1[BUFLEN_64];
   char val2[BUFLEN_64], val3[BUFLEN_64];
   FILE *fp = NULL;
   EUObject *euObj = NULL;
   ExecEnvObject *eeObj = NULL;
   UBOOL8 found = FALSE;
   InstanceIdStack iidStack;
   char eeFullPath[MDM_SINGLE_FULLPATH_BUFLEN]={0};
   char *ptr;

   INIT_INSTANCE_ID_STACK(&iidStack);
   memset(cmd, 0, BUFLEN_256);
   memset(info, 0, sizeof(CONTAINER_INFO));

   /* make sure container name does not end with \n and space */
   ptr = strchr(container_name, '\n');
   if (ptr)
   {
      *ptr = '\0';
   }
   
   ptr = strchr(container_name, ' ');
   if (ptr)
   {
      *ptr = '\0';
   }

   /*
    * find out who owns the container name
    * 1. if EU owns the container name, call lxc-attach to run lxc-info
    * 2. if EE owns the container name, call lxc-info
    */
   while (!found && cmsObj_getNextFlags(MDMOID_EU,
                                        &iidStack,
                                        OGF_NO_VALUE_UPDATE,
                                        (void **)&euObj) == CMSRET_SUCCESS)
   {
      if (cmsUtl_strcmp(euObj->EUID, container_name) == 0)
      {
         found = TRUE;
         cmsUtl_strncpy(eeFullPath, euObj->executionEnvRef, 
                        sizeof(eeFullPath)-1);

         cmsLog_debug("container<%s> belongs to EUID<%s> of EE<%s>", 
                      container_name, euObj->EUID, euObj->executionEnvRef);
      }

      cmsObj_free((void **)&euObj);
   }

   if (found)
   {
      /* this container belongs to EUObj */
      MdmPathDescriptor pathDesc;

      memset(&pathDesc, 0, sizeof(MdmPathDescriptor));

      ret = cmsMdm_fullPathToPathDescriptor(eeFullPath, &pathDesc);
      if (ret != CMSRET_SUCCESS)
      {
         cmsLog_error("Could not convert %s", eeFullPath);
         return ret;
      }

      /* Get ExecEnvObject to have container name */
      ret = cmsObj_get(pathDesc.oid,
                       &(pathDesc.iidStack),
                       OGF_NO_VALUE_UPDATE,
                       (void **)&eeObj);

      if (ret != CMSRET_SUCCESS)
      {
         cmsLog_error("could not get ExecEnv object, ret=%d", ret);
         return ret;
      }

      if (eeObj->enable && (cmsUtl_strcmp(eeObj->status, MDMVS_UP) == 0))
      {
         if (IS_EMPTY_STRING(eeObj->X_BROADCOM_COM_ContainerName))
         {
            /* Associated EE is not run in a container */
            sprintf(cmd, "lxc-info -n %s", container_name);
         }
         else
         {
            /* Run lxc-info inside the container to get correct info */
            sprintf(cmd, "lxc-attach -n %s -- lxc-info -n %s", 
                    eeObj->X_BROADCOM_COM_ContainerName, container_name);
         }
      }
      else
      {
         /* 
          * If associated EE is not up, EU must be idle. 
          * Run lxc-info directly from host to get the status
          */
         sprintf(cmd, "lxc-info -n %s", container_name);
      }

      cmsObj_free((void **)&eeObj);
   }
   else
   {
      /* this container belongs to EEObj */
      sprintf(cmd, "lxc-info -n %s", container_name);
   }

   if ((fp = popen(cmd, "r")) == NULL)
   {
      cmsLog_error("Error opening pipe!\n");
      return ret;
   }

   while (fgets(buf, BUFLEN_256, fp) != NULL)
   {
      memset(name, 0, BUFLEN_64);
      memset(val1, 0, BUFLEN_64);
      memset(val2, 0, BUFLEN_64);
      memset(val3, 0, BUFLEN_64);

      sscanf(buf, "%s %s %s %s", name, val1, val2, val3);

      if (val2[0] != '\0')
      {
         if (cmsUtl_strcmp(name, "CPU") == 0)
         {
	        snprintf(info->cpu_use, BUFLEN_32, "%s %s", val2, val3);
         }
         else if (cmsUtl_strcmp(name, "Memory") == 0)
         {
	        snprintf(info->mem_use, BUFLEN_32, "%s %s", val2, val3);
         }
         else if (cmsUtl_strcmp(name, "TX") == 0)
         {
	        snprintf(info->byte_sent, BUFLEN_32, "%s %s", val2, val3);
         }
         else if (cmsUtl_strcmp(name, "RX") == 0)
         {
	        snprintf(info->byte_received, BUFLEN_32, "%s %s", val2, val3);
         }
      }
      else
      {
         if (cmsUtl_strcmp(name, "Name:") == 0)
         {
            cmsUtl_strncpy(info->name, val1, BUFLEN_64);
            /*cmsUtl_strncpy(info->id, "", BUFLEN_64);*/
         }
         else if (cmsUtl_strcmp(name, "State:") == 0)
         {
            cmsUtl_strncpy(info->status, val1, BUFLEN_32);
         }
         else if (cmsUtl_strcmp(name, "PID:") == 0)
         {
            cmsUtl_strncpy(info->pid, val1, BUFLEN_32);
         }
         else if (cmsUtl_strcmp(name, "Link:") == 0)
         {
            cmsUtl_strncpy(info->interface, val1, BUFLEN_32);
         }
         else if (cmsUtl_strcmp(name, "IP:") == 0)
         {
	        if (info->ipv4_addrs[0] == '\0')
               cmsUtl_strncpy(info->ipv4_addrs, val1, BUFLEN_32);
	        else
	           sprintf(info->ipv4_addrs, "%s, %s", info->ipv4_addrs, val1);
	     }
      }
   }

   if (pclose(fp))
   {
      printf("Command not found or exited with error status\n");
      return ret;
   }

   return CMSRET_SUCCESS;
}


static CmsRet container_dm_add(const PCONTAINER_INFO info,
                               int instance_id)
{
   CmsRet ret = CMSRET_OBJECT_NOT_FOUND;
   char euFullPath[MDM_SINGLE_FULLPATH_BUFLEN]={0};
   UBOOL8 found = FALSE;
   InstanceIdStack iidStack = EMPTY_INSTANCE_ID_STACK;
   InstanceIdStack euIidStack = EMPTY_INSTANCE_ID_STACK;
   EUObject *euObj = NULL;
   ContainerInfoObject *containerInfoObj = NULL;
   ContainerStateObject *containerStateObj = NULL;
   ContainerNetworkObject *containerNetworkObj = NULL;
   ContainerStatsObject *containerStatsObj = NULL;

   cmsLog_debug("\ninfo->id %s\ninfo->name %s\ninfo->status %s\ninfo->pid %s\ninfo->cpu_use %s\ninfo->mem_use\n\n",
       info->id, info->name, info->status, info->pid, info->cpu_use, info->mem_use);

   /* Create container info object */
   PUSH_INSTANCE_ID(&iidStack, instance_id);
   ret = cmsObj_addInstance(MDMOID_CONTAINER_INFO, &iidStack);
   if (ret != CMSRET_SUCCESS)
   {
      cmsLog_error("Could not add instance of container info object, returned %d", ret);
      goto out;
   }

   /* Get container info object */
   ret = cmsObj_get(MDMOID_CONTAINER_INFO,
                    &iidStack,
                    0,
                    (void **) &containerInfoObj);
   if (ret != CMSRET_SUCCESS)
   {
      cmsLog_error("Could not get container info object, returned %d", ret);
      goto out;
   }

   /* Look for EU object that has its EUID matched with the given name */
   while (found == FALSE &&
          cmsObj_getNextFlags(MDMOID_EU,
                              &euIidStack,
                              OGF_NO_VALUE_UPDATE,
                              (void **) &euObj) == CMSRET_SUCCESS)
   {
      if (cmsUtl_strcmp(euObj->EUID, info->name) == 0)
      {
         found = TRUE;

         /* Update execEnvRef parameter in container info object */
         REPLACE_STRING_IF_NOT_EQUAL(containerInfoObj->execEnvRef, euObj->executionEnvRef);

         qdmModsw_getExecUnitFullPathByEuidLocked(euObj->EUID,
                                                  euFullPath, sizeof(euFullPath));

         /* Update referencePath parameter in container info object */
         REPLACE_STRING_IF_NOT_EQUAL(containerInfoObj->referencePath, euFullPath);
      }

      /* Free EUObject */
      cmsObj_free((void **) &euObj);
   }

   /* Openwrt has container named "obox". It's not in data model */
   if (found == FALSE && cmsUtl_strcmp(info->name, "obox") == 0)
   {
      char eeFullPath[MDM_SINGLE_FULLPATH_BUFLEN]={0};

      /* Get "Openwrt" exec. env. full path */
      qdmModsw_getExecEnvFullPathByNameLocked(OPENWRTEE_NAME, eeFullPath, sizeof(eeFullPath));

      /* Update execEnvRef parameter in container info object */
      REPLACE_STRING_IF_NOT_EQUAL(containerInfoObj->execEnvRef, eeFullPath);
   }

   /* Update standard parameter in container info -- so far only LXC */
   REPLACE_STRING_IF_NOT_EQUAL(containerInfoObj->standard, MDMVS_LXC);

   /* Set container info object */
   ret = cmsObj_set(containerInfoObj, &iidStack);

   /* Free container info object */
   cmsObj_free((void **) &containerInfoObj);

   /* Get container state object */
   ret = cmsObj_get(MDMOID_CONTAINER_STATE,
                    &iidStack,
                    0,
                    (void **) &containerStateObj);
   if (ret != CMSRET_SUCCESS)
   {
      cmsLog_error("Could not get container state object, returned %d", ret);
      goto out;
   }

   /* Update container state parameters */
   REPLACE_STRING_IF_NOT_EQUAL(containerStateObj->ID, info->id);
   REPLACE_STRING_IF_NOT_EQUAL(containerStateObj->name, info->name);
   if (cmsUtl_strcasecmp(info->status, MDMVS_STARTING) == 0)
   {
      REPLACE_STRING_IF_NOT_EQUAL(containerStateObj->status, MDMVS_STARTING);
   }
   else if (cmsUtl_strcasecmp(info->status, MDMVS_RUNNING) == 0)
   {
      REPLACE_STRING_IF_NOT_EQUAL(containerStateObj->status, MDMVS_RUNNING);
   }
   else if (cmsUtl_strcasecmp(info->status, MDMVS_STOPPING) == 0)
   {
      REPLACE_STRING_IF_NOT_EQUAL(containerStateObj->status, MDMVS_STOPPING);
   }
   else if (cmsUtl_strcasecmp(info->status, MDMVS_STOPPED) == 0)
   {
      REPLACE_STRING_IF_NOT_EQUAL(containerStateObj->status, MDMVS_STOPPED);
   }
   else if (cmsUtl_strcasecmp(info->status, MDMVS_ABORTING) == 0)
   {
      REPLACE_STRING_IF_NOT_EQUAL(containerStateObj->status, MDMVS_ABORTING);
   }
   REPLACE_STRING_IF_NOT_EQUAL(containerStateObj->PID, info->pid);
   REPLACE_STRING_IF_NOT_EQUAL(containerStateObj->cpuUse, info->cpu_use);
   REPLACE_STRING_IF_NOT_EQUAL(containerStateObj->memoryUse, info->mem_use);

   /* Set container state object */
   ret = cmsObj_set(containerStateObj, &iidStack);

   /* Free container state object */
   cmsObj_free((void **) &containerStateObj);

   /* Get container network object */
   ret = cmsObj_get(MDMOID_CONTAINER_NETWORK,
                    &iidStack,
                    0,
                    (void **) &containerNetworkObj);
   if (ret != CMSRET_SUCCESS)
   {
      cmsLog_error("Could not get container network object, returned %d", ret);
      goto out;
   }

   /* Update container network parameters */
   REPLACE_STRING_IF_NOT_EQUAL(containerNetworkObj->interface, info->interface);
   REPLACE_STRING_IF_NOT_EQUAL(containerNetworkObj->IPv4Addresses, info->ipv4_addrs);
   REPLACE_STRING_IF_NOT_EQUAL(containerNetworkObj->ports, info->ports);

   /* Set container network object */
   ret = cmsObj_set(containerNetworkObj, &iidStack);

   /* Free container network object */
   cmsObj_free((void **) &containerNetworkObj);

   /* Get container stats object */
   ret = cmsObj_get(MDMOID_CONTAINER_STATS,
                    &iidStack,
                    0,
                    (void **) &containerStatsObj);
   if (ret != CMSRET_SUCCESS)
   {
      cmsLog_error("Could not get container stats object, returned %d", ret);
      goto out;
   }

   /* Update container stats parameters */
   REPLACE_STRING_IF_NOT_EQUAL(containerStatsObj->bytesSent, info->byte_sent);
   REPLACE_STRING_IF_NOT_EQUAL(containerStatsObj->bytesReceived, info->byte_received);

   /* Set container stats object */
   ret = cmsObj_set(containerStatsObj, &iidStack);

   /* Free container stats object */
   cmsObj_free((void **) &containerStatsObj);

out:
   if (containerInfoObj != NULL)
      cmsObj_free((void **) &containerInfoObj);
   if (containerStateObj != NULL)
      cmsObj_free((void **) &containerStateObj);
   if (containerNetworkObj != NULL)
      cmsObj_free((void **) &containerNetworkObj);
   if (containerStatsObj != NULL)
      cmsObj_free((void **) &containerStatsObj);

   return ret;
}


static CmsRet container_dm_remove_all(void)
{
   CmsRet ret = CMSRET_SUCCESS;
   InstanceIdStack iidStack = EMPTY_INSTANCE_ID_STACK;
   ContainerInfoObject *obj = NULL;

   /* Look for container info object */
   while (cmsObj_getNextFlags(MDMOID_CONTAINER_INFO,
                              &iidStack,
                              OGF_NO_VALUE_UPDATE,
                              (void **) &obj) == CMSRET_SUCCESS)
   {
      /* Remove container info object */
      ret = cmsObj_deleteInstance(MDMOID_CONTAINER_INFO, &iidStack);

      /* Re-initialize container info instance stack*/
      INIT_INSTANCE_ID_STACK(&iidStack);

      /* Free container info object */
      cmsObj_free((void **) &obj);

      /* exit if error */
      if (ret != CMSRET_SUCCESS)
      {
         cmsLog_error("Cannot remove ContainerInfoObject, ret %d", ret);
         break;
      }
   }

   return ret;
}


static CmsRet container_dm_update_all(_ContainerObject *obj,
                                      const InstanceIdStack *iidStack)
{
   CmsRet ret = CMSRET_SUCCESS;
   int count = 0;
   char *cmd = "lxc-ls";
   char buf[BUFLEN_256];
   FILE *fp = NULL;
   CONTAINER_INFO info;

   if ((fp = popen(cmd, "r")) == NULL)
   {
      cmsLog_error("Error opening pipe!\n");
      return CMSRET_INTERNAL_ERROR;
   }

   if (obj->containerNumberOfEntries > 0)
   {
      /* Remove all container info object */
      ret = container_dm_remove_all();
      if (ret != CMSRET_SUCCESS)
         goto out;

      /* Reset number of container info object */
      obj->containerNumberOfEntries = 0;

      /* Set container object */
      ret = cmsObj_set(obj, iidStack);
      if (ret != CMSRET_SUCCESS)
         goto out;
   }

   while (fgets(buf, BUFLEN_256, fp) != NULL)
   {
      /* Retrieve current container information */
      ret = container_get_info(buf, &info);

      if (ret != CMSRET_SUCCESS)
         goto out;

      /* Add new container info object */
      ret = container_dm_add(&info, ++count);
  
      if (ret != CMSRET_SUCCESS)
         goto out;
   }

out:
   pclose(fp);

   return ret;
}


CmsRet stl_containerObject(_ContainerObject *obj,
                           const InstanceIdStack *iidStack)
{
   CmsRet ret = CMSRET_SUCCESS;

   /* Remove old then add current container info object */
   ret = container_dm_update_all(obj, iidStack);

   return ret;
}


CmsRet stl_containerInfoObject(_ContainerInfoObject *obj __attribute__((unused)),
                           const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}


CmsRet stl_containerStateObject(_ContainerStateObject *obj __attribute__((unused)),
                                const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}


CmsRet stl_containerNetworkObject(_ContainerNetworkObject *obj __attribute__((unused)),
                                  const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}


CmsRet stl_containerStatsObject(_ContainerStatsObject *obj __attribute__((unused)),
                                const InstanceIdStack *iidStack __attribute__((unused)))
{
   /* DONE.  This handler function does not need to do anything. */
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}


#endif /* DMP_X_BROADCOM_COM_CONTAINER_1 */
