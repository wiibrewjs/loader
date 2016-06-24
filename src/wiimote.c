/**
 * src/wiimote.c - wiibrew-js
 * Copyright (C) 2016 Karim Alibhai.
 */

#include "wiimote.h"

void wiimote_init() {
    WPAD_Init();
}

int wBtnDown( int BTN ) {
    return WPAD_ButtonsDown(0) & BTN;
}