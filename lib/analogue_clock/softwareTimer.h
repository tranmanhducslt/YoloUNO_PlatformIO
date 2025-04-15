#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

void setTimer(int index, int value);
int getTimer(int index); 
int isTimerExpired(int index);

void timerInit();
void timerRun();
#endif