/*
 * button.h
 *
 *  Created on: Sep 24, 2026
 *      Author: PHUOC_NHM
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define NORMAL_STATE GPIO_PIN_SET;
#define PRESSED_STATE GPIO_PIN_RESET;

extern int btn_mode_flag;
extern int btn_inc_flag;
extern int btn_dig_flag;
extern int btn_set_flag;

void getKeyInput();

#endif /* INC_BUTTON_H_ */
