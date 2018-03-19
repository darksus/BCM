/*
 * $Id: xgsm_reg.h,v 1.1 Broadcom SDK $
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
 * XGS register access functions.
 */

#ifndef __XGSM_REG_H__
#define __XGSM_REG_H__

#include <cdk/arch/xgsm_chip.h>

/*******************************************************************************
 *
 * Common register routines (internal)
 *
 *
 ******************************************************************************/

extern int
cdk_xgsm_reg_read(int unit, uint32_t adext, uint32_t addr,
                  uint32_t *data, int size);

extern int
cdk_xgsm_reg_write(int unit, uint32_t adext, uint32_t addr,
                   uint32_t *data, int size);

extern int
cdk_xgsm_reg_port_read(int unit, uint32_t blkacc, int port,
                       uint32_t offset, int idx, void *data, int size);

extern int
cdk_xgsm_reg_port_write(int unit, uint32_t blkacc, int port,
                        uint32_t offset, int idx, void *data, int size);

extern int
cdk_xgsm_reg_block_read(int unit, uint32_t blkacc, int block,
                        uint32_t offset, int idx, void *data, int size);

extern int
cdk_xgsm_reg_block_write(int unit, uint32_t blkacc, int block,
                         uint32_t offset, int idx, void *data, int size);

extern int
cdk_xgsm_reg_blocks_read(int unit, uint32_t blkacc, int port,
                         uint32_t offset, int idx, void *vptr, int size);

extern int
cdk_xgsm_reg_blocks_write(int unit, uint32_t blkacc, int port,
                          uint32_t offset, int idx, void *vptr, int size);

/*******************************************************************************
 *
 * Access 32 bit internal registers
 *
 *
 ******************************************************************************/

extern int 
cdk_xgsm_reg32_read(int unit, uint32_t adext, uint32_t addr, void *data); 

extern int 
cdk_xgsm_reg32_write(int unit, uint32_t adext, uint32_t addr, void *data); 

extern int
cdk_xgsm_reg32_writei(int unit, uint32_t adext, uint32_t addr, uint32_t data); 


/*******************************************************************************
 *
 * Access 32 bit internal port-based registers
 *
 *
 ******************************************************************************/

extern int
cdk_xgsm_reg32_port_read(int unit, uint32_t blkacc, int port,
                         uint32_t offset, int idx, void *data);

extern int 
cdk_xgsm_reg32_port_write(int unit, uint32_t blkacc, int port,
                          uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg32_port_writei(int unit, uint32_t blkacc, int port,
                           uint32_t offset, int idx, uint32_t data);


/*******************************************************************************
 *
 * Access 32 bit internal block-based registers
 *
 *
 ******************************************************************************/

extern int 
cdk_xgsm_reg32_block_read(int unit, uint32_t blkacc, int block,
                          uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg32_block_write(int unit, uint32_t blkacc, int block,
                           uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg32_block_writei(int unit, uint32_t blkacc, int block,
                            uint32_t offset, int idx, uint32_t data);


/*******************************************************************************
 *
 * Access 32 bit internal registers by both block and port. 
 *
 *
 ******************************************************************************/

extern int 
cdk_xgsm_reg32_blockport_read(int unit, uint32_t blkacc, int block, int port,
                              uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg32_blockport_write(int unit, uint32_t blkacc, int block, int port,
                               uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg32_blockport_writei(int unit, uint32_t blkacc, int block, int port,
                                uint32_t offset, int idx, uint32_t data); 


/*******************************************************************************
 *
 * Access 32 bit internal block-based registers on all blocks of given types
 *
 *
 ******************************************************************************/

extern int
cdk_xgsm_reg32_blocks_read(int unit, uint32_t blkacc, int port,
                           uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg32_blocks_write(int unit, uint32_t blkacc, int port,
                            uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg32_blocks_writei(int unit, uint32_t blkacc, int port,
                             uint32_t offset, int idx, uint32_t data); 


/*******************************************************************************
 *
 * Access 64 bit internal registers
 *
 *
 ******************************************************************************/

extern int
cdk_xgsm_reg64_read(int unit, uint32_t adext, uint32_t addr, void *data); 

extern int
cdk_xgsm_reg64_write(int unit, uint32_t adext, uint32_t addr, void *data); 


/*******************************************************************************
 *
 * Access 64 bit internal port-based registers
 *
 *
 ******************************************************************************/

extern int
cdk_xgsm_reg64_port_read(int unit, uint32_t blkacc, int port,
                         uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg64_port_write(int unit, uint32_t blkacc, int port,
                          uint32_t offset, int idx, void *data);



/*******************************************************************************
 *
 * Access 64 bit internal block-based registers
 *
 *
 ******************************************************************************/

extern int
cdk_xgsm_reg64_block_read(int unit, uint32_t blkacc, int block,
                          uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg64_block_write(int unit, uint32_t blkacc, int block,
                           uint32_t offset, int idx, void *data);


/*******************************************************************************
 *
 * Access 64 bit internal registers by both block and port. 
 *
 *
 ******************************************************************************/

extern int 
cdk_xgsm_reg64_blockport_read(int unit, uint32_t blkacc, int block, int port,
                              uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg64_blockport_write(int unit, uint32_t blkacc, int block, int port,
                               uint32_t offset, int idx, void *data);


/*******************************************************************************
 *
 * Access 64 bit internal block-based registers on all blocks of given types
 *
 *
 ******************************************************************************/

extern int
cdk_xgsm_reg64_blocks_read(int unit, uint32_t blkacc, int port,
                            uint32_t offset, int idx, void *data);

extern int
cdk_xgsm_reg64_blocks_write(int unit, uint32_t blkacc, int port,
                            uint32_t offset, int idx, void *data);


/*******************************************************************************
 *
 * Validate index for per-port variable register array
 *
 *
 ******************************************************************************/

extern int
cdk_xgsm_reg_index_valid(int unit, int port, int regidx,
                         int encoding, int regidx_max); 


#endif /* __XGSM_REG_H__ */
