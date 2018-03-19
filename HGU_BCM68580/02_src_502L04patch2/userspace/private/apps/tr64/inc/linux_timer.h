/*****************************************************************************
//
// Copyright (c) 2006-2012 Broadcom Corporation
// All Rights Reserved
//
// <:label-BRCM:2012:proprietary:standard
// 
//  This program is the proprietary software of Broadcom and/or its
//  licensors, and may only be used, duplicated, modified or distributed pursuant
//  to the terms and conditions of a separate, written license agreement executed
//  between you and Broadcom (an "Authorized License").  Except as set forth in
//  an Authorized License, Broadcom grants no license (express or implied), right
//  to use, or waiver of any kind with respect to the Software, and Broadcom
//  expressly reserves all rights in and to the Software and all intellectual
//  property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE
//  NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY
//  BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE.
// 
//  Except as expressly set forth in the Authorized License,
// 
//  1. This program, including its structure, sequence and organization,
//     constitutes the valuable trade secrets of Broadcom, and you shall use
//     all reasonable efforts to protect the confidentiality thereof, and to
//     use this information only in connection with your use of Broadcom
//     integrated circuit products.
// 
//  2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
//     AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR
//     WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
//     RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND
//     ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT,
//     FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR
//     COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE
//     TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE OR
//     PERFORMANCE OF THE SOFTWARE.
// 
//  3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR
//     ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
//     INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY
//     WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN
//     IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES;
//     OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE
//     SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS
//     SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY
//     LIMITED REMEDY.
// :>
//
******************************************************************************
//
//  Filename:       linux_timer.h
//
******************************************************************************/

#ifndef _linux_timer_h_
#define _linux_timer_h_

#if defined(linux)


timer_t enqueue_event(struct itimerspec *value, event_callback_t func, void *arg);

void init_event_queue(int);
int timer_create(clockid_t         clock_id, /* clock ID (always CLOCK_REALTIME) */
                 struct sigevent * evp,      /* user event handler */
                 timer_t *         pTimer    /* ptr to return value */);
int timer_settime
(
    timer_t                   timerid, /* timer ID */
    int                       flags,   /* absolute or relative */
    const struct itimerspec * value,   /* time to be set */
    struct itimerspec *       ovalue   /* previous time set (NULL=no result) */
);

int timer_connect(timer_t     timerid, /* timer ID timer*/
                  void (*routine)(timer_t, int), /* user routine */
                  uintptr_t arg      /* user argument */);

int timer_delete(timer_t timerid /* timer ID */);

#endif /* linux */

#endif /* linux_timer_h_ */
