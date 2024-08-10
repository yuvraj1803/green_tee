// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#include <asm/fsl_serdes.h>
#include <asm/processor.h>
#include <asm/io.h>
#include "fsl_corenet2_serdes.h"

struct serdes_config {
	u8 protocol;
	u8 lanes[SRDS_MAX_LANES];
};

#ifdef CONFIG_ARCH_B4860
static struct serdes_config serdes1_cfg_tbl[] = {
	/* SerDes 1 */
	{0x01, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x02, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x04, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x05, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x06, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x07, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x08, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x09, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x0A, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x0B, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x0C, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x0D, {CPRI8, CPRI7, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x0E, {CPRI8, CPRI7,	CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x12, {CPRI8, CPRI7,	CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x29, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		CPRI6, CPRI5, CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x2a, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		CPRI6, CPRI5, CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x2C, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		CPRI6, CPRI5, CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x2D, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		CPRI6, CPRI5, CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x2E, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		CPRI6, CPRI5, CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x2F, {AURORA, AURORA,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x30, {AURORA, AURORA,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x32, {AURORA, AURORA,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x33, {AURORA, AURORA,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x34, {AURORA, AURORA,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x39, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x3A, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x3C, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x3D, {AURORA, AURORA, CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x3E, {CPRI8, CPRI7,	CPRI6, CPRI5,
		CPRI4, CPRI3, CPRI2, CPRI1}},
	{0x5C, {AURORA, AURORA,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{0x5D, {AURORA, AURORA,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		CPRI4, CPRI3, CPRI2, CPRI1} },
	{}
};
static struct serdes_config serdes2_cfg_tbl[] = {
	/* SerDes 2 */
	{0x17, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		AURORA, AURORA,	SRIO1, SRIO1} },
	{0x18, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		AURORA, AURORA,	SRIO1, SRIO1}},
	{0x1D, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		AURORA, AURORA,	SRIO1, SRIO1}},
	{0x2A, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SRIO2, SRIO2,
		AURORA, AURORA, SRIO1, SRIO1} },
	{0x2B, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SRIO2, SRIO2,
		AURORA, AURORA, SRIO1, SRIO1}},
	{0x30, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SRIO2, SRIO2,
		AURORA, AURORA,
		SRIO1, SRIO1}},
	{0x48, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, AURORA,
		SRIO1, SRIO1, SRIO1, SRIO1} },
	{0x49, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, AURORA,
		SRIO1, SRIO1, SRIO1, SRIO1}},
	{0x4A, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, AURORA,
		SRIO1, SRIO1, SRIO1, SRIO1}},
	{0x4C, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, AURORA,
		SRIO1, SRIO1, SRIO1, SRIO1}},
	{0x4E, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, AURORA,
		SRIO1, SRIO1, SRIO1, SRIO1}},
	{0x79, {SRIO2, SRIO2, SRIO2, SRIO2,
		SRIO1, SRIO1, SRIO1, SRIO1} },
	{0x7A, {SRIO2, SRIO2, SRIO2, SRIO2,
		SRIO1, SRIO1, SRIO1, SRIO1}},
	{0x83, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SRIO2, SRIO2, AURORA, AURORA,
		XFI_FM1_MAC9, XFI_FM1_MAC10} },
	{0x84, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SRIO2, SRIO2, AURORA, AURORA,
		XFI_FM1_MAC9, XFI_FM1_MAC10}},
	{0x85, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SRIO2, SRIO2, AURORA, AURORA,
		XFI_FM1_MAC9, XFI_FM1_MAC10}},
	{0x86, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SRIO2, SRIO2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		XFI_FM1_MAC9, XFI_FM1_MAC10} },
	{0x87, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SRIO2, SRIO2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		XFI_FM1_MAC9, XFI_FM1_MAC10}},
	{0x8C, {SRIO2, SRIO2, SRIO2, SRIO2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		XFI_FM1_MAC9, XFI_FM1_MAC10} },
	{0x8D, {SRIO2, SRIO2, SRIO2, SRIO2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		XFI_FM1_MAC9, XFI_FM1_MAC10}},
	{0x93, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10}},
	{0x9E, {PCIE1, PCIE1,	PCIE1, PCIE1,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10}},
	{0x9A, {PCIE1, PCIE1,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10}},
	{0xB1, {PCIE1, PCIE1, PCIE1, PCIE1,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		XFI_FM1_MAC9, XFI_FM1_MAC10} },
	{0xB2, {PCIE1, PCIE1, PCIE1, PCIE1,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		XFI_FM1_MAC9, XFI_FM1_MAC10}},
	{0xC3, {XAUI_FM1_MAC9, XAUI_FM1_MAC9,
		XAUI_FM1_MAC9, XAUI_FM1_MAC9,
		SRIO1, SRIO1, SRIO1, SRIO1}},
	{0x98, {XAUI_FM1_MAC9, XAUI_FM1_MAC9,
		XAUI_FM1_MAC9, XAUI_FM1_MAC9,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10}},
	{}
};
#endif

#ifdef CONFIG_ARCH_B4420
static struct serdes_config serdes1_cfg_tbl[] = {
	{0x0D, {NONE, NONE, CPRI6, CPRI5,
		CPRI4, CPRI3, NONE, NONE} },
	{0x0E, {NONE, NONE, CPRI8, CPRI5,
		CPRI4, CPRI3, NONE, NONE} },
	{0x0F, {NONE, NONE, CPRI6, CPRI5,
		CPRI4, CPRI3, NONE, NONE} },
	{0x17, {NONE, NONE,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		NONE, NONE, NONE, NONE} },
	{0x18, {NONE, NONE,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		NONE, NONE, NONE, NONE} },
	{0x1B, {NONE, NONE,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		NONE, NONE, NONE, NONE} },
	{0x1D, {NONE, NONE, AURORA, AURORA,
		NONE, NONE, NONE, NONE} },
	{0x1E, {NONE, NONE, AURORA, AURORA,
		NONE, NONE, NONE, NONE} },
	{0x21, {NONE, NONE, AURORA, AURORA,
		NONE, NONE, NONE, NONE} },
	{0x3E, {NONE, NONE, CPRI6, CPRI5,
		CPRI4, CPRI3, NONE, NONE} },
	{}
};
static struct serdes_config serdes2_cfg_tbl[] = {
	{0x48, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, AURORA,
		NONE, NONE, NONE, NONE} },
	{0x49, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, AURORA,
		NONE, NONE, NONE, NONE} },
	{0x4A, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, AURORA,
		NONE, NONE, NONE, NONE} },
	{0x6E, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		AURORA, AURORA, NONE, NONE, NONE, NONE} },
	{0x6F, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		AURORA, AURORA,	NONE, NONE, NONE, NONE} },
	{0x70, {SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		AURORA, AURORA,	NONE, NONE, NONE, NONE} },
	{0x99, {PCIE1, PCIE1,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		NONE, NONE, NONE, NONE} },
	{0x9A, {PCIE1, PCIE1,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		NONE, NONE, NONE, NONE} },
	{0x9D, {PCIE1, PCIE1, PCIE1, PCIE1,
		NONE, NONE, NONE, NONE} },
	{0x9E, {PCIE1, PCIE1, PCIE1, PCIE1,
		NONE, NONE, NONE, NONE} },
	{}
};
#endif

static struct serdes_config *serdes_cfg_tbl[] = {
	serdes1_cfg_tbl,
	serdes2_cfg_tbl,
};

enum srds_prtcl serdes_get_prtcl(int serdes, int cfg, int lane)
{
	struct serdes_config *ptr;

	if (serdes >= ARRAY_SIZE(serdes_cfg_tbl))
		return 0;

	ptr = serdes_cfg_tbl[serdes];
	while (ptr->protocol) {
		if (ptr->protocol == cfg)
			return ptr->lanes[lane];
		ptr++;
	}

	return 0;
}

int is_serdes_prtcl_valid(int serdes, u32 prtcl)
{
	int i;
	struct serdes_config *ptr;

	if (serdes >= ARRAY_SIZE(serdes_cfg_tbl))
		return 0;

	ptr = serdes_cfg_tbl[serdes];
	while (ptr->protocol) {
		if (ptr->protocol == prtcl)
			break;
		ptr++;
	}

	if (!ptr->protocol)
		return 0;

	for (i = 0; i < SRDS_MAX_LANES; i++) {
		if (ptr->lanes[i] != NONE)
			return 1;
	}

	return 0;
}