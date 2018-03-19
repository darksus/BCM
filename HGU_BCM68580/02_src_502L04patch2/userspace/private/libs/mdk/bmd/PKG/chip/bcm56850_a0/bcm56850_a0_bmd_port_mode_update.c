#include <bmd_config.h>
#if CDK_CONFIG_INCLUDE_BCM56850_A0 == 1

/*
 * $Id: bcm56850_a0_bmd_port_mode_update.c,v 1.2 Broadcom SDK $
 * 
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
 */

#include <bmd/bmd.h>
#include <bmd/bmd_device.h>

#include <bmdi/bmd_link.h>
#include <bmdi/arch/xgsm_led.h>

#include <cdk/chip/bcm56850_a0_defs.h>
#include <cdk/cdk_device.h>
#include <cdk/cdk_error.h>

#include "bcm56850_a0_bmd.h"
#include "bcm56850_a0_internal.h"

#define LED_DATA_OFFSET 0x80

int
bcm56850_a0_port_enable_set(int unit, int port, int enable)
{
    int ioerr = 0;
    int rv = CDK_E_NONE;
    int lport;
    XLMAC_CTRLr_t xlmac_ctrl;
    EPC_LINK_BMAPm_t epc_link;
    uint32_t pbm[PBM_LPORT_WORDS];

    lport = P2L(unit, port);

    /* Update XMAC */
    ioerr += READ_XLMAC_CTRLr(unit, port, &xlmac_ctrl);
    XLMAC_CTRLr_RX_ENf_SET(xlmac_ctrl, enable);
    XLMAC_CTRLr_SOFT_RESETf_SET(xlmac_ctrl, !enable);
    ioerr += WRITE_XLMAC_CTRLr(unit, port, xlmac_ctrl);

    /* Update link map */
    ioerr += READ_EPC_LINK_BMAPm(unit, 0, &epc_link);
    EPC_LINK_BMAPm_PORT_BITMAPf_GET(epc_link, pbm);
    if (enable) {
        PBM_PORT_ADD(pbm, lport);
    } else {
        PBM_PORT_REMOVE(pbm, lport);
    }
    EPC_LINK_BMAPm_PORT_BITMAPf_SET(epc_link, pbm);
    ioerr += WRITE_EPC_LINK_BMAPm(unit, 0, epc_link);

    /* Let PHYs know the new MAC state */
    rv = bmd_phy_notify_mac_enable(unit, port, enable);

    return ioerr ? CDK_E_IO : rv;
}

int
bcm56850_a0_bmd_port_mode_update(int unit, int port)
{
    int rv = CDK_E_NONE;
    int ioerr = 0;
    int led_flags;
    int status_change;
    int autoneg;
    int mac_en;
    bmd_port_mode_t mode;
    uint32_t flags;

    BMD_CHECK_UNIT(unit);
    BMD_CHECK_PORT(unit, port);

    rv = bmd_link_update(unit, port, &status_change);
    if (CDK_SUCCESS(rv) && status_change) {
        rv = bmd_phy_autoneg_get(unit, port, &autoneg);
        if (CDK_SUCCESS(rv) && autoneg) {
            rv = bcm56850_a0_bmd_port_mode_get(unit, port, &mode, &flags);
            if (CDK_SUCCESS(rv)) {
                flags |= BMD_PORT_MODE_F_INTERNAL;
                rv = bcm56850_a0_bmd_port_mode_set(unit, port, mode, flags);
            }
        }

        /* Set configuration according to link state */
        mac_en = 0;
        led_flags = 0;
        if (BMD_PORT_STATUS(unit, port) & BMD_PST_LINK_UP) {
            mac_en = 1;
            led_flags = XGSM_LED_LINK;
        }
        if (CDK_SUCCESS(rv)) {
            rv = bcm56850_a0_port_enable_set(unit, port, mac_en);
        }

        /* Update LED controller data */
        if (port > 36) {
            CMIC_LEDUP1_DATA_RAMr_t led_data1;
            uint32_t led_data;
            int offset;

            /* Update link status port LED processor #1 */
            offset = 0x80 + (port - 36);
            ioerr += READ_CMIC_LEDUP1_DATA_RAMr(unit, offset, &led_data1);
            led_data = CMIC_LEDUP1_DATA_RAMr_GET(led_data1);
            led_data &= ~0x81;
            if (led_flags & XGSM_LED_LINK) {
                led_data |= 0x01;
            }
            CMIC_LEDUP1_DATA_RAMr_SET(led_data1, led_data);
            ioerr += WRITE_CMIC_LEDUP1_DATA_RAMr(unit, offset, led_data1);
        } else {
            xgsm_led_update(unit, LED_DATA_OFFSET + port, led_flags);
        }
    }

    return ioerr ? CDK_E_IO : rv;
}
#endif /* CDK_CONFIG_INCLUDE_BCM56850_A0 */
