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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "trig.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  uint16_t time_taken;
  uint8_t inVal;
  uint16_t outVal;
  double outVal_d;
  short outVal_s;
  char sign;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  SendString(" Enter 1 for sin and 2 for cos\n\r");
	  inVal = ReadChar();
	  sprintf(MSG, "Entered = %c\n\r", inVal);
	  SendString(MSG);

	  if(inVal == 49)
	  {
		  // x * 32767
		  SendString("Enter any to continue\n\r");
		  inVal = ReadChar();
		  outVal_s = custom_sin(0);
		  if(outVal_s >= 0)
		  {
			  sign = " ";
		  }
		  else
		  {
			  sign = "-";
		  }
		  outVal = (uint16_t)abs(outVal_s);
		  sprintf(MSG, "Custom Sin 0 = %d / 32768\n\r", outVal);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  SendString("Enter any to continue\n\r");
		  inVal = ReadChar();
		  outVal_s = custom_sin(-0.3 * 32768);
		  if(outVal_s >= 0)
		  {
			  sign = " ";
		  }
		  else
		  {
			  sign = "-";
		  }
		  outVal = (uint16_t)abs(outVal_s);
		  sprintf(MSG, "Custom Sin 0 = %c %d / 32768\n\r", sign, outVal);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  SendString("Enter any to continue\n\r");
		  inVal = ReadChar();
		  outVal_d = regular_sin(0);
		  outVal = (uint16_t)(outVal_d * 32768);
		  sprintf(MSG, "Regular Sin 0 = %d / 32768\n\r", outVal);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  SendString("Enter any to continue\n\r");
		  inVal = ReadChar();
		  outVal = (uint16_t)custom_sin(0.3 * 32768);
		  sprintf(MSG, "Custom Sin 0.3 pi = %d / 32768\n\r", outVal);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  SendString("Enter any to continue\n\r");
		  inVal = ReadChar();
		  outVal_d = regular_sin(0.3 * M_PI);
		  outVal = (uint16_t)(outVal_d * 32768);
		  sprintf(MSG, "Regular Sin 0.3 pi = %d / 32768\n\r", outVal);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  SendString("Enter any to continue\n\r");
		  inVal = ReadChar();
		  outVal = (uint16_t)custom_sin(0.5 * 32768);
		  sprintf(MSG, "Custom Sin 0.5 pi = %d / 32768\n\r", outVal);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  SendString("Enter any to continue\n\r");
		  inVal = ReadChar();
		  outVal_d = regular_sin(0.5 * M_PI);
		  outVal = (uint16_t)(outVal_d * 32768);
		  sprintf(MSG, "Regular Sin 0.5 pi = %d / 32768\n\r", outVal);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  SendString("Enter any to continue\n\r");
		  inVal = ReadChar();
		  outVal = (uint16_t)custom_sin(32768);
		  sprintf(MSG, "Custom Sin pi = %d / 32768\n\r", outVal);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));

		  SendString("Enter any to continue\n\r");
		  inVal = ReadChar();
		  outVal_d = regular_sin(M_PI);
		  outVal = (uint16_t)(outVal_d * 32768);
		  sprintf(MSG, "Regular Sin pi = %d / 32768\n\r", outVal);
		  HAL_UART_Transmit(&huart2, MSG, sizeof(MSG), 100);
		  memset(MSG, 0, sizeof(MSG));
	  }
	  else if(inVal == 50)
	  {

	  }
	  HAL_Delay(1000);
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
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin D7_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
