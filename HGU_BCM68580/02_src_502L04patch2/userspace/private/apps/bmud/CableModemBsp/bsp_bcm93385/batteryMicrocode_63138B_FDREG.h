//****************************************************************************
//
// Copyright � 2005-2016 Broadcom Corporation
//
// This program is the proprietary software of Broadcom Corporation and/or
// its licensors, and may only be used, duplicated, modified or distributed
// pursuant to the terms and conditions of a separate, written license
// agreement executed between you and Broadcom (an "Authorized License").
// Except as set forth in an Authorized License, Broadcom grants no license
// (express or implied), right to use, or waiver of any kind with respect to
// the Software, and Broadcom expressly reserves all rights in and to the
// Software and all intellectual property rights therein.  IF YOU HAVE NO
// AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE IN ANY WAY,
// AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE ALL USE OF THE
// SOFTWARE.  
//
// Except as expressly set forth in the Authorized License,
//
// 1.     This program, including its structure, sequence and organization,
// constitutes the valuable trade secrets of Broadcom, and you shall use all
// reasonable efforts to protect the confidentiality thereof, and to use this
// information only in connection with your use of Broadcom integrated circuit
// products.
//
// 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED
// "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS
// OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
// RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL
// IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR
// A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
// ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. YOU ASSUME
// THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
//
// 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM
// OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL,
// INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY WAY
// RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN IF BROADCOM
// HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN
// EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR U.S. $1,
// WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY
// FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
//
//****************************************************************************
//  $Id$
//
//  Filename:       batteryMicrocode_63138B_FDREG_2.6.1a10.h
//  Author:         Tom Johnson (via post-processor)
//  Creation Date:  February 05, 2016
//
//****************************************************************************
//  Description:
//      63138B BMU pico code
//
//****************************************************************************

#ifndef BATTERYMICROCODE_H
#define BATTERYMICROCODE_H

#define PICO_CODE_REV		"2.6.1a10"
#define PICO_BUILD_DATE		"02/05/16"
#define PICO_BUILD_TIME		"09:33:00"
#define PICO_BUILD_TIME_T	1454664780

const uint32 batteryPicocode[] = 
{
	0xa879a87f, 0xa887a8d7, 0xd0001061, 0xaa80ac68, 0xab53d6fd, 0xa801d000, 
	0x13e41760, 0xc3981760, 0xbb98d000, 0x2bbc8b89, 0xd705a801, 0x8878d000, 
	0x10621760, 0xc000ab9b, 0xa01713e2, 0x1760c385, 0xd17f1460, 0xd342a801, 
	0xd00c13e0, 0xd310e380, 0x13e4d310, 0xe380d6fd, 0xa8011760, 0xd083bb80, 
	0xd0002bb9, 0x8b851760, 0xd08ec600, 0xaa98ac79, 0xd1101060, 0xaa92aaa3, 
	0xaa66d46e, 0xa801d458, 0xa801ac49, 0x8817d700, 0x1061aa56, 0x70131760, 
	0xbb9816e6, 0x23ef938e, 0x1760bbaf, 0x1b8f738a, 0x1760bbb0, 0x1b8fd450, 
	0x83801760, 0xbbad1b8f, 0xd44b7b80, 0xaac17009, 0xd30ede80, 0x8e86ab9b, 
	0x8e84d02f, 0x1060d711, 0xa8011760, 0xd081b800, 0xac06d081, 0x1060aa4f, 
	0xd705a801, 0x8807d6fd, 0xa801aac1, 0x7003ad5c, 0xd4e0a801, 0xd737a801, 
	0xa038d800, 0x46001760, 0xc605c618, 0xb078d17f, 0x1760c600, 0x0f777f7d, 
	0xd17f1460, 0xb0780f47, 0xc7801470, 0xd03213e0, 0xd333e380, 0xd342a801, 
	0x13e4d310, 0xe38013e4, 0xd32ce380, 0x13e1d321, 0xe380d322, 0xe380a9f7, 
	0xd30813e0, 0xd31ae380, 0x13e11760, 0xd212c380, 0x13e61760, 0xd20cc380, 
	0xd00813e0, 0x1760d213, 0xc3801760, 0xd20dc380, 0x1760d20f, 0xc3801760, 
	0xd210c380, 0x1760d211, 0xc3801760, 0xd244c380, 0x1760d227, 0xbb801760, 
	0xd227bb80, 0xd0102bb8, 0x8bfad1e7, 0x13e0d010, 0x5bb8d067, 0x3bb81760, 
	0xd207c380, 0xd04013e0, 0x1760d209, 0xc3801740, 0xbf801471, 0xb0780be7, 
	0x1760d080, 0xc380d008, 0x13e01760, 0xc3a0d36f, 0x13e01760, 0xc3a11760, 
	0xc3a213e3, 0x1760c3a3, 0x13e41760, 0xc3a5d040, 0x1160d058, 0x11e0d361, 
	0x13e01760, 0xc38ed7f9, 0x0be7d32b, 0xe38013e4, 0x1760c391, 0x13e01760, 
	0xc392d087, 0x13e01760, 0xc38fd008, 0x13e01760, 0xc390d3ce, 0x13e01760, 
	0xc393d17e, 0x13e01760, 0xc3b8d084, 0x13e01760, 0xc3b9d3d1, 0x13e01760, 
	0xc3abd388, 0x1060d39b, 0x10e00f10, 0xc0000f10, 0xc0860f10, 0xc0870f10, 
	0xc0810f18, 0xc0000f18, 0xc0860f18, 0xc0810f18, 0xc087d286, 0x10600f10, 
	0xc0030f18, 0xc003d286, 0x10600f10, 0xc0120f18, 0xc012d2de, 0x10600f10, 
	0xc0130f18, 0xc013d3c2, 0x10600f10, 0xc0140f18, 0xc014d31c, 0x10600f10, 
	0xc0150f18, 0xc015d3c0, 0x13e01760, 0xc3bad064, 0x13e01760, 0xc3bbd01b, 
	0x13e01760, 0xc3bcd035, 0x13e01760, 0xc3bdd035, 0x13e01760, 0xc3bed145, 
	0x13e01760, 0xc3a813e1, 0x1760c3a9, 0xd00a13e0, 0x1760c3aa, 0xd35513e0, 
	0x1760c3ac, 0xd26f13e0, 0x1760c3ae, 0xd28513e0, 0x1760c3ad, 0xd30513e0, 
	0x1760c3af, 0xd11013e0, 0x1760c3b0, 0xd23413e0, 0x1760c3b1, 0xd25613e0, 
	0x1760c3b2, 0xd08513e0, 0x1760c3b3, 0xd06b13e0, 0x1760c3b4, 0xd00a13e0, 
	0x1760c3b5, 0xd00a13e0, 0x1760c3b6, 0xd01113e0, 0x1760c3b7, 0xd3a11060, 
	0x0f10c00b, 0x0f18c00b, 0xd2041060, 0x0f10c00c, 0x0f18c00c, 0xd06b1060, 
	0x0f10c002, 0x0f18c002, 0xd10b1060, 0x0f10c004, 0x0f18c004, 0x0f10c009, 
	0x0f18c009, 0xd0ba1060, 0x0f10c005, 0x0f18c005, 0xd01b1060, 0x0f10c008, 
	0x0f18c008, 0xd1401060, 0x0f10c00a, 0x0f18c00a, 0xd2801060, 0x0f10c00d, 
	0x0f18c00d, 0xd42b1060, 0x0f10c00e, 0x0f18c00e, 0xd0c01061, 0x0f10c00f, 
	0x0f18c00f, 0xd7d01060, 0x0f10c010, 0x0f18c010, 0xd0c81060, 0x0f10c011, 
	0x0f18c011, 0x10611760, 0xc0261760, 0xc02713e3, 0x1760c3a4, 0x1760c604, 
	0x1760c603, 0x13e51760, 0xd095c380, 0x13e51760, 0xd0a1c380, 0xb078d016, 
	0x10601760, 0xd20ec000, 0x1760d226, 0xb8001760, 0xd226b800, 0xd0102800, 
	0x887a1760, 0xd21eb800, 0xd7ff2807, 0xd0080800, 0x58041760, 0xd0a7c000, 
	0xd3e013e0, 0x18381760, 0xd0a9c000, 0x1760d23c, 0xbb80d015, 0x5bb8d7e5, 
	0x6bbf1760, 0xd0a8c380, 0x03b8d32a, 0xe3801760, 0xd0a6c380, 0xb0780b87, 
	0x7388d330, 0xe600d331, 0xe60013e1, 0x53b8d31e, 0xe380b078, 0x1760d230, 
	0xbb8014e1, 0x54c823cf, 0x8b8d5801, 0x0f00d231, 0xbb800f00, 0xd105c380, 
	0x0f00d233, 0xbb800f00, 0xd106c380, 0xb078d31a, 0xe600b078, 0xd30813e0, 
	0xd31ae380, 0xb0780f00, 0xbc8014c9, 0x2cc90f00, 0xc480b078, 0x1760bb83, 
	0x20071760, 0xbb842007, 0xb0781760, 0xbb833007, 0x1760c003, 0x1760bb84, 
	0x2007b078, 0x0f47c680, 0x14701760, 0xbe802be9, 0x73861760, 0xd083bb80, 
	0x3bb91760, 0xc3801760, 0xbb98d020, 0x2bb87384, 0xd43c13e7, 0x1760c397, 
	0x1740be80, 0x1471b078, 0x1760d083, 0xbb8033b8, 0x1760d083, 0xc380b078, 
	0xd7ff4b87, 0x1760d083, 0xbc8024cf, 0x1760d083, 0xc480b078, 0x0f00bb80, 
	0x13b90f00, 0xc380b078, 0x1760bbb7, 0xd00a5bb8, 0xd300dc80, 0x04cf1760, 
	0xd10fc480, 0xb0780f46, 0xc001c780, 0x14701760, 0xd083bb80, 0xd0002bb9, 
	0x8b8f1760, 0xbb98d010, 0x2bb8738a, 0xd300db80, 0x1760d10f, 0xbc801bcf, 
	0x7383d000, 0x1061aa88, 0x0f40bf80, 0xb8011472, 0xb0781760, 0xd083bb80, 
	0xd0002839, 0xb0780f46, 0xc001c780, 0x1470d000, 0x1061aa88, 0x0f40bf80, 
	0xb8011472, 0xb0780f46, 0xc081c780, 0x1470d092, 0x10881760, 0xb80fab18, 
	0x1760bb90, 0x1be7600f, 0xd76e0807, 0x0f40bf80, 0xb8811472, 0xb0780ee0, 
	0x700216e1, 0x18607082, 0x4ee918e1, 0x0ce0b078, 0x1760d240, 0xc0001760, 
	0xd243bb80, 0x3cba1760, 0xd243c480, 0x1760d243, 0xc380b078, 0x0f46c681, 
	0xc7801470, 0x1760bc98, 0xd0402cc8, 0x748c1760, 0xd240be80, 0xd00c2ee8, 
	0x90061760, 0xd240bb80, 0x2bbb3038, 0xaaf00f40, 0xbf80be81, 0x1472b078, 
	0x0f45c002, 0xc681c780, 0x1470aae7, 0x882b88aa, 0x1b887b83, 0x13881080, 
	0x10380b87, 0x73821488, 0xa34a8820, 0x2b818b81, 0x04c95889, 0x5807a329, 
	0x0f45c002, 0xc681c780, 0x1470aae7, 0x88138892, 0x0b877382, 0x1488a34a, 
	0x13e11d08, 0x85035bb9, 0x5801a33d, 0x5bbf5807, 0x8b851d08, 0x857b1888, 
	0x04cf70f8, 0x08c88e81, 0x18e10f40, 0xbf80be81, 0xb8021473, 0xb0780f44, 
	0xc003c102, 0xc681c780, 0x14701760, 0xd080be80, 0x90230bef, 0x73885cea, 
	0x14ce0f48, 0xbb80d7df, 0x2bbf0f48, 0xc3800b87, 0x738b5c82, 0x14ce0f48, 
	0xbb80d020, 0x3bb80f48, 0xc38013e1, 0x53b8a375, 0x0be0d010, 0x3bb8d30b, 
	0xe3801760, 0xd080c000, 0x1760b825, 0xd711a801, 0x1740bf80, 0xbe81b902, 
	0xb803d004, 0x0c70b078, 0x0b877388, 0x5c8214ce, 0x0f48bb80, 0xd7df2bbf, 
	0x0f48c380, 0xd01013e0, 0xd30be380, 0x0be71760, 0xd080c380, 0xb0780f47, 
	0xc0001470, 0x1760d080, 0xb8000b87, 0x73885c82, 0x14ce0f48, 0xbb80d7df, 
	0x2bbf0f48, 0xc380d010, 0x13e0d30b, 0xe3800be7, 0x1760d080, 0xc3801740, 
	0xb8001471, 0xb078d7fa, 0x0f47c005, 0xc104c183, 0xc202c681, 0xc7801470, 
	0x08e00b87, 0x73b95902, 0x11160f10, 0xbc802bca, 0x8bb31760, 0xd080b980, 
	0x5f03d004, 0x5a000274, 0xd0401220, 0xab53d3eb, 0xa8010f10, 0xbc80d7f3, 
	0x2ccf0f20, 0xbb801b8f, 0x7b920f20, 0xbb921b8f, 0x7b89d3eb, 0xa8010f20, 
	0xbb921b8f, 0x7b83d010, 0x3cc8a3f3, 0x0f20bb93, 0x1b8f8385, 0xa3f1d008, 
	0x3cc8d7ef, 0x2ccf0f10, 0xc4801760, 0xbe8513e3, 0x9b81ac86, 0x1018ab53, 
	0x1740bf80, 0xbe81ba02, 0xb983b904, 0xb805d006, 0x0c70b078, 0xd7f90f47, 
	0xc006c085, 0xc104c183, 0xc202c681, 0xc7801470, 0x802d0b87, 0x73ab1760, 
	0xbb98d008, 0x2bb873a6, 0x120059a2, 0x119e0f18, 0xbe80d38d, 0xa8011108, 
	0xd47ba801, 0x79011962, 0x1760bba8, 0x19177116, 0x1760bbba, 0x1b8f8b84, 
	0x2be98b90, 0x0ee0a435, 0x2be9738c, 0x3ee9d004, 0x3ee90f18, 0xc6801021, 
	0x58032be9, 0x7382aa88, 0xa43eaa80, 0x1740bf80, 0xbe81ba02, 0xb983b904, 
	0xb885b806, 0xd0070c70, 0xb0780f45, 0xc082c101, 0xc6801470, 0x10e10960, 
	0x16e31760, 0xd083bb80, 0xd0002bb9, 0x8b8116e1, 0x5b8a13be, 0x0f38bb80, 
	0x2bbb9b81, 0x1111088f, 0x78f71010, 0x0f40be80, 0xb901b882, 0x1473b078, 
	0x0f47c680, 0x1470d30e, 0xde801061, 0x13e29383, 0x5bbf0807, 0x787cd7ff, 
	0x28071740, 0xbe801471, 0xb0780f46, 0xc001c780, 0x14701060, 0xac060861, 
	0xac060f40, 0xbf80b801, 0x1472b078, 0x0f45c002, 0xc081c780, 0x1470aad3, 
	0x1760bb82, 0x1bb88b8f, 0x13e11760, 0xd0a0c380, 0xd38da801, 0x788118e1, 
	0x1760bbbd, 0x1b8f8383, 0xd4001060, 0xaa5d0f40, 0xbf80b881, 0xb8021473, 
	0xb07813e3, 0x1760c385, 0xd17f1460, 0xd00c13e0, 0xd310e380, 0x13e4d310, 
	0xe3801760, 0xd08bc600, 0x1760d081, 0xc6001760, 0xd082c600, 0xd6fda801, 
	0xd1111060, 0xaa92aaa3, 0xaa66ac49, 0xd458a801, 0xd357887f, 0xd7001061, 
	0xaa56d352, 0x707f1760, 0xbb9816e6, 0x23efd34c, 0x93ffd0f0, 0x1060aa56, 
	0x700b1760, 0xbb982bba, 0x73871760, 0xbbb11b8f, 0x7b83ac68, 0xd0cea001, 
	0xaac17001, 0xab9b1164, 0xd2001060, 0x1760bbb1, 0x1b8f7b84, 0xaa80d008, 
	0x1160a4ef, 0xaa881010, 0xaafed705, 0xa8017011, 0x1760d08b, 0xbb807388, 
	0x1760d081, 0xb800ac06, 0xd0811060, 0xaa4fa559, 0x0bbf1760, 0xd08bc380, 
	0xa559d6fd, 0xa801aac1, 0x7007d00a, 0x1060d711, 0xa801d4e0, 0xa801ad5c, 
	0xd7001061, 0xaa56703b, 0x1760d082, 0xb8005902, 0x11165f03, 0xd0045a00, 
	0x0274d040, 0x12200f10, 0xb9802c9a, 0x8cacaac7, 0xabb70f20, 0xbb801b8f, 
	0x7ba11760, 0xbb982bbc, 0x739d1760, 0xb8021760, 0xbbad1b87, 0x8397d70f, 
	0x1061aa56, 0x7013d040, 0x2c987490, 0xd7002c98, 0xd7f85ccf, 0x1760bba4, 
	0x1bcf7b88, 0x1760d094, 0xbb808b84, 0x1760d082, 0xb800ad7f, 0xd00a13e0, 
	0x1760d08b, 0xc3801760, 0xd082b800, 0x10012801, 0x1760d082, 0xc000d46e, 
	0xa801d737, 0xa801a4bc, 0x0f45c002, 0xc081c780, 0x1470d426, 0xa8011760, 
	0xd0a4c080, 0x1760bbb8, 0x1b8f838b, 0x1760d095, 0xbb800bbf, 0x73871760, 
	0xd0a3c080, 0xd2001060, 0xaa5d13e5, 0x1760d095, 0xc3800f40, 0xbf80b881, 
	0xb8021473, 0xb078d7fb, 0x0f47c004, 0xc083c102, 0xc181c780, 0x14701180, 
	0xd1e01060, 0xaa88d008, 0x16e01018, 0x5f03d004, 0x5b8003f7, 0xd04013b8, 
	0x0f38b900, 0xab538e9d, 0x1018d3eb, 0xa8011b8a, 0x7b820eef, 0xa597ab9b, 
	0x1740bf80, 0xb981b902, 0xb883b804, 0xd0050c70, 0xb0781180, 0xd1601060, 
	0xaa88d080, 0x10601760, 0xbb8033b8, 0x1760c380, 0xaa8013e4, 0x1760c385, 
	0xd03213e0, 0x1760d098, 0xc380d17f, 0x1460ab9b, 0x1760d087, 0xc1801018, 
	0xabb7d00a, 0xa8011760, 0xd085c000, 0xaf74d300, 0xdb801760, 0xd10cc380, 
	0xae971018, 0xaa271760, 0xd089c600, 0xd1121060, 0xaa92d737, 0xa801aa66, 
	0xd46ea801, 0x1760d087, 0xb800aa32, 0xd05ba801, 0xd458a801, 0xd70f1061, 
	0xaa56d1fe, 0x70001760, 0xd087b800, 0x5b8213be, 0x0f38b900, 0x2c92d1f4, 
	0x8c80d040, 0x2c90d1f0, 0x74801760, 0xbe982bec, 0x8b861760, 0xbb80d080, 
	0x2bb8d1e6, 0x8b801760, 0xbbb11c8f, 0x7c8ad7f0, 0x1061aa56, 0xd1dd7000, 
	0x2bead1da, 0x7380d0ce, 0xa001afdb, 0x881bd310, 0xdb802bbc, 0x73861760, 
	0xbb851760, 0xd085c380, 0xaedcd008, 0x13e01760, 0xc385d700, 0x1061aa56, 
	0xd7b0707f, 0x1760d082, 0xb800abb7, 0xd0821060, 0xaa4fa5d6, 0xd310db80, 
	0x2bbb738c, 0x1760b802, 0x1760bbad, 0x1b878be5, 0x1760d085, 0xbb801760, 
	0xc385af0e, 0x1760d087, 0xb800abb7, 0xaf218803, 0xd0901060, 0xa65caff1, 
	0xaff2afa6, 0x8813affb, 0x8803d091, 0x1060a65c, 0xaf9a1760, 0xd083bb80, 
	0xd0802cb8, 0xd1918c80, 0xd1001060, 0xaa80a7e9, 0xaf87a7e9, 0xae70d7b2, 
	0x707fae9e, 0xaec8d00a, 0xa8011760, 0xbe85d76d, 0x907f1760, 0xc005af2d, 
	0xaf74d087, 0xa801a5d6, 0x1760d087, 0xbc805f4b, 0xd0045848, 0x0070d040, 
	0x10000f00, 0xb80a1760, 0xd101bb80, 0x1bb88397, 0x1760b805, 0x16e59019, 
	0x1760d086, 0xbb80083f, 0x1760d086, 0xc0007010, 0x10620f47, 0xc7801470, 
	0xaa5d1740, 0xbf801471, 0x88070867, 0xa7e9d00a, 0x0be01760, 0xd086c380, 
	0x0860b078, 0x0f45c102, 0xc181c780, 0x14701760, 0xd087b800, 0x59021116, 
	0x5f03d004, 0x598001f3, 0xd0401198, 0x0f10b882, 0x0f18bb86, 0xd7fb5d3f, 
	0x03d71760, 0xbd131d57, 0x7d021760, 0xbb93188f, 0x88841061, 0xaa5dd128, 
	0x70001008, 0x0f40bf80, 0xb981b902, 0x1473b078, 0x1760d08d, 0xbc801760, 
	0xd089bb80, 0x1bcf7388, 0x1760bd39, 0x03d77b87, 0xd0921060, 0xaf87a7e9, 
	0x1760d089, 0xc480b078, 0x0f46c001, 0xc7801470, 0x1064d310, 0xe000aef6, 
	0x1760d7a0, 0xb801d6f7, 0xa8011760, 0xd087b800, 0xab881760, 0xb825d711, 
	0xa8010f40, 0xbf80b801, 0x1472b078, 0x1760d300, 0xbb801760, 0xd10bbc80, 
	0x1ccf7481, 0x0ce01760, 0xd10bc480, 0xb0781760, 0xd10bbc80, 0x1760d300, 
	0xbb8004cf, 0x1760d10b, 0xc480b078, 0x0f46c001, 0xc7801470, 0x1760d087, 
	0xb800ab53, 0xaf03af2d, 0xd087a801, 0xd6fda801, 0x0f40bf80, 0xb8011472, 
	0xb0781760, 0xd300bb80, 0x1760d10b, 0xb8001807, 0x88020860, 0xb0781061, 
	0xb078d7fb, 0x0f47c004, 0xc083c102, 0xc181c780, 0x14701760, 0xd087b800, 
	0x5f03d004, 0x598001f3, 0xd0401198, 0x0f18b90b, 0x1760bb85, 0xd7fb0d3f, 
	0x75050f18, 0xb8010f18, 0xb882a758, 0xd7fa0d3f, 0x75050f18, 0xb8060f18, 
	0xb884a758, 0x0f18b807, 0x0f18b889, 0x0f18b90c, 0x10000f18, 0xbb941cb8, 
	0x74810838, 0xd316e000, 0x2817d32c, 0xe0005815, 0x1760d209, 0xc000d3dc, 
	0xa801d317, 0xe0801740, 0xbf80b981, 0xb902b883, 0xb804d005, 0x0c70b078, 
	0xd7fb0b87, 0x7b810be0, 0x0f38bca0, 0xd00f5cc8, 0xd310db80, 0x2bbb8b83, 
	0xd300db80, 0x04cf1760, 0xd10bc480, 0xb0780f47, 0xc7801470, 0xaa921740, 
	0xbf801471, 0x1760d087, 0xbb805bba, 0x13be0f38, 0xbc80d100, 0x14c80f38, 
	0xc480b078, 0x1760d087, 0xbb805bba, 0x13be0f38, 0xbc80d0ff, 0x2ccf0f38, 
	0xc480b078, 0x0f45c082, 0xc101c780, 0x14701760, 0xd087bc80, 0x5f4bd004, 
	0x59480172, 0xd0401110, 0x1760bb85, 0xd7f90bbf, 0x83961760, 0xd225bb80, 
	0xd0102cb8, 0x1760d088, 0xbb808c8f, 0xd38da801, 0x0f10bb88, 0x1b8f7387, 
	0x1760d088, 0xbb800bbf, 0x73841061, 0xa7d21760, 0xbbaa0860, 0x1760d088, 
	0xc3800f40, 0xbf80b901, 0xb8821473, 0xb0781760, 0xb8021760, 0xbbae1b87, 
	0x83861760, 0xbb982bb9, 0x73820860, 0xb0781061, 0xb0781064, 0xd310e000, 
	0xd0801060, 0xaa88ab9b, 0xa4a5b078, 0x0f47c780, 0x1470d38d, 0xa8011740, 
	0xbf801471, 0xb0781760, 0xd300bb80, 0x1760d10c, 0xb8001bb8, 0xd0300bbf, 
	0x7b831061, 0xd009a001, 0x0860b078, 0xd7fb0f47, 0xc084c103, 0xc182c681, 
	0xc7801470, 0x1760be85, 0x1067903b, 0x1760d087, 0xb8005902, 0x11165f03, 
	0xd0045980, 0x01f3d040, 0x11980f10, 0xb8820f18, 0xbb831b8f, 0x7b8316e5, 
	0xd051a001, 0x0f18bb86, 0xd7f80bbf, 0x1b8f839a, 0xd310db80, 0x2bbc7396, 
	0x1760d101, 0xb8800f18, 0xbb851b8f, 0x7b8a1760, 0xd098bb80, 0x0bbf838d, 
	0x1760d098, 0xc380d04a, 0xa001d032, 0x13e01760, 0xd098c380, 0x16e6d051, 
	0xa0011760, 0xd225bb80, 0x16e71068, 0x1740bf80, 0xbe81b982, 0xb903b884, 
	0xd0050c70, 0xb0780f44, 0xc003c082, 0xc681c780, 0x14701760, 0xd081b800, 
	0xac065b82, 0x13be0f38, 0xbb8016e6, 0x23ef9b90, 0xd310db80, 0x2bbc7388, 
	0xaedc1760, 0xd081b800, 0xabb7af0e, 0xd07ca001, 0x1760d081, 0xb800abb7, 
	0xd0811060, 0xaa4f1740, 0xbf80be81, 0xb882b803, 0xd0040c70, 0xb0780f45, 
	0xc002c081, 0xc7801470, 0x13e1d310, 0xe380d064, 0x1060d711, 0xa801d38d, 
	0xa8010f40, 0xbf80b881, 0xb8021473, 0xb0780f46, 0xc081c780, 0x14701080, 
	0x08077018, 0xd70f1061, 0xaa567014, 0x5b8a13be, 0x0f38bc80, 0x2bca8b8e, 
	0xd0402bc8, 0x738bd700, 0x2cc8d7f8, 0x5ccf1760, 0xbba4184f, 0x78031061, 
	0xd0bba001, 0x08600f40, 0xbf80b881, 0x1472b078, 0x1760d087, 0xc000ab53, 
	0xd0203860, 0x1760bb80, 0x33b81760, 0xc380aa80, 0xd337a801, 0xd1c01060, 
	0xaa8813e1, 0x1760d09f, 0xc380d009, 0x13e01760, 0xc385d17f, 0x1460d331, 
	0xa8017682, 0xd34ea801, 0x1760d080, 0xbb801760, 0xd087c380, 0xd213a801, 
	0x1760d087, 0xbb800bbf, 0xd0de7380, 0x1760d113, 0xc600d259, 0xa801d331, 
	0xa8017682, 0xd261a801, 0xd6fda801, 0xd1131060, 0xaa921760, 0xd087b800, 
	0xabb7aaa3, 0xaa66d213, 0xa8017817, 0x1760d087, 0xb980591a, 0x11160f10, 
	0xbb80d080, 0x2cb8d1e0, 0x74802bba, 0xd1dd8b80, 0xd426a801, 0xabb70f10, 
	0xbb80d010, 0x2bb8d0af, 0x73801760, 0xd087b980, 0x591a1116, 0x0f10b880, 
	0xd331a801, 0x8eb52b89, 0x8b90d080, 0x2b88738d, 0xd0102b88, 0x73871760, 
	0xd08fbb80, 0x0f10b802, 0x1b8773a6, 0xd0401060, 0xaa80d020, 0x1060aa88, 
	0xd458a801, 0x1760bbb1, 0x1b8f8385, 0x14e31760, 0xc485d2f1, 0xa0017b84, 
	0xd34ea801, 0xd261a801, 0xd259a801, 0xd3b81061, 0xd6f7a801, 0xd342a801, 
	0xd3b81061, 0xd6f7a801, 0x13e11760, 0xd0a0c380, 0xd2c9a801, 0x5f1bd004, 
	0x5b9803f7, 0xd04013b8, 0x0f38bb95, 0x1b8f7b8a, 0xd326a801, 0x70070862, 
	0xaa80d00c, 0x1060aafe, 0xd177a001, 0x0862aa88, 0xd0081060, 0xaafed265, 
	0xa801d310, 0xdb802bbb, 0x738fd38d, 0xa8011760, 0xd114c080, 0x1760bbbc, 
	0x1760d115, 0xc380038f, 0x738313e6, 0xd310e380, 0xd35da801, 0xd458a801, 
	0xd331a801, 0x8e861760, 0xbbb11c8f, 0x7c82d139, 0xa001768c, 0x1760bbb2, 
	0x1c8f8c88, 0x1064aafe, 0xd2001060, 0xaa8814e3, 0xd2f1a001, 0x1760d087, 
	0xb800ac06, 0x1760d081, 0xb800ac06, 0xd0811060, 0xaa4fd705, 0xa8018808, 
	0xd6fda801, 0xd46ea801, 0x1760d087, 0xb800aa32, 0xd35da801, 0xd7f01061, 
	0xaa56d12e, 0x70001760, 0xbb982bba, 0xd1297380, 0xd737a801, 0xd0faa001, 
	0x1064aa80, 0xd0201060, 0xaa88d300, 0xdb80d680, 0x13bf1760, 0xd109c380, 
	0xd00a13e0, 0x1760c385, 0xd705a801, 0x7029aa66, 0xd458a801, 0x1760bbb2, 
	0x188f7098, 0x1760d081, 0xb800ac06, 0xd0811060, 0xaa4fd35d, 0xa8011760, 
	0xd087b800, 0xabb75b82, 0x13be0f38, 0xbb80d010, 0x2bb88b84, 0xd213a801, 
	0xd1dca001, 0x1064aa88, 0xd6fda801, 0xd00913e0, 0x1760c385, 0xd139a001, 
	0xab9baa66, 0xd458a801, 0x1760bbb2, 0x188f88f9, 0xd1fea001, 0xb078d7fb, 
	0x0f47c084, 0xc103c182, 0xc681c780, 0x14701760, 0xd087b900, 0xd331a801, 
	0x76910b97, 0x73925b92, 0x13be0f38, 0xb88016e1, 0x1760d083, 0xbc80d000, 
	0x2bc97381, 0x3eead093, 0x2b889b83, 0x1190d24f, 0xa001aac7, 0x16e311e1, 
	0x5b9a13be, 0x0f38b880, 0xd0932b88, 0x9b82d245, 0xa001099f, 0x79f5d24f, 
	0xa0011018, 0xab531010, 0xaa321018, 0xaa27abb7, 0x1760d087, 0xc1801018, 
	0x1740bf80, 0xbe81b982, 0xb903b884, 0xd0050c70, 0xb078d00c, 0x13e0d310, 
	0xe38013e4, 0xd310e380, 0xb07813e1, 0xd307e380, 0xb0781760, 0xd083bb80, 
	0xd0002bb9, 0x8b81b078, 0xd7fb0f47, 0xc004c103, 0xc182c681, 0xc7801470, 
	0x1760d087, 0xb9805f1b, 0xd0045998, 0x01f3d040, 0x1198d300, 0xd900d35d, 
	0xa8010f18, 0xbb8f038f, 0x8bb31760, 0xd08ebe80, 0x0f18bb8d, 0x038f73a6, 
	0x2be97389, 0x3ee90f18, 0xbb900397, 0x1760d10d, 0xc380d29c, 0xa0011760, 
	0xd10dbb80, 0x1bba839c, 0x0f18bb8e, 0x038f7394, 0x2bea7389, 0x3eea0f18, 
	0xbb9103ba, 0x1760d10e, 0xc380d2bd, 0xa0011760, 0xd10dbb80, 0x1bba8388, 
	0xd2bda001, 0xd7fe2eef, 0xd7fd2eef, 0xd2bda001, 0xd0101060, 0xaa5dd2f1, 
	0xa0011760, 0xd08ec680, 0x1740bf80, 0xbe81b982, 0xb903b804, 0xd0050c70, 
	0xb0780f44, 0xc003c082, 0xc101c780, 0x14701760, 0xd087b800, 0xabb7d310, 
	0xdc802ccb, 0x0cce848f, 0xaad3d458, 0xa8011888, 0x708ad38d, 0xa8011760, 
	0xbbbe188f, 0x8084d020, 0x1060aa5d, 0x700ad35d, 0xa8011740, 0xbf80b901, 
	0xb882b803, 0xd0040c70, 0xb078d259, 0xa8011760, 0xb823d711, 0xa801d342, 
	0xa8011760, 0xb823d711, 0xa801d307, 0xe6001760, 0xd087b800, 0xaa32aa47, 
	0xd2581060, 0xd6f7a801, 0xa4a50f46, 0xc081c780, 0x14701080, 0x08077010, 
	0xd7f01061, 0xaa56700c, 0x5b8a13be, 0x0f38bc80, 0x2bca8b86, 0xd0902bc8, 
	0x73831061, 0xd321a001, 0x08600f40, 0xbf80b881, 0x1472b078, 0x1760d087, 
	0xb8001001, 0x28015802, 0x10060f00, 0xb800283a, 0xb0781760, 0xd083be80, 
	0xd0202ee8, 0xb0781760, 0xd243c600, 0x3be21760, 0xd243c380, 0x1760d243, 
	0xc600b078, 0x13e11760, 0xd243c380, 0x3cba1760, 0xd243c480, 0x1760d243, 
	0xc380b078, 0x0f47c780, 0x1470d008, 0x1060aafe, 0xd2001060, 0xaa80d304, 
	0xe3801740, 0xbf801471, 0xb0780f46, 0xc001c780, 0x14701760, 0xd0a0bb80, 
	0x8b8c1760, 0xd22bbb80, 0x1760d22b, 0xbb80d010, 0x2bb88bfa, 0x1760d0a0, 
	0xc6001760, 0xd223b880, 0x1760d104, 0xb800588c, 0x1760bb8e, 0x188f0088, 
	0x1760b811, 0xab181760, 0xbb921be7, 0x608fd3cd, 0xa8011760, 0xd101c080, 
	0x0f40bf80, 0xb8011472, 0xb0781760, 0xbb85d7f7, 0x0bbf7bcb, 0x0f47c780, 
	0x14701760, 0xd0a0bb80, 0x8b9613e1, 0xd323e380, 0xd321db80, 0x2bbad321, 
	0xe380d016, 0x13e01760, 0xd20dc380, 0x1760d225, 0xb8801760, 0xd225b880, 
	0xd0102888, 0x88fa1760, 0xd21db880, 0x688cd3cd, 0xa8011760, 0xd101c080, 
	0x1760d0a0, 0xbb808b8d, 0xd321db80, 0x3bb9d321, 0xe380d008, 0x13e01760, 
	0xd20dc380, 0x1760d0a0, 0xc6001740, 0xbf801471, 0xb0780f46, 0xc001c780, 
	0x14701760, 0xb826ab18, 0x1760b827, 0xab300f40, 0xbf80b801, 0x1472b078, 
	0x0f46c001, 0xc7801470, 0x1760b827, 0xab181760, 0xb826ab30, 0x0f40bf80, 
	0xb8011472, 0xb0781760, 0xd09fbb80, 0x8b891760, 0xd224b880, 0x1760d224, 
	0xb880d010, 0x288888fa, 0x1760d21c, 0xb880588c, 0x5b8213be, 0x0f38c082, 
	0x1760d08d, 0xc0801760, 0xd09fc600, 0xd310db80, 0x2bbc8b97, 0x1760bbab, 
	0x1b8f8393, 0x1760d0a1, 0xbb800bbf, 0x738f1760, 0xd0a2c080, 0x0f46c001, 
	0xc7801470, 0xd0001061, 0xaa5d0f40, 0xbf80b801, 0x147213e5, 0x1760d0a1, 
	0xc380b078, 0x13e11760, 0xd09fc380, 0x13e31760, 0xd20cc380, 0xd321db80, 
	0x2bbad321, 0xe3807384, 0xd323e600, 0xd43ba001, 0x13e4d323, 0xe3801760, 
	0xd224b880, 0x1760d224, 0xb880d010, 0x28887082, 0xd43ea001, 0x1760d21c, 
	0xb880588c, 0x1760d0a5, 0xc08013e6, 0x1760d20c, 0xc380d321, 0xdb803bb9, 
	0xd321e380, 0xd403a001, 0x1760d222, 0xb880588c, 0x1760c082, 0x0f46c001, 
	0xc7801470, 0x1760bbac, 0x1b8f8383, 0xd1001060, 0xaa5d0f40, 0xbf80b801, 
	0x1472b078, 0x1760d21f, 0xb880588c, 0x1760c081, 0x1760d246, 0xbb805bbc, 
	0x1760c396, 0xb0780f47, 0xc1001470, 0x0f00d220, 0xb9005914, 0x0f00d228, 
	0xb8800f00, 0xd228b880, 0xd0202888, 0x88fa0f00, 0xd218b880, 0x5b8213be, 
	0x0f38c101, 0x1740b900, 0x1471b078, 0x0f45c002, 0xc101c780, 0x14701760, 
	0xd20db900, 0xd00a1060, 0x1760d20d, 0xc0001760, 0xd213c000, 0x1760d225, 
	0xb8001760, 0xd22bb800, 0x1760d22b, 0xb800d010, 0x28008806, 0x1760d225, 
	0xb800d010, 0x28007009, 0xd458a801, 0x1760bbb1, 0x188f8890, 0xaa66d4ac, 
	0xa0011760, 0xd223b880, 0x688c1760, 0xbb8e19b9, 0x1760d21d, 0xb880688c, 
	0xd4d2a001, 0x1760b8bb, 0xd00a1088, 0xd00813e0, 0x1760d213, 0xc3801760, 
	0xd20dc100, 0x0f40bf80, 0xb901b802, 0x1473b078, 0x0f44c003, 0xc082c181, 
	0xc7801470, 0xd30ed800, 0x70271760, 0xd093b800, 0x88060807, 0x1760d093, 
	0xc000d510, 0xa001d496, 0xa8011008, 0x70011860, 0x1760bbbb, 0x18077014, 
	0xd32bd800, 0x1881d32b, 0xe0801760, 0xd097c080, 0x1760d104, 0xc1801061, 
	0x1760d094, 0xc000d078, 0x08601760, 0xd093c000, 0x1740bf80, 0xb981b882, 
	0xb803d004, 0x0c70b078, 0x0f44c003, 0xc082c101, 0xc7801470, 0x1160d316, 
	0xdb801760, 0xd09ac380, 0xd317db80, 0x1760d09b, 0xc380d310, 0xdb801760, 
	0xd09cc380, 0xd32cdb80, 0x1760d09d, 0xc3801760, 0xd209bb80, 0x1760d09e, 
	0xc38013e4, 0xd310e380, 0xac685f03, 0xd0045880, 0x00f1d040, 0x10880f08, 
	0xbb94d316, 0xe3801760, 0xbbb3d317, 0xe38013e1, 0xd32ce380, 0xd07413e0, 
	0x1760d209, 0xc380d340, 0xe6001760, 0xbbb4d341, 0xe3801760, 0xbbb5d342, 
	0xe3801760, 0xbbb6d343, 0xe38013e1, 0xd310e380, 0x13e1d33f, 0xe380d33f, 
	0xe6001065, 0xd6f7a801, 0xd336db80, 0x73831166, 0xd582a001, 0xd458a801, 
	0x1760bbae, 0x1b8f7b83, 0x1166d582, 0xa001d43c, 0x13e71760, 0xc397d33d, 
	0xdb808bf0, 0x13e4d310, 0xe3801760, 0xd09abb80, 0xd316e380, 0x1760d09b, 
	0xbb80d317, 0xe3801760, 0xd09dbb80, 0xd32ce380, 0x1760d09e, 0xbb801760, 
	0xd209c380, 0x1760d099, 0xb800ab53, 0x1760d09c, 0xbb80d310, 0xe3801010, 
	0x1740bf80, 0xb901b882, 0xb803d004, 0x0c70b078, 0xd7fa0f47, 0xc005c084, 
	0xc103c182, 0xc201c780, 0x14700f47, 0xc0001470, 0x11081760, 0xd084c600, 
	0xd6b8a801, 0x7007d008, 0x13e01760, 0xd084c380, 0xd5e9a001, 0x1740b800, 
	0xd0cc10e0, 0xd6e3a801, 0xd0f010e0, 0xd6e3a801, 0xd0055890, 0xd6e3a801, 
	0x08e0d6e3, 0xa801d6d2, 0xa801d010, 0x116009e0, 0xd6d2a801, 0xd0085a08, 
	0xd6d2a801, 0x308c0f18, 0xd070c080, 0x11990917, 0x71731740, 0xb8001471, 
	0x1740bf80, 0xba01b982, 0xb903b884, 0xb805d006, 0x0c70b078, 0x13e3d308, 
	0xe380d309, 0xe600d333, 0xdb80d100, 0x3bb8d333, 0xe380b078, 0xd333db80, 
	0xd0ff2bb8, 0xd333e380, 0xb0780f44, 0xc003c102, 0xc181c780, 0x14701080, 
	0x09634182, 0xd308e180, 0x1066d6f7, 0xa801d308, 0xe100d009, 0x1060d6f7, 
	0xa801d30a, 0xdb8020b9, 0x888110e1, 0xd0341060, 0xd6f7a801, 0x1740bf80, 
	0xb981b902, 0xb803d004, 0x0c70b078, 0xd7fb0f47, 0xc004c103, 0xc182c201, 
	0xc7801470, 0x09634182, 0xd308e180, 0x7088d03c, 0x1060d6f7, 0xa801d00a, 
	0x1060d648, 0xa0011066, 0xd6f7a801, 0xd0401060, 0xd308e100, 0xd6f7a801, 
	0x1740bf80, 0xba01b982, 0xb903b804, 0xd0050c70, 0xb078d7f9, 0x0f47c086, 
	0xc105c184, 0xc203c282, 0xc681c780, 0x14700f47, 0xc0001470, 0x1760d084, 
	0xc600d6b8, 0xa8017007, 0xd00813e0, 0x1760d084, 0xc380d6a5, 0xa0011740, 
	0xb800d0f0, 0x10e0d6e3, 0xa8011162, 0xd5f6a801, 0x13e15038, 0xd02011e0, 
	0x12a00a60, 0x0ce0d609, 0xa8010f47, 0xc0801470, 0xd609a801, 0x1740be80, 
	0x14719094, 0x10e8d62e, 0xa8015a27, 0xd01f5888, 0x3221099f, 0x71ec0917, 
	0x71651760, 0xd102c280, 0x1760d103, 0xc20014c9, 0xd6a5a001, 0x1760d0e8, 
	0xc48013e7, 0x1760d084, 0xc380d602, 0xa8011740, 0xb8001471, 0x1760d084, 
	0xb8001740, 0xbf80be81, 0xba82ba03, 0xb984b905, 0xb886d007, 0x0c70b078, 
	0x0f46c081, 0xc7801470, 0xd00b5b80, 0xd0003bba, 0xd332e380, 0xd6caa801, 
	0x28090f40, 0xbf80b881, 0x1472b078, 0xd334d880, 0xd1002b88, 0x8bfbd0ff, 
	0x2888b078, 0x0f46c001, 0xc7801470, 0xd00b5b80, 0xd2003bba, 0xd332e380, 
	0xd6caa801, 0x0f40bf80, 0xb8011472, 0xb0780f45, 0xc002c081, 0xc7801470, 
	0xd00b5b80, 0xd1003bba, 0x33b9d332, 0xe380d6ca, 0xa8010f40, 0xbf80b881, 
	0xb8021473, 0xb078d301, 0xe000d301, 0xd800707d, 0xb078d300, 0xdb80d3e8, 
	0x13b81760, 0xd109c380, 0xb078d300, 0xdb801760, 0xd109b800, 0x1b878b83, 
	0x0860d710, 0xa0011061, 0xb0780f45, 0xc082c681, 0xc7801470, 0xd300db80, 
	0x0007d300, 0xde809015, 0x1760bb98, 0x2bba73f9, 0x1760bb85, 0x8bf6d7f7, 
	0x0bbf7bf3, 0xd458a801, 0x1760bbb1, 0x1b8f73ed, 0x13e4d310, 0xe380d0ce, 
	0xa0010f40, 0xbf80be81, 0xb8821473, 0xb0780f44, 0xc003c082, 0xc681c780, 
	0x14701760, 0xb8992b89, 0xd0468b80, 0xd7801060, 0x0be74007, 0x20885b8e, 
	0xd01f2bb8, 0x8baf0bbf, 0x8bad0bbf, 0xd0638b80, 0x0bbfd074, 0x8b800bbf, 
	0xd07a8b80, 0x0bbfd07b, 0x8b800bbf, 0xd08d8b80, 0x0bbfd08f, 0x8b800bbf, 
	0xd09c8b80, 0x0bbfd0a5, 0x8b800bbf, 0xd0ae8b80, 0x0bbfd0be, 0x8b800bbf, 
	0xd0c98b80, 0x0bbfd0d2, 0x8b800bbf, 0xd1018b80, 0x0bbfd110, 0x8b800bbf, 
	0xd1138b80, 0xd0803888, 0xd784a001, 0x1760c01a, 0xd7f05807, 0x1760c01b, 
	0xd79ca801, 0x1760c099, 0x1740bf80, 0xbe81b882, 0xb803d004, 0x0c70b078, 
	0xd1803888, 0xd784a001, 0xd2803888, 0xd784a001, 0xd2003888, 0xd784a001, 
	0x0ce10be7, 0x44cf20c9, 0xb0780f46, 0xc081c780, 0x1470d79c, 0xa8011760, 
	0xc0990f40, 0xbf80b881, 0x1472b078, 0xd7f5580f, 0x0b8773e2, 0xb078d7ae, 
	0xa8010f47, 0xc0801470, 0x1760b89a, 0xd5aca801, 0x1760d084, 0xb8001740, 
	0xb8801471, 0xd0075800, 0x3088d784, 0xa001d7ae, 0xa801d655, 0xa801d007, 
	0x58003088, 0xd784a001, 0x1760c603, 0xd784a001, 0x1760bb85, 0x16e39bc0, 
	0xd7f5580f, 0xd309a801, 0xd7b6887f, 0x1760b81a, 0x1760d08f, 0xc000d7a1, 
	0xa801d7f5, 0x580fd0c0, 0xa001d020, 0x1060aa88, 0xd784a001, 0x1760bb85, 
	0x16e3d7a5, 0x9bffd7f5, 0x580fd09b, 0xa801d79b, 0x887fd7a1, 0xa801d7f5, 
	0x580fa5a9, 0x1760be85, 0x0bec8386, 0xd7f80bef, 0x7383d7a1, 0xa801a7e9, 
	0xd784a001, 0xd7aea801, 0x5b8213be, 0x0f38b800, 0xd0ff2807, 0x0f38c000, 
	0xd784a001, 0xd7aea801, 0x5b8213be, 0x0f38b800, 0xd7ff2804, 0xd00014e2, 
	0x30483802, 0x0f38c000, 0xd0001061, 0xaa88d784, 0xa001d7ae, 0xa8015b82, 
	0x13be0f38, 0xb800d7fd, 0x2804d000, 0x38030f38, 0xc000d784, 0xa001d7f5, 
	0x580f2801, 0x5801d321, 0xdb802bb9, 0x33b8d321, 0xe380d784, 0xa001d7f5, 
	0x580f0b85, 0x73811380, 0x0cbed745, 0x84ff0cbf, 0xd74274ff, 0xd323db80, 
	0x0f47c380, 0x1470d323, 0xe000d321, 0xdb800f47, 0xc3801470, 0x2bbad321, 
	0xe3801760, 0xd226bb80, 0x1760d226, 0xbb80d090, 0x2bb88bfa, 0x1760d21e, 
	0xb8001740, 0xbb801471, 0xd321e380, 0x1740bb80, 0x1471d323, 0xe380d77e, 
	0xa001d7ae, 0xa8011760, 0xd102bb80, 0xd330e380, 0x1760d103, 0xbb80d331, 
	0xe50013e1, 0x53b8d31e, 0xe380d784, 0xa0011760, 0xbb9ad32a, 0xe380d784, 
	0xa001d7ae, 0xa801d336, 0xdb80d705, 0x73ff1760, 0xbc821760, 0xbbad1ccf, 
	0xd6fe84ff, 0x1760be85, 0x0be39383, 0x13e6d6f7, 0x9bff5b82, 0x13be0f38, 
	0xbb802bba, 0xd6ec8bff, 0x0f47c080, 0x14701760, 0xd080bb80, 0x1760d099, 
	0xc380ab53, 0xd426a801, 0x5f03d004, 0x5b8003f7, 0xd04013b8, 0x0f38bb83, 
	0x1b8f8391, 0xd518a801, 0x1740b880, 0x1471d007, 0x58003088, 0xd33bd800, 
	0xd0105800, 0xd33cdb80, 0x3007d77e, 0xa0011740, 0xb8801471, 0xd4803888, 
	0xd784a001, 0x00000000
};

#endif
