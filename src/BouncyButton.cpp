#include "BouncyButton.h"
#include "Arduino.h"
#include "SoftwareInterrupt.h"

Bouncy_Button::Bouncy_Button(int Pin, int Mode, int State, mytype Type){
    PIN=Pin;
    MODE=Mode;
    STATE=State;
    TYPE=Type;
    if (TYPE){
        INTER = Software_Interrupt(PIN);
    }
}


Bouncy_Button::~Bouncy_Button(){
    //dtor
}

void Bouncy_Button::IRS(){
    if (TYPE){
        INTER.detachInterrupt();
    }else{
        detachInterrupt(PIN);
    }
    pressed=true;
    pressed_time=millis();
}

void Bouncy_Button::setup(void (*main_func)(),void (*irs_func)()){
    if (TYPE){
        INTER.setup(MODE);
    }else{
        pinMode(PIN,MODE);
    }
    main_handler=main_func;
    irs_handler=irs_func;
    if (TYPE){
        INTER.attachInterrupt(irs_handler,STATE);
    }else{
        attachInterrupt(PIN,irs_handler,STATE);
    }
    setup_finished=true;
}


void Bouncy_Button::disable(){
  setup_finished=false;
  main_handler=NULL;
  irs_handler=NULL;
}

void Bouncy_Button::main(){
    if (TYPE){
        INTER.main();
    }
    if(setup_finished && pressed){
       if (millis()-pressed_time>=500){
            pressed=false;
            main_handler();
            if (TYPE){
                INTER.attachInterrupt(irs_handler, STATE);
            }else{
                attachInterrupt(PIN, irs_handler, STATE);
            }
        } 
    }                               
}
