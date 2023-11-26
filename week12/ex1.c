#include <linux/input-event-codes.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define EVENT_FILE "/dev/input/by-path/platform-i8042-serio-0-event-kbd"
#define SHORTCUT_PE "PE"
#define SHORTCUT_CAP "CAP"
#define SHORTCUT_CUSTOM "RU"
#define CAP "Get some cappuccino!\n"
#define PE "I passed the Exam!\n"
#define RU "RUSSIA\n"

int e_pressed = 0;
int p_pressed = 0;
int c_pressed = 0;
int a_pressed = 0;
int r_pressed = 0;
int u_pressed = 0;
int x_pressed = 0;

void handle_event(struct input_event event) {
    switch (event.type) {
        case EV_KEY:
            if (event.value == 0 || event.value == 1 || event.value == 2) {
                printf("RELEASED 0x%04X (%d)\n", event.code, event.code);
                switch (event.code) {
                    case KEY_E:
                        e_pressed =0;
                        break;
                    case KEY_P:
                        p_pressed =0;
                        break;
                    case KEY_C:
                        c_pressed =0;
                        break;
                    case KEY_A:
                        a_pressed =0;
                        break;
                    case KEY_R:
                        r_pressed =0;
                        break;
                    case KEY_U:
                        u_pressed =0;
                        break;
                    case KEY_X:
                        x_pressed =0;
                        break;
                    default:
                        break;
                }
            }
            if (event.value == 1){
                printf("PRESSED 0x%04X (%d)\n",event.code,event.code);
                switch (event.code) {
                    case KEY_E:
                        e_pressed =1;
                        break;
                    case KEY_P:
                        p_pressed =1;
                        break;
                    case KEY_C:
                        c_pressed =1;
                        break;
                    case KEY_A:
                        a_pressed =1;
                        break;
                    case KEY_R:
                        r_pressed =1;
                        break;
                    case KEY_U:
                        u_pressed =1;
                        break;
                    case KEY_X:
                        x_pressed =1;
                        break;
                    default:
                        break;
                }
            }
            if (event.value == 2){
                printf("REPEATED 0x%04X (%d)\n",event.code,event.code);
            }
            fflush(stdout);
            break;
        default:
            break;
    }
}

int main() {
    int fd = open(EVENT_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Error opening input device");
        return EXIT_FAILURE;
    }

    while (1) {
        struct input_event event;
        ssize_t bytesRead = read(fd, &event, sizeof(event));
        if (bytesRead == sizeof(event)) {
            handle_event(event);

            if (p_pressed && e_pressed){
                printf(PE);
            }
            if (c_pressed && a_pressed && p_pressed){
                printf(CAP);
            }
            if (r_pressed && u_pressed){
                printf(RU);
            }
            if (e_pressed && x_pressed){
                exit(EXIT_SUCCESS);
            }
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}
