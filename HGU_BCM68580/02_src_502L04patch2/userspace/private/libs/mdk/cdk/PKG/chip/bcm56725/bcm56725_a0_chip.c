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

#include <cdk/chip/bcm56725_a0_defs.h>

/* Block types */
const char *bcm56725_a0_blktype_names[] = {
    "cmic",
    "epipe",
    "gxport",
    "ipipe",
    "mmu",
    "qgport"
};

/* Block structures */
cdk_xgs_block_t bcm56725_a0_blocks[] = 
{
    { BCM56725_A0_BLKTYPE_GXPORT,       0,      CDK_PBMP_1(0x01fffffe) },
    { BCM56725_A0_BLKTYPE_QGPORT,       2,      CDK_PBMP_1(0x1e000000) },
    { BCM56725_A0_BLKTYPE_IPIPE,        1,      CDK_PBMP_1(0x1fffffff) },
    { BCM56725_A0_BLKTYPE_EPIPE,        4,      CDK_PBMP_1(0x1fffffff) },
    { BCM56725_A0_BLKTYPE_MMU,          13,     CDK_PBMP_1(0x1fffffff) }
};

/* Symbol table */
#if CDK_CONFIG_INCLUDE_CHIP_SYMBOLS == 1
#if CDK_CONFIG_CHIP_SYMBOLS_USE_DSYMS == 1
extern cdk_symbols_t bcm56725_a0_dsymbols;
#else
extern cdk_symbols_t bcm56725_a0_symbols;
#endif
#endif

/* Physical port numbers */
#if CDK_CONFIG_INCLUDE_PORT_MAP == 1
static cdk_port_map_port_t _ports[] = {
    0, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18
};
#endif

/* Declare function first to prevent compiler warnings */
extern uint32_t
bcm56725_a0_blockport_addr(int block, int port, uint32_t offset);

uint32_t
bcm56725_a0_blockport_addr(int block, int port, uint32_t offset)
{
    if (block == 0) {
        port += 1;
    } else if (block == 2) {
        port += 25;
    }
    return ((block * 0x100000) | (port * 0x1000) | (offset & ~0xf00000)); 
}

/* Index ranges for this chip */
static cdk_xgs_numel_range_t _numel_ranges[] = {
    {  0,  7, CDK_PBMP_1(0x1ffffffe)                         }, /*  0 */
    {  0,  0, CDK_PBMP_1(0x1ffffffe)                         }, /*  1 */
    {  0,  9, CDK_PBMP_1(0x1fffffff)                         }, /*  2 */
    { 10, 31, CDK_PBMP_1(0x00000001)                         }, /*  3 */
    {  0,  0, CDK_PBMP_1(0x01fffffe)                         }  /*  4 */
};

/* Register array encodings for this chip */
static cdk_xgs_numel_encoding_t _numel_encodings[] = {
    { { 5 } },
    { {  0, -1 } },
    { {  1, -1 } },
    { {  2,  3, -1 } },
    { {  4, -1 } }
};

/* Variable register array info */
cdk_xgs_numel_info_t bcm56725_a0_numel_info = {
    _numel_ranges,
    _numel_encodings
};

/* Chip information structure */
static cdk_xgs_chip_info_t bcm56725_a0_chip_info = {

    /* CMIC block */
    BCM56725_A0_CMIC_BLOCK,

    /* Other (non-CMIC) block types */
    6,
    bcm56725_a0_blktype_names,

    /* Address calculation */
    bcm56725_a0_blockport_addr,

    /* Other (non-CMIC) blocks */
    5,
    bcm56725_a0_blocks,

    /* Valid ports for this chip */
    CDK_PBMP_1(0x0007ff81),

    /* Chip flags */
    CDK_XGS_CHIP_FLAG_CLAUSE45 |
    CDK_XGS_CHIP_FLAG_SCHAN_EXT |
    BCM56725_A0_CHIP_FLAG_TDM3_X |
    BCM56725_A0_CHIP_FLAG_TDM3_Y |
    BCM56725_A0_CHIP_FLAG_CLK_245 |
    0,

#if CDK_CONFIG_INCLUDE_CHIP_SYMBOLS == 1
#if CDK_CONFIG_CHIP_SYMBOLS_USE_DSYMS == 1
    /* Use regenerated symbol tables from the DSYM program */
    &bcm56725_a0_dsymbols,
#else
    /* Use the static per-chip symbol tables */
    &bcm56725_a0_symbols,
#endif
#endif

    /* Port map */
#if CDK_CONFIG_INCLUDE_PORT_MAP == 1
    sizeof(_ports)/sizeof(_ports[0]),
    _ports,
#endif

    /* Variable register array info */
    &bcm56725_a0_numel_info,

    /* Configuration dependent memory max index */
    NULL,

};

/* Declare function first to prevent compiler warnings */
extern int
bcm56725_a0_setup(cdk_dev_t *dev);

int
bcm56725_a0_setup(cdk_dev_t *dev)
{
    dev->chip_info = &bcm56725_a0_chip_info;

    return cdk_xgs_setup(dev);
}

