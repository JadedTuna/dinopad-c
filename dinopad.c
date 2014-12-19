/*
 * Copyright LGPL (c) 2014 Victor Kindhart
 */

#include <stdio.h>
#include <stdlib.h>
#include "dinopad.h"

// Exit with an error message.
void gamepad_die(char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

// Bind an event to a function.
void gamepad_bind(int evt, void (*func)(int, int)) {
    actions[evt] = *func;
}

// Unbind an event.
void gamepad_unbind(int evt) {
    actions[evt] = NULL;
}

/* Main (listen) loop. *fn* is input device's location.
 * Use JS0 for default.
 */
void gamepad_mainloop(char* fn) {
    char action[8];
    unsigned char val, value1, value2, type, number;

    FILE* fp = fopen(fn, "r");
    if (!fp) gamepad_die("gamepad_mainloop: gamepad not found");
    setbuf(stdout, NULL);
    for (;;) {
        fread(action, 8, 1, fp);


        value1 = 4[action];
        value2 = 5[action];
        type   = 6[action];
        number = 7[action];

        switch (type) {
            case 0x01:
                switch (number) {
                    case EVT_BUTTON_X:
                    case EVT_BUTTON_A:
                    case EVT_BUTTON_B:
                    case EVT_BUTTON_Y:
                    case EVT_LB:
                    case EVT_RB:
                    case EVT_LT:
                    case EVT_RT:
                    case EVT_Start:
                    case EVT_Back:
                    case EVT_J1_BTN:
                    case EVT_J2_BTN:
                        if (actions[number])
                            actions[number](value1, value2);
                        break;
                    default:
                        fprintf(stderr,
                            "unknown action number for "
                            "type 0x1: 0x%x\n",
                            number);
                        break;
                    }
                break;
            case 0x02:
                val = (value1 > 0);
                switch (number) {
                    case 0x00:
                        // J1 HORZ
                        if (actions[EVT_J1_HORZ])
                            actions[EVT_J1_HORZ](value1, value2);
                        break;
                    case 0x01:
                        // J1 VERT
                        if (actions[EVT_J1_VERT])
                            actions[EVT_J1_VERT](value1, value2);
                        break;
                    case 0x02:
                        // J2 HORZ
                        if (actions[EVT_J2_HORZ])
                            actions[EVT_J2_HORZ](value1, value2);
                        break;
                    case 0x03:
                        // J2 VERT
                        if (actions[EVT_J2_VERT])
                            actions[EVT_J2_VERT](value1, value2);
                        break;
                    case 0x04:
                        switch (value2) {
                            case 0x80:
                                if (actions[EVT_ARROW_LEFT])
                                    actions[EVT_ARROW_LEFT](val, value2);
                                break;
                            case 0x7f:
                                if (actions[EVT_ARROW_RIGHT])
                                    actions[EVT_ARROW_RIGHT](val, value2);
                                break;
                            case 0x0:
                                if (actions[EVT_ARROW_HORZ])
                                    actions[EVT_ARROW_HORZ](val, value2);
                                break;
                            default:
                                fprintf(stderr,
                                    "unknown value#2 for "
                                    "ARROW_HORIZONTAL: 0x%x\n",
                                    value2);
                                break;
                        }
                        break;
                    case 0x05:
                        switch (value2) {
                            case 0x80:
                                if (actions[EVT_ARROW_UP])
                                    actions[EVT_ARROW_UP](val, value2);
                                break;
                            case 0x7f:
                                if (actions[EVT_ARROW_DOWN])
                                    actions[EVT_ARROW_DOWN](val, value2);
                                break;
                            case 0x0:
                                if (actions[EVT_ARROW_VERT])
                                    actions[EVT_ARROW_VERT](val, value2);
                                break;
                            default:
                                fprintf(stderr,
                                    "unknown value#2 for "
                                    "ARROW_VERTICAL: 0x%x\n",
                                    value2);
                                break;
                        }
                        break;
                    default:
                        fprintf(stderr,
                            "unknown action number for "
                            "type 0x2: 0x%x\n",
                            number);
                        break;
                }
                break;

            /* These types init buttons I guess */
            case 0x81:
            case 0x82:
                break;

            default:
                fprintf(stderr, "unknown action type: 0x%x\n", type);
                break;
        }
    }
}
