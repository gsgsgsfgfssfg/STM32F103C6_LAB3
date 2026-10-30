#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "global.h"

#define TRAFFIC_OFF 0
#define TRAFFIC_RED_GREEN 1
#define TRAFFIC_RED_AMBER 2
#define TRAFFIC_GREEN_RED 3
#define TRAFFIC_AMBER_RED 4
#define TRAFFIC_RED_RED 5
#define TRAFFIC_AMBER_AMBER 6
#define TRAFFIC_GREEN_GREEN 7

void traffic_light(uint8_t led);

#endif /* INC_TRAFFIC_LIGHT_H_ */
