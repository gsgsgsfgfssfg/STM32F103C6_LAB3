/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2026
 *      Author: PHUOC_NHM
 */


int TIME_CYCLES = 10;

int timer0_flag=0;
int timer0_counter=0;
void setTimer0(int duration){
	timer0_flag = 0;
	if (TIME_CYCLES <= duration) timer0_counter = duration/TIME_CYCLES;
	else timer0_counter = 1;
}

int timer1_flag=0;
int timer1_counter=0;
void setTimer1(int duration){
	timer1_flag = 0;
	if (TIME_CYCLES <= duration) timer1_counter = duration/TIME_CYCLES;
	else timer1_counter = 1;
}

int timer2_flag=0;
int timer2_counter=0;
void setTimer2(int duration){
	timer2_flag = 0;
	if (TIME_CYCLES <= duration) timer2_counter = duration/TIME_CYCLES;
	else timer2_counter = 1;
}

int timer3_flag=0;
int timer3_counter=0;
void setTimer3(int duration){
	timer3_flag = 0;
	if (TIME_CYCLES <= duration) timer3_counter = duration/TIME_CYCLES;
	else timer3_counter = 1;
}

int timer4_flag=0;
int timer4_counter=0;
void setTimer4(int duration){
	timer4_flag = 0;
	if (TIME_CYCLES <= duration) timer4_counter = duration/TIME_CYCLES;
	else timer4_counter = 1;
}

int timer5_flag=0;
int timer5_counter=0;
void setTimer5(int duration){
	timer5_flag = 0;
	if (TIME_CYCLES <= duration) timer5_counter = duration/TIME_CYCLES;
	else timer5_counter = 1;
}

void timer_run(){
	if (timer0_counter > 0){
		timer0_counter--;
		if (timer0_counter <= 0) timer0_flag = 1;
	}
	if (timer1_counter > 0){
		timer1_counter--;
		if (timer1_counter <= 0) timer1_flag = 1;
	}
	if (timer2_counter > 0){
		timer2_counter--;
		if (timer2_counter <= 0) timer2_flag = 1;
	}
	if (timer3_counter > 0){
		timer3_counter--;
		if (timer3_counter <= 0) timer3_flag = 1;
	}
	if (timer4_counter > 0){
		timer4_counter--;
		if (timer4_counter <= 0) timer4_flag = 1;
	}
	if (timer5_counter > 0){
		timer5_counter--;
		if (timer5_counter <= 0) timer5_flag = 1;
	}
}
