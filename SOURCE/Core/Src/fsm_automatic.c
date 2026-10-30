#include "fsm_automatic.h"

void fsmAutomaticInit(){
	init7SEG();
	setStatus(AUTO_RED_GREEN);
	setTimer(0,getLED_GREEN());
	setTimer(2,1000);
	setLedNum(0, getLED_RED()/1000);
	setLedNum(1, getLED_GREEN()/1000);
}
void fsmAutomaticRun(){
	switch(getStatus()){
		case AUTO_RED_GREEN:
			setLedOnOff(LED_ON);
			traffic_light(TRAFFIC_RED_GREEN);
			if (isButtonPressed(4) == 1) {
				fsmManualInit();
				blinkStart();
				break;
			}
			if (getTimerFlag(0) == 1){
				setTimer(0,getLED_AMBER());
				setLedNum(1, getLED_AMBER()/1000);
				setNoChange(1, NO_CHANGE_ON);
				setStatus(AUTO_RED_AMBER);
			}
			break;
		case AUTO_RED_AMBER:
			setLedOnOff(LED_ON);
			traffic_light(TRAFFIC_RED_AMBER);
			if (isButtonPressed(4) == 1) {
				setStatus(MANUAL_RED_AMBER);
				blinkStart();
				break;
			}
			if (getTimerFlag(0) == 1){
				setTimer(0,getLED_GREEN());
				setLedNum(0, getLED_GREEN()/1000);
				setNoChange(0, NO_CHANGE_ON);
				setLedNum(1, getLED_RED()/1000);
				setNoChange(1,NO_CHANGE_ON);
				setStatus(AUTO_GREEN_RED);
			}
			break;
		case AUTO_GREEN_RED:
			setLedOnOff(LED_ON);
			traffic_light(TRAFFIC_GREEN_RED);
			if (isButtonPressed(4) == 1) {
				setStatus(MANUAL_GREEN_RED);
				blinkStart();
				break;
			}
			if (getTimerFlag(0) == 1){
				setTimer(0,getLED_AMBER());
				setLedNum(0, getLED_AMBER()/1000);
				setNoChange(0,NO_CHANGE_ON);
				setStatus(AUTO_AMBER_RED);
			}
			break;
		case AUTO_AMBER_RED:
			setLedOnOff(LED_ON);
			traffic_light(TRAFFIC_AMBER_RED);
			if (isButtonPressed(4) == 1) {
				setStatus(MANUAL_AMBER_RED);
				blinkStart();
				break;
			}
			if (getTimerFlag(0) == 1){
				setTimer(0, getLED_GREEN());
				setLedNum(0, getLED_RED()/1000);
				setNoChange(0, NO_CHANGE_ON);
				setLedNum(1, getLED_GREEN()/1000);
				setNoChange(1, NO_CHANGE_ON);
				setStatus(AUTO_RED_GREEN);
			}
			break;
	}
}
