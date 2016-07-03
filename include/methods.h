/**
 * include/methods.h - wiibrewjs
 * Definitions of all supported methods.
 * Copyright (C) 2016 Karim Alibhai.
 */

#ifndef __METHODS_H
#define __METHODS_H

typedef void (*Method)(int, char*);

void print(int _, char *data);

extern const Method methods[];

#endif