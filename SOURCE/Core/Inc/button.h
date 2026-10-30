#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "software_timer.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

typedef struct{
	GPIO_TypeDef *port;
	uint16_t pin;
	uint8_t flag;
	uint8_t last_read;
	uint8_t last_read_stable;
	uint8_t tick;
} button_Typedef;
extern button_Typedef btn[5];

void buttonInit();
void getKeyInput();
uint8_t isButtonPressed(uint8_t index);

#endif /* INC_BUTTON_H_ */
