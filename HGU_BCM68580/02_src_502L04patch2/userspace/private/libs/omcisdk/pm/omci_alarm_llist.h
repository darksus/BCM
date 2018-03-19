/***********************************************************************
 *
 *  Copyright (c) 2014 Broadcom
 *  All Rights Reserved
 *
<:label-BRCM:2012:proprietary:omcid

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

#ifndef __OMCI_ALARM_LLIST_H__
#define __OMCI_ALARM_LLIST_H__

/*!\file omci_alarm_llist.h
 * Alarm link list functions for GPON Performance Monitoring functionality.
 *
 */


#include "os_defs.h"
#include "omcipm_api.h"
#include "omci_pm.h"

UINT32 omci_alarm_create(
    BCM_COMMON_LLIST *pHead,
    UINT16 class_ID,
    UINT16 obj_ID,
    UINT16 alarmBitmap);

UINT32 omci_alarm_delete(
    BCM_COMMON_LLIST *pHead,
    UINT16 class_ID,
    UINT16 obj_ID);

BCM_OMCIPM_ALARM_ENTRY* omci_alarm_getByIndex(
    const BCM_COMMON_LLIST *pHead,
    UINT16 alarmIndex);

BCM_OMCIPM_ALARM_ENTRY* omci_alarm_get(
    const BCM_COMMON_LLIST *pHead,
    UINT16 class_ID,
    UINT16 obj_ID);

UINT32 omci_alarm_set(
    const BCM_COMMON_LLIST *pHead,
    UINT16 class_ID,
    UINT16 obj_ID,
    UINT16 alarmBitmap);

void omci_alarm_releaseByHeadList(BCM_COMMON_LLIST *pHead);

BCM_COMMON_LLIST* omci_alarm_getFrozenListPtr(void);

BCM_COMMON_LLIST* omci_alarm_getNonTcaListPtr(void);

UINT32 omci_alarm_timer_create(
    ALARM_TIMER_TYPE timerType,
    ALARM_CB_FUNC cbFunction,
    ALARM_TIMER_FREQ alarmFreq);

UINT32 omci_alarm_timer_delete(
    ALARM_TIMER_TYPE timerType,
    ALARM_TIMER_FREQ alarmFreq);

BCM_OMCIPM_ALARM_TIMER_ENTRY* omci_alarm_timer_get(
    ALARM_TIMER_TYPE timerType,
    ALARM_TIMER_FREQ alarmFreq);

UINT32 omci_alarm_timer_set(
    ALARM_TIMER_TYPE timerType,
    ALARM_CB_FUNC cbFunction,
    ALARM_TIMER_FREQ alarmFreq);

 void omci_alarm_timer_releaseByHeadList(
    BCM_COMMON_LLIST *pHead);

BCM_COMMON_LLIST* omci_alarm_timer_getListPtr(
    ALARM_TIMER_FREQ freq);


#endif  // __OMCI_ALARM_LLIST_H__
