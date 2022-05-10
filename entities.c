#include <stdio.h>
#include <stdlib.h>

#include "screen.h"
#include "entities.h"

Point direction_delta[] = {
        { .x =  0, .y =  1 },
        { .x =  0, .y = -1 },
        { .x = -1, .y =  0 },
        { .x =  1, .y =  0 },
};

void snake_build(Snake *snake, int headx, int heady, Direction direction, int length) {
        for (int i = length - 1; i >= 0; i--) {
                snake->segments[i].x = headx;
                snake->segments[i].y = heady;
                headx -= direction_delta[direction].x;
                heady -= direction_delta[direction].y;
        }
        snake->head = length - 1;
        snake->tail = 0;
        snake->direction = direction;
        snake->lastdirection = direction;
}

int snake_tick(Snake *snake, Fruit *fruit) {
        int head_new = (snake->head + 1) % MAX_SNAKE_LENGTH;
        Direction dir = snake->direction;
        if ((dir & 2) == (snake->lastdirection & 2))
                dir = snake->lastdirection;
        snake->segments[head_new].x = snake->segments[snake->head].x + direction_delta[dir].x;
        snake->segments[head_new].y = snake->segments[snake->head].y + direction_delta[dir].y;
        snake->head = head_new;
        snake->lastdirection = dir;
        int eaten = snake->segments[head_new].x == fruit->location.x &&
                    snake->segments[head_new].y == fruit->location.y;
        if (!eaten)
                snake->tail = (snake->tail + 1) % MAX_SNAKE_LENGTH;
        return eaten;
}

int snake_collide(Snake *snake, int screen_width, int screen_height) {
        int headx = snake->segments[snake->head].x;
        int heady = snake->segments[snake->head].y;
        if (headx < 0 || heady < 0 || headx >= screen_width || heady >= screen_height)
                return 1;
        for (int i = snake->tail; i != snake->head; ) {
                if (snake->segments[i].x == headx && snake->segments[i].y == heady)
                        return 1;
                i = (i + 1) % MAX_SNAKE_LENGTH;
        }
        return 0;
}

void snake_draw(Snake *snake, Screen *screen) {
        for (int i = snake->tail; i != snake->head; ) {
                screen_set(screen, ' ', WHITE, GREEN, snake->segments[i].x, snake->segments[i].y);
                i = (i + 1) % MAX_SNAKE_LENGTH;
        }
        screen_set(screen, ' ', WHITE, BLUE, snake->segments[snake->head].x, snake->segments[snake->head].y);
}

void fruit_randomize(Fruit *fruit, Snake *snake, int screen_width, int screen_height) {
        for (;;) {
                int redo = 0;
                int x = rand() % screen_width;
                int y = rand() % screen_height;
                for (int i = snake->tail; i != snake->head; ) {
                        if (snake->segments[i].x == x && snake->segments[i].y == y) {
                                redo = 1;
                                break;
                        }
                        i = (i + 1) % MAX_SNAKE_LENGTH;
                }
                if (snake->segments[snake->head].x == x && snake->segments[snake->head].y == y)
                        redo = 1;
                if (!redo) {
                        fruit->location.x = x;
                        fruit->location.y = y;
                        return;
                }
        }
}

void fruit_draw(Fruit *fruit, Screen *screen) {
        screen_set(screen, ' ', WHITE, RED, fruit->location.x, fruit->location.y);
}
