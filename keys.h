#ifndef _CSNAKE_KEYS_H
#define _CSNAKE_KEYS_H

#include "entities.h"

typedef struct {
        int running;
        Direction *direction;
} KeyhandlerData;


void keys_setup();
void keys_cleanup();

void *keys_handle(void *);

#endif
