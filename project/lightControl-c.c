#include <msp430.h>
#include "led.h"

void lightControl(int trig){
  switch(trig){
  case 0://Both LEDs turned off
    P1OUT &= ~LEDS;
    break;
  case 1://Green LED turned on only
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  case 2://Red LED turned on only
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
    break;
  default://Both LEDs turned on
    P1OUT |= LEDS;
    break;
  }

}
