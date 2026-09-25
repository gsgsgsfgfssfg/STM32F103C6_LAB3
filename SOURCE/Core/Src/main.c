/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "button.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{
	STATE_RED,
	STATE_AMBER,
	STATE_GREEN
}TrafficLight_Typedef;

typedef enum{
	STATE_1,
	STATE_10
}Digit_Typedef;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
TrafficLight_Typedef Led0_state = STATE_RED, Led1_state = STATE_GREEN;
int LED_RED = 5000, LED_AMB = 2000, LED_GRE = 3000;
int led0,led1;
int ledbuffer[4];
int nochange0 = 0, nochange1 = 0;

const int MAX_LED = 4;
int index_led = 0;

const int MAX_MODE = 4;
int mode = 0;

Digit_Typedef Digit_state = STATE_1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void updateTrafficLight();
void checkLedTrafficState();
void update7SEGbuffer();
void scan7SEG();
void checkBtnMode();
void checkBtnInc();
void checkBtnDig();
void checkBtnSet();
void display7SEG(int num);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  //TIME_CYCLES = htim2.Init.Period+1;
  setTimer0(LED_RED);
  led0=LED_RED/1000;
  ledbuffer[0]=led0/10;
  ledbuffer[1]=led0%10;
  setTimer1(LED_GRE);
  led1=LED_GRE/1000;
  ledbuffer[2]=led1/10;
  ledbuffer[3]=led1%10;
  setTimer2(1000);
  setTimer3(250);
  setTimer4(1000);
  setTimer5(10);
  TIME_CYCLES = ( (htim2.Init.Prescaler+1)*(htim2.Init.Period + 1)* 1000)/8000000;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (mode == 0) checkLedTrafficState();
	  updateTrafficLight();
	  update7SEGbuffer();
	  scan7SEG();
	  getKeyInput();
	  checkBtnMode();
	  checkBtnInc();
	  checkBtnDig();
	  checkBtnSet();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |RED0_Pin|AMB0_Pin|GRE0_Pin|RED1_Pin
                          |AMB1_Pin|GRE1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           RED0_Pin AMB0_Pin GRE0_Pin RED1_Pin
                           AMB1_Pin GRE1_Pin */
  GPIO_InitStruct.Pin = EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |RED0_Pin|AMB0_Pin|GRE0_Pin|RED1_Pin
                          |AMB1_Pin|GRE1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin SEG3_Pin
                           SEG4_Pin SEG5_Pin SEG6_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_MODE_Pin BTN_INC_Pin BTN_DIG_Pin BTN_SET_Pin */
  GPIO_InitStruct.Pin = BTN_MODE_Pin|BTN_INC_Pin|BTN_DIG_Pin|BTN_SET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timer_run();
}

void checkLedTrafficState(){
	if (timer0_flag == 1){
		switch(Led0_state){
		case STATE_RED:
			Led0_state = STATE_GREEN;
			setTimer0(LED_GRE);
			led0 = LED_GRE/1000;
			setTimer2(1000);
			break;
		case STATE_AMBER:
			Led0_state = STATE_RED;
			setTimer0(LED_RED);
			led0 = LED_RED/1000;
			setTimer2(1000);
			break;
		case STATE_GREEN:
			Led0_state = STATE_AMBER;
			setTimer0(LED_AMB);
			led0 = LED_AMB/1000;
			setTimer2(1000);
			break;
		default: Led0_state = STATE_RED;
		}
	}
	if (timer1_flag == 1){
		switch(Led1_state){
		case STATE_RED:
			Led1_state = STATE_GREEN;
			setTimer1(LED_GRE);
			led1 = LED_GRE/1000;
			setTimer4(1000);
			break;
		case STATE_AMBER:
			Led1_state = STATE_RED;
			setTimer1(LED_RED);
			led1 = LED_RED/1000;
			setTimer4(1000);
			break;
		case STATE_GREEN:
			Led1_state = STATE_AMBER;
			setTimer1(LED_AMB);
			led1 = LED_AMB/1000;
			setTimer4(1000);
			break;
		default: Led1_state = STATE_RED;
		}
	}
}

void updateTrafficLight(){
	if (mode == 0){
		switch(Led0_state){
			case STATE_RED:
				HAL_GPIO_WritePin(RED0_GPIO_Port,RED0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GRE0_GPIO_Port,AMB0_Pin|GRE0_Pin,GPIO_PIN_SET);
				break;
			case STATE_AMBER:
				HAL_GPIO_WritePin(AMB0_GPIO_Port,AMB0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(RED0_GPIO_Port,RED0_Pin|GRE0_Pin,GPIO_PIN_SET);
				break;
			case STATE_GREEN:
				HAL_GPIO_WritePin(GRE0_GPIO_Port,GRE0_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(AMB0_GPIO_Port,RED0_Pin|AMB0_Pin,GPIO_PIN_SET);
				break;
			default: Led0_state = STATE_RED;
		}

		switch(Led1_state){
			case STATE_RED:
				HAL_GPIO_WritePin(RED1_GPIO_Port,RED1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GRE1_GPIO_Port,AMB1_Pin|GRE1_Pin,GPIO_PIN_SET);
				break;
			case STATE_AMBER:
				HAL_GPIO_WritePin(AMB1_GPIO_Port,AMB1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(RED1_GPIO_Port,RED1_Pin|GRE1_Pin,GPIO_PIN_SET);
				break;
			case STATE_GREEN:
				HAL_GPIO_WritePin(GRE1_GPIO_Port,GRE1_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(AMB1_GPIO_Port,RED1_Pin|AMB1_Pin,GPIO_PIN_SET);
				break;
			default: Led1_state = STATE_RED;
		  }
	}
	if (mode == 1){
		HAL_GPIO_WritePin(GPIOA,RED0_Pin|RED1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,AMB0_Pin|AMB1_Pin|GRE0_Pin|GRE1_Pin,GPIO_PIN_SET);
	}
	if (mode == 2){
		HAL_GPIO_WritePin(GPIOA,AMB0_Pin|AMB1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,RED0_Pin|RED1_Pin|GRE0_Pin|GRE1_Pin,GPIO_PIN_SET);
	}
	if (mode == 3){
		HAL_GPIO_WritePin(GPIOA,GRE0_Pin|GRE1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA,AMB0_Pin|AMB1_Pin|RED0_Pin|RED1_Pin,GPIO_PIN_SET);
	}
}

void update7SEGbuffer(){
	if (mode == 0){
		ledbuffer[0]=led0/10;
		ledbuffer[1]=led0%10;
		ledbuffer[2]=led1/10;
		ledbuffer[3]=led1%10;
		if (timer2_flag == 1) {
			led0--;
			setTimer2(1000);
		}
		if (timer4_flag == 1) {
			led1--;
			setTimer4(1000);
		}
	}
	if (mode == 1){
		ledbuffer[0] = 0;
		ledbuffer[1] = 1;
	}
	if (mode == 2){
			ledbuffer[0] = 0;
			ledbuffer[1] = 2;
		}
	if (mode == 3){
			ledbuffer[0] = 0;
			ledbuffer[1] = 3;
		}
}

void scan7SEG(){
	if (timer3_flag == 1){
		index_led = (index_led+1)%MAX_LED;
		setTimer3(250);
	}
	switch (index_led){
		case 0:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN0_Pin|EN3_Pin, GPIO_PIN_SET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN2_Pin|EN0_Pin, GPIO_PIN_SET);
			break;
	}
	display7SEG(ledbuffer[index_led]);
}

void display7SEG(int num){
	switch(num){
		case 0:
			HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,SEG6_Pin,GPIO_PIN_SET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOB,SEG1_Pin|SEG2_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG3_Pin
                    |SEG4_Pin|SEG5_Pin|SEG6_Pin,GPIO_PIN_SET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG1_Pin|SEG3_Pin
                          |SEG4_Pin|SEG6_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,SEG2_Pin|SEG5_Pin,GPIO_PIN_SET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG6_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,SEG4_Pin|SEG5_Pin,GPIO_PIN_SET);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOB,SEG1_Pin|SEG2_Pin
                          |SEG5_Pin|SEG6_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG3_Pin|SEG4_Pin,GPIO_PIN_SET);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG2_Pin|SEG3_Pin
                          |SEG5_Pin|SEG6_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,SEG1_Pin|SEG4_Pin,GPIO_PIN_SET);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,SEG1_Pin,GPIO_PIN_SET);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG1_Pin|SEG2_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin,GPIO_PIN_SET);
			break;
		case 8:
			HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin,GPIO_PIN_RESET);
			break;
		case 9:
			HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG5_Pin|SEG6_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,SEG4_Pin,GPIO_PIN_SET);
			break;
		default:
			HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
					|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_SET);
			break;
	}
}

void checkBtnMode(){
	if (btn_mode_flag == 1) {
		Digit_state = STATE_1;
		mode = (mode+1)%4;
		if (mode == 0){
			setTimer0(LED_RED);
			led0=LED_RED/1000;
			ledbuffer[0]=led0/10;
			ledbuffer[1]=led0%10;
			setTimer1(LED_GRE);
			led1=LED_GRE/1000;
			ledbuffer[2]=led1/10;
			ledbuffer[3]=led1%10;
			setTimer2(1000);
			setTimer4(1000);
			Led0_state = STATE_RED;
			Led1_state = STATE_GREEN;
		}
		if (mode == 1){
			ledbuffer[2] = LED_RED/10000;
			ledbuffer[3] = (LED_RED/1000)%10;
		}
		if (mode == 2){
			ledbuffer[2] = LED_AMB/10000;
			ledbuffer[3] = (LED_AMB/1000)%10;
		}
		if (mode == 3){
			ledbuffer[2] = LED_GRE/10000;
			ledbuffer[3] = (LED_GRE/1000)%10;
		}
		btn_mode_flag = 0;
	}
}

void checkBtnInc(){
	if (btn_inc_flag == 1){
		if (mode != 0){
			if (Digit_state == STATE_1) ledbuffer[3] = (ledbuffer[3]+1)%10;
			if (Digit_state == STATE_10) ledbuffer[2] = (ledbuffer[2]+1)%10;
			if (mode == 1){
				if (ledbuffer[2]*10 + ledbuffer[3] < 2){
					ledbuffer[3]=2;
				}
			}
			if (mode == 2 || mode == 3){
				if (ledbuffer[2]*10 + ledbuffer[3] < 1){
					ledbuffer[3]=1;
				}
			}
		}
		btn_inc_flag = 0;
	}
}

void checkBtnDig(){
	if (btn_dig_flag == 1){
		switch(Digit_state){
			case STATE_1:
				Digit_state = STATE_10;
				break;
			case STATE_10:
				Digit_state = STATE_1;
				break;
		}
		btn_dig_flag = 0;
	}
}

void checkBtnSet(){
	if (btn_set_flag == 1){
		if (mode == 1){
			LED_RED = (ledbuffer[2]*10 + ledbuffer[3])*1000;
			if (LED_AMB >= LED_RED){
				LED_AMB = LED_RED - 1000;
				LED_GRE = 1000;
			}
			if (LED_GRE >= LED_RED){
				LED_GRE = LED_RED - 1000;
				LED_AMB = 1000;
			}
			if (LED_GRE + LED_AMB != LED_RED) LED_GRE = LED_RED - LED_AMB;
		}
		if (mode == 2){
			LED_AMB = (ledbuffer[2]*10 + ledbuffer[3])*1000;
			if (LED_AMB >= LED_RED){
				LED_AMB = LED_RED - 1000;
				LED_GRE = 1000;
			}
			if (LED_GRE + LED_AMB != LED_RED) LED_GRE = LED_RED - LED_AMB;
			ledbuffer[2] = (LED_AMB/1000)/10;
			ledbuffer[3] = (LED_AMB/1000)%10;
		}
		if (mode == 3) {
			LED_GRE = (ledbuffer[2]*10 + ledbuffer[3])*1000;
			if (LED_GRE >= LED_RED){
				LED_GRE = LED_RED - 1000;
				LED_AMB = 1000;
			}
			if (LED_GRE + LED_AMB != LED_RED) LED_AMB = LED_RED - LED_GRE;
			ledbuffer[2] = (LED_GRE/1000)/10;
			ledbuffer[3] = (LED_GRE/1000)%10;
		}
		btn_set_flag = 0;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
