#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "stm32f1xx_hal.h"
extern uint8_t status;

extern uint32_t LED_RED, LED_AMB, LED_GRE, LED_MAN;

extern TIM_HandleTypeDef htim2;

#define EN0_Pin GPIO_PIN_1
#define EN0_GPIO_Port GPIOA
#define EN1_Pin GPIO_PIN_2
#define EN1_GPIO_Port GPIOA
#define EN2_Pin GPIO_PIN_3
#define EN2_GPIO_Port GPIOA
#define EN3_Pin GPIO_PIN_4
#define EN3_GPIO_Port GPIOA
#define RED0_Pin GPIO_PIN_5
#define RED0_GPIO_Port GPIOA
#define AMB0_Pin GPIO_PIN_6
#define AMB0_GPIO_Port GPIOA
#define GRE0_Pin GPIO_PIN_7
#define GRE0_GPIO_Port GPIOA
#define SEG0_Pin GPIO_PIN_0
#define SEG0_GPIO_Port GPIOB
#define SEG1_Pin GPIO_PIN_1
#define SEG1_GPIO_Port GPIOB
#define SEG2_Pin GPIO_PIN_2
#define SEG2_GPIO_Port GPIOB
#define BTN_MODE_Pin GPIO_PIN_10
#define BTN_MODE_GPIO_Port GPIOB
#define BTN_INC_Pin GPIO_PIN_11
#define BTN_INC_GPIO_Port GPIOB
#define BTN_DIG_Pin GPIO_PIN_12
#define BTN_DIG_GPIO_Port GPIOB
#define BTN_SET_Pin GPIO_PIN_13
#define BTN_SET_GPIO_Port GPIOB
#define BTN_MAN_Pin GPIO_PIN_14
#define BTN_MAN_GPIO_Port GPIOB
#define RED1_Pin GPIO_PIN_8
#define RED1_GPIO_Port GPIOA
#define AMB1_Pin GPIO_PIN_9
#define AMB1_GPIO_Port GPIOA
#define GRE1_Pin GPIO_PIN_10
#define GRE1_GPIO_Port GPIOA
#define SEG3_Pin GPIO_PIN_3
#define SEG3_GPIO_Port GPIOB
#define SEG4_Pin GPIO_PIN_4
#define SEG4_GPIO_Port GPIOB
#define SEG5_Pin GPIO_PIN_5
#define SEG5_GPIO_Port GPIOB
#define SEG6_Pin GPIO_PIN_6
#define SEG6_GPIO_Port GPIOB

uint32_t getLED_RED();
uint32_t getLED_GREEN();
uint32_t getLED_AMBER();
uint32_t getLED_MAN();
uint8_t getStatus();
void setLED_RED(uint32_t val);
void setLED_GREEN(uint32_t val);
void setLED_AMBER(uint32_t val);
void setLED_MAN(uint32_t val);
void setStatus(uint8_t newStatus);

#endif /* INC_GLOBAL_H_ */
