################################################################################
#
#
#
package PhyInstaller;

use strict; 

sub new 
{    
    my ($class) = @_;
    my $self = {};
    bless($self, $class);
    $self;
}

sub begin_phy_buslist
{
    my ($self, $fh) = @_;

    print $fh <<EOT; 
/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 */

#ifndef __PHY_BUSLIST_H__
#define __PHY_BUSLIST_H__

#include <phy/phy.h>

EOT
}

sub end_phy_buslist
{
    my ($self, $fh) = @_;

    print $fh <<EOT; 
#endif /* __PHY_BUSLIST_H__ */

EOT
}

sub begin_phy_config_chips
{
    my ($self, $fh) = @_;

    print $fh <<EOT; 
/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 */

#ifndef __PHY_CONFIG_CHIPS_H__
#define __PHY_CONFIG_CHIPS_H__

/* This determines whether a PHY is included or excluded by default */
#ifndef PHY_CONFIG_INCLUDE_CHIP_DEFAULT
#ifdef CDK_CONFIG_INCLUDE_CHIP_DEFAULT
#define PHY_CONFIG_INCLUDE_CHIP_DEFAULT CDK_CONFIG_INCLUDE_CHIP_DEFAULT
#else
#define PHY_CONFIG_INCLUDE_CHIP_DEFAULT 1
#endif
#endif

/* Pick up internel PHY inclusion from CDK */
#if PHY_CONFIG_INCLUDE_CHIP_AUTO == 1
#ifdef CDK_CONFIG_INCLUDE_CHIP_DEFAULT
#include <cdk_config_phys.h>
#endif
#endif

EOT
}

sub end_phy_config_chips
{
    my ($self, $fh) = @_;

    print $fh <<EOT; 
#endif /* __PHY_CONFIG_CHIPS_H__ */

EOT
}

sub begin_phy_config_chips_opt
{
    my ($self, $fh) = @_;

    print $fh <<EOT; 
/*
 * CONFIG_OPTION Macros. Can be used to determine the build configuration.
 */
 
#ifdef CONFIG_OPTION
EOT
}

sub end_phy_config_chips_opt
{
    my ($self, $fh) = @_;

    print $fh <<EOT; 
#undef CONFIG_OPTION
#endif /* #ifdef CONFIG_OPTION */

EOT
}

sub begin_phy_devlist
{
    my ($self, $fh) = @_;

    print $fh <<EOT; 
#ifdef PHY_DEVLIST_ENTRY
/*
 * PHY_DEVLIST_ENTRY MACROS
 * 
 * Before including this file, define PHY_DEVLIST_ENTRY
 * as a macro to operate on the following parameters:
 *     #define PHY_DEVLIST_ENTRY(_nm,_bd,_fl,_desc,_r0,_r1)
 * 
 *     _nm: Chip Name
 *     _bd: SW Base Driver
 *     _fl: Flags
 *     _desc: Description
 *     _r0: Reserved
 *     _r1: Reserved
 * 
 * Note that this macro will be undefined at the end of this file.
 */

EOT
}

sub end_phy_devlist
{
    my ($self, $fh) = @_;

    print $fh <<EOT; 
/* End PHY_DEVLIST_ENTRY Macros */

#ifdef PHY_DEVLIST_INCLUDE_ALL
#undef PHY_DEVLIST_INCLUDE_ALL
#endif
#undef PHY_DEVLIST_ENTRY
#endif /* PHY_DEVLIST_ENTRY */

EOT
}

sub begin_phy_allsyms
{
    my ($self, $fh) = @_;

    print $fh <<EOT; 
/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 */

#include <phy_config.h>

/* ISO C forbids empty source files */
int phy_allsyms_not_empty;

#define PHY_EXCLUDE_CHIPLESS_TYPES

EOT
}

sub end_phy_allsyms
{
    my ($self, $fh) = @_;

    print $fh <<EOT; 
EOT
}

1;
