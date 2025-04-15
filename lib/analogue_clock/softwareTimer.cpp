#include "softwareTimer.h"
#define NUM_TIMERS 10

int timer_counter[NUM_TIMERS];
int timer_flag[NUM_TIMERS];

void timerInit() {
    for (int i = 0; i < NUM_TIMERS; i++) {
        timer_counter[i] = 0;
        timer_flag[i] = 0;
    }
}

void setTimer(int index, int value) {
    if (index < NUM_TIMERS) {
        timer_counter[index] = value;
        timer_flag[index] = 0;
    }
}

int getTimer(int index){ // how much time left
    if (index < NUM_TIMERS)
        return timer_counter[index];
    return -1; // Invalid index
}

int isTimerExpired(int index) {
    if (index < NUM_TIMERS) {
        if (timer_counter[index] == 0) {
            timer_flag[index] = 1;
            return 1;
        } else {
            timer_counter[index]--;
        }
    }
    return 0;
}
void timerRun() {
    for (int i = 0; i < NUM_TIMERS; i++) {
        if (timer_counter[i] > 0) {
            timer_counter[i]--;
            if (timer_counter[i] == 0) {
                timer_flag[i] = 1; // Set the flag when the timer expires
            }
        }
    }
}