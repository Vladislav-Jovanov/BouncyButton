#ifndef BOUNCYBUTTON_H
#define BOUNCYBUTTON_H

#include <Arduino.h>
#include <SoftwareInterrupt.h>
//this is the type of interrupt that will be connected to the pin
enum mytype{
    MYSOFT=1,    
    MYHARD=0,
};

class Bouncy_Button
{
    public:
        Bouncy_Button(int Pin, int Mode, int State, mytype Type);
        virtual ~Bouncy_Button();
        void setup(void (*main_func)(),void (*irs_func)(), int delay=NULL);
        void IRS();
        void main();
        void disable();
    protected:
        
        
    private:
        void update_time();
        bool time_passed;
        void (*main_handler)()=NULL;
        void (*irs_handler)()=NULL;
        bool pressed=false;
        bool setup_finished=false;
        long int pressed_time;
        int PIN;
        int MODE;
        int STATE;
        int delay=500;
        mytype TYPE;
        Software_Interrupt INTER=NULL;
};

#endif // BOUNCYBUTTON_H
