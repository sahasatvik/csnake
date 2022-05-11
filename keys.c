#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <pthread.h>

#include "entities.h"
#include "keys.h"


struct termios term_orig_attr, term_new_attr;

void keys_setup() {
        tcgetattr(fileno(stdin), &term_orig_attr);
        memcpy(&term_new_attr, &term_orig_attr, sizeof(term_new_attr));
        term_new_attr.c_lflag &= ~(ICANON | ECHO);
        term_new_attr.c_cc[VMIN] = 1;
        term_new_attr.c_cc[VTIME] = 0; 
        tcsetattr(fileno(stdin), TCSANOW, &term_new_attr);
}

void keys_cleanup() {
        tcsetattr(fileno(stdin), TCSANOW, &term_orig_attr);
}


void *keys_handle(void *args) {
        KeyhandlerData *kd = (KeyhandlerData *) args;
        
        int c = '\0';
        while ((c = getc(stdin)) != EOF) {
                if (c == 'q')
                        break;
                switch (c) {
                        case 'h':
                                *kd->direction = LEFT;
                                break;
                        case 'j':
                                *kd->direction = DOWN;
                                break;
                        case 'k':
                                *kd->direction = UP;
                                break;
                        case 'l':
                                *kd->direction = RIGHT;
                                break;
                }
        }
        
        if (feof(stdin))
                clearerr(stdin);

        kd->running = 0;

        return NULL;
}
