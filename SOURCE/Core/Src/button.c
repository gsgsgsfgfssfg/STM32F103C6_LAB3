/*
 * button.c
 *
 *  Created on: Sep 24, 2026
 *      Author: PHUOC_NHM
 */

#include "button.h"
#include "main.h"
#include "software_timer.h"

uint8_t last_read_btn_mode = NORMAL_STATE;
uint8_t last_read_btn_mode_stable = NORMAL_STATE;
int btn_mode_tick = 0;
int btn_mode_flag = 0;

uint8_t last_read_btn_inc = NORMAL_STATE;
uint8_t last_read_btn_inc_stable = NORMAL_STATE;
int btn_inc_tick = 0;
int btn_inc_flag = 0;

uint8_t last_read_btn_dig = NORMAL_STATE;
uint8_t last_read_btn_dig_stable = NORMAL_STATE;
int btn_dig_tick = 0;
int btn_dig_flag = 0;

uint8_t last_read_btn_set = NORMAL_STATE;
uint8_t last_read_btn_set_stable = NORMAL_STATE;
int btn_set_tick = 0;
int btn_set_flag = 0;

void getKeyInput(){
	if (timer5_flag == 1){
		uint8_t current_btn_mode = HAL_GPIO_ReadPin(BTN_MODE_GPIO_Port,BTN_MODE_Pin);
		if (last_read_btn_mode != current_btn_mode) {
			btn_mode_tick = 0;
		}
		else {
			if (TIME_CYCLES > 10) btn_mode_tick += TIME_CYCLES;
			else btn_mode_tick += (10/TIME_CYCLES) * TIME_CYCLES;
		}
		if (btn_mode_tick >= 30){
			if (current_btn_mode == GPIO_PIN_SET && last_read_btn_mode_stable == GPIO_PIN_RESET ){
				btn_mode_tick = 0;
				btn_mode_flag = 1;
			}
			last_read_btn_mode_stable = current_btn_mode;
		}
		last_read_btn_mode = current_btn_mode;

		uint8_t current_btn_inc = HAL_GPIO_ReadPin(BTN_INC_GPIO_Port,BTN_INC_Pin);
		if (last_read_btn_inc != current_btn_inc) {
			btn_inc_tick = 0;
		}
		else {
			if (TIME_CYCLES > 10) btn_inc_tick += TIME_CYCLES;
			else btn_inc_tick += (10/TIME_CYCLES) * TIME_CYCLES;
		}
		if (btn_inc_tick >= 30){
			if (current_btn_inc == GPIO_PIN_SET && last_read_btn_inc_stable == GPIO_PIN_RESET ){
				btn_inc_tick = 0;
				btn_inc_flag = 1;
			}
			last_read_btn_inc_stable = current_btn_inc;
		}
		last_read_btn_inc = current_btn_inc;

		uint8_t current_btn_dig = HAL_GPIO_ReadPin(BTN_DIG_GPIO_Port,BTN_DIG_Pin);
		if (last_read_btn_dig != current_btn_dig) {
			btn_dig_tick = 0;
		}
		else {
			if (TIME_CYCLES > 10) btn_dig_tick += TIME_CYCLES;
			else btn_dig_tick += (10/TIME_CYCLES) * TIME_CYCLES;
		}
		if (btn_dig_tick >= 30){
			if (current_btn_dig == GPIO_PIN_SET && last_read_btn_dig_stable == GPIO_PIN_RESET ){
				btn_dig_tick = 0;
				btn_dig_flag = 1;
			}
			last_read_btn_dig_stable = current_btn_dig;
		}
		last_read_btn_dig= current_btn_dig;

		uint8_t current_btn_set = HAL_GPIO_ReadPin(BTN_SET_GPIO_Port,BTN_SET_Pin);
		if (last_read_btn_set != current_btn_dig) {
			btn_set_tick = 0;
		}
		else {
			if (TIME_CYCLES > 10) btn_set_tick += TIME_CYCLES;
			else btn_set_tick += (10/TIME_CYCLES) * TIME_CYCLES;
		}
		if (btn_set_tick >= 30){
			if (current_btn_set == GPIO_PIN_SET && last_read_btn_set_stable == GPIO_PIN_RESET ){
				btn_set_tick = 0;
				btn_set_flag = 1;
			}
			last_read_btn_set_stable = current_btn_set;
		}
		last_read_btn_set= current_btn_set;

		setTimer5(10);
	}
}
