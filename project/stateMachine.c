#include <msp430.h>
#include "stateMachine.h"
#include "libTimer.h"
#include "buzzer.h"
#include "sheetMusic.h"
#include "led.h"
#include "switch.h"

int button = 0;

//int playAmerica = 0;
int halfCount = 0;
int play = 2;
int ind = 0;
int hold = 0;

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
  //For every half second
  halfCount ++;
  if(halfCount >= 125){
    hold --;
    if(!hold){
      play = 2;
      lightControl(0);
      buzzer_set_period(0);
    }
    halfCount = 0;
  }
}

//int musicAndLights
int secondCount = 0;
int blinkCount = 0;
int blinkLimit = 0;
int getDim = 0;

void blinkUpdate(){

  blinkCount ++;

  if (blinkCount >= blinkLimit) { 
    blinkCount = 0;
    buzzer_set_period(doReMi[blinkLimit]);
    lightControl(1);
  }
  else{
    lightControl(0);
  }
  secondCount ++;

  //For Every second
  if (secondCount >= 250) {
    secondCount = 0;
    if(!getDim){
      blinkLimit ++;
      if (blinkLimit >= 8){
	getDim = 1;
      }
    }
    else{
      blinkLimit--;
      if(blinkLimit <= -1){
	getDim = 0;
	blinkLimit = 0;
      }
    }
  }
}

void stopUpdates(){
  buzzer_set_period(0);
  lightControl(0);
}

void stateChange(int state){
  switch(state){
  case 1:
    button = 1;
    break;
  case 3:
    button = 3;
    break;
  case 4:
    button = 4;
    break;
  }
}

void timeAdvStateMachines(){
  switch(button){
  case 1:
    noteUpdate();
    break;
  case 3:
    blinkUpdate();
    break;
  case 4:
    stopUpdates();
    break;
  }
}
