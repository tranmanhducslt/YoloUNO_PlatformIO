#include "softwareTimer.h"
#include "fsm_cx1.h"
#include "Arduino.h"

// 4 light devices, each to 2 pins
#define D3 6
#define D4 7
#define D5 8
#define D6 9
#define D7 10
#define D8 11
#define D9 12
#define D10 13

#define L_RED 0
#define L_YELLOW 1
#define L_GREEN 2

void lightSwitch(int Lcode, int colour){
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
        default: // turn off 
            digitalWrite(Lcode, LOW);
            digitalWrite(Lcode + 1, LOW);
    }
}

void clockSwitch(int position){
    // positions: 0-2, 3-5, 6-8, 9-11
    int lightCode = 0;
    if (position >= 0 && position <= 2) lightCode = D3; 
    else if (position >= 3 && position <= 5) lightCode = D5; 
    else if (position >= 6 && position <= 8) lightCode = D7; 
    else if (position >= 9 && position <= 11) lightCode = D9; 
    else {
        lightSwitch(lightCode, 3); // turn off all lights
        return;
    }
    lightSwitch(lightCode, position % 3);
}

/* 
    - the 4 light devices represent clock positions (0-2, 3-5, 6-8, 9-11)
    - they're connected to the pins D3-4, D5-6, D7-8 and D9-10
    - three hands, each controlling all lights and may overlap
*/

int timeSeconds = 0; // 0 to 43200 (12 hours)
int Hhd = 0, Mhd = 0, Shd = 0; // hands: hours, minutes, seconds
int fsm_status = 0; // 0: initial, 1: running

void fsm_run(){
    switch(fsm_status){
        case 0:
            fsm_status = 1;
            setTimer(0, T_light);
            // initialise the lights
            pinMode(D3, OUTPUT); pinMode(D4, OUTPUT); 
            pinMode(D5, OUTPUT); pinMode(D6, OUTPUT); 
            pinMode(D7, OUTPUT); pinMode(D8, OUTPUT);
            pinMode(D9, OUTPUT); pinMode(D10, OUTPUT);
            break;
        case 1:
            // check if the timer has expired
            if (getTimer(0) == 1000) {
                timeSeconds = (timeSeconds + 1) % 43200; // increment the time in seconds
                
                // update the hands based on the time in seconds
                Hhd = (timeSeconds / 3600); // hour hand, 1 hour per position
                Mhd = (timeSeconds / 300) % 12; // minute hand, 5 minutes per position
                Shd = (timeSeconds / 5) % 12; // second hand, 5 seconds per position

                // update the lights based on the hands
                clockSwitch(Hhd); clockSwitch(Mhd); clockSwitch(Shd); 

                setTimer(0, 1000); // reset the timer
                fsm_status = 1; // continue running
            }
            break;
        default:
            fsm_status = 0;
            break;
    }
}