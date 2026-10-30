#include "software_timer.h"

uint8_t TIME_CYCLES = 10;
uint8_t timer_flag[20];
uint16_t timer_counter[20];

uint8_t getTimerFlag(uint8_t index){
	if (index >= 20) return 0;
	return timer_flag[index];
}
void setTimerFlag(uint8_t index, uint8_t val){
	if (index >= 20) return;
	timer_flag[index] = val;
}

void timerInit(){
	for(uint8_t i=0;i<20;i++){
		setTimerFlag(i,0);
		timer_counter[i]=0;
	}
	TIME_CYCLES = ( (htim2.Init.Prescaler+1)*(htim2.Init.Period + 1)* 1000)/8000000;
}

void setTimer(uint8_t index, uint32_t delay){
	if (index >= 20) return;
	setTimerFlag(index,0);
	if (delay < TIME_CYCLES) timer_counter[index] = 1;
	else timer_counter[index] = delay/TIME_CYCLES;
}

void timer_run(){
	for(uint8_t i=0;i<20;i++){
		if (timer_counter[i] > 0){
			timer_counter[i]--;
			if (timer_counter[i] <= 0) setTimerFlag(i,1);
		}
	}
}
