/* 
* <:copyright-BRCM:2011:proprietary:standard
* 
*    Copyright (c) 2011 Broadcom 
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
* :>
*/


#ifdef DMP_DEVICE2_PERIODICSTATSADV_1

#include "cms.h"
#include "cms_util.h"
#include "cms_core.h"
#include "ssk.h"


void processSampleSetStatusChanged_dev2(CmsMsgHeader *msg)
{
   int found = 0;
   CmsRet ret;
   InstanceIdStack iidStack = EMPTY_INSTANCE_ID_STACK;
   Dev2SampleSetObject *pSmpsetObj = NULL;

   if ((ret = cmsLck_acquireLockWithTimeout(SSK_LOCK_TIMEOUT)) != CMSRET_SUCCESS)
   {
      cmsLog_error("could not get lock, ret=%d", ret);
      cmsLck_dumpInfo();
      return;
   }

   cmsLog_debug("calling cmsObjGet");

   INIT_INSTANCE_ID_STACK(&iidStack);
   while (!found && (cmsObj_getNext(MDMOID_DEV2_SAMPLE_SET, &iidStack, (void **) &pSmpsetObj)) == CMSRET_SUCCESS)
   {
      unsigned int id = PEEK_INSTANCE_ID(&iidStack); 
      if (id == msg->wordData)
      {
         cmsLog_debug("Same entry found, update sampleset entry");
         CMSMEM_REPLACE_STRING(pSmpsetObj->status, MDMVS_TRIGGER);
         cmsObj_set(pSmpsetObj, &iidStack);
         found = 1;
      }
      cmsObj_free((void **) &pSmpsetObj);
   } /* while */

   cmsLck_releaseLock();
   return;
}
#endif /* DMP_DEVICE2_PERIODICSTATSADV_1 */
