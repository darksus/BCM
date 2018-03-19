/*
 * $Id: robo_mem_garl_write.c,v 1.3 Broadcom SDK $
 * $Copyright: Copyright 2013 Broadcom Corporation.
 * This program is the proprietary software of Broadcom Corporation
 * and/or its licensors, and may only be used, duplicated, modified
 * or distributed pursuant to the terms and conditions of a separate,
 * written license agreement executed between you and Broadcom
 * (an "Authorized License").  Except as set forth in an Authorized
 * License, Broadcom grants no license (express or implied), right
 * to use, or waiver of any kind with respect to the Software, and
 * Broadcom expressly reserves all rights in and to the Software
 * and all intellectual property rights therein.  IF YOU HAVE
 * NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE
 * IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE
 * ALL USE OF THE SOFTWARE.  
 *  
 * Except as expressly set forth in the Authorized License,
 *  
 * 1.     This program, including its structure, sequence and organization,
 * constitutes the valuable trade secrets of Broadcom, and you shall use
 * all reasonable efforts to protect the confidentiality thereof,
 * and to use this information only in connection with your use of
 * Broadcom integrated circuit products.
 *  
 * 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS
 * PROVIDED "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES,
 * REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY,
 * OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY
 * DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
 * NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
 * ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
 * OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 * 
 * 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
 * BROADCOM OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL,
 * INCIDENTAL, SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER
 * ARISING OUT OF OR IN ANY WAY RELATING TO YOUR USE OF OR INABILITY
 * TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF
 * THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR USD 1.00,
 * WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING
 * ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.$
 *
 * ROBO ARL access through debug memory interface.
 */

#include <cdk/cdk_device.h>
#include <cdk/cdk_assert.h>
#include <cdk/cdk_debug.h>
#include <cdk/cdk_field.h>

#include <cdk/arch/robo_mem_regs.h>
#include <cdk/arch/robo_mem.h>

#define MAX_POLL 20

int
cdk_robo_mem_garl_write(int unit, uint32_t addr, uint32_t idx, void *vptr, int size)
{
    int ioerr = 0;
    int wsize = CDK_BYTES2WORDS(size);
    uint32_t *wdata = (uint32_t *)vptr;
    uint32_t data_reg, mem_type;
    ROBO_OTHER_TABLE_INDEXr_t tidx;
    ROBO_ARLA_RWCTLr_t arla_rwctl;
    int cnt;
    uint32_t data[6];

    if (size > (int)sizeof(data)) {
        return CDK_E_FAIL;
    }

    data_reg = addr & 0xffff;
    mem_type = (addr >> 16) & 0xff;

    /* Copy data into local buffer */
    CDK_MEMSET(data, 0, sizeof(data));
    for (cnt = 0; cnt < wsize; cnt++) {
        data[cnt] = wdata[cnt];
    }

    /* Write data registers */
    ioerr += cdk_robo_reg_write(unit, data_reg, data, 8);
    if (size > 8) {
        ioerr += cdk_robo_reg_write(unit, data_reg + 8, &data[2], 8);
        if (size > 16) {
            ioerr += cdk_robo_reg_write(unit, data_reg + 16, &data[4], 8);
        }
    }

    /* Set memory index */
    ROBO_OTHER_TABLE_INDEXr_SET(tidx, idx);
    ioerr += ROBO_WRITE_OTHER_TABLE_INDEXr(unit, tidx);

    /* Initialize read operation */
    ROBO_ARLA_RWCTLr_CLR(arla_rwctl);
    ROBO_ARLA_RWCTLr_TAB_RWf_SET(arla_rwctl, ROBO_MEM_OP_WRITE);
    ROBO_ARLA_RWCTLr_TAB_INDEXf_SET(arla_rwctl, mem_type);
    ROBO_ARLA_RWCTLr_ARL_STRTDNf_SET(arla_rwctl, 1);
    ioerr += ROBO_WRITE_ARLA_RWCTLr(unit, arla_rwctl);

    cnt = 0;
    while (cnt < MAX_POLL) {
        ioerr += ROBO_READ_ARLA_RWCTLr(unit, &arla_rwctl);
        if (ioerr == 0 && ROBO_ARLA_RWCTLr_ARL_STRTDNf_GET(arla_rwctl) == 0) {
            break;
        }
    }

    /* Check for errors */
    if (ioerr || cnt >= MAX_POLL) {
        CDK_ERR(("cdk_robo_mem_garl_write[%d]: error writing addr=%08"PRIx32"\n",
                 unit, addr));
        return CDK_E_FAIL;
    }

    /* Debug output */
    CDK_DEBUG_MEM(("cdk_robo_mem_garl_write[%d]: addr=0x%08"PRIx32" idx=%"PRIu32" data:",
                   unit, addr, idx));

    for (cnt = 0; cnt < wsize; cnt++) {
        CDK_DEBUG_MEM((" 0x%08"PRIx32, wdata[cnt]));
    }
    CDK_DEBUG_MEM(("\n"));

    return CDK_E_NONE;
}
