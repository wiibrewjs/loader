/**
 * include/server.h - wiibrewjs
 * Copyright (C) 2016 Karim Alibhai.
 */

#ifndef __SERVER_H_
#define __SERVER_H_

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <network.h>
#include <wiiuse/wpad.h>

void server_init();
void *server_run(void* arg);
void server_get_client(void* server);

#endif