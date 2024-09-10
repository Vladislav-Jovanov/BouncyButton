#include <BouncyButton.h>



int prg_nmbr=0;
Bouncy_Button mybutton(4,INPUT_PULLUP, FALLING, MYSOFT);


void IRS(){
     mybutton.IRS();
 }

void main_action(){
    prg_nmbr--;
    if (prg_nmbr<=-1){
        prg_nmbr=prg_nmbr + 4;
    }
    Serial.println(prg_nmbr);
}


void setup() {
  Serial.begin(115200);
  mybutton.setup(&main_action,&IRS);
}

void loop() {
    mybutton.main();  
}
