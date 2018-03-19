/*
 * Automatically generated C config: don't edit
 */
#define __CONFIG_NAT__ 1

/*
 * Base Features
 */
#define __CONFIG_RC__ 1
#define __CONFIG_NVRAM__ 1
#define __CONFIG_NVRAM_UTILITY__ 1
#define __CONFIG_SHARED__ 1
#define __CONFIG_LIBBCM__ 1
#undef __CONFIG_BUZZZ__
#define __CONFIG_BUSYBOX__ 1
#define __CONFIG_BUSYBOX_CONFIG__ "router"
#define __CONFIG_WLCONF__ 1
#define __CONFIG_BRIDGE__ 1
#define __CONFIG_VLAN__ 1
#define __CONFIG_HTTPD__ 1
#define __CONFIG_WWW__ 1
#define __CONFIG_NETCONF__ 1
#define __CONFIG_IPTABLES__ 1
#undef __CONFIG_LIBIPT__
#undef __CONFIG_GLIBC__
#define __CONFIG_UCLIBC__ 1
#undef __CONFIG_LIBOPT__
#undef __CONFIG_USBAP__
#define __CONFIG_GMAC3__ 1
#define __CONFIG_DHDAP__ 1
#undef __CONFIG_FLATLAS__
#define __CONFIG_SQUASHFS__ 1
#undef __CONFIG_CRAMFS__

/*
 * Options
 */
#define __CONFIG_VENDOR__ "broadcom"
#define __CONFIG_UDHCPD__ 1
#define __CONFIG_PPP__ 1
#define __CONFIG_LIBUPNP__ 1
#define __CONFIG_IGD__ 1
#define __CONFIG_SAMBA__ 1
#define __CONFIG_TASKSET__ 1
#define __CONFIG_MPSTAT__ 1
#define __CONFIG_FFMPEG__ 1
#undef __CONFIG_BCM_MEVENT__

/*
 * DLNA
 */
#define __CONFIG_DLNA_DMS__ 1
#undef __CONFIG_DLNA_DMR__
#define __CONFIG_MFP__ 1
#define __CONFIG_HSPOT__ 1
#undef __CONFIG_WNM__
#define __CONFIG_NAS__ 1
#undef __CONFIG_WAPI__
#define __CONFIG_NAND_JFFS2__ 1
#define __CONFIG_NAND_YAFFS2__ 1
#undef __CONFIG_WAPI_IAS__
#define __CONFIG_SES__ 1
#define __CONFIG_SES_CL__ 1
#define __CONFIG_WPS__ 1
#undef __CONFIG_NFC__
#ifdef DSLCPE
#undef __CONFIG_WFI__
#else 
#define __CONFIG_WFI__ 1
#endif
#define __CONFIG_EZC__ 1
#define __CONFIG_LLD2D__ 1
#define __CONFIG_NTP__ 1
#define __CONFIG_DNSMASQ__ 1
#define __CONFIG_UTILS__ 1
#define __CONFIG_WLEXE__ 1
#undef __CONFIG_ETC__
#define __CONFIG_BCMWPA2__ 1
#undef __CONFIG_WCN__
#define __CONFIG_EMF__ 1
#define __CONFIG_IGMP_PROXY__ 1
#undef __CONFIG_WL_ACI__
#define __CONFIG_TRAFFIC_MGMT_RSSI_POLICY__ 1
#undef __CONFIG_PHYMON_UTILITY__
#undef __CONFIG_SHRINK_MEMORY__
#define __CONFIG_BCMDCS__ 1
#define __CONFIG_EXTACS__ 1
#define __CONFIG_BCMBSD__ 1
#define __CONFIG_BCMSSD__ 1
#define __CONFIG_TOAD__ 1
#undef __CONFIG_PLC__
#undef __CONFIG_TREND_IQOS__
#define __CONFIG_IPV6__ 1
#define __CONFIG_RADVD__ 1
#undef __CONFIG_IPROUTE2__
#define __CONFIG_DHCPV6S__ 1
#undef __CONFIG_DHCPV6C__
#undef __CONFIG_IPUTILS__
#undef __CONFIG_DUAL_IMAGE_FLASH_SUPPORT__
#define __CONFIG_FAILSAFE_UPGRADE_SUPPORT__ 1
#undef __CONFIG_VOIP__
#undef __CONFIG_MDNSRESPONDER__
#define __CONFIG_LIBZ__ 1
#undef __CONFIG_SOUND__
#define __CONFIG_LIBID3TAG__ 1
#define __AIRPLAYDIR__ "$(BASEDIR)/airplay"

/*
 * Additional C libraries
 */
#define __CONFIG_LIBCRYPT__ 1
#define __CONFIG_LIBDL__ 1
#define __CONFIG_LIBFLOW__ 1
#define __CONFIG_LIBM__ 1
#undef __CONFIG_LIBNSL__
#define __CONFIG_LIBPTHREAD__ 1
#define __CONFIG_LIBRESOLV__ 1
#define __CONFIG_LIBSTDCPP__ 1
#undef __CONFIG_LIBUTIL__
#define __CONFIG_LIBNFNETLINK__ 1
#define __CONFIG_LIBNETFILTER_CONNTRACK__ 1
#define __CONFIG_LIBNETFILTER_QUEUE__ 1
#define __CONFIG_LIBMNL__ 1

/*
 * Environment
 */
#define __LIBDIR__ "$(TOOLCHAIN)/lib"
#define __USRLIBDIR__ "$(TOOLCHAIN)/usr/lib"
#undef __CONFIG_RTR_OPTIMIZE_SIZE__
#undef __CONFIG_MINI_ROUTER__

/*
 * Internal Options
 */
#define __CONFIG_UTELNETD__ 1
#undef __CONFIG_ACCEL_PPTP__
#undef __CONFIG_PPTP__
#undef __CONFIG_L2TP__
#undef __CONFIG_ACCEL_L2TP__
#define __CONFIG_ENVRAM_UTILITY__ 1
#undef __CONFIG_PCMCIA__
#undef __CONFIG_WIRELESS__
#undef __CONFIG_TRUEFFS__
#undef __CONFIG_FDISK__
#define __CONFIG_DISKTYPE__ 1
#undef __CONFIG_E2FSPROGS__
#undef __CONFIG_NCURSES__
#undef __CONFIG_TERMINFO__
#undef __CONFIG_NTSW__
#define __CONFIG_B57LDIAG__ 1
#undef __CONFIG_ETHTOOL__
#undef __CONFIG_LIBPCAP__
#undef __CONFIG_TCPDUMP__
#undef __CONFIG_IPTRAF__
#undef __CONFIG_DIALOG__
#undef __CONFIG_CRYPTO__
#undef __CONFIG_GDBSERVER__
#undef __CONFIG_PDRIVER__
#define __CONFIG_VMSTAT__ 1
#undef __CONFIG_CIFS__

/*
 * Advanced Router Features
 */
#define __CONFIG_BCMQOS__ 1
#define __CONFIG_VISUALIZATION__ 1
