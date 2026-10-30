#include "mode_management.h"

const int MAX_MODE = 5;
uint8_t mode = 0;
Digit_Typedef DigitState = STATE_1;

uint8_t getMode(){
	return mode;
}
Digit_Typedef getDigitState(){
	return DigitState;
}
void setMode(uint8_t newMode){
	mode = newMode;
}
void setDigitState(Digit_Typedef newDigitState){
	DigitState = newDigitState;
}

void checkBtnMode(){
	if (isButtonPressed(0)) {
		blinkStart();
		setLedOnOff(LED_ON);
		setDigitState(STATE_1);
		setMode((getMode()+1)%MAX_MODE);
		if (getMode() == 0){
			fsmAutomaticInit();
		}
		if (getMode() == 1){
			setBuffer(2,getLED_RED()/10000);
			setBuffer(3,(getLED_RED()/1000)%10);
			setTimer(3,250);
		}
		if (getMode() == 2){
			setBuffer(2,getLED_AMBER()/10000);
			setBuffer(3,(getLED_AMBER()/1000)%10);
			setTimer(3,250);
		}
		if (getMode() == 3){
			setBuffer(2,getLED_GREEN()/10000);
			setBuffer(3,(getLED_GREEN()/1000)%10);
			setTimer(3,250);
		}
		if (getMode() == 4){
			setBuffer(2,getLED_MAN()/10000);
			setBuffer(3,(getLED_MAN()/1000)%10);
			setTimer(3,250);
		}
	}
}

void checkBtnInc(){
	if (isButtonPressed(1) && getMode() != 0){
		blinkStart();
		setLedOnOff(LED_ON);
		if (getDigitState() == STATE_1) setBuffer(3,(getBuffer(3)+1)%10);
		if (getDigitState() == STATE_10) setBuffer(2,(getBuffer(2)+1)%10);
		if (getMode() == 1 && (getBuffer(2)*10 + getBuffer(3) < 2)){
			setBuffer(3,2);
		}
		if (getMode() !=1 && (getBuffer(2)*10 + getBuffer(3) < 1)){
			setBuffer(3,1);
		}
	}
}

void checkBtnDig(){
	if (isButtonPressed(2) && getMode() != 0){
		blinkStart();
		setLedOnOff(LED_ON);
		switch(getDigitState()){
			case STATE_1:
				setDigitState(STATE_10);
				break;
			case STATE_10:
				setDigitState(STATE_1);
				break;
		}
	}
}

void checkBtnSet(){
	if (isButtonPressed(3) && getMode() != 0){
		blinkStart();
		setLedOnOff(LED_ON);
		if (getMode() == 1){
			setLED_RED((getBuffer(2)*10 + getBuffer(3))*1000);
			if (getLED_AMBER() >= getLED_RED()){
				setLED_AMBER(getLED_RED() - 1000);
				setLED_GREEN(1000);
			}
			if (getLED_GREEN() >= getLED_RED()){
				setLED_GREEN(getLED_RED() - 1000);
				setLED_AMBER(1000);
			}
			if (getLED_GREEN() + getLED_AMBER() != getLED_RED()) setLED_GREEN(getLED_RED() - getLED_AMBER());
		}
		if (getMode() == 2){
			setLED_AMBER((getBuffer(2)*10 + getBuffer(3))*1000);
			if (getLED_AMBER() >= getLED_RED()){
				setLED_AMBER(getLED_RED() - 1000);
				setLED_GREEN(1000);
			}
			if (getLED_GREEN() + getLED_AMBER() != getLED_RED()) setLED_GREEN(getLED_RED() - getLED_AMBER());
			setBuffer(2,(getLED_AMBER()/1000)/10);
			setBuffer(3,(getLED_AMBER()/1000)%10);
		}
		if (getMode() == 3) {
			setLED_GREEN((getBuffer(2)*10 + getBuffer(3))*1000);
			if (getLED_GREEN() >= getLED_RED()){
				setLED_GREEN(getLED_RED() - 1000);
				setLED_AMBER(1000);
			}
			if (getLED_GREEN() + getLED_AMBER() != getLED_RED()) setLED_GREEN(getLED_RED() - getLED_GREEN());
			setBuffer(2,(getLED_GREEN()/1000)/10);
			setBuffer(3,(getLED_GREEN()/1000)%10);
		}
		if (getMode() == 4){
			setLED_MAN((getBuffer(2)*10 + getBuffer(3))*1000);
		}
	}
}
