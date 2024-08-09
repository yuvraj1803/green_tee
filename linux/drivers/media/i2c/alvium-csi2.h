/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Allied Vision Technologies GmbH Alvium camera driver
 *
 * Copyright (C) 2023 Tommaso Merciai
 * Copyright (C) 2023 Martin Hecht
 * Copyright (C) 2023 Avnet EMG GmbH
 */

#ifndef ALVIUM_CSI2_H_
#define ALVIUM_CSI2_H_

#include <linux/kernel.h>
#include <linux/regulator/consumer.h>
#include <media/v4l2-cci.h>
#include <media/v4l2-common.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-fwnode.h>
#include <media/v4l2-subdev.h>

#define REG_BCRM_V4L2					BIT(31)

#define REG_BCRM_V4L2_8BIT(n)				(REG_BCRM_V4L2 | CCI_REG8(n))
#define REG_BCRM_V4L2_16BIT(n)				(REG_BCRM_V4L2 | CCI_REG16(n))
#define REG_BCRM_V4L2_32BIT(n)				(REG_BCRM_V4L2 | CCI_REG32(n))
#define REG_BCRM_V4L2_64BIT(n)				(REG_BCRM_V4L2 | CCI_REG64(n))

/* Basic Control Register Map register offsets (BCRM) */
#define REG_BCRM_MINOR_VERSION_R			CCI_REG16(0x0000)
#define REG_BCRM_MAJOR_VERSION_R			CCI_REG16(0x0002)
#define REG_BCRM_REG_ADDR_R				CCI_REG16(0x0014)

#define REG_BCRM_FEATURE_INQUIRY_R			REG_BCRM_V4L2_64BIT(0x0008)
#define REG_BCRM_DEVICE_FW				REG_BCRM_V4L2_64BIT(0x0010)
#define REG_BCRM_WRITE_HANDSHAKE_RW			REG_BCRM_V4L2_8BIT(0x0018)

/* Streaming Control Registers */
#define REG_BCRM_SUPPORTED_CSI2_LANE_COUNTS_R		REG_BCRM_V4L2_8BIT(0x0040)
#define REG_BCRM_CSI2_LANE_COUNT_RW			REG_BCRM_V4L2_8BIT(0x0044)
#define REG_BCRM_CSI2_CLOCK_MIN_R			REG_BCRM_V4L2_32BIT(0x0048)
#define REG_BCRM_CSI2_CLOCK_MAX_R			REG_BCRM_V4L2_32BIT(0x004c)
#define REG_BCRM_CSI2_CLOCK_RW				REG_BCRM_V4L2_32BIT(0x0050)
#define REG_BCRM_BUFFER_SIZE_R				REG_BCRM_V4L2_32BIT(0x0054)

#define REG_BCRM_IPU_X_MIN_W				REG_BCRM_V4L2_32BIT(0x0058)
#define REG_BCRM_IPU_X_MAX_W				REG_BCRM_V4L2_32BIT(0x005c)
#define REG_BCRM_IPU_X_INC_W				REG_BCRM_V4L2_32BIT(0x0060)
#define REG_BCRM_IPU_Y_MIN_W				REG_BCRM_V4L2_32BIT(0x0064)
#define REG_BCRM_IPU_Y_MAX_W				REG_BCRM_V4L2_32BIT(0x0068)
#define REG_BCRM_IPU_Y_INC_W				REG_BCRM_V4L2_32BIT(0x006c)
#define REG_BCRM_IPU_X_R				REG_BCRM_V4L2_32BIT(0x0070)
#define REG_BCRM_IPU_Y_R				REG_BCRM_V4L2_32BIT(0x0074)

#define REG_BCRM_PHY_RESET_RW				REG_BCRM_V4L2_8BIT(0x0078)
#define REG_BCRM_LP2HS_DELAY_RW				REG_BCRM_V4L2_32BIT(0x007c)

/* Acquisition Control Registers */
#define REG_BCRM_ACQUISITION_START_RW			REG_BCRM_V4L2_8BIT(0x0080)
#define REG_BCRM_ACQUISITION_STOP_RW			REG_BCRM_V4L2_8BIT(0x0084)
#define REG_BCRM_ACQUISITION_ABORT_RW			REG_BCRM_V4L2_8BIT(0x0088)
#define REG_BCRM_ACQUISITION_STATUS_R			REG_BCRM_V4L2_8BIT(0x008c)
#define REG_BCRM_ACQUISITION_FRAME_RATE_RW		REG_BCRM_V4L2_64BIT(0x0090)
#define REG_BCRM_ACQUISITION_FRAME_RATE_MIN_R		REG_BCRM_V4L2_64BIT(0x0098)
#define REG_BCRM_ACQUISITION_FRAME_RATE_MAX_R		REG_BCRM_V4L2_64BIT(0x00a0)
#define REG_BCRM_ACQUISITION_FRAME_RATE_INC_R		REG_BCRM_V4L2_64BIT(0x00a8)
#define REG_BCRM_ACQUISITION_FRAME_RATE_EN_RW		REG_BCRM_V4L2_8BIT(0x00b0)

#define REG_BCRM_FRAME_START_TRIGGER_MODE_RW		REG_BCRM_V4L2_8BIT(0x00b4)
#define REG_BCRM_FRAME_START_TRIGGER_SOURCE_RW		REG_BCRM_V4L2_8BIT(0x00b8)
#define REG_BCRM_FRAME_START_TRIGGER_ACTIVATION_RW	REG_BCRM_V4L2_8BIT(0x00bc)
#define REG_BCRM_FRAME_START_TRIGGER_SOFTWARE_W		REG_BCRM_V4L2_8BIT(0x00c0)
#define REG_BCRM_FRAME_START_TRIGGER_DELAY_RW		REG_BCRM_V4L2_32BIT(0x00c4)
#define REG_BCRM_EXPOSURE_ACTIVE_LINE_MODE_RW		REG_BCRM_V4L2_8BIT(0x00c8)
#define REG_BCRM_EXPOSURE_ACTIVE_LINE_SELECTOR_RW	REG_BCRM_V4L2_8BIT(0x00cc)
#define REG_BCRM_LINE_CONFIGURATION_RW			REG_BCRM_V4L2_32BIT(0x00d0)

#define REG_BCRM_IMG_WIDTH_RW				REG_BCRM_V4L2_32BIT(0x0100)
#define REG_BCRM_IMG_WIDTH_MIN_R			REG_BCRM_V4L2_32BIT(0x0104)
#define REG_BCRM_IMG_WIDTH_MAX_R			REG_BCRM_V4L2_32BIT(0x0108)
#define REG_BCRM_IMG_WIDTH_INC_R			REG_BCRM_V4L2_32BIT(0x010c)

#define REG_BCRM_IMG_HEIGHT_RW				REG_BCRM_V4L2_32BIT(0x0110)
#define REG_BCRM_IMG_HEIGHT_MIN_R			REG_BCRM_V4L2_32BIT(0x0114)
#define REG_BCRM_IMG_HEIGHT_MAX_R			REG_BCRM_V4L2_32BIT(0x0118)
#define REG_BCRM_IMG_HEIGHT_INC_R			REG_BCRM_V4L2_32BIT(0x011c)

#define REG_BCRM_IMG_OFFSET_X_RW			REG_BCRM_V4L2_32BIT(0x0120)
#define REG_BCRM_IMG_OFFSET_X_MIN_R			REG_BCRM_V4L2_32BIT(0x0124)
#define REG_BCRM_IMG_OFFSET_X_MAX_R			REG_BCRM_V4L2_32BIT(0x0128)
#define REG_BCRM_IMG_OFFSET_X_INC_R			REG_BCRM_V4L2_32BIT(0x012c)

#define REG_BCRM_IMG_OFFSET_Y_RW			REG_BCRM_V4L2_32BIT(0x0130)
#define REG_BCRM_IMG_OFFSET_Y_MIN_R			REG_BCRM_V4L2_32BIT(0x0134)
#define REG_BCRM_IMG_OFFSET_Y_MAX_R			REG_BCRM_V4L2_32BIT(0x0138)
#define REG_BCRM_IMG_OFFSET_Y_INC_R			REG_BCRM_V4L2_32BIT(0x013c)

#define REG_BCRM_IMG_MIPI_DATA_FORMAT_RW		REG_BCRM_V4L2_32BIT(0x0140)
#define REG_BCRM_IMG_AVAILABLE_MIPI_DATA_FORMATS_R	REG_BCRM_V4L2_64BIT(0x0148)
#define REG_BCRM_IMG_BAYER_PATTERN_INQUIRY_R		REG_BCRM_V4L2_8BIT(0x0150)
#define REG_BCRM_IMG_BAYER_PATTERN_RW			REG_BCRM_V4L2_8BIT(0x0154)
#define REG_BCRM_IMG_REVERSE_X_RW			REG_BCRM_V4L2_8BIT(0x0158)
#define REG_BCRM_IMG_REVERSE_Y_RW			REG_BCRM_V4L2_8BIT(0x015c)

#define REG_BCRM_SENSOR_WIDTH_R				REG_BCRM_V4L2_32BIT(0x0160)
#define REG_BCRM_SENSOR_HEIGHT_R			REG_BCRM_V4L2_32BIT(0x0164)
#define REG_BCRM_WIDTH_MAX_R				REG_BCRM_V4L2_32BIT(0x0168)
#define REG_BCRM_HEIGHT_MAX_R				REG_BCRM_V4L2_32BIT(0x016c)

#define REG_BCRM_EXPOSURE_TIME_RW			REG_BCRM_V4L2_64BIT(0x0180)
#define REG_BCRM_EXPOSURE_TIME_MIN_R			REG_BCRM_V4L2_64BIT(0x0188)
#define REG_BCRM_EXPOSURE_TIME_MAX_R			REG_BCRM_V4L2_64BIT(0x0190)
#define REG_BCRM_EXPOSURE_TIME_INC_R			REG_BCRM_V4L2_64BIT(0x0198)
#define REG_BCRM_EXPOSURE_AUTO_RW			REG_BCRM_V4L2_8BIT(0x01a0)

#define REG_BCRM_INTENSITY_AUTO_PRECEDENCE_RW		REG_BCRM_V4L2_8BIT(0x01a4)
#define REG_BCRM_INTENSITY_AUTO_PRECEDENCE_VALUE_RW	REG_BCRM_V4L2_32BIT(0x01a8)
#define REG_BCRM_INTENSITY_AUTO_PRECEDENCE_MIN_R	REG_BCRM_V4L2_32BIT(0x01ac)
#define REG_BCRM_INTENSITY_AUTO_PRECEDENCE_MAX_R	REG_BCRM_V4L2_32BIT(0x01b0)
#define REG_BCRM_INTENSITY_AUTO_PRECEDENCE_INC_R	REG_BCRM_V4L2_32BIT(0x01b4)

#define REG_BCRM_BLACK_LEVEL_RW				REG_BCRM_V4L2_32BIT(0x01b8)
#define REG_BCRM_BLACK_LEVEL_MIN_R			REG_BCRM_V4L2_32BIT(0x01bc)
#define REG_BCRM_BLACK_LEVEL_MAX_R			REG_BCRM_V4L2_32BIT(0x01c0)
#define REG_BCRM_BLACK_LEVEL_INC_R			REG_BCRM_V4L2_32BIT(0x01c4)

#define REG_BCRM_GAIN_RW				REG_BCRM_V4L2_64BIT(0x01c8)
#define REG_BCRM_GAIN_MIN_R				REG_BCRM_V4L2_64BIT(0x01d0)
#define REG_BCRM_GAIN_MAX_R				REG_BCRM_V4L2_64BIT(0x01d8)
#define REG_BCRM_GAIN_INC_R				REG_BCRM_V4L2_64BIT(0x01e0)
#define REG_BCRM_GAIN_AUTO_RW				REG_BCRM_V4L2_8BIT(0x01e8)

#define REG_BCRM_GAMMA_RW				REG_BCRM_V4L2_64BIT(0x01f0)
#define REG_BCRM_GAMMA_MIN_R				REG_BCRM_V4L2_64BIT(0x01f8)
#define REG_BCRM_GAMMA_MAX_R				REG_BCRM_V4L2_64BIT(0x0200)
#define REG_BCRM_GAMMA_INC_R				REG_BCRM_V4L2_64BIT(0x0208)

#define REG_BCRM_CONTRAST_VALUE_RW			REG_BCRM_V4L2_32BIT(0x0214)
#define REG_BCRM_CONTRAST_VALUE_MIN_R			REG_BCRM_V4L2_32BIT(0x0218)
#define REG_BCRM_CONTRAST_VALUE_MAX_R			REG_BCRM_V4L2_32BIT(0x021c)
#define REG_BCRM_CONTRAST_VALUE_INC_R			REG_BCRM_V4L2_32BIT(0x0220)

#define REG_BCRM_SATURATION_RW				REG_BCRM_V4L2_32BIT(0x0240)
#define REG_BCRM_SATURATION_MIN_R			REG_BCRM_V4L2_32BIT(0x0244)
#define REG_BCRM_SATURATION_MAX_R			REG_BCRM_V4L2_32BIT(0x0248)
#define REG_BCRM_SATURATION_INC_R			REG_BCRM_V4L2_32BIT(0x024c)

#define REG_BCRM_HUE_RW					REG_BCRM_V4L2_32BIT(0x0250)
#define REG_BCRM_HUE_MIN_R				REG_BCRM_V4L2_32BIT(0x0254)
#define REG_BCRM_HUE_MAX_R				REG_BCRM_V4L2_32BIT(0x0258)
#define REG_BCRM_HUE_INC_R				REG_BCRM_V4L2_32BIT(0x025c)

#define REG_BCRM_ALL_BALANCE_RATIO_RW			REG_BCRM_V4L2_64BIT(0x0260)
#define REG_BCRM_ALL_BALANCE_RATIO_MIN_R		REG_BCRM_V4L2_64BIT(0x0268)
#define REG_BCRM_ALL_BALANCE_RATIO_MAX_R		REG_BCRM_V4L2_64BIT(0x0270)
#define REG_BCRM_ALL_BALANCE_RATIO_INC_R		REG_BCRM_V4L2_64BIT(0x0278)

#define REG_BCRM_RED_BALANCE_RATIO_RW			REG_BCRM_V4L2_64BIT(0x0280)
#define REG_BCRM_RED_BALANCE_RATIO_MIN_R		REG_BCRM_V4L2_64BIT(0x0288)
#define REG_BCRM_RED_BALANCE_RATIO_MAX_R		REG_BCRM_V4L2_64BIT(0x0290)
#define REG_BCRM_RED_BALANCE_RATIO_INC_R		REG_BCRM_V4L2_64BIT(0x0298)

#define REG_BCRM_GREEN_BALANCE_RATIO_RW			REG_BCRM_V4L2_64BIT(0x02a0)
#define REG_BCRM_GREEN_BALANCE_RATIO_MIN_R		REG_BCRM_V4L2_64BIT(0x02a8)
#define REG_BCRM_GREEN_BALANCE_RATIO_MAX_R		REG_BCRM_V4L2_64BIT(0x02b0)
#define REG_BCRM_GREEN_BALANCE_RATIO_INC_R		REG_BCRM_V4L2_64BIT(0x02b8)

#define REG_BCRM_BLUE_BALANCE_RATIO_RW			REG_BCRM_V4L2_64BIT(0x02c0)
#define REG_BCRM_BLUE_BALANCE_RATIO_MIN_R		REG_BCRM_V4L2_64BIT(0x02c8)
#define REG_BCRM_BLUE_BALANCE_RATIO_MAX_R		REG_BCRM_V4L2_64BIT(0x02d0)
#define REG_BCRM_BLUE_BALANCE_RATIO_INC_R		REG_BCRM_V4L2_64BIT(0x02d8)

#define REG_BCRM_WHITE_BALANCE_AUTO_RW			REG_BCRM_V4L2_8BIT(0x02e0)
#define REG_BCRM_SHARPNESS_RW				REG_BCRM_V4L2_32BIT(0x0300)
#define REG_BCRM_SHARPNESS_MIN_R			REG_BCRM_V4L2_32BIT(0x0304)
#define REG_BCRM_SHARPNESS_MAX_R			REG_BCRM_V4L2_32BIT(0x0308)
#define REG_BCRM_SHARPNESS_INC_R			REG_BCRM_V4L2_32BIT(0x030c)

#define REG_BCRM_DEVICE_TEMPERATURE_R			REG_BCRM_V4L2_32BIT(0x0310)
#define REG_BCRM_EXPOSURE_AUTO_MIN_RW			REG_BCRM_V4L2_64BIT(0x0330)
#define REG_BCRM_EXPOSURE_AUTO_MAX_RW			REG_BCRM_V4L2_64BIT(0x0338)
#define REG_BCRM_GAIN_AUTO_MIN_RW			REG_BCRM_V4L2_64BIT(0x0340)
#define REG_BCRM_GAIN_AUTO_MAX_RW			REG_BCRM_V4L2_64BIT(0x0348)

/* Heartbeat reg*/
#define REG_BCRM_HEARTBEAT_RW				CCI_REG8(0x021f)

/* GenCP Registers */
#define REG_GENCP_CHANGEMODE_W				CCI_REG8(0x021c)
#define REG_GENCP_CURRENTMODE_R				CCI_REG8(0x021d)
#define REG_GENCP_IN_HANDSHAKE_RW			CCI_REG8(0x001c)
#define REG_GENCP_OUT_SIZE_W				CCI_REG16(0x0020)
#define REG_GENCP_IN_SIZE_R				CCI_REG16(0x0024)

/* defines */
#define REG_BCRM_HANDSHAKE_STATUS_MASK			0x01
#define REG_BCRM_HANDSHAKE_AVAILABLE_MASK		0x80

#define BCRM_HANDSHAKE_W_DONE_EN_BIT			BIT(0)

#define ALVIUM_DEFAULT_FR_HZ				10
#define ALVIUM_DEFAULT_PIXEL_RATE_MHZ			148000000

#define ALVIUM_LP2HS_DELAY_MS				100

#define BCRM_DEVICE_FW_MAJOR_MASK			GENMASK_ULL(15, 8)
#define BCRM_DEVICE_FW_MAJOR_SHIFT			8
#define BCRM_DEVICE_FW_MINOR_MASK			GENMASK_ULL(31, 16)
#define BCRM_DEVICE_FW_MINOR_SHIFT			16
#define BCRM_DEVICE_FW_PATCH_MASK			GENMASK_ULL(63, 32)
#define BCRM_DEVICE_FW_PATCH_SHIFT			32
#define BCRM_DEVICE_FW_SPEC_MASK			GENMASK_ULL(7, 0)
#define BCRM_DEVICE_FW_SPEC_SHIFT			0

enum alvium_bcrm_mode {
	ALVIUM_BCM_MODE,
	ALVIUM_GENCP_MODE,
	ALVIUM_NUM_MODE
};

enum alvium_mipi_fmt {
	ALVIUM_FMT_UYVY8_2X8 = 0,
	ALVIUM_FMT_UYVY8_1X16,
	ALVIUM_FMT_YUYV8_1X16,
	ALVIUM_FMT_YUYV8_2X8,
	ALVIUM_FMT_YUYV10_1X20,
	ALVIUM_FMT_RGB888_1X24,
	ALVIUM_FMT_RBG888_1X24,
	ALVIUM_FMT_BGR888_1X24,
	ALVIUM_FMT_RGB888_3X8,
	ALVIUM_FMT_Y8_1X8,
	ALVIUM_FMT_SGRBG8_1X8,
	ALVIUM_FMT_SRGGB8_1X8,
	ALVIUM_FMT_SGBRG8_1X8,
	ALVIUM_FMT_SBGGR8_1X8,
	ALVIUM_FMT_Y10_1X10,
	ALVIUM_FMT_SGRBG10_1X10,
	ALVIUM_FMT_SRGGB10_1X10,
	ALVIUM_FMT_SGBRG10_1X10,
	ALVIUM_FMT_SBGGR10_1X10,
	ALVIUM_FMT_Y12_1X12,
	ALVIUM_FMT_SGRBG12_1X12,
	ALVIUM_FMT_SRGGB12_1X12,
	ALVIUM_FMT_SGBRG12_1X12,
	ALVIUM_FMT_SBGGR12_1X12,
	ALVIUM_FMT_SBGGR14_1X14,
	ALVIUM_FMT_SGBRG14_1X14,
	ALVIUM_FMT_SRGGB14_1X14,
	ALVIUM_FMT_SGRBG14_1X14,
	ALVIUM_NUM_SUPP_MIPI_DATA_FMT
};

enum alvium_av_bayer_bit {
	ALVIUM_BIT_BAY_NONE = -1,
	ALVIUM_BIT_BAY_MONO = 0,
	ALVIUM_BIT_BAY_GR,
	ALVIUM_BIT_BAY_RG,
	ALVIUM_BIT_BAY_GB,
	ALVIUM_BIT_BAY_BG,
	ALVIUM_NUM_BAY_AV_BIT
};

enum alvium_av_mipi_bit {
	ALVIUM_BIT_YUV420_8_LEG = 0,
	ALVIUM_BIT_YUV420_8,
	ALVIUM_BIT_YUV420_10,
	ALVIUM_BIT_YUV420_8_CSPS,
	ALVIUM_BIT_YUV420_10_CSPS,
	ALVIUM_BIT_YUV422_8,
	ALVIUM_BIT_YUV422_10,
	ALVIUM_BIT_RGB888,
	ALVIUM_BIT_RGB666,
	ALVIUM_BIT_RGB565,
	ALVIUM_BIT_RGB555,
	ALVIUM_BIT_RGB444,
	ALVIUM_BIT_RAW6,
	ALVIUM_BIT_RAW7,
	ALVIUM_BIT_RAW8,
	ALVIUM_BIT_RAW10,
	ALVIUM_BIT_RAW12,
	ALVIUM_BIT_RAW14,
	ALVIUM_BIT_JPEG,
	ALVIUM_NUM_SUPP_MIPI_DATA_BIT
};

struct alvium_avail_feat {
	u64 rev_x:1;
	u64 rev_y:1;
	u64 int_autop:1;
	u64 black_lvl:1;
	u64 gain:1;
	u64 gamma:1;
	u64 contrast:1;
	u64 sat:1;
	u64 hue:1;
	u64 whiteb:1;
	u64 sharp:1;
	u64 auto_exp:1;
	u64 auto_gain:1;
	u64 auto_whiteb:1;
	u64 dev_temp:1;
	u64 acq_abort:1;
	u64 acq_fr:1;
	u64 fr_trigger:1;
	u64 exp_acq_line:1;
	u64 reserved:45;
};

struct alvium_avail_mipi_fmt {
	u64 yuv420_8_leg:1;
	u64 yuv420_8:1;
	u64 yuv420_10:1;
	u64 yuv420_8_csps:1;
	u64 yuv420_10_csps:1;
	u64 yuv422_8:1;
	u64 yuv422_10:1;
	u64 rgb888:1;
	u64 rgb666:1;
	u64 rgb565:1;
	u64 rgb555:1;
	u64 rgb444:1;
	u64 raw6:1;
	u64 raw7:1;
	u64 raw8:1;
	u64 raw10:1;
	u64 raw12:1;
	u64 raw14:1;
	u64 jpeg:1;
	u64 reserved:45;
};

struct alvium_avail_bayer {
	u8 mono:1;
	u8 gr:1;
	u8 rg:1;
	u8 gb:1;
	u8 bg:1;
	u8 reserved:3;
};

struct alvium_mode {
	struct v4l2_rect crop;
	struct v4l2_mbus_framefmt fmt;
	u32 width;
	u32 height;
};

struct alvium_pixfmt {
	u32 code;
	u32 colorspace;
	u64 mipi_fmt_regval;
	u64 bay_fmt_regval;
	u8 id;
	u8 is_raw;
	u8 fmt_av_bit;
	u8 bay_av_bit;
};

struct alvium_ctrls {
	struct v4l2_ctrl_handler handler;
	struct v4l2_ctrl *pixel_rate;
	struct v4l2_ctrl *link_freq;
	struct v4l2_ctrl *auto_exp;
	struct v4l2_ctrl *exposure;
	struct v4l2_ctrl *auto_wb;
	struct v4l2_ctrl *blue_balance;
	struct v4l2_ctrl *red_balance;
	struct v4l2_ctrl *auto_gain;
	struct v4l2_ctrl *gain;
	struct v4l2_ctrl *saturation;
	struct v4l2_ctrl *hue;
	struct v4l2_ctrl *contrast;
	struct v4l2_ctrl *gamma;
	struct v4l2_ctrl *sharpness;
	struct v4l2_ctrl *hflip;
	struct v4l2_ctrl *vflip;
};

struct alvium_dev {
	struct i2c_client *i2c_client;
	struct v4l2_subdev sd;
	struct v4l2_fwnode_endpoint ep;
	struct media_pad pad;
	struct regmap *regmap;

	struct regulator *reg_vcc;

	u16 bcrm_addr;

	struct alvium_avail_feat avail_ft;
	u8 is_mipi_fmt_avail[ALVIUM_NUM_SUPP_MIPI_DATA_BIT];
	u8 is_bay_avail[ALVIUM_NUM_BAY_AV_BIT];

	u32 min_csi_clk;
	u32 max_csi_clk;
	u32 dft_img_width;
	u32 img_min_width;
	u32 img_max_width;
	u32 img_inc_width;
	u32 dft_img_height;
	u32 img_min_height;
	u32 img_max_height;
	u32 img_inc_height;
	u32 min_offx;
	u32 max_offx;
	u32 inc_offx;
	u32 min_offy;
	u32 max_offy;
	u32 inc_offy;
	u64 dft_gain;
	u64 min_gain;
	u64 max_gain;
	u64 inc_gain;
	u64 dft_exp;
	u64 min_exp;
	u64 max_exp;
	u64 inc_exp;
	u64 dft_rbalance;
	u64 min_rbalance;
	u64 max_rbalance;
	u64 inc_rbalance;
	u64 dft_bbalance;
	u64 min_bbalance;
	u64 max_bbalance;
	u64 inc_bbalance;
	s32 dft_hue;
	s32 min_hue;
	s32 max_hue;
	s32 inc_hue;
	u32 dft_contrast;
	u32 min_contrast;
	u32 max_contrast;
	u32 inc_contrast;
	u32 dft_sat;
	u32 min_sat;
	u32 max_sat;
	u32 inc_sat;
	s32 dft_black_lvl;
	s32 min_black_lvl;
	s32 max_black_lvl;
	s32 inc_black_lvl;
	u64 dft_gamma;
	u64 min_gamma;
	u64 max_gamma;
	u64 inc_gamma;
	s32 dft_sharp;
	s32 min_sharp;
	s32 max_sharp;
	s32 inc_sharp;

	struct alvium_mode mode;

	u8 h_sup_csi_lanes;
	u64 link_freq;

	struct alvium_ctrls ctrls;

	u8 bcrm_mode;

	struct alvium_pixfmt *alvium_csi2_fmt;
	u8 alvium_csi2_fmt_n;

	u8 streaming;
	u8 apply_fiv;
};

static inline struct alvium_dev *sd_to_alvium(struct v4l2_subdev *sd)
{
	return container_of_const(sd, struct alvium_dev, sd);
}

static inline struct v4l2_subdev *ctrl_to_sd(struct v4l2_ctrl *ctrl)
{
	return &container_of_const(ctrl->handler, struct alvium_dev,
					  ctrls.handler)->sd;
}
#endif /* ALVIUM_CSI2_H_ */
