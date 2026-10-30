#ifndef INC_CONTROL7SEG_H_
#define INC_CONTROL7SEG_H_

#include "global.h"
#include "software_timer.h"
#include "mode_management.h"

extern uint8_t led0,led1;
extern uint8_t ledbuffer[4];

extern const uint8_t MAX_LED;
extern uint8_t index_led;
extern uint8_t ledOn;
extern uint8_t nochange[2];

extern const uint8_t Seg7Value[11];

#define LED_OFF 0
#define LED_ON 1
#define NO_CHANGE_OFF 0
#define NO_CHANGE_ON 1

void init7SEG();
uint8_t getBuffer(uint8_t index);
uint8_t getLedOnOff();
uint8_t getNoChange(uint8_t index);
void setBuffer(uint8_t index, uint8_t val);
void setLedNum(uint8_t index, uint8_t val);
void setNoChange(uint8_t index, uint8_t val);
void setLedOnOff(uint8_t val);
void decreaseLedNum(uint8_t index);
void update7SEGbuffer();
void scan7SEG();
void display7SEG(uint8_t num);

#endif /* INC_CONTROL7SEG_H_ */
