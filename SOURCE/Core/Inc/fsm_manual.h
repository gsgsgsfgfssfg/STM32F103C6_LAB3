#ifndef INC_FSM_MANUAL_H_
#define INC_FSM_MANUAL_H_

#include "global.h"
#include "traffic_light.h"
#include "software_timer.h"
#include "control7seg.h"
#include "mode_management.h"
#include "fsm_automatic.h"

#define MANUAL_RED_GREEN 21
#define MANUAL_RED_AMBER 22
#define MANUAL_GREEN_RED 23
#define MANUAL_AMBER_RED 24

void fsmManualInit();
void fsmManualRun();

#endif /* INC_FSM_MANUAL_H_ */
