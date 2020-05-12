#ifndef GRAPHICS_MATRIX_LED_H
#define GRAPHICS_MATRIX_LED_H

#include <Arduino.h>

//global variables
extern byte left_arrow[];
extern byte forward_arrow[];
extern byte right_arrow[];
extern byte reverse_arrow[];
extern byte happy_face[];
extern byte sad_face[];
extern byte error_sign[];

//functions prototype
void graphics_setup();
void graphic(byte character []);

#endif
