#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "sheetMusic.h"
#include "led.h"

int main() {
    P1DIR |= LEDS;
    P1OUT &= ~LEDS;

    configureClocks();
    buzzer_init();
    enableWDTInterrupts();
 
    or_sr(0x18);          // CPU off, GIE on
}

int secondCount = 0;
int play = 1;
int ind = 0;
int hold = 0;

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
   
    if (secondCount % 125 == 0) {
      oncePerHalfSecond();
    }

    if (secondCount >= 125) { // once each second
      secondCount = 0;
    }
}

void timeAdvStateMachines(){
    secondUpdate();
    noteUpdate();
}

void __interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
    timeAdvStateMachines();
}
