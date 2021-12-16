#include <zephyr.h>
#include <shell/shell.h>
#include <drivers/video.h>

#include "hdmi.h"

/* HDMI predefined timings */
struct video_timing vt1920x1080_60Hz = {
	.pixel_clock = 14850,

	.h_active = 1920,
	.h_blanking = 280,
	.h_sync_offset = 88,
	.h_sync_width = 44,

	.v_active = 1080,
	.v_blanking = 45,
	.v_sync_offset = 4,
	.v_sync_width = 5,
};

struct video_timing vt1280x720_60Hz = {

	.pixel_clock = 7425,

	.h_active = 1280,
	.h_blanking = 370,
	.h_sync_offset = 110,
	.h_sync_width = 40,

	.v_active = 720,
	.v_blanking = 30,
	.v_sync_offset = 5,
	.v_sync_width = 5,
};

struct video_timing vt800x600_60Hz = {

	.pixel_clock = 4000,

	.h_active = 800,
	.h_blanking = 256,
	.h_sync_offset = 40,
	.h_sync_width = 128,

	.v_active = 600,
	.v_blanking = 28,
	.v_sync_offset = 1,
	.v_sync_width = 4,
};

struct video_timing vt640x480_75Hz = {

	.pixel_clock = 3150,

	.h_active = 640,
	.h_blanking = 200,
	.h_sync_offset = 16,
	.h_sync_width = 64,

	.v_active = 480,
	.v_blanking = 20,
	.v_sync_offset = 1,
	.v_sync_width = 3,
};

struct video_timing vt640x480_60Hz = {

	.pixel_clock = 2517,

	.h_active = 640,
	.h_blanking = 160,
	.h_sync_offset = 16,
	.h_sync_width = 96,

	.v_active = 480,
	.v_blanking = 45,
	.v_sync_offset = 10,
	.v_sync_width = 2,

};

static int cmd_display_set_resolution_1920x1080_60Hz(const struct shell *shell, size_t argc, char **argv)
{
	hdmi_out0_core_initiator_enable_write(0);
	hdmi_out0_driver_clocking_mmcm_reset_write(1);

	timings_write(&vt1920x1080_60Hz);

	hdmi_out0_driver_clocking_mmcm_reset_write(0);

	shell_print(shell, "\nResoluton 1920x1080 @ 60Hz frequency set!\n");

	return 0;
}

static int cmd_display_set_resolution_1280x720_60Hz(const struct shell *shell, size_t argc, char **argv)
{
	hdmi_out0_core_initiator_enable_write(0);
	hdmi_out0_driver_clocking_mmcm_reset_write(1);

	timings_write(&vt1280x720_60Hz);

	hdmi_out0_driver_clocking_mmcm_reset_write(0);

	shell_print(shell, "\nResoluton 1280x720 @ 60Hz frequency set!\n");

	return 0;
}

static int cmd_display_set_resolution_800x600_60Hz(const struct shell *shell, size_t argc, char **argv)
{
	hdmi_out0_core_initiator_enable_write(0);
	hdmi_out0_driver_clocking_mmcm_reset_write(1);

	timings_write(&vt800x600_60Hz);

	hdmi_out0_driver_clocking_mmcm_reset_write(0);

	shell_print(shell, "\nResoluton 800x600 @ 60Hz frequency set!\n");

	return 0;
}

static int cmd_display_set_resolution_640x480_75Hz(const struct shell *shell, size_t argc, char **argv)
{
	hdmi_out0_core_initiator_enable_write(0);
	hdmi_out0_driver_clocking_mmcm_reset_write(1);

	timings_write(&vt640x480_75Hz);

	hdmi_out0_driver_clocking_mmcm_reset_write(0);

	shell_print(shell, "\nResoluton 640x480 @ 75Hz frequency set!\n");

	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_display_resolution,
	SHELL_CMD_ARG(mode_1920x1080_60Hz, NULL, "\t1920x1080_60Hz", cmd_display_set_resolution_1920x1080_60Hz, 1, 0),
	SHELL_CMD_ARG(mode_1280x720_60Hz,  NULL, "\t1280x720_60Hz",  cmd_display_set_resolution_1280x720_60Hz,  1, 0),
	SHELL_CMD_ARG(mode_800x600_60Hz,   NULL, "\t800x600_60Hz",   cmd_display_set_resolution_800x600_60Hz,   1, 0),
	SHELL_CMD_ARG(mode_640x480_75Hz,   NULL, "\t640x480_75Hz",   cmd_display_set_resolution_640x480_75Hz,   1, 0),
	SHELL_SUBCMD_SET_END);

SHELL_STATIC_SUBCMD_SET_CREATE(
	sub_display,
	SHELL_CMD(set_resolution, &sub_display_resolution,
						"Resolutions:\n"
						"1920x1080_60Hz\t"
						"1280x720_60Hz\t"
						"800x600_60Hz\t"
						"640x480_75Hz\n", NULL),
	SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(display, &sub_display, "\tConfigure display", NULL);
