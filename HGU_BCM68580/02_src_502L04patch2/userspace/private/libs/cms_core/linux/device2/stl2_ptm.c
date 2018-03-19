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

#ifdef DMP_DEVICE2_PTMLINK_1

#include "stl.h"
#include "cms_util.h"
#include "rut_system.h"
#include "rut2_ptm.h"
#include "rut_util.h"


/*!\file stl2_ptm.c
 * \brief This file contains device 2 device.ptm. statistics objects related functions.
 *
 */

CmsRet stl_dev2PtmObject(_Dev2PtmObject *obj __attribute__((unused)), const InstanceIdStack *iidStack __attribute__((unused)))
{
   return CMSRET_SUCCESS_OBJECT_UNCHANGED;
}

CmsRet stl_dev2PtmLinkObject(_Dev2PtmLinkObject *obj,
                     const InstanceIdStack *iidStack __attribute__((unused)))
{
   /*
    * When DSL line comes up, it reports whether it detected ATM or PTM.
    * This info is read by ssk, which propagates that info up the intf stack.
    * Therefore, PTM link status is *set* by ssk and handled in the RCL handler
    * function.
    */


   /* Calculate and return the TR181 LastChange */
   IF_OBJ_NOT_NULL_GET_LASTCHANGE(obj);

   return CMSRET_SUCCESS;
}

CmsRet stl_dev2PtmLinkStatsObject(_Dev2PtmLinkStatsObject *obj, const InstanceIdStack *iidStack) 
{
   Dev2PtmLinkObject *ptmObj;
   UBOOL8 reset = FALSE;

   if (cmsObj_get(MDMOID_DEV2_PTM_LINK,iidStack,0,(void **)&ptmObj) == CMSRET_SUCCESS)
   {
      if ((obj != NULL) && (!cmsUtl_strcmp(ptmObj->status, MDMVS_UP)))
      {
         /* clear stats not requested, and the link is up, go at the stats */
         rutptm_getLinkStats_dev2(obj,ptmObj->name,ptmObj->X_BROADCOM_COM_PTMPortId,reset);
      }
      else
      {
         /* request for reset of stats received or link is simple down (require per TR181) */
         reset = TRUE;
         rutptm_getLinkStats_dev2(obj,ptmObj->name,ptmObj->X_BROADCOM_COM_PTMPortId,reset);
      }
      cmsObj_free((void **) &ptmObj);
      return CMSRET_SUCCESS;
   }
   else
   {
      return CMSRET_SUCCESS_OBJECT_UNCHANGED;
   }
}

#endif   /* DMP_DEVICE2_PTMLINK_1 */

#endif /* DMP_DEVICE2_BASELINE_1 */
