/***********************************************************************
 *
 *  Copyright (c) 2006-2008  Broadcom Corporation
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
#include <ctype.h>
#include <net/if.h>
#include <net/route.h>
#include <fcntl.h>
#include <unistd.h>

#include "cms_core.h"
#include "cms_util.h"
#include "rcl.h"
#include "rut_util.h"
#include "rut_ebtables.h"



CmsRet rcl_accessTimeRestrictionObject( _AccessTimeRestrictionObject *newObj,
                                 const _AccessTimeRestrictionObject *currObj,
                                 const InstanceIdStack *iidStack __attribute__((unused)),
                                 char **errorParam __attribute__((unused)),
                                 CmsRet *errorCode __attribute__((unused)))
{
   CmsRet ret = CMSRET_SUCCESS;
   InstanceIdStack iidStack1 = EMPTY_INSTANCE_ID_STACK;   
   _AccessTimeRestrictionObject *Obj = NULL;

   if ((ret = rut_validateObjects(newObj, currObj)) != CMSRET_SUCCESS)
   {
      return ret;
   }

   /* add and enable access time restriction, or enable existing access time restriction */
   if (ENABLE_NEW_OR_ENABLE_EXISTING(newObj, currObj))
   {
      cmsLog_debug("Adding access time restriction entry: username=%s, startTime=%s, endTime=%s, days=%s, MACAddress=%s", newObj->username, newObj->startTime, newObj->endTime, newObj->days, newObj->MACAddress);

      if (cmsUtl_isValidMacAddress(newObj->MACAddress) == FALSE)
      {
         cmsLog_error("Invalid MAC address");
         return CMSRET_INVALID_ARGUMENTS;		
      }

      if (currObj != NULL)
      {
         while (cmsObj_getNext(MDMOID_ACCESS_TIME_RESTRICTION, &iidStack1, (void **) &Obj) == CMSRET_SUCCESS)
         {
            if(Obj->username != NULL && cmsMdm_compareIidStacks(&iidStack1, iidStack))
            {
               if ( strcmp(Obj->username, newObj->username) == 0 ) 
               {
                  cmsObj_free((void **) &Obj);	
                  return CMSRET_INVALID_PARAM_VALUE;
               }
               else if (strcmp(Obj->startTime, newObj->startTime) == 0 && strcmp(Obj->endTime, newObj->endTime) == 0 && strcmp(Obj->days, newObj->days) == 0 && strcmp(Obj->MACAddress, newObj->MACAddress) == 0)
               {
                  cmsObj_free((void **) &Obj);	
                  return CMSRET_INVALID_ARGUMENTS;
               }
               cmsObj_free((void **) &Obj);	 
            }
         }
      }

      rut_accessTimeRestriction(newObj, TRUE);

   }

   /* remove ifc, or disable ifc*/
   else if (DELETE_OR_DISABLE_EXISTING(newObj, currObj))
   {
      cmsLog_debug("Deleting access time restriction entry: username=%s, startTime=%s, endTime=%s, days=%s, MACAddress=%s", currObj->username, currObj->startTime, currObj->endTime, currObj->days, currObj->MACAddress);

      rut_accessTimeRestriction(currObj, FALSE);
	
   }   
   
   return ret;

}



