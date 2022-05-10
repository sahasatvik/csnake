#ifndef _CSNAKE_ENTITIES_H
#define _CSNAKE_ENTITIES_H

#include "screen.h"

#define MAX_SNAKE_LENGTH        1000

typedef struct {
        int x;
        int y;
} Point;

typedef enum {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT,
} Direction;

typedef struct {
        int head;
        int tail;
        Point segments[MAX_SNAKE_LENGTH];
        Direction direction;
        Direction lastdirection;
} Snake;

typedef struct {
        Point location;
} Fruit;

Snake *snake_init(Point, Direction, int);
void snake_free(Snake *);
int snake_tick(Snake *, Fruit *);
int snake_collide(Snake *, int, int);
void snake_draw(Snake *, Screen *);

void fruit_randomize(Fruit *, Snake *, int, int);
void fruit_draw(Fruit *, Screen *);

#endif
