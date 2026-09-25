/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2026
 *      Author: PHUOC_NHM
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int TIME_CYCLES;

extern int timer0_flag;
extern int timer0_counter;
void setTimer0(int duration);

extern int timer1_flag;
extern int timer1_counter;
void setTimer1(int duration);

extern int timer2_flag;
extern int timer2_counter;
void setTimer2(int duration);

extern int timer3_flag;
extern int timer3_counter;
void setTimer3(int duration);

extern int timer4_flag;
extern int timer4_counter;
void setTimer4(int duration);

extern int timer5_flag;
extern int timer5_counter;
void setTimer5(int duration);

void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
