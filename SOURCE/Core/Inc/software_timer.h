#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "global.h"

extern uint8_t TIME_CYCLES;
extern uint8_t timer_flag[20];
extern uint16_t timer_counter[20];

uint8_t getTimerFlag(uint8_t index);
void setTimerFlag(uint8_t index, uint8_t val);
void timerInit();
void setTimer(uint8_t index, uint32_t delay);
void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
