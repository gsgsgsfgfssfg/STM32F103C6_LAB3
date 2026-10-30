#include "fsm_manual.h"

void fsmManualInit(){
	setStatus(MANUAL_RED_GREEN);
	setTimer(0,getLED_MAN());
}

void fsmManualRun(){
	switch(getStatus()){
		case MANUAL_RED_GREEN:
			setLedOnOff(LED_OFF);
			traffic_light(TRAFFIC_RED_GREEN);
			if (getTimerFlag(0) == 1){
				fsmAutomaticInit();
				break;
			}
			if (isButtonPressed(4) == 1) {
				setStatus(MANUAL_RED_AMBER);
				blinkStart();
			}
			break;
		case MANUAL_RED_AMBER:
			setLedOnOff(LED_OFF);
			traffic_light(TRAFFIC_RED_AMBER);
			if (isButtonPressed(4) == 1) {
				setStatus(MANUAL_GREEN_RED);
				blinkStart();
			}
			break;
		case MANUAL_GREEN_RED:
			setLedOnOff(LED_OFF);
			traffic_light(TRAFFIC_GREEN_RED);
			if (isButtonPressed(4) == 1) {
				setStatus(MANUAL_AMBER_RED);
				blinkStart();
			}
			break;
		case MANUAL_AMBER_RED:
			setLedOnOff(LED_OFF);
			traffic_light(TRAFFIC_AMBER_RED);
			if (isButtonPressed(4) == 1) {
				setStatus(MANUAL_RED_GREEN);
				setTimer(0,getLED_MAN());
				blinkStart();
			}
			break;
	}
}
