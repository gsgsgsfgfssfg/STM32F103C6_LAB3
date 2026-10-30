#include "global.h"

uint8_t status = 0;

uint32_t LED_RED = 5000, LED_AMB = 2000, LED_GRE = 3000;
uint32_t LED_MAN = 10000;

uint32_t getLED_RED(){
	return LED_RED;
}
uint32_t getLED_GREEN(){
	return LED_GRE;
}
uint32_t getLED_AMBER(){
	return LED_AMB;
}
uint32_t getLED_MAN(){
	return LED_MAN;
}
uint8_t getStatus(){
	return status;
}
void setLED_RED(uint32_t val){
	LED_RED = val;
}
void setLED_GREEN(uint32_t val){
	LED_GRE = val;
}
void setLED_AMBER(uint32_t val){
	LED_AMB = val;
}
void setLED_MAN(uint32_t val){
	LED_MAN = val;
}
void setStatus(uint8_t newStatus){
	status = newStatus;
}
