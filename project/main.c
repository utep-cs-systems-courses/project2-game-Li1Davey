#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"
#include "switch.h"
#include "stateMachine.h"


void led_init(){
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}
void wdt_init(){
  configureClocks(); /* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts(); /* enable periodic interrupt */
}

int main() { // Initialize everything at the start
    switch_init();
    led_init();
    buzzer_init();
    wdt_init();
 
    or_sr(0x18);          // CPU off, GIE on
}

void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
    timeSM();
}
