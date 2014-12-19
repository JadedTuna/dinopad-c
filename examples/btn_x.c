#include <stdio.h>
#include "dinopad.h"

void button_x(int state, int value2) {
    printf("Button X: %i\n", state);
}

int main() {
    gamepad_bind(EVT_BUTTON_X, button_x);
    gamepad_mainloop(JS0);
}
