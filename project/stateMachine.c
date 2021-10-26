#include <msp430.h>
#include "stateMachine.h"
#include "libTimer.h"
#include "buzzer.h"
#include "sheetMusic.h"
#include "led.h"
#include "switch.h"

int button = 0;

//int playAmerica = 0;
int halfCountAma = 0;
int playAma = 2;
int indAma = 0;
int holdAma = 0;

void americaUpdate(){//edit play
  if(playAma > 1){
    playAma --;
  }
  else if (playAma == 1){
    playAma = 0;
    if(americaNotes[indAma] > 0){
      lightControl(1);
    }
    else{
      lightControl(2);
    }
    buzzer_set_period(americaNotes[indAma]);
    holdAma = americaHold[indAma];
    indAma++;
  }

  americaCounter();
}

void americaCounter(){
  //For every half second
  halfCountAma ++;
  
  if(halfCountAma >= 125){
    holdAma --;
    if(!holdAma){
      if(indAma == 43){
	button = 4;
      }
      playAma = 2;
      lightControl(0);
      buzzer_set_period(0);
    }
    halfCountAma = 0;
  }
}

//int playHallowen = 0;
int halfCountHal = 0;
int playHal = 2;
int indHal = 0;
int holdHal = 0;

void halloweenUpdate(){//edit play
  if(playHal > 1){
    playHal --;
  }
  else if (playHal == 1){
    playHal = 0;
    if(halloweenNotes[indHal] > 0){
      lightControl(1);
    }
    else{
      lightControl(2);
    }
    buzzer_set_period(halloweenNotes[indHal]);
    holdHal = halloweenHold[indHal];
    indHal++;
  }

  halloweenCounter();
}

void halloweenCounter(){
  //For every half second
  halfCountHal ++;
  
  if(halfCountHal >= 62){
    holdHal --;
    if(!holdHal){
      if(indHal == 63){
	button = 4;
      }
      playHal = 2;
      lightControl(0);
      buzzer_set_period(0);
    }
    halfCountHal = 0;
  }
}


//int musicAndLights = 0;
int secondCount = 0;
int blinkCount = 0;
int blinkLimit = 0;
int getDim = 0;

void blinkUpdate(){

  blinkCount ++;

  if (blinkCount >= blinkLimit && doReMi[blinkLimit] > 0) { 
    blinkCount = 0;
    buzzer_set_period(doReMi[blinkLimit]);
    lightControl(1);
  }
  else{
    lightControl(0);
  }
  
  blinkCounter();
}

void blinkCounter(){
  //For Every second
  secondCount ++;
  
  if (secondCount >= 250) {
    secondCount = 0;
    if(!getDim){
      blinkLimit ++;
      if (blinkLimit >= 7){
	getDim = 1;
      }
    }
    else{
      blinkLimit--;
      if(blinkLimit <= -1){
	button = 4;
      }
    }
  }
}

void stopUpdates(){
  halfCountAma = 0;
  playAma = 2;
  indAma = 0;
  holdAma = 0;

  halfCountHal = 0;
  playHal = 2;
  indHal = 0;
  holdHal = 0;

  secondCount = 0;
  blinkCount = 0;
  blinkLimit = 0;
  getDim = 0;

  buzzer_set_period(0);
  lightControl(0);
}

void stateChange(int state){
  switch(state){
  case 1:
    button = 1;
    break;
  case 2:
    button = 2;
    break;
  case 3:
    button = 3;
    break;
  case 4:
    button = 4;
    break;
  }
}

void timeSM(){
  switch(button){
  case 1:
    americaUpdate();
    break;
  case 2:
    halloweenUpdate();
    break;
  case 3:
    blinkUpdate();
    break;
  case 4:
    stopUpdates();
    break;
  }
}
