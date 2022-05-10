#ifndef _CSNAKE_SCREEN_H
#define _CSNAKE_SCREEN_H

#define ANSI_RESET      "\033[0m"
#define ANSI_CLEAR      "\033[2J"
#define ANSI_HOME       "\033[H"
#define ANSI_GOTO       "\033[%d;%dH"
#define ANSI_BOLD       "\033[1m"
#define ANSI_HIDE_CUR   "\033[?25l"
#define ANSI_SHOW_CUR   "\033[?25h"

#define ANSI_FG_BLACK   "\033[30m"
#define ANSI_FG_RED     "\033[31m"
#define ANSI_FG_GREEN   "\033[32m"
#define ANSI_FG_YELLOW  "\033[33m"
#define ANSI_FG_BLUE    "\033[34m"
#define ANSI_FG_MAGENTA "\033[35m"
#define ANSI_FG_CYAN    "\033[36m"
#define ANSI_FG_WHITE   "\033[37m"

#define ANSI_BG_BLACK   "\033[40m"
#define ANSI_BG_RED     "\033[41m"
#define ANSI_BG_GREEN   "\033[42m"
#define ANSI_BG_YELLOW  "\033[43m"
#define ANSI_BG_BLUE    "\033[44m"
#define ANSI_BG_MAGENTA "\033[45m"
#define ANSI_BG_CYAN    "\033[46m"
#define ANSI_BG_WHITE   "\033[47m"

typedef struct {
        int width;
        int height;
        char *pixels;
        char *colors;
} Screen;

Screen *screen_init(int, int);
void screen_free(Screen *);
void screen_reset(Screen *);

void screen_set(Screen *, char, int, int);
char screen_get(Screen *, int, int);

void screen_display(Screen *, Screen *);

#endif
