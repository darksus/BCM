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

#include <cdk/chip/bcm56840_b0_defs.h>

/* Block types */
const char *bcm56840_b0_blktype_names[] = {
    "cmic",
    "epipe",
    "ipipe",
    "lbport",
    "mmu",
    "port_group4",
    "port_group5",
    "xlport"
};

/* Block structures */
cdk_xgs_block_t bcm56840_b0_blocks[] = 
{
    { BCM56840_B0_BLKTYPE_LBPORT,       28,     CDK_PBMP_3(0x00000000, 0x00000000, 0x00000200) },
    { BCM56840_B0_BLKTYPE_XLPORT,       10,     CDK_PBMP_1(0x0000001e) },
    { BCM56840_B0_BLKTYPE_XLPORT,       11,     CDK_PBMP_1(0x000001e0) },
    { BCM56840_B0_BLKTYPE_XLPORT,       12,     CDK_PBMP_1(0x00001e00) },
    { BCM56840_B0_BLKTYPE_XLPORT,       13,     CDK_PBMP_1(0x0001e000) },
    { BCM56840_B0_BLKTYPE_XLPORT,       14,     CDK_PBMP_1(0x001e0000) },
    { BCM56840_B0_BLKTYPE_XLPORT,       15,     CDK_PBMP_1(0x01e00000) },
    { BCM56840_B0_BLKTYPE_XLPORT,       16,     CDK_PBMP_1(0x1e000000) },
    { BCM56840_B0_BLKTYPE_XLPORT,       17,     CDK_PBMP_2(0xe0000000, 0x00000001) },
    { BCM56840_B0_BLKTYPE_XLPORT,       18,     CDK_PBMP_2(0x00000000, 0x0000001e) },
    { BCM56840_B0_BLKTYPE_XLPORT,       19,     CDK_PBMP_2(0x00000000, 0x000001e0) },
    { BCM56840_B0_BLKTYPE_XLPORT,       20,     CDK_PBMP_2(0x00000000, 0x00001e00) },
    { BCM56840_B0_BLKTYPE_XLPORT,       21,     CDK_PBMP_2(0x00000000, 0x0001e000) },
    { BCM56840_B0_BLKTYPE_XLPORT,       22,     CDK_PBMP_2(0x00000000, 0x001e0000) },
    { BCM56840_B0_BLKTYPE_XLPORT,       23,     CDK_PBMP_2(0x00000000, 0x01e00000) },
    { BCM56840_B0_BLKTYPE_XLPORT,       24,     CDK_PBMP_2(0x00000000, 0x1e000000) },
    { BCM56840_B0_BLKTYPE_XLPORT,       25,     CDK_PBMP_3(0x00000000, 0xe0000000, 0x00000001) },
    { BCM56840_B0_BLKTYPE_XLPORT,       26,     CDK_PBMP_3(0x00000000, 0x00000000, 0x0000001e) },
    { BCM56840_B0_BLKTYPE_XLPORT,       27,     CDK_PBMP_3(0x00000000, 0x00000000, 0x000001e0) },
    { BCM56840_B0_BLKTYPE_XLPORT,       29,     CDK_PBMP_1(0x00000000) },
    { BCM56840_B0_BLKTYPE_XLPORT,       30,     CDK_PBMP_1(0x00000000) },
    { BCM56840_B0_BLKTYPE_IPIPE,        1,      CDK_PBMP_3(0xffffffff, 0xffffffff, 0x00000003) },
    { BCM56840_B0_BLKTYPE_EPIPE,        2,      CDK_PBMP_3(0xffffffff, 0xffffffff, 0x00000003) },
    { BCM56840_B0_BLKTYPE_MMU,          3,      CDK_PBMP_3(0xffffffff, 0xffffffff, 0x00000003) },
    { BCM56840_B0_BLKTYPE_PORT_GROUP4,  6,      CDK_PBMP_2(0xffe00000, 0x0000001f) },
    { BCM56840_B0_BLKTYPE_PORT_GROUP4,  7,      CDK_PBMP_3(0x00000000, 0xfe000000, 0x000001ff) },
    { BCM56840_B0_BLKTYPE_PORT_GROUP5,  8,      CDK_PBMP_1(0x001ffffe) },
    { BCM56840_B0_BLKTYPE_PORT_GROUP5,  9,      CDK_PBMP_2(0x00000000, 0x01ffffe0) }
};

/* Symbol table */
#if CDK_CONFIG_INCLUDE_CHIP_SYMBOLS == 1
#if CDK_CONFIG_CHIP_SYMBOLS_USE_DSYMS == 1
extern cdk_symbols_t bcm56840_b0_dsymbols;
#else
extern cdk_symbols_t bcm56840_b0_symbols;
#endif
#endif

/* Physical port numbers */
#if CDK_CONFIG_INCLUDE_PORT_MAP == 1
static cdk_port_map_port_t _ports[] = {
    0, 1, 2, 3, 4, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68
};
#endif

/* Declare function first to prevent compiler warnings */
extern uint32_t
bcm56840_b0_blockport_addr(int block, int port, uint32_t offset);

uint32_t
bcm56840_b0_blockport_addr(int block, int port, uint32_t offset)
{
    if (block & 0x10) {
        block &= 0xf;
        block |= 0x400;
    }
    return ((block * 0x100000) | (port * 0x1000) | (offset & ~0xf00000)); 
}

/* Index ranges for this chip */
static cdk_xgs_numel_range_t _numel_ranges[] = {
    {  0,  0, CDK_PBMP_3(0xfffffffe, 0xfffffffd, 0x00000003) }, /*  0 */
    {  0,  0, CDK_PBMP_3(0xfffffffe, 0xffffffff, 0x00000003) }, /*  1 */
    {  0,  6, CDK_PBMP_3(0xffffffff, 0xffffffff, 0x00000003) }, /*  2 */
    {  7, 47, CDK_PBMP_1(0x00000001)                         }, /*  3 */
    {  0, 71, CDK_PBMP_2(0x0000001e, 0x0000003c)             }, /*  4 */
    {  0,  4, CDK_PBMP_3(0xffffffff, 0xffffffff, 0x00000003) }, /*  5 */
    {  5, 14, CDK_PBMP_3(0xffffffff, 0xfffffffd, 0x00000003) }, /*  6 */
    { 15, 47, CDK_PBMP_2(0x0000001f, 0x0000003c)             }, /*  7 */
    { 48, 78, CDK_PBMP_2(0x0000001e, 0x0000003c)             }, /*  8 */
    {  0,  4, CDK_PBMP_3(0xfffffffe, 0xffffffff, 0x00000003) }, /*  9 */
    {  0,  0, CDK_PBMP_2(0x0000001e, 0x0000003c)             }, /* 10 */
    {  0, 73, CDK_PBMP_2(0x0000001e, 0x0000003c)             }, /* 11 */
    {  5, 47, CDK_PBMP_1(0x00000001)                         }, /* 12 */
    {  0,  3, CDK_PBMP_3(0xfffffffe, 0xfffffffd, 0x00000003) }, /* 13 */
    {  0,  9, CDK_PBMP_3(0xfffffffe, 0xfffffffd, 0x00000003) }, /* 14 */
    {  0, 11, CDK_PBMP_3(0xfffffffe, 0xffffffff, 0x00000003) }, /* 15 */
    {  0,  3, CDK_PBMP_3(0xfffffffe, 0xffffffff, 0x00000003) }, /* 16 */
    {  0,  2, CDK_PBMP_3(0xfffffffe, 0xffffffff, 0x00000003) }, /* 17 */
    {  0,  7, CDK_PBMP_3(0xfffffffe, 0xffffffff, 0x00000003) }, /* 18 */
    {  8, 71, CDK_PBMP_2(0x0000001e, 0x0000003c)             }, /* 19 */
    {  0,  7, CDK_PBMP_3(0xfffffffe, 0xfffffffd, 0x00000003) }  /* 20 */
};

/* Register array encodings for this chip */
static cdk_xgs_numel_encoding_t _numel_encodings[] = {
    { { 17 } },
    { {  0, -1 } },
    { {  1, -1 } },
    { {  2,  3, -1 } },
    { {  4, -1 } },
    { {  5,  6,  7,  8, -1 } },
    { {  9, -1 } },
    { { 10, -1 } },
    { { 11, -1 } },
    { {  5, 12, -1 } },
    { { 13, -1 } },
    { { 14, -1 } },
    { { 15, -1 } },
    { { 16, -1 } },
    { { 17, -1 } },
    { { 18, 19, -1 } },
    { { 20, -1 } }
};

/* Variable register array info */
cdk_xgs_numel_info_t bcm56840_b0_numel_info = {
    _numel_ranges,
    _numel_encodings
};

/* Chip information structure */
static cdk_xgs_chip_info_t bcm56840_b0_chip_info = {

    /* CMIC block */
    BCM56840_B0_CMIC_BLOCK,

    /* Other (non-CMIC) block types */
    8,
    bcm56840_b0_blktype_names,

    /* Address calculation */
    bcm56840_b0_blockport_addr,

    /* Other (non-CMIC) blocks */
    28,
    bcm56840_b0_blocks,

    /* Valid ports for this chip */
    CDK_PBMP_3(0xffffffff, 0xffffffff, 0x000003ff),

    /* Chip flags */
    CDK_XGS_CHIP_FLAG_CLAUSE45 |
    CDK_XGS_CHIP_FLAG_SCHAN_EXT |
    CDK_XGS_CHIP_FLAG_SCHAN_SB0 |
    0,

#if CDK_CONFIG_INCLUDE_CHIP_SYMBOLS == 1
#if CDK_CONFIG_CHIP_SYMBOLS_USE_DSYMS == 1
    /* Use regenerated symbol tables from the DSYM program */
    &bcm56840_b0_dsymbols,
#else
    /* Use the static per-chip symbol tables */
    &bcm56840_b0_symbols,
#endif
#endif

    /* Port map */
#if CDK_CONFIG_INCLUDE_PORT_MAP == 1
    sizeof(_ports)/sizeof(_ports[0]),
    _ports,
#endif

    /* Variable register array info */
    &bcm56840_b0_numel_info,

    /* Configuration dependent memory max index */
    NULL,

};

/* Declare function first to prevent compiler warnings */
extern int
bcm56840_b0_setup(cdk_dev_t *dev);

int
bcm56840_b0_setup(cdk_dev_t *dev)
{
    dev->chip_info = &bcm56840_b0_chip_info;

    return cdk_xgs_setup(dev);
}

