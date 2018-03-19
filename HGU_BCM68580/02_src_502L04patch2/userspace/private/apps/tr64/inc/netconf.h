/*
 * Network configuration layer
 *
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 *
 * <:label-BRCM:2012:proprietary:standard
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
 *
 * $Id: netconf.h,v 1.24.8.1 2003/10/16 21:26:01 mthawani Exp $
 */

#ifndef _netconf_h_
#define _netconf_h_

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <typedefs.h>
#include <ethernet.h>

/* Supported match states */
#define NETCONF_INVALID		0x01	/* Packet could not be classified */
#define NETCONF_ESTABLISHED	0x02	/* Packet is related to an existing connection */
#define NETCONF_RELATED		0x04	/* Packet is part of an established connection */
#define NETCONF_NEW		0x08	/* Packet is trying to establish a new connection */

/* Supported match flags */
#define	NETCONF_INV_SRCIP	0x01	/* Invert the sense of source IP address */
#define	NETCONF_INV_DSTIP	0x02	/* Invert the sense of destination IP address */
#define	NETCONF_INV_SRCPT	0x04	/* Invert the sense of source port range */
#define	NETCONF_INV_DSTPT	0x08	/* Invert the sense of destination port range */
#define NETCONF_INV_MAC		0x10	/* Invert the sense of source MAC address */
#define NETCONF_INV_IN		0x20	/* Invert the sense of inbound interface */
#define NETCONF_INV_OUT		0x40	/* Invert the sense of outbound interface */
#define NETCONF_INV_STATE	0x80	/* Invert the sense of state */
#define NETCONF_INV_DAYS	0x100	/* Invert the sense of day of the week */
#define NETCONF_INV_SECS	0x200	/* Invert the sense of time of day */

/* Entry is disabled */
#define NETCONF_DISABLED	0x80000000

/* Match description */
typedef struct _netconf_match_t {
	int ipproto;			/* IP protocol (TCP/UDP) */
	struct {
		struct in_addr ipaddr;	/* Match by IP address */
		struct in_addr netmask;
		uint16 ports[2];	/* Match by TCP/UDP port range */
	} src, dst;
	struct ether_addr mac;		/* Match by source MAC address */
	struct {
		char name[IFNAMSIZ];	/* Match by interface name */
	} in, out;
	int state;			/* Match by packet state */
	int flags;			/* Match flags */
	uint days[2];			/* Match by day of the week (local time) (0 == Sunday) */
	uint secs[2];			/* Match by time of day (local time) (0 == 12:00 AM) */
	struct _netconf_match_t *next, *prev;
} netconf_match_t;

#define netconf_valid_ipproto(ipproto) \
	((ipproto == 0) || (ipproto) == IPPROTO_TCP || (ipproto) == IPPROTO_UDP)

/* Supported firewall target types */
enum netconf_target {
	NETCONF_DROP,			/* Drop packet (filter) */
	NETCONF_ACCEPT,			/* Accept packet (filter) */
	NETCONF_LOG_DROP,		/* Log and drop packet (filter) */
	NETCONF_LOG_ACCEPT,		/* Log and accept packet (filter) */
	NETCONF_SNAT,			/* Source NAT (nat) */
	NETCONF_DNAT,			/* Destination NAT (nat) */
	NETCONF_MASQ,			/* IP masquerade (nat) */
	NETCONF_APP,			/* Application specific port forward (app) */
	NETCONF_TARGET_MAX
};

#define netconf_valid_filter(target) \
	((target) == NETCONF_DROP || (target) == NETCONF_ACCEPT || \
	 (target) == NETCONF_LOG_DROP || (target) == NETCONF_LOG_ACCEPT)

#define netconf_valid_nat(target) \
	((target) == NETCONF_SNAT || (target) == NETCONF_DNAT || (target) == NETCONF_MASQ)

#define netconf_valid_target(target) \
	((target) >= 0 && (target) < NETCONF_TARGET_MAX)

#define NETCONF_FW_COMMON \
	netconf_match_t match;		/* Match type */ \
	enum netconf_target target;	/* Target type */ \
	char desc[40];			/* String description */ \
	struct _netconf_fw_t *next, *prev \

/* Generic firewall entry description */
typedef struct _netconf_fw_t {
	NETCONF_FW_COMMON;
	char data[0];			/* Target specific */
} netconf_fw_t;

/* Supported filter directions */
enum netconf_dir {
	NETCONF_IN,			/* Packets destined for the firewall */
	NETCONF_FORWARD,		/* Packets routed through the firewall */
	NETCONF_OUT,			/* Packets generated by the firewall */
	NETCONF_DIR_MAX
};

#define netconf_valid_dir(dir) \
	((dir) >= 0 && (dir) < NETCONF_DIR_MAX)

/* Filter target firewall entry description */
typedef struct _netconf_filter_t {
	NETCONF_FW_COMMON;
	enum netconf_dir dir;		/* Direction to filter */
} netconf_filter_t;

/* NAT target firewall entry description */
typedef struct _netconf_nat_t {
	NETCONF_FW_COMMON;
	struct in_addr ipaddr;		/* Address to map packet to */
	uint16 ports[2];		/* Port(s) to map packet to (network order) */
} netconf_nat_t;

/* Application specific port forward description */
typedef struct _netconf_app_t {
	NETCONF_FW_COMMON;
	uint16 proto;			/* Related protocol */
	uint16 dport[2];		/* Related destination port(s) (network order) */
	uint16 to[2];			/* Port(s) to map related destination port to (network order) */
} netconf_app_t;

/* Generic doubly linked list processing macros */
#define netconf_list_init(head) ((head)->next = (head)->prev = (head))

#define netconf_list_empty(head) ((head)->next == (head))

#define netconf_list_add(new, head) do { \
	(head)->next->prev = (new); \
	(new)->next = (head)->next; \
	(new)->prev = (head); \
	(head)->next = (new); \
} while (0)

#define netconf_list_del(old) do { \
	(old)->next->prev = (old)->prev; \
	(old)->prev->next = (old)->next; \
} while (0)

#define netconf_list_for_each(pos, head) \
	for ((pos) = (head)->next; (pos) != (head); (pos) = (pos)->next)

#define netconf_list_free(head) do { \
	typeof (head) pos, next; \
	for ((pos) = (head)->next; (pos) != (head); (pos) = next) { \
		next = pos->next; \
		netconf_list_del(pos); \
		free(pos); \
	} \
} while (0)

/* 
 * Functions that work on arrays take a pointer to the array byte
 * length. If the length is zero, the function will set the length to
 * the number of bytes that must be provided to fulfill the
 * request. If the length is non-zero, then the array will be
 * constructed until the buffer length is exhausted or the request is
 * fulfilled.
 */

/*
 * Add a firewall entry
 * @param	fw	firewall entry
 * @return	0 on success and errno on failure
 */
extern int netconf_add_fw(netconf_fw_t *fw);

/*
 * Delete a firewall entry
 * @param	fw	firewall entry
 * @return	0 on success and errno on failure
 */
extern int netconf_del_fw(netconf_fw_t *fw);

/*
 * Get a list of the current firewall entries
 * @param	fw_list		list of firewall entries
 * @return	0 on success and errno on failure
 */
extern int netconf_get_fw(netconf_fw_t *fw_list);

/*
 * See if a given firewall entry already exists
 * @param	nat	NAT entry to look for
 * @return	whether NAT entry exists
 */
extern bool netconf_fw_exists(netconf_fw_t *fw);

/*
 * Reset the firewall to a sane state
 * @return 0 on success and errno on failure */
extern int netconf_reset_fw(void);

/*
 * Add a NAT entry or list of NAT entries
 * @param	nat_list	NAT entry or list of NAT entries
 * @return	0 on success and errno on failure
 */
extern int netconf_add_nat(netconf_nat_t *nat_list);

/*
 * Delete a NAT entry or list of NAT entries
 * @param	nat_list	NAT entry or list of NAT entries
 * @return	0 on success and errno on failure
 */
extern int netconf_del_nat(netconf_nat_t *nat_list);

/*
 * Get an array of the current NAT entries
 * @param	nat_array	array of NAT entries
 * @param	space		Pointer to size of nat_array in bytes
 * @return 0 on success and errno on failure
 */
extern int netconf_get_nat(netconf_nat_t *nat_array, int *space);

/*
 * Add a filter entry or list of filter entries
 * @param	filter_list	filter entry or list of filter entries
 * @return	0 on success and errno on failure
 */
extern int netconf_add_filter(netconf_filter_t *filter_list);

/*
 * Delete a filter entry or list of filter entries
 * @param	filter_list	filter entry or list of filter entries
 * @return	0 on success and errno on failure
 */
extern int netconf_del_filter(netconf_filter_t *filter_list);

/*
 * Get an array of the current filter entries
 * @param	filter_array	array of filter entries
 * @param	space		Pointer to size of filter_array in bytes
 * @return 0 on success and errno on failure
 */
extern int netconf_get_filter(netconf_filter_t *filter_array, int *space);

extern int netconf_clamp_mss_to_pmtu(void);


#endif /* _netconf_h_ */
