/**
 * src/methods.c - wiibrewjs
 * Copyright (C) 2016 Karim Alibhai.
 */

#include <stdio.h>

#include "methods.h"

const Method methods[] = {
    print
};

void print(int _, char *data) {
    printf("%s\n", data);
}