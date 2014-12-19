#include <stdio.h>
#include "dinopad.h"

void j1_vert(int unknown, int push) {
    printf("J1 VERT: %i\n", push);
}

int main() {
    gamepad_bind(EVT_J1_VERT, j1_vert);
    gamepad_mainloop(JS0);
}
