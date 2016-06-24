/**
 * src/graphics.c - wiibrew-js
 * Copyright (C) 2016 Karim Alibhai.
 */

#include "graphics.h"

static void *GS_FB = NULL;
static GXRModeObj *GS_MODE = NULL;

void graphics_init() {
	VIDEO_Init();

	GS_MODE = VIDEO_GetPreferredMode(NULL);
	GS_FB = MEM_K0_TO_K1(SYS_AllocateFramebuffer(GS_MODE));
	console_init(GS_FB, 20, 20, GS_MODE->fbWidth, GS_MODE->xfbHeight, GS_MODE->fbWidth*VI_DISPLAY_PIX_SZ);

	VIDEO_Configure(GS_MODE);
	VIDEO_SetNextFramebuffer(GS_FB);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();

	if(GS_MODE->viTVMode & VI_NON_INTERLACE) {
		VIDEO_WaitVSync();
	}
}

void graphics_textpos(int row, int column) {
    printf("\x1b[%d;%dH", row, column);
}