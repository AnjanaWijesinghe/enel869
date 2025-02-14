/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "timer_impl.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t ReadChar(void)
{
	uint8_t val;
	while(!(USART2->SR & (1<<5)));
	val = USART2->DR;
	return val;
}

void SendChar(uint8_t c)
{
	USART2->DR = c;
	while(!(USART2->SR & (1<<6)));
}

void SendString(char* string)
{
	while(*string) SendChar(*string++);
}

uint16_t TimeTakenInNs(uint16_t t)
{
	return (uint16_t)((t *1000) / 72);
}
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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  uint8_t MSG[40] = {'\0'};
  uint8_t inVal;

//  char temp_str[10];
//  uint16_t CounterTicks = 0;
//  uint16_t CounterTicks2 = 0;

//  volatile uint32_t testValue1 = 0;
//  volatile uint32_t testValue2 = 0;
//  volatile uint32_t testValue3 = 0;

//  volatile uint8_t testValue1 = 0;
//  volatile uint8_t testValue2 = 0;
//  volatile uint8_t testValue3 = 0;

  uint16_t time_taken;
  double elapsedtime;

//  RCC->APB1ENR |= 0x0002; //RCC_APB1ENR_TIM3EN;
//  TIM3->CR1 = 0x0001;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  CounterTicks = TIM3->CNT;
//	  CounterTicks2 = TIM3->CNT;
//	  CounterTicks3 = CounterTicks2 - CounterTicks;

	  SendString("Enter 1 to get timings for different calculations\n\r");
	  SendString("Enter 2 to read RCC registers\n\r");

	  inVal = ReadChar();
	  sprintf(MSG, "Entered = %c\n\r", inVal);
	  SendString(MSG);

	  if(inVal == 49)
	  {
		  SendString("Generating timings for different calculations\n\r");
		  time_taken = time_to_add_32();
		  time_taken = TimeTakenInNs(time_taken);
		  sprintf(MSG, "32 add time = %d\n\r", time_taken);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  time_taken = time_to_add_64();
		  time_taken = TimeTakenInNs(time_taken);
		  sprintf(MSG, "64 add time = %d\n\r", time_taken);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  time_taken = time_to_mul_32();
		  time_taken = TimeTakenInNs(time_taken);
		  sprintf(MSG, "32 mul time = %d\n\r", time_taken);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  time_taken = time_to_mul_64();
		  time_taken = TimeTakenInNs(time_taken);
		  sprintf(MSG, "64 mul time = %d\n\r", time_taken);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  time_taken = time_to_div_32();
		  time_taken = TimeTakenInNs(time_taken);
		  sprintf(MSG, "32 div time = %d\n\r", time_taken);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  time_taken = time_to_div_64();
		  time_taken = TimeTakenInNs(time_taken);
		  sprintf(MSG, "64 div time = %d\n\r", time_taken);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  time_taken = time_to_copy_8B();
		  time_taken = TimeTakenInNs(time_taken);
		  sprintf(MSG, "8B cp time = %d\n\r", time_taken);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  time_taken = time_to_copy_128B();
		  time_taken = TimeTakenInNs(time_taken);
		  sprintf(MSG, "128B cp time = %d\n\r", time_taken);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  time_taken = time_to_copy_1024B();
		  time_taken = TimeTakenInNs(time_taken);
		  sprintf(MSG, "1024B cp time = %d\n\r", time_taken);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));
	  }
	  else if (inVal == 50)
	  {
		  SendString("Reading RCC registers\n\r");
		  uint32_t reg_val;

		  reg_val = RCC->CR;
		  SendString("Clock control register which is used to set the clock flags\n\r");
		  sprintf(MSG, "RCC->CR: %X\n\r", reg_val);
		  SendString(MSG);

		  reg_val = RCC->CFGR;
		  SendString("Clock configuration register which is used to set prescalers to adjust clock speeds\n\r");
		  sprintf(MSG, "RCC->CFGR: %X\n\r", reg_val);
		  SendString(MSG);

		  reg_val = RCC->CIR;
		  SendString("Clock interrupt register which is used what types of clock interrupts are enabled\n\r");
		  sprintf(MSG, "RCC->CIR: %X\n\r", reg_val);
		  SendString(MSG);

		  reg_val = RCC->APB2RSTR;
		  SendString("APB2 peripheral reset register which is used to set and reset clock timers\n\r");
		  sprintf(MSG, "RCC->APB2RSTR: %X\n\r", reg_val);
		  SendString(MSG);

		  reg_val = RCC->APB1RSTR;
		  SendString("APB1 peripheral reset register which is used to reset communication connections and windowed watchdog and other timers\n\r");
		  sprintf(MSG, "RCC->APB1RSTR: %X\n\r", reg_val);
		  SendString(MSG);

		  reg_val = RCC->AHBENR;
		  SendString("APB pheripheral clock enable register which  is used to enable pheripheral clocks\n\r");
		  sprintf(MSG, "RCC->AHBENR: %X\n\r", reg_val);
		  SendString(MSG);

		  reg_val = RCC->APB2ENR;
		  SendString("APB2 pheripheral clock enable register which is used to enable pheripheral clocks including IO\n\r");
		  sprintf(MSG, "RCC->APB2ENR %X\n\r", reg_val);
		  SendString(MSG);

		  reg_val = RCC->APB1ENR;
		  SendString("APB1 pheripheral clock enable register which is used to enable clocks to communication pheripherals\n\r");
		  sprintf(MSG, "RCC->APB1ENR %X\n\r", reg_val);
		  SendString(MSG);

		  reg_val = RCC->BDCR;
		  SendString("Backup domain control register, used to enable main RTC and select clock source\n\r");
		  sprintf(MSG, "RCC->BDCR %X\n\r", reg_val);
		  SendString(MSG);

		  reg_val = RCC->CSR;
		  SendString("Control status register, used to control reset requirements\n\r");
		  sprintf(MSG, "RCC->CSR %X\n\r", reg_val);
		  SendString(MSG);
	  }

	  SendString("Completed!\n\r");
	  SendString("\n\r");
//	  HAL_Delay(500);
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
