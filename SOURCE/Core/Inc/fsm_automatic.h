#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

#include "global.h"
#include "traffic_light.h"
#include "software_timer.h"
#include "control7seg.h"
#include "mode_management.h"
#include "fsm_manual.h"

#define AUTO_RED_GREEN 11
#define AUTO_RED_AMBER 12
#define AUTO_GREEN_RED 13
#define AUTO_AMBER_RED 14

void fsmAutomaticInit();
void fsmAutomaticRun();

#endif /* INC_FSM_AUTOMATIC_H_ */
