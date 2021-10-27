#include <msp430.h>
#include "stateMachine.h"
#include "libTimer.h"
#include "buzzer.h"
#include "sheetMusic.h"
#include "led.h"
#include "switch.h"

int button = 0;

int halfCountAma = 0;
int playAma = 2;
int indAma = 0;
int holdAma = 0;

void americaUpdate(){ //Play the America Song
  if(playAma > 1){
    playAma --;
  }
  else if (playAma == 1){
    playAma = 0;
    if(americaNotes[indAma] > 0){ //Turns the Green LED on if buzzer cycle is not zero.
      lightControl(1);
    }
    else{
      lightControl(2); //Turns the Red LED on if the buzzer cycle is zero.
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

int halfCountHal = 0;
int playHal = 2;
int indHal = 0;
int holdHal = 0;

void halloweenUpdate(){ //Plays Halloween song
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
  //For every qurater second
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
      if (blinkLimit >= 7){ //when blink limit reaches highest limit it will tell the blink counter to make the LED dimmer
	getDim = 1;
      }
    }
    else{
      blinkLimit--;
      if(blinkLimit <= -1){
	button = 4; //Stops everyting
      }
    }
  }
}

void stopUpdates(){ //Turns off the buzzer and LEDs and reutrns all initial variables to their original value to start over
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

void timeSM(){ //Changes the method based on the button pressed
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
