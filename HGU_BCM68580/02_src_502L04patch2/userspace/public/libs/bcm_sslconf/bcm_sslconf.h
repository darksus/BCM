/***********************************************************************
 *
 *  Copyright (c) 2014  Broadcom Corporation
 *  All Rights Reserved
 *
 * <:label-BRCM:2006:DUAL/GPL:standard
 * 
 * Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed
 * to you under the terms of the GNU General Public License version 2
 * (the "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
 * with the following added to such license:
 * 
 *    As a special exception, the copyright holders of this software give
 *    you permission to link this software with independent modules, and
 *    to copy and distribute the resulting executable under terms of your
 *    choice, provided that you also meet, for each linked independent
 *    module, the terms and conditions of the license of that module.
 *    An independent module is a module which is not derived from this
 *    software.  The special exception does not apply to any modifications
 *    of the software.
 * 
 * Not withstanding the above, under no circumstances may you combine
 * this software in any way with any other Broadcom software provided
 * under a license other than the GPL, without Broadcom's express prior
 * written consent.
 * 
 * :>
 *
 ************************************************************************/


#ifndef _OPENSSL_CONF_LIB_H_
#define _OPENSSL_CONF_LIB_H_

#include <openssl/ssl.h>


#define SSLCONF_FILE_NAME           "/etc/openssl/sslconf.xml"
#define SSLCONF_FILE_SIZE_MAX       (4*1024)
#define SSLCONF_BUFF_SIZE            1024


typedef enum
{
   SSLCONF_RET_SUCCESS              = 0,
   SSLCONF_RET_OPEN_FILE_ERROR      = 1,
   SSLCONF_RET_XML_STATUS_ERROR     = 2,
   SSLCONF_RET_CONF_CTX_ERROR       = 3,
   SSLCONF_RET_INTERNAL_ERROR       = 4
} SslConfRet;


typedef struct {
    char appName[SSLCONF_BUFF_SIZE];
    SSL_CONF_CTX *cctx;
} SslConfData_t;


SslConfRet sslconf_apply_config(const char *appName, SSL_CTX *ctx);

#endif

