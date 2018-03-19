/***********************************************************************
 *
 *  Copyright (c) 2013  Broadcom Corporation
 *  All Rights Reserved
 *
<:label-BRCM:2013:proprietary:standard

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
#ifdef DMP_DEVICE2_ADVANCEDFIREWALL_1

#include "rcl.h"
#include "cms_util.h"
#include "cms_qdm.h"
#include "rut_util.h"
#include "rut_iptables.h"

int rutIpt_doFirewallChainRule_dev2(const Dev2FirewallChainRuleObject *obj, UBOOL8 isEnable)
{
   char cmd[BUFLEN_256]={0};
   char srcIP[CMS_IPADDR_LENGTH+BUFLEN_8]={0};
   char srcPort[BUFLEN_16]={0};
   char srcIf[CMS_IFNAME_LENGTH+BUFLEN_8]={0};
   char dstIP[CMS_IPADDR_LENGTH+BUFLEN_8]={0};
   char dstPort[BUFLEN_16]={0};
   char dstIf[CMS_IFNAME_LENGTH+BUFLEN_8]={0};
   char proto[BUFLEN_16]={0};
   char target[BUFLEN_8]={0};
   int ipver = 4;

   cmsLog_debug("enter");

   if (obj->IPVersion !=4 && obj->IPVersion !=6)
   {
      cmsLog_notice("IPVersion is neither 4 nor 6, use 4 by default");
   }
   else
   {
      ipver = obj->IPVersion;
   }

   if (!cmsUtl_strcmp(obj->target, MDMVS_DROP))
   {
      cmsUtl_strncpy(target, "DROP", sizeof(target));
   }
   else if (!cmsUtl_strcmp(obj->target, MDMVS_ACCEPT))
   {
      cmsUtl_strncpy(target, "ACCEPT", sizeof(target));
   }
   else
   {
      cmsLog_error("target is neither DROP nor ACCEPT");
      return 1;
   }

   if (!IS_EMPTY_STRING(obj->sourceIP))
   {
      sprintf(srcIP, "-s %s", obj->sourceIP);
   }

   if (!IS_EMPTY_STRING(obj->destIP))
   {
      sprintf(dstIP, "-d %s", obj->destIP);
   }

   if (!IS_EMPTY_STRING(obj->sourceInterface))
   {
      sprintf(srcIf, "-i %s", obj->sourceInterface);
   }

   if (!IS_EMPTY_STRING(obj->destInterface))
   {
      sprintf(dstIf, "-o %s", obj->destInterface);
   }

   if (obj->sourcePort > 0)
   {
      sprintf(srcPort, "--sport %d", obj->sourcePort);
   }

   if (obj->destPort > 0)
   {
      sprintf(dstPort, "--dport %d", obj->destPort);
   }

   if (obj->protocol > 0)
   {
      sprintf(proto, "-p %d", obj->protocol);
   }

   sprintf(cmd, "%s -%c FORWARD %s %s %s %s %s %s %s -j %s", (ipver==4)?"iptables":"ip6tables", isEnable?'I':'D', proto, srcIP, srcPort, dstIP, dstPort, srcIf, dstIf, target);

   cmsLog_debug("exit: %s", cmd);
   rut_doSystemAction("setDefaultPolicy", cmd);

   return 0;
}

int rutfirewall_enableChain_dev2(const InstanceIdStack *chainIidStack, UBOOL8 isEnable)
{
   /* walk through all rule objs and do configuration */
   Dev2FirewallChainRuleObject *ruleobj = NULL;
   InstanceIdStack ruleIidStack = EMPTY_INSTANCE_ID_STACK;

   cmsLog_debug("enter");
   while (cmsObj_getNextInSubTreeFlags(MDMOID_DEV2_FIREWALL_CHAIN_RULE, 
                     chainIidStack, &ruleIidStack, 
                     OGF_NO_VALUE_UPDATE, (void **)&ruleobj) == CMSRET_SUCCESS)
   {
      rutIpt_doFirewallChainRule_dev2(ruleobj, isEnable);
      cmsObj_free((void **) &ruleobj);
   }

   return 0;
}

int rutfirewall_setDefaultPolicy_dev2(const char *policy, UBOOL8 isEnable)
{
   char cmd[BUFLEN_128];

   cmsLog_debug("enter: policy<%s>", policy);
   if (!cmsUtl_strcmp(policy, MDMVS_DROP))
   {
      sprintf(cmd, "iptables -%c FORWARD -j %s", isEnable?'A':'D', "DROP");
   }
   else if (!cmsUtl_strcmp(policy, MDMVS_ACCEPT))
   {
      sprintf(cmd, "iptables -%c FORWARD -j %s", isEnable?'A':'D', "ACCEPT");
   }
   else
   {
      cmsLog_error("no support policy<%s>", policy);
      return 1;
   }
   
   rut_doSystemAction("setDefaultPolicy", cmd);

   return 0;
}

int rutfirewall_enableFirewall_dev2(const char *level, UBOOL8 isEnable)
{
   /*
    * 1. configure defaultpolicy
    * 2. call rutfirewall_enableChain_dev2 to configure all rules
    */
   Dev2FirewallLevelObject *levelobj = NULL;
   Dev2FirewallChainObject *chainobj = NULL;
   MdmPathDescriptor levelPathDesc;
   MdmPathDescriptor chainPathDesc;

   cmsLog_debug("level<%s> isEnable<%d>", level, isEnable);

   INIT_PATH_DESCRIPTOR(&levelPathDesc);
   if (cmsMdm_fullPathToPathDescriptor(level, &levelPathDesc) != CMSRET_SUCCESS)
   {
      cmsLog_error("cmsMdm_fullPathToPathDescriptor fails for %s", level);
      return 1;
   }

   if (cmsObj_get(levelPathDesc.oid, &levelPathDesc.iidStack, 0, (void **)&levelobj) != CMSRET_SUCCESS)
   {
      cmsLog_error("cannot get levelobj");
      return 1;
   }

   rutfirewall_setDefaultPolicy_dev2(levelobj->defaultPolicy, isEnable);

   INIT_PATH_DESCRIPTOR(&chainPathDesc);
   if (cmsMdm_fullPathToPathDescriptor(levelobj->chain, &chainPathDesc) != CMSRET_SUCCESS)
   {
      cmsLog_error("cmsMdm_fullPathToPathDescriptor fails for %s", levelobj->chain);
      cmsObj_free((void **) &levelobj);
      return 1;
   }

   if (cmsObj_get(chainPathDesc.oid, &chainPathDesc.iidStack, 0, (void **)&chainobj) != CMSRET_SUCCESS)
   {
      cmsLog_error("cannot get chainobj");
      cmsObj_free((void **) &levelobj);
      return 1;
   }

   if (chainobj->enable)
   {
      rutfirewall_enableChain_dev2(&chainPathDesc.iidStack, isEnable);
   }

   cmsObj_free((void **) &levelobj);
   cmsObj_free((void **) &chainobj);

   return 0;
}

/*
 * To determine if this level object is active:
 * 1. firewall.enable == TRUE
 * 2. firewall.config == advanced
 * 3. firewall.advancedLevel matches this level path
 */
static UBOOL8 isLevelObjActive(const InstanceIdStack *leveliidStack)
{
   InstanceIdStack iidStackFirewall = EMPTY_INSTANCE_ID_STACK;
   Dev2FirewallObject *firewallobj = NULL;
   UBOOL8 isActive = FALSE;

   if (cmsObj_get(MDMOID_DEV2_FIREWALL, &iidStackFirewall, 0, (void **)&firewallobj) != CMSRET_SUCCESS)
   {
      cmsLog_error("fail to get firewall object");
      return FALSE;
   }

   if (firewallobj->enable)
   {
      if (!cmsUtl_strcmp(firewallobj->config, MDMVS_ADVANCED))
      {
         char *levelFullPath = NULL;
         MdmPathDescriptor levelPathDesc;

         memset(&levelPathDesc, 0, sizeof(MdmPathDescriptor));
         levelPathDesc.oid = MDMOID_DEV2_FIREWALL_LEVEL;
         levelPathDesc.iidStack = *leveliidStack;

         if (cmsMdm_pathDescriptorToFullPathNoEndDot(&levelPathDesc, &levelFullPath) != CMSRET_SUCCESS)
         {
            cmsLog_error("cmsMdm_pathDescriptorToFullPathNoEndDot error");
            goto out;
         }

         if (!cmsUtl_strcmp(levelFullPath, firewallobj->advancedLevel))
         {
            isActive = TRUE;
         }

         CMSMEM_FREE_BUF_AND_NULL_PTR(levelFullPath);
      }
   }

out:
   cmsObj_free((void **) &firewallobj);

   return isActive;
}

/* FIXME: targetchain is not supported!! */
/*
 * To determine if this chain object is active:
 * 1. firewall.enable == TRUE
 * 2. firewall.config == advanced
 * 3. firewall.advancedLevel.chain matches this chain path
 */
static UBOOL8 isChainObjActive(const InstanceIdStack *chainiidStack)
{
   InstanceIdStack iidStackFirewall = EMPTY_INSTANCE_ID_STACK;
   Dev2FirewallObject *firewallobj = NULL;
   UBOOL8 isActive = FALSE;

   if (cmsObj_get(MDMOID_DEV2_FIREWALL, &iidStackFirewall, 0, (void **)&firewallobj) != CMSRET_SUCCESS)
   {
      cmsLog_error("fail to get firewall object");
      return FALSE;
   }

   if (firewallobj->enable)
   {
      if (!cmsUtl_strcmp(firewallobj->config, MDMVS_ADVANCED))
      {
         Dev2FirewallLevelObject *levelobj = NULL;
         char *chainFullPath = NULL;
         MdmPathDescriptor chainPathDesc;
         MdmPathDescriptor levelPathDesc;

         memset(&chainPathDesc, 0, sizeof(MdmPathDescriptor));
         chainPathDesc.oid = MDMOID_DEV2_FIREWALL_CHAIN;
         chainPathDesc.iidStack = *chainiidStack;

         if (cmsMdm_pathDescriptorToFullPathNoEndDot(&chainPathDesc, &chainFullPath) != CMSRET_SUCCESS)
         {
            cmsLog_error("cmsMdm_pathDescriptorToFullPathNoEndDot error");
            goto out;
         }

         INIT_PATH_DESCRIPTOR(&levelPathDesc);
         if (cmsMdm_fullPathToPathDescriptor(firewallobj->advancedLevel, &levelPathDesc) != CMSRET_SUCCESS)
         {
            cmsLog_error("cmsMdm_fullPathToPathDescriptor fails for %s", firewallobj->advancedLevel);
            CMSMEM_FREE_BUF_AND_NULL_PTR(chainFullPath);
            return FALSE;
         }

         if (cmsObj_get(levelPathDesc.oid, &levelPathDesc.iidStack, 0, (void **)&levelobj) != CMSRET_SUCCESS)
         {
            cmsLog_error("cannot get levelobj");
            CMSMEM_FREE_BUF_AND_NULL_PTR(chainFullPath);
            return FALSE;
         }

         if (!cmsUtl_strcmp(chainFullPath, levelobj->chain))
         {
            isActive = TRUE;
         }

         CMSMEM_FREE_BUF_AND_NULL_PTR(chainFullPath);
         cmsObj_free((void **)&levelobj);
      }
   }

out:
   cmsObj_free((void **) &firewallobj);

   return isActive;
}

/* FIXME: targetchain is not supported!! */
static UBOOL8 isRuleObjActive(const InstanceIdStack *ruleiidStack)
{
   UBOOL8 isActive = FALSE;
   InstanceIdStack chainIidStack = *ruleiidStack;
   Dev2FirewallChainObject *chainobj = NULL;

   if (cmsObj_getAncestorFlags(MDMOID_DEV2_FIREWALL_CHAIN,
                                 MDMOID_DEV2_FIREWALL_CHAIN_RULE,
                                 &chainIidStack,
                                 OGF_NO_VALUE_UPDATE,
                                 (void **) &chainobj) != CMSRET_SUCCESS)
   {
      cmsLog_error("cannot get chain obj");
      return FALSE;
   }

   if (chainobj->enable)
   {
      isActive = isChainObjActive(&chainIidStack);
   }

   cmsObj_free((void **) &chainobj);

   return isActive;
}

static CmsRet getChainPath(char *chainpath, UINT32 pathLen)
{
   InstanceIdStack iidStack = EMPTY_INSTANCE_ID_STACK;
   Dev2FirewallChainObject *chainobj = NULL;
   CmsRet ret = CMSRET_SUCCESS;

   cmsLog_debug("enter");

   if ((ret = cmsObj_addInstance(MDMOID_DEV2_FIREWALL_CHAIN, &iidStack)) != CMSRET_SUCCESS)
   {
      cmsLog_error("Failed to add Chain Instance, ret = %d", ret);
      return ret;
   }

   if ((ret = cmsObj_get(MDMOID_DEV2_FIREWALL_CHAIN, &iidStack, 0, (void **) &chainobj)) != CMSRET_SUCCESS)
   {
      cmsLog_error("Failed to get chainobj, ret = %d", ret);
      cmsObj_deleteInstance(MDMOID_DEV2_FIREWALL_CHAIN, &iidStack);
      return ret;
   }

   ret = cmsObj_set(chainobj, &iidStack);
   cmsObj_free((void **) &chainobj);

   if (ret != CMSRET_SUCCESS)
   {
      cmsLog_error("Failed to set chainobj. ret=%d", ret);
      cmsObj_deleteInstance(MDMOID_DEV2_FIREWALL_CHAIN, &iidStack);
      return ret;
   }

   {
      char *fullPath=NULL;
      MdmPathDescriptor chainPathDesc;

      memset(&chainPathDesc, 0, sizeof(MdmPathDescriptor));
      chainPathDesc.oid = MDMOID_DEV2_FIREWALL_CHAIN;
      chainPathDesc.iidStack = iidStack;
      if ((ret = cmsMdm_pathDescriptorToFullPathNoEndDot(&chainPathDesc, &fullPath)) != CMSRET_SUCCESS)
      {
         cmsLog_error("cmsMdm_pathDescriptorToFullPathNoEndDot returns error. ret=%d", ret);
         cmsObj_deleteInstance(MDMOID_DEV2_FIREWALL_CHAIN, &iidStack);
         return ret;
      }

      cmsUtl_strncpy(chainpath, fullPath, pathLen);

      CMSMEM_FREE_BUF_AND_NULL_PTR(fullPath);
   }

   cmsLog_debug("chainpath<%s>", chainpath);
   return ret;
}

CmsRet rcl_dev2FirewallObject( _Dev2FirewallObject *newObj,
                const _Dev2FirewallObject *currObj,
                const InstanceIdStack *iidStack,
                char **errorParam,
                CmsRet *errorCode)
{
   CmsRet ret = CMSRET_SUCCESS;

   if (newObj && newObj->enable)
   {
      if (currObj)
      {
         if (currObj->enable == FALSE)
         {
            cmsLog_debug("turn on firewall");
            /* Firewall is turned on */
            if (cmsUtl_strcmp(newObj->config, MDMVS_ADVANCED))
            {
               cmsLog_notice("Only advanced firewall is supported now");
               return ret;
            }

            rutIpt_insertIpModules();
#ifdef SUPPORT_IPV6            
            rutIpt_insertIpModules6();
#endif            
            rutfirewall_enableFirewall_dev2(newObj->advancedLevel, TRUE);
         }
         else if (cmsUtl_strcmp(newObj->config, currObj->config))
         {
            cmsLog_notice("runtime change config is not supported");
         }
         else if (cmsUtl_strcmp(newObj->advancedLevel, currObj->advancedLevel))
         {
            cmsLog_notice("runtime change advancedLevel is not supported");
         }
      }
      else
      {
         if (cmsUtl_strcmp(newObj->config, MDMVS_ADVANCED))
         {
            cmsLog_notice("Only advanced firewall is supported now");
            return ret;
         }

         cmsLog_debug("bootup with firewall on");
         rutIpt_insertIpModules();
#ifdef SUPPORT_IPV6            
         rutIpt_insertIpModules6();
#endif     
      }
   }
   else
   {
      if (currObj && (currObj->enable == TRUE))
      {
         /* Firewall is turned off */
         rutfirewall_enableFirewall_dev2(newObj->advancedLevel, FALSE);
      }
   }

   return ret;
}  /* rcl_dev2FirewallObject */

CmsRet rcl_dev2FirewallLevelObject( _Dev2FirewallLevelObject *newObj,
                const _Dev2FirewallLevelObject *currObj,
                const InstanceIdStack *iidStack,
                char **errorParam,
                CmsRet *errorCode)
{
   CmsRet ret = CMSRET_SUCCESS;

   if (ADD_NEW(newObj, currObj))
   {
      if (IS_EMPTY_STRING(newObj->chain))
      {
         /* 
          * When level object is created, an associated chain object needs to be
          * automatically created. 
          */
         char chainPath[MDM_SINGLE_FULLPATH_BUFLEN];

         if ((ret = getChainPath(chainPath, sizeof(chainPath))) == CMSRET_SUCCESS)
         {
            CMSMEM_REPLACE_STRING_FLAGS(newObj->chain, chainPath, mdmLibCtx.allocFlags);
         }
      }
   }

   /* level object can take action of default policy only if it is active */
   if (isLevelObjActive(iidStack))
   {
      cmsLog_debug("level obj active");
      if (newObj)
      {
         if (currObj)
         {
            rutfirewall_setDefaultPolicy_dev2(currObj->defaultPolicy, FALSE);
         }

         rutfirewall_setDefaultPolicy_dev2(newObj->defaultPolicy, TRUE);
      }
      else
      {
         rutfirewall_setDefaultPolicy_dev2(currObj->defaultPolicy, FALSE);
      }
   }

   return ret;
}  /* rcl_dev2FirewallLevelObject */

CmsRet rcl_dev2FirewallChainObject( _Dev2FirewallChainObject *newObj,
                const _Dev2FirewallChainObject *currObj,
                const InstanceIdStack *iidStack,
                char **errorParam,
                CmsRet *errorCode)
{
   CmsRet ret = CMSRET_SUCCESS;

   /* 
    * Chain object can take action based on its child rule objects 
    * only if this chain object is active 
    */
   if (ADD_NEW(newObj, currObj))
   {
      return ret;
   }

   if (isChainObjActive(iidStack))
   {
      cmsLog_debug("chain active");
      if (ENABLE_NEW_OR_ENABLE_EXISTING(newObj, currObj))
      {
         rutfirewall_enableChain_dev2(iidStack, TRUE);
      }
      else if (DELETE_OR_DISABLE_EXISTING(newObj, currObj))
      {
         rutfirewall_enableChain_dev2(iidStack, FALSE);
      }
   }

   return ret;
}  /* rcl_dev2FirewallChainObject */

CmsRet rcl_dev2FirewallChainRuleObject( _Dev2FirewallChainRuleObject *newObj,
                const _Dev2FirewallChainRuleObject *currObj,
                const InstanceIdStack *iidStack,
                char **errorParam,
                CmsRet *errorCode)
{
   CmsRet ret = CMSRET_SUCCESS;

   /* Rule object can take action only if parent Chain object is active */
   if (isRuleObjActive(iidStack))
   {
      if (ENABLE_NEW_OR_ENABLE_EXISTING(newObj, currObj))
      {
         rutIpt_doFirewallChainRule_dev2(newObj, TRUE);
         CMSMEM_REPLACE_STRING_FLAGS(newObj->status, MDMVS_ENABLED, mdmLibCtx.allocFlags);
      }
      else if (POTENTIAL_CHANGE_OF_EXISTING(newObj, currObj))
      {
         rutIpt_doFirewallChainRule_dev2(currObj, FALSE);
         rutIpt_doFirewallChainRule_dev2(newObj, TRUE);
      }
      else if (DELETE_OR_DISABLE_EXISTING(newObj, currObj))
      {
         rutIpt_doFirewallChainRule_dev2(currObj, FALSE);

         if (newObj != NULL)
         {
            CMSMEM_REPLACE_STRING_FLAGS(newObj->status, MDMVS_DISABLED, mdmLibCtx.allocFlags);
         }
      }
   }
   else
   {
      if (newObj != NULL)
      {
         CMSMEM_REPLACE_STRING_FLAGS(newObj->status, MDMVS_DISABLED, mdmLibCtx.allocFlags);
      }
   }

   return ret;
}  /* rcl_dev2FirewallChainRuleObject */




CmsRet rcl_dev2FirewallExceptionObject(_Dev2FirewallExceptionObject *newObj,
				const _Dev2FirewallExceptionObject *currObj,
				const InstanceIdStack *iidStack __attribute__((unused)),
				char **errorParam __attribute__((unused)),
				CmsRet *errorCode __attribute__((unused)))
{
   CmsRet ret = CMSRET_SUCCESS;

   if (CMSRET_SUCCESS != (ret = rut_validateObjects(newObj, currObj))) {
	  return ret;
   }

   return ret;
} /* rcl_dev2FirewallExceptionObject */


CmsRet rcl_dev2FirewallExceptionRuleObject(_Dev2FirewallExceptionRuleObject *newObj,
				const _Dev2FirewallExceptionRuleObject *currObj,
				const InstanceIdStack *iidStack,
				char **errorParam __attribute__((unused)),
				CmsRet *errorCode __attribute__((unused)))
{
   CmsRet ret = CMSRET_SUCCESS;
   InstanceIdStack parentIidStack = *iidStack;
   _Dev2FirewallExceptionObject *exceptionObj = NULL;
   char ifName[CMS_IFNAME_LENGTH]={0};
   char ipvxServiceStatus[BUFLEN_32]={0};
   UINT32 ipvx=0;
   UBOOL8 prevHideObjectsPendingDelete;

   cmsLog_debug("Entered: newObj=%p currObj=%p iidStack=%s",
                newObj, currObj, cmsMdm_dumpIidStack(iidStack));


   /* if this is not modem bootup or new object creation (during these events,
    * currObj==NULL), we need the ifName and possibly the ipvxServiceStatus.
    * Get those first so the rest of the logic is easier to follow.
    */
   if (currObj != NULL)
   {
      /* in case this is a delete, we still want to see our ancestor obj */
      prevHideObjectsPendingDelete = mdmLibCtx.hideObjectsPendingDelete;
      mdmLibCtx.hideObjectsPendingDelete = FALSE;

      // the interface name for this rule is in the ancestor obj
      if ((ret = cmsObj_getAncestor(MDMOID_DEV2_FIREWALL_EXCEPTION,
                                    MDMOID_DEV2_FIREWALL_EXCEPTION_RULE,
                                    &parentIidStack,
                                (void **) &exceptionObj)) != CMSRET_SUCCESS)
      {
         cmsLog_error("Failed to get Dev2FirewallExceptionObject. ret=%d", ret);
      }
      else
      {
         /* convert IP interface fullpath to ifName */
         ret = qdmIntf_fullPathToIntfnameLocked_dev2(exceptionObj->IPInterface,
                                                     ifName);
         if (ret != CMSRET_SUCCESS)
         {
            cmsLog_error("Failed to get ifName on %s. ret=%d",
                         exceptionObj->IPInterface  ,ret);
         }
         else
         {
            /* got ifName, now if this could be an activate, get ipvxServiceStatus */
            if (newObj && newObj->enable)
            {
               ipvx = (*(newObj->IPVersion) == '4') ? CMS_AF_SELECT_IPV4 :
                                                      CMS_AF_SELECT_IPV6;

               qdmIpIntf_getIpvxServiceStatusFromFullPathLocked_dev2(
                                                  exceptionObj->IPInterface,
                                                  ipvx,
                                                  ipvxServiceStatus,
                                                  sizeof(ipvxServiceStatus));
            }
         }
         /* we are done with this object. free it now before we forget. */
         cmsObj_free((void **) &exceptionObj);
      }

      mdmLibCtx.hideObjectsPendingDelete = prevHideObjectsPendingDelete;

      if (ret != CMSRET_SUCCESS)
      {
         return ret;
      }
   }


   /*
    * By checking for currObj != NULL, we are saying we don't execute
    * this block if this function is called during modem bootup
    * and for object creation.  (During these two conditions, the
    * currObj is NULL.)
    */
   if (newObj != NULL && currObj != NULL && newObj->enable)
   {
      cmsLog_debug("Enable IP filter In on %s, ipvx=0x%x ServiceStatus=%s, currObj=%p",
                   ifName, ipvx, ipvxServiceStatus, currObj);

      /* XXX this RCL does not handle edits of existing firewall exceptions.
       * It would have to delete the existing one, and then add the new one
       * But how to add it at the exact same place as before?  iptables can
       * only insert at head or at end.  Maybe for firewall exceptions it
       * does not matter?  (always insert at head)
       */

      /* only need to check validity and duplicates if object changed,
       * usually from initially created obj to filled in obj by WebUI.
       */
      if (!rutIpt_isFirewallExceptionSame_dev2(newObj, currObj))
      {
         if (!rutIpt_isFirewallExceptionValid_dev2(newObj))
         {
            return CMSRET_INVALID_ARGUMENTS;
         }

         if (rutIpt_isDuplicateFirewallException_dev2(newObj, iidStack))
         {
            return CMSRET_INVALID_ARGUMENTS;
         }
      }

      /*
       * Add the FirewallException rule if the IP interface state
       * is SERVICESTARTING (because in rut2_ipservicecfg, we do the
       * firewall rules as soon as layer 2 link is up) or SERVICEUP (in
       * case user adds a rule after the service has already gone up.)
       */
       if(!cmsUtl_strcmp(ipvxServiceStatus, MDMVS_SERVICESTARTING) ||
          !cmsUtl_strcmp(ipvxServiceStatus, MDMVS_SERVICEUP))
       {
          cmsLog_debug("Adding firewall exception on %s", ifName);
          rutIpt_doFirewallExceptionRule_dev2(newObj,ifName,TRUE);
       }
   }

   else if (DELETE_OR_DISABLE_EXISTING(newObj, currObj))
   {
      cmsLog_debug("Delete/Disable IP filter In on %s, filterName=%s",
                   ifName, currObj->filterName);

      /*
       * The set on the object from dalSec_addIpFilter could have failed.
       * In that case, filterName would be NULL, so don't take
       * any action since it was not put there in the first place.
       */
      if(currObj->filterName != NULL && !IS_EMPTY_STRING(ifName) )
      {
         cmsLog_debug("Deleting firewall exception on %s", ifName);
         rutIpt_doFirewallExceptionRule_dev2(currObj,ifName,FALSE);
      }
   }

   return ret;

} /* rcl_dev2FirewallExceptionRuleObject */

#endif /* DMP_DEVICE2_SIMPLEFIREWALL_1 */
#endif /* DMP_DEVICE2_BASELINE_1 */

