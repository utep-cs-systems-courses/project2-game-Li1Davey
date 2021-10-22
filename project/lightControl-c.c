#include <msp430.h>
#include "led.h"

void lightControl(int trig){
  switch(trig){
  case 0://Both off
    P1OUT &= ~LEDS;
    break;
  case 1://Green on only
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
    break;
  case 2://Red on only
    P1OUT &= ~LED_GREEN;
    P1OUT |= LED_RED;
    break;
  default://Both on
    P1OUT |= LEDS;
    break;
  }

}
