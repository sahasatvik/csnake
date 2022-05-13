#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ioctl.h>

#include "entities.h"
#include "keys.h"

int main(int argc, const char *argv[]) {
        
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        int width = w.ws_col / 2;
        int height = w.ws_row;

        Screen *screen = screen_init(width, height);
        Screen *screen_b = screen_init(width, height);
        
        Snake snake;
        Fruit fruit;

        snake_build(&snake, width / 2, height / 2, RIGHT, 10);
        fruit_randomize(&fruit, &snake, width, height);

        KeyhandlerData kd = { .direction = &(snake.direction), .running = 1 };
        keys_setup();

        pthread_t keys_id;
        pthread_create(&keys_id, NULL, keys_handle, &kd);

        printf(ANSI_CLEAR);
        printf(ANSI_HIDE_CUR);

        int fruiteaten = 0;
        long sleep_time = 200000;

        while (kd.running) {
                screen_reset(screen);
                int eaten = snake_tick(&snake, &fruit);
                if (eaten) {
                        fruiteaten++;
                        if (sleep_time > 10000)
                                sleep_time = (long) (sleep_time * 0.98);
                        fruit_randomize(&fruit, &snake, width, height);
                }
                snake_draw(&snake, screen);
                fruit_draw(&fruit, screen);
                if (snake_collide(&snake, width, height)) {
                        sleep(1);
                        kd.running = 0;
                        pthread_cancel(keys_id);
                        break;
                }
                screen_display(screen, screen_b);
                
                Screen *temp = screen;
                screen = screen_b;
                screen_b = temp;

                usleep(sleep_time);
        }
        
        keys_cleanup();
        screen_free(screen);

        printf(ANSI_GOTO, 0, 0);
        printf(ANSI_CLEAR);
        printf(ANSI_SHOW_CUR);

        pthread_join(keys_id, NULL);

        printf("Fruit eaten: %d\n", fruiteaten);

        return 0;
}
