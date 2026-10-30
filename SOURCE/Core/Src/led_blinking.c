#include "led_blinking.h"

void blinkInit(){
	blink_state = BLINK_IDLE;
	blink_count = 0;
	writeLED(GPIO_PIN_SET);
}

void blinkStart(){
    blink_state = BLINK_RUNNING;
    blink_count = 0;
    setTimer(1, 50);
}
void blinkRun(){
    if (blink_state != BLINK_RUNNING)
        return;

    if (getTimerFlag(1) == 1) {
        setTimer(1, 50);

        toggleLED();
        blink_count++;

        if (blink_count >= 4) {
        	blink_state = BLINK_FINISHED;
        	writeLED(GPIO_PIN_SET);
        }
    }
}
void toggleLED(){
	HAL_GPIO_TogglePin(DEBUGGG_GPIO_Port, DEBUGGG_Pin);
}
void writeLED(GPIO_PinState val){
	HAL_GPIO_WritePin(DEBUGGG_GPIO_Port, DEBUGGG_Pin, val);
}
