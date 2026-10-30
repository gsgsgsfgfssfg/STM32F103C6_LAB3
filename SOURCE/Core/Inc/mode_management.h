#ifndef INC_MODE_MANAGEMENT_H_
#define INC_MODE_MANAGEMENT_H_

#include "global.h"
#include "button.h"
#include "control7seg.h"

extern uint8_t mode;
extern const int MAX_MODE;

typedef enum{
	STATE_1,
	STATE_10
}Digit_Typedef;
extern Digit_Typedef DigitState;

uint8_t getMode();
Digit_Typedef getDigitState();
void setMode(uint8_t newMode);
void setDigitState(Digit_Typedef newDigitState);
void checkBtnMode();
void checkBtnInc();
void checkBtnDig();
void checkBtnSet();

#endif /* INC_MODE_MANAGEMENT_H_ */
