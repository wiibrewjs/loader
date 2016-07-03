/**
 * src/app.c - wiibrewjs
 * Copyright (C) 2016 Karim Alibhai.
 */

#include "app.h"

static int APP_RUNNING = TRUE;

void app_init() {
    graphics_init();
    wiimote_init();
    server_init();
}

int app_sync() {
    VIDEO_WaitVSync();
    WPAD_ScanPads();

    return APP_RUNNING;
}

void app_data_recv(int method, int size, char* data) {
    if ( method == 0 ) {
        // TODO: load asset
    } else {
        methods[method - 1](size, data);
    }
}

void app_quit() {
    APP_RUNNING = FALSE;
    exit(0);
}
