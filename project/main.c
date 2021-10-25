#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "sheetMusic.h"
#include "led.h"

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 |  SW2 |  SW3 | SW4) //(0xF)

void switch_init(){
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
}
void led_init(){
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}
void wdt_init(){
  configureClocks();
  enableWDTInterrupts();
}

int main() {
    switch_init();
    led_init();
    buzzer_init();
    wdt_init();
 
    or_sr(0x18);          // CPU off, GIE on
}

int secondCount = 0;
//int blinkLimit = 0;
//int dimmer = 0;
int play = 0;
int ind = 0;
int hold = 0;
int button = 0;

void oncePerHalfSecond(){
  hold --;
  if(!hold){
    play = 2;
    lightControl(0);
    buzzer_set_period(0);
  }
}

void noteUpdate(){//edit play
  if(play > 1){
    play --;
  }
  else if (play == 1){
    play = 0;
    if(americaNotes[ind] > 0){
      lightControl(1);
    }
    else{
      lightControl(2);
    }
    buzzer_set_period(americaNotes[ind]);
    hold = americaHold[ind];
    ind++;
    if(ind == 43){
      ind = 0;
    }
  }
}
void secondUpdate(){
    secondCount ++;
    if (secondCount % 125 == 0) { // every half second
      oncePerHalfSecond();
    }

    if (secondCount >= 125) { // once each second
      secondCount = 0;
      //oncePerSecond();
    }
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
  
  char state = (p2val & SW1) ? 0 : 1;
  if (state == 0) state = (p2val & SW2) ? 0 : 2;
  if (state == 0) state = (p2val & SW3) ? 0 : 3;
  if (state == 0) state = (p2val & SW4) ? 0 : 4;
  stateChange(state); 
  
}

void stateChange(int state){
  switch(state){
  case 1:
    play = 1;
    button = 1;
    break;
    /*
  case 3:
    dimmer = 1;
    button = 3;
    break;
    */
  case 4:
    play = 0;
    ind = 0;
    hold = 0;
    button = 4;
    break;
  }

}

void timeAdvStateMachines(){
    secondUpdate();
    switch(button){
    case 1:
      noteUpdate();
      break;
    case 4:
      lightControl(0);
      buzzer_set_period(0);
      break;
    }
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}

void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
    timeAdvStateMachines();
}
