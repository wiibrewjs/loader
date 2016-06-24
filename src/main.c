/**
 * src/main.c - wiibrewjs
 * Copyright (C) 2016 Karim Alibhai.
 */

#include "app.h"
#include "server.h"
#include "graphics.h"

#include <wiiuse/wpad.h>

int main ( int argc, char** argv ) {
    app_init();
	graphics_textpos(2, 0);

    while ( app_sync() ) {
		if ( wBtnDown( bHOME ) ) {
			app_quit();
		}
	}

	return 0;
}