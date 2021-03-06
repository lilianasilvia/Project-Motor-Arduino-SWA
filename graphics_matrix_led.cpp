#include <LedControl.h>
#include "graphics_matrix_led.h"

int DIN = 14;
int CS = 12;
int CLK = 13;

byte forward_arrow[] = {0x08,0x08,0x08,0x08,0x7f,0x3e,0x1c,0x08}; 
byte left_arrow[] = {0x00,0x08,0x0c,0x0e,0xff,0x0e,0x0c,0x08};
byte right_arrow[] = {0x00,0x10,0x30,0x70,0xff,0x70,0x30,0x10};
byte reverse_arrow[] = {0x08,0x1c,0x3e,0x7f,0x08,0x08,0x08,0x08};
byte happy_face[] = {0x00,0x66,0x66,0x00,0x18,0x81,0x42,0x3c};
byte sad_face[] = {0x00,0x66,0x66,0x00,0x18,0x00,0x7e,0x81};
byte error_sign[] = {0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81};

LedControl lc = LedControl(DIN,CLK,CS,0);

void graphics_setup() {
  lc.shutdown(0,false);  //setam controllerul sa se reseteze
  lc.setIntensity(0,15); //setam intensitatea ledurilor
  lc.clearDisplay(0); //golim contentul de pe ecran

}

void graphic(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
