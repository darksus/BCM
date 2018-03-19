/*******************************************************************************
 *
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated from the registers file.
 * Edits to this file will be lost when it is regenerated.
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
 *
 ******************************************************************************/

#include <cdk/chip/bcm53101_a0_defs.h>

/* Block types */
const char *bcm53101_a0_blktype_names[] = {
    "cpic",
    "epic",
    "exp",
    "spi",
    "sys"
};

/* Block structures */
cdk_robo_block_t bcm53101_a0_blocks[] = 
{
    { BCM53101_A0_BLKTYPE_EPIC,       CDK_PBMP_1(0x0000003f) },
    { BCM53101_A0_BLKTYPE_CPIC,       CDK_PBMP_1(0x00000100) },
    { BCM53101_A0_BLKTYPE_EXP,        CDK_PBMP_1(0x0000013f) },
    { BCM53101_A0_BLKTYPE_SPI,        CDK_PBMP_1(0x0000013f) },
    { BCM53101_A0_BLKTYPE_SYS,        CDK_PBMP_1(0x0000013f) }
};

/* Symbol table */
#if CDK_CONFIG_INCLUDE_CHIP_SYMBOLS == 1
#if CDK_CONFIG_CHIP_SYMBOLS_USE_DSYMS == 1
extern cdk_symbols_t bcm53101_a0_dsymbols;
#else
extern cdk_symbols_t bcm53101_a0_symbols;
#endif
#endif

/* Physical port numbers */
#if CDK_CONFIG_INCLUDE_PORT_MAP == 1
static cdk_port_map_port_t _ports[] = {
    8, 0, 1, 2, 3, 4, 5
};
#endif

/* Declare function first to prevent compiler warnings */
extern uint32_t
bcm53101_a0_blockport_addr(int port, int size, uint32_t offset);

uint32_t
bcm53101_a0_blockport_addr(int port, int size, uint32_t offset)
{
    if (port < 0) {
        port = 0;
    }
    if ((offset & 0xff00) == 0x1000 ||  /* GMII */
        (offset & 0xff00) == 0x2000) {  /* MIB */
        /* Use page size */
        size = 0x100;
    }
    port -= (offset >> 16);
    return (offset & 0xffff) + (port * size); 
}

/* Chip information structure */
static cdk_robo_chip_info_t bcm53101_a0_chip_info = {

    /* Block types */
    5,
    bcm53101_a0_blktype_names,

    /* Address calculation */
    bcm53101_a0_blockport_addr,

    /* Chip blocks */
    5,
    bcm53101_a0_blocks,

    /* Valid ports for this chip */
    CDK_PBMP_1(0x0000013f),

    /* Chip flags */
    0,

#if CDK_CONFIG_INCLUDE_CHIP_SYMBOLS == 1
#if CDK_CONFIG_CHIP_SYMBOLS_USE_DSYMS == 1
    &bcm53101_a0_dsymbols,
#else
    &bcm53101_a0_symbols,
#endif
#endif

    /* Port map */
#if CDK_CONFIG_INCLUDE_PORT_MAP == 1
    sizeof(_ports)/sizeof(_ports[0]),
    _ports,
#endif

};

/* Declare function first to prevent compiler warnings */
extern int
bcm53101_a0_setup(cdk_dev_t *dev);

int
bcm53101_a0_setup(cdk_dev_t *dev)
{
    dev->chip_info = &bcm53101_a0_chip_info;

    return cdk_robo_setup(dev);
}

