/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Terminal.h"
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
SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart1;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI2_Init(void);
void StartDefaultTask(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//-----Variables-----
MatrixKeyboard_st key = {0};
RC522_st          rc522Main = {0};
ST7789_st         display = {0};
MicroGFX_st       gfxDisplay = {0};
LED_st            buzzer = {0};

ModuleBuzzer_st    moduleBuzzer = {0};
ModuleKeyboard_st  moduleKeyboard = {0};
ModuleDisplay_st   moduleDisplay = {0};
ModuleRFID_st      moduleRFID = {0};

Terminal_st terminal = {0};
//-----Variables-----



//-----Function prototypes-----
//-----RC522-----
void SPI_Transmit_RC522(RC522_st* rc522, uint8_t* txBuf, size_t size);
void SPI_Receive_RC522(RC522_st* rc522, uint8_t* rxBuf, size_t size);
void SPI_ChipSelect_RC522(RC522_st* rc522, uint8_t level);
void CardEvent_Callback_RC522(RC522_st* rc522, RC522_CardEvent_et event);
//-----RC522-----

//-----ST7789-----
void SPI_Transmit_ST7789(ST7789_st* st7789, uint8_t* data, size_t size);
void SPI_ChipSelect_ST7789(ST7789_st* st7789, uint8_t level);
void SelectDataCommand_ST7789(ST7789_st* st7789, uint8_t level);
//-----ST7789-----

//-----MicroGFX-----
void MicroGFX_SetPixel_Display(MicroGFX_st* gfx, uint16_t x, uint16_t y, uint16_t color);
void MicroGFX_SetPixelArray_Display(MicroGFX_st* gfx, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t* color, uint8_t singleFlag);
//-----MicroGFX-----

//-----Keyboard-----
void MatrixKeyboardSetRowState3x4(MatrixKeyboard_st* keyboard, uint8_t row, uint8_t state);
uint8_t MatrixKeyboardGetColState3x4(MatrixKeyboard_st* keyboard, uint8_t col);
void MatrixKeyboardEventCallback3x4(MatrixKeyboard_st* keyboard, MatrixKeyboardEvent_et event, uint8_t button);
//-----Keyboard-----

//-----Buzzer-----
void SetState_Buzzer(LED_st* led, LedState_et state);
void IndicationIsOverCallbackBuzzer(LED_st* led, LedIndications_et indication, uint8_t repeatCounter);
//-----Buzzer-----
//-----Function prototypes-----



//-----Descriptors-----
//-----RC522-----
RC522_Descriptor_st RC522Descriptor = {
		.getTick = HAL_GetTick,
		.spiChipSelect = SPI_ChipSelect_RC522,
		.spiTransmit = SPI_Transmit_RC522,
		.spiReceive = SPI_Receive_RC522,
		.eventCallback = CardEvent_Callback_RC522,
};
//-----RC522-----

//-----ST7789-----
ST7789_Descriptor_st displayDescriptor = {
    .spiTransmit = SPI_Transmit_ST7789,
    .spiChipSelect = SPI_ChipSelect_ST7789,
    .selectDataCommand = SelectDataCommand_ST7789,
    .width = 240,
    .height = 280,
};
//-----ST7789-----

//-----MicroGFX-----
MicroGFX_Descriptor_st gfxDisplayDescriptor = {
		.setPixel = MicroGFX_SetPixel_Display,
		.setPixelArray = MicroGFX_SetPixelArray_Display,
		.height = 280,
		.width = 240
};
//-----MicroGFX-----

//-----Keyboard-----
static MatrixKeyboardDescriptor_st keyUserFunctions = {
		.getColState = MatrixKeyboardGetColState3x4,
		.setRowState = MatrixKeyboardSetRowState3x4,
		.eventCallback = MatrixKeyboardEventCallback3x4,
		.cols = 3,
		.rows = 4
};
//-----Keyboard-----

//-----Buzzer-----
LedUserFunctions_st buzzerUserFunctions = {
		.setState = SetState_Buzzer,
		.getTick = HAL_GetTick,
		.indicationIsOverCallback = IndicationIsOverCallbackBuzzer
};
//-----Buzzer-----
//-----Descriptors-----



//-----Function definitions-----
//-----RC522-----
void SPI_Transmit_RC522(RC522_st* rc522, uint8_t* txBuf, size_t size){
	HAL_SPI_Transmit(&hspi2, txBuf, size, 5000);
}
void SPI_Receive_RC522(RC522_st* rc522, uint8_t* rxBuf, size_t size){
	HAL_SPI_Receive(&hspi2, rxBuf, size, 5000);
}
void SPI_ChipSelect_RC522(RC522_st* rc522, uint8_t level){
	HAL_GPIO_WritePin(RC522_CS_GPIO_Port, RC522_CS_Pin, level);
}
//-----RC522-----

//-----ST7789-----
void SPI_Transmit_ST7789(ST7789_st* st7789, uint8_t* data, size_t size){
  HAL_SPI_Transmit(&hspi1, data, size, 5000);
}
void SPI_ChipSelect_ST7789(ST7789_st* st7789, uint8_t level){
  HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, level);
}
void SelectDataCommand_ST7789(ST7789_st* st7789, uint8_t level){
  HAL_GPIO_WritePin(ST7789_DC_GPIO_Port, ST7789_DC_Pin, level);
}
//-----ST7789-----

//-----MicroGFX-----
void MicroGFX_SetPixel_Display(MicroGFX_st* gfx, uint16_t x, uint16_t y, uint16_t color){
	if(gfx == &gfxDisplay){
		ST7789_SetPixel(&display, x, y, color);
	}
}

void MicroGFX_SetPixelArray_Display(MicroGFX_st* gfx, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t* color, uint8_t singleFlag){
	if(gfx == &gfxDisplay){
		ST7789_SetPixelArray(&display, x, y, w, h, color, singleFlag);
	}
}
//-----MicroGFX-----

//-----Keyboard-----
void MatrixKeyboardSetRowState3x4(MatrixKeyboard_st* keyboard, uint8_t row, uint8_t state){
	if(row == 0){
		HAL_GPIO_WritePin(KEYBOARD_ROW_1_GPIO_Port, KEYBOARD_ROW_1_Pin, state);
	}
	else if(row == 1){
		HAL_GPIO_WritePin(KEYBOARD_ROW_2_GPIO_Port, KEYBOARD_ROW_2_Pin, state);
	}
	else if(row == 2){
		HAL_GPIO_WritePin(KEYBOARD_ROW_3_GPIO_Port, KEYBOARD_ROW_3_Pin, state);
	}
	else if(row == 3){
		HAL_GPIO_WritePin(KEYBOARD_ROW_4_GPIO_Port, KEYBOARD_ROW_4_Pin, state);
	}
}

uint8_t MatrixKeyboardGetColState3x4(MatrixKeyboard_st* keyboard, uint8_t col){
	if(col == 0){
		return HAL_GPIO_ReadPin(KEYBOARD_COL_1_GPIO_Port, KEYBOARD_COL_1_Pin);
	}
	else if(col == 1){
		return HAL_GPIO_ReadPin(KEYBOARD_COL_2_GPIO_Port, KEYBOARD_COL_2_Pin);
	}
	else if(col == 2){
		return HAL_GPIO_ReadPin(KEYBOARD_COL_3_GPIO_Port, KEYBOARD_COL_3_Pin);
	}

	return 0;
}
//-----Keyboard-----

//-----Buzzer-----
void SetState_Buzzer(LED_st* led, LedState_et state){
	if(led == &buzzer){
		if(state == LED_STATE_ON) HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
		else                      HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
	}
}
//-----Buzzer-----
//-----Function definitions-----



//-----Callbacks-----
void MatrixKeyboardEventCallback3x4(MatrixKeyboard_st* keyboard, MatrixKeyboardEvent_et event, uint8_t button){
	if(event == MATRIX_KEYBOARD_EVENT_PRESS){
		ModuleKeyboard_Click(&moduleKeyboard, button);
	}
}

void CardEvent_Callback_RC522(RC522_st* rc522, RC522_CardEvent_et event){
	if(event == RC522_CARD_DETECTED){
		ModuleRFID_CardDetected(&moduleRFID);

		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	}
	else if(event == RC522_CARD_REMOVED){
		ModuleRFID_CardRemoved(&moduleRFID);

		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
	}
}

void IndicationIsOverCallbackBuzzer(LED_st* led, LedIndications_et indication, uint8_t repeatCounter){

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
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(RC522_RST_GPIO_Port, RC522_RST_Pin, 0);
  HAL_Delay(50);
  HAL_GPIO_WritePin(RC522_RST_GPIO_Port, RC522_RST_Pin, 1);
  HAL_Delay(50);

  HAL_GPIO_WritePin(ST7789_RES_GPIO_Port, ST7789_RES_Pin, GPIO_PIN_RESET);
  HAL_Delay(20);
  HAL_GPIO_WritePin(ST7789_RES_GPIO_Port, ST7789_RES_Pin, GPIO_PIN_SET);
  HAL_Delay(20);

  MatrixKeyboard_Init(&key, &keyUserFunctions);
  LED_Init(&buzzer, &buzzerUserFunctions);
  RC522_Init(&rc522Main, &RC522Descriptor);

  ST7789_Init(&display, &displayDescriptor);
  ST7789_SetOffsetY(&display, 20);
  ST7789_SetRotation(&display, ST7789_ROTATION_VERTICAL_180);
  ST7789_FillScreen(&display, BLACK_RGB565);

  MicroGFX_Init(&gfxDisplay, &gfxDisplayDescriptor);
  MicroGFX_FillScreen(&gfxDisplay, WHITE_RGB565);

  ModuleBuzzer_Init(&moduleBuzzer, &buzzer);
  ModuleKeyboard_Init(&moduleKeyboard, &key);
  ModuleRFID_Init(&moduleRFID, &rc522Main);
  ModuleDisplay_Init(&moduleDisplay, &display, &gfxDisplay);

  Terminal_Init(&terminal, &moduleBuzzer, &moduleDisplay, &moduleKeyboard, &moduleRFID);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ST7789_CS_Pin|ST7789_RES_Pin|ST7789_DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, BUZZER_Pin|LED_Pin|RC522_RST_Pin|RC522_CS_Pin
                          |KEYBOARD_ROW_1_Pin|KEYBOARD_ROW_2_Pin|KEYBOARD_ROW_3_Pin|KEYBOARD_ROW_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ST7789_CS_Pin ST7789_RES_Pin ST7789_DC_Pin */
  GPIO_InitStruct.Pin = ST7789_CS_Pin|ST7789_RES_Pin|ST7789_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BUZZER_Pin */
  GPIO_InitStruct.Pin = BUZZER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUZZER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Pin RC522_RST_Pin RC522_CS_Pin KEYBOARD_ROW_1_Pin
                           KEYBOARD_ROW_2_Pin KEYBOARD_ROW_3_Pin KEYBOARD_ROW_4_Pin */
  GPIO_InitStruct.Pin = LED_Pin|RC522_RST_Pin|RC522_CS_Pin|KEYBOARD_ROW_1_Pin
                          |KEYBOARD_ROW_2_Pin|KEYBOARD_ROW_3_Pin|KEYBOARD_ROW_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : KEYBOARD_COL_1_Pin KEYBOARD_COL_2_Pin KEYBOARD_COL_3_Pin */
  GPIO_InitStruct.Pin = KEYBOARD_COL_1_Pin|KEYBOARD_COL_2_Pin|KEYBOARD_COL_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	  Terminal_Run(&terminal);

    osDelay(1);
  }
  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
#ifdef USE_FULL_ASSERT
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
