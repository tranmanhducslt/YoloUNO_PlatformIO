#include "softwareTimer.h"
#include "fsm_cx1.h"
#include "Arduino.h"

#define D3 6
#define D4 7
#define D5 8
#define D6 9

#define L_RED 1
#define L_YELLOW 2
#define L_GREEN 3

int fsm_status = 0;

void lightSwitch(int Lcode, int colour){
    // Lcode is here D3 or D5, respectively
    switch(colour){
        case L_RED:
            digitalWrite(Lcode, HIGH);
            digitalWrite(Lcode + 1, HIGH);
            break;
        case L_YELLOW:
            digitalWrite(Lcode, LOW);
            digitalWrite(Lcode + 1, HIGH);
            break;
        case L_GREEN:
            digitalWrite(Lcode, HIGH);
            digitalWrite(Lcode + 1, LOW);
            break;
        default: // 0: turn off
            digitalWrite(Lcode, LOW);
            digitalWrite(Lcode + 1, LOW);
    }
}

// PHASES: 0, 1 [10-8], 2 [7-6], 3 [5-3], 4 [2-1]
void fsm_run(){
    switch(fsm_status){
        case 0:
            fsm_status = 1;
            setTimer(0, T_light);
            // initialise the lights
            pinMode(D3, OUTPUT); 
            pinMode(D4, OUTPUT); 
            pinMode(D5, OUTPUT); 
            pinMode(D6, OUTPUT); 
            break;
        case 1: 
            lightSwitch(D3, L_RED); lightSwitch(D5, L_GREEN);
            if (getTimer(0) == 700) fsm_status = 2;
            break;
        case 2:
            lightSwitch(D5, L_YELLOW);
            if (getTimer(0) == 500) fsm_status = 3;
            break;
        case 3:
            lightSwitch(D3, L_GREEN); lightSwitch(D5, L_RED);
            if (getTimer(0) == 200) fsm_status = 4;
            break;
        case 4:
            lightSwitch(D3, L_YELLOW);
            if (isTimerExpired(0)){
                fsm_status = 1;
                setTimer(0, T_light);
            }
            break;
        default: 
            fsm_status = 0;
            break;
    }
}