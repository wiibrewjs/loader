/**
 * include/wiimote.h - wiibrew-js
 * Copyright (C) 2016 Karim Alibhai.
 */

#ifndef __WIIMOTE_H
#define __WIIMOTE_H

#include <wiiuse/wpad.h>

#define bHOME WPAD_BUTTON_HOME

void wiimote_init();
int wBtnDown( int BTN );

#endif