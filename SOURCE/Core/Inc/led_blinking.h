#ifndef INC_LED_BLINKING_H_
#define INC_LED_BLINKING_H_

#include "global.h"
#include "software_timer.h"

#define BLINK_IDLE 0
#define BLINK_RUNNING 1
#define BLINK_FINISHED 2

uint8_t blink_state;
uint8_t blink_count;
void blinkInit();
void blinkStart();
void blinkRun();
void toggleLED();
void writeLED(GPIO_PinState val);

#endif /* INC_LED_BLINKING_H_ */
