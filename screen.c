#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

Screen *screen_init(int width, int height) {
        Screen *screen = malloc(sizeof(Screen));
        screen->width = width;
        screen->height = height;
        screen->pixels = calloc(width * height, sizeof(char));
        return screen;
}

void screen_free(Screen *screen) {
        free(screen->pixels);
        free(screen);
}

void screen_reset(Screen *screen) {
        memset(screen->pixels, 0, screen->width * screen->height * sizeof(char));
}

void screen_set(Screen *screen, char c, int x, int y) {
        if (x < 0 || y < 0 || x >= screen->width || y >= screen->height)
                return;
        screen->pixels[screen->height * x + y] = c;
}

char screen_get(Screen *screen, int x, int y) {
        if (x < 0 || y < 0 || x >= screen->width || y >= screen->height)
                return 0;
        return screen->pixels[screen->height * x + y];
}

void screen_display(Screen *screen, Screen *old) {
        int rewrites = 0;
        printf(ANSI_RESET);
        for (int y = 0; y < screen->height; y++) {
                for (int x = 0; x < screen->width; x++) {
                        char c1 = screen_get(screen, x, y);
                        char c2 = screen_get(old, x, y);
                        if (c1 == c2)
                                continue;
                        if (c1 == 0)
                                c1 = ' ';
                        if (c1 == '*')
                                printf(ANSI_GOTO ANSI_BG_GREEN "  " ANSI_RESET, screen->height - y, 2 * x + 1);
                        else if (c1 == 'H')
                                printf(ANSI_GOTO ANSI_BG_BLUE "  " ANSI_RESET, screen->height - y, 2 * x + 1);
                        else if (c1 == 'F')
                                printf(ANSI_GOTO ANSI_BG_RED "  " ANSI_RESET, screen->height - y, 2 * x + 1);
                        else
                                printf(ANSI_GOTO "%c%c", screen->height - y, 2 * x + 1, c1, c1);
                        rewrites++;
                }
        }
        fflush(stdout);
}
