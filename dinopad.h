/*
 * Copyright LGPL (c) 2014 Victor Kindhart
 */

// Defining button events
#define EVT_BUTTON_X    0x0
#define EVT_BUTTON_A    0x1
#define EVT_BUTTON_B    0x2
#define EVT_BUTTON_Y    0x3
#define EVT_LB          0x4
#define EVT_RB          0x5
#define EVT_LT          0x6
#define EVT_RT          0x7
#define EVT_Back        0x8
#define EVT_Start       0x9
#define EVT_J1_BTN      0xa
#define EVT_J2_BTN      0xb

/*
 * Arrow keys behave a bit differently -
 * when you release ARROW_UP, it is goint to
 * send two events: ARROW_UP(down) and ARROW_DOWN(down).
 * Same for ARROW_LEFT/ARROW_RIGHT.
 */
#define EVT_ARROW_LEFT  0xc
#define EVT_ARROW_RIGHT 0xd
#define EVT_ARROW_HORZ  0xe

#define EVT_ARROW_UP    0xf
#define EVT_ARROW_DOWN  0x10
#define EVT_ARROW_VERT  0x11

// Moving events for Joystick#1 && Joystick#2
#define EVT_J1_HORZ     0x12
#define EVT_J1_VERT     0x13
#define EVT_J2_HORZ     0x14
#define EVT_J2_VERT     0x15

// Default input device location
#define JS0 "/dev/input/js0"

void gamepad_die();
void gamepad_bind(int evt, void (*func)(int, int));
void gamepad_unbind(int evt);
void gamepad_mainloop();

// Array holding pointers to functions
void (*actions[21])(int, int);
