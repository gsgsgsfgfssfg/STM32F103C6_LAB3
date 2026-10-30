#include "control7seg.h"

uint8_t led0,led1;
uint8_t ledbuffer[4];

const uint8_t MAX_LED = 4;
uint8_t index_led;
uint8_t ledOn = 1;
uint8_t nochange[2] = {NO_CHANGE_OFF, NO_CHANGE_OFF};

const uint8_t Seg7Value[11] = {
		0b0000001,
		0b1001111,
		0b0010010,
		0b0000110,
		0b1001100,
		0b0100100,
		0b0100000,
		0b0001111,
		0b0000000,
		0b0000100,
		0b1111111
};

void init7SEG(){
	index_led = 0;
	setTimer(3,250);
}

uint8_t getLedOnOff(){
	return ledOn;
}

uint8_t getBuffer(uint8_t index){
	if (index >= MAX_LED) return 10;
	return ledbuffer[index];
}

uint8_t getNoChange(uint8_t index){
	if (index == 0) {
		uint8_t res = nochange[0];
		setNoChange(0, NO_CHANGE_OFF);
		return res;
	}
	if (index == 1){
		uint8_t res = nochange[1];
		setNoChange(1, NO_CHANGE_OFF);
		return res;
	}
	return 0;
}

void setLedOnOff(uint8_t val){
	if (val != LED_OFF) ledOn = LED_ON;
	else ledOn = LED_OFF;
}

void setBuffer(uint8_t index, uint8_t val){
	if (index >= MAX_LED) return;
	ledbuffer[index] = val;
}

void setLedNum(uint8_t index, uint8_t val){
	if (index == 0) led0 = val;
	if (index == 1) led1 = val;
}

void setNoChange(uint8_t index, uint8_t val){
	if (index >= 2) return;
	nochange[index] = val;
}

void decreaseLedNum(uint8_t index){
	if (index == 0) led0--;
	if (index == 1) led1--;
}

void update7SEGbuffer(){
	if (getMode() == 0){
		setBuffer(0, led0/10);
		setBuffer(1, led0%10);
		setBuffer(2, led1/10);
		setBuffer(3, led1%10);
		if (getTimerFlag(2) == 1) {
			if (getNoChange(0) == NO_CHANGE_OFF) decreaseLedNum(0);
			if (getNoChange(1) == NO_CHANGE_OFF) decreaseLedNum(1);
			setTimer(2,1000);
		}
		return;
	}
	if (getMode() == 1){
		setBuffer(0, 0);
		setBuffer(1, 1);
		return;
	}
	if (getMode() == 2){
		setBuffer(0, 0);
		setBuffer(1, 2);
		return;
	}
	if (getMode() == 3){
		setBuffer(0, 0);
		setBuffer(1, 3);
		return;
	}
	if (getMode() == 4){
		setBuffer(0,0);
		setBuffer(1,4);
		return;
	}
}

void scan7SEG(){
	if (getLedOnOff() == LED_OFF){
		HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
		return;
	}
	if (getTimerFlag(3) == 1){
		index_led = (index_led+1)%MAX_LED;
		setTimer(3,250);
	}
	switch (index_led){
		case 0:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN0_Pin|EN3_Pin, GPIO_PIN_SET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN2_Pin|EN0_Pin, GPIO_PIN_SET);
			break;
	}
	display7SEG(getBuffer(index_led));
}

void display7SEG(uint8_t num){
	int index=num;
	if (num > 9) index = 10;
	HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, Seg7Value[index] & 0x40);
	HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, Seg7Value[index] & 0x20);
	HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, Seg7Value[index] & 0x10);
	HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, Seg7Value[index] & 0x08);
	HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, Seg7Value[index] & 0x04);
	HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, Seg7Value[index] & 0x02);
	HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, Seg7Value[index] & 0x01);
}
