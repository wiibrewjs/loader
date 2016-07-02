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
    switch ( method ) {
        case 0x01:
        printf("%s\n", data);
        break;

        default:
        break;
    }
}

void app_quit() {
    APP_RUNNING = FALSE;
    exit(0);
}
