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
//this should be provided as IRS function in the IRS main for the desired state
void Bouncy_Button::IRS(){
    if (TYPE==MYHARD){
        detachInterrupt(PIN);
    }
    pressed=true;
    pressed_time=millis();
}

void Bouncy_Button::setup(void (*main_func)(),void (*irs_func)(),int delay){
    if (TYPE){
        INTER.setup(MODE);
    }else{
        if (MODE==(INPUT || INPUT_PULLUP)){
            pinMode(PIN,MODE);
        }
    }
    main_handler=main_func;
    irs_handler=irs_func;
    if (TYPE){
        INTER.attachInterrupt(irs_handler,STATE,delay);
    }else{
        attachInterrupt(PIN,irs_handler,STATE);
    }
    setup_finished=true;
}


void Bouncy_Button::disable(){
    setup_finished=false;
    if (TYPE){
        INTER.detachInterrupt();
    }else{
        detachInterrupt(PIN);
    }
}


void Bouncy_Button::update_time(){
    if (millis()-pressed_time>=delay){
        time_passed=true;
    }
}

void Bouncy_Button::main(){
    if (setup_finished && TYPE){
        INTER.main();
    }
    if(setup_finished && pressed){
        if (pressed){
            update_time();
        }
        if (time_passed){
            time_passed=false;
            pressed=false;
            main_handler();
            if (TYPE==MYHARD){
                attachInterrupt(PIN, irs_handler, STATE);
            }
        } 
    }                               
}
