/**
 * include/app.h - wiibrewjs
 * Copyright (C) 2016 Karim Alibhai.
 */

#ifndef __COMMON_H_
#define __COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "methods.h"
#include "wiimote.h"
#include "graphics.h"

#define TRUE 1
#define FALSE 0

void app_init();
int app_sync();
void app_quit();
void app_data_recv(int method, int size, char* data);

#endif