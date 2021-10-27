#include <msp430.h>
#include "libTimer.h"
#include "switch.h"
#include "stateMachine.h"

void switch_init(){
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
}

static char checkSwitches(){
  char p2val = P2IN;
  //Check if there is a change
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */
  return p2val;
}

void switch_interrupt_handler(){
  char p2val = checkSwitches();
  //set the value of state to the corresponding switch that is pressed
  char state = (p2val & SW1) ? 0 : 1;
  if (state == 0) state = (p2val & SW2) ? 0 : 2;
  if (state == 0) state = (p2val & SW3) ? 0 : 3;
  if (state == 0) state = (p2val & SW4) ? 0 : 4; 
  stateChange(state);
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}
