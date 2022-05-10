#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

char *colormap[8][8] = {
        {
                ANSI_FG_BLACK,
                ANSI_FG_RED,
                ANSI_FG_GREEN,
                ANSI_FG_YELLOW,
                ANSI_FG_BLUE,
                ANSI_FG_MAGENTA,
                ANSI_FG_CYAN,
                ANSI_FG_WHITE,
        },
        {
                ANSI_BG_BLACK,
                ANSI_BG_RED,
                ANSI_BG_GREEN,
                ANSI_BG_YELLOW,
                ANSI_BG_BLUE,
                ANSI_BG_MAGENTA,
                ANSI_BG_CYAN,
                ANSI_BG_WHITE,
        },
};

Screen *screen_init(int width, int height) {
        Screen *screen = malloc(sizeof(Screen));
        screen->width = width;
        screen->height = height;
        screen->pixels = calloc(width * height, sizeof(Pixel));
        return screen;
}

void screen_free(Screen *screen) {
        free(screen->pixels);
        free(screen);
}

void screen_reset(Screen *screen) {
        memset(screen->pixels, 0, screen->width * screen->height * sizeof(Pixel));
}

void screen_set(Screen *screen, char c, Color fg, Color bg, int x, int y) {
        if (x < 0 || y < 0 || x >= screen->width || y >= screen->height)
                return;
        screen->pixels[screen->height * x + y].item = c;
        screen->pixels[screen->height * x + y].fg = fg;
        screen->pixels[screen->height * x + y].bg = bg;
}

Pixel screen_get(Screen *screen, int x, int y) {
        if (x < 0 || y < 0 || x >= screen->width || y >= screen->height)
                return (Pixel) { .item = ' ', .fg = BLACK, .bg = BLACK };
        return screen->pixels[screen->height * x + y];
}

void screen_display(Screen *screen, Screen *old) {
        printf(ANSI_RESET);
        for (int y = 0; y < screen->height; y++) {
                for (int x = 0; x < screen->width; x++) {
                        Pixel p1 = screen_get(screen, x, y);
                        Pixel p2 = screen_get(old, x, y);
                        if (p1.item == p2.item && p1.fg == p2.fg && p1.bg == p2.bg)
                                continue;
                        char c = p1.item;
                        if (c == 0)
                                c = ' ';
                        printf(ANSI_GOTO, screen->height - y, 2 * x + 1);
                        printf(colormap[0][p1.fg]);
                        printf(colormap[1][p1.bg]);
                        printf("%c%c" ANSI_RESET, c, c);
                }
        }
        fflush(stdout);
}
