/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "dma.h"
#include "quadspi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "w25q128jv.h"
#include "callback.h"
#include "wrap.h"
#include "string.h"
#include "stdio.h"
#include "jedec.h"
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

/* USER CODE BEGIN PV */
volatile enum DATA_TRANSFER uart_transmission,qspi_transmission,qspi_reception,qspi_cmd_transmission;
volatile enum STATUS_MATCH qspi_status_match;
char output[200];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
	MX_DMA_Init();
	MX_QUADSPI_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	SW25Q128JV_Handle OW25Q128JV_Hdle;
	EW25Q128JVErrorCode error_w25q128jv_write_enable,error_w25q128jv_read_stat_reg,error_w25q128jv_write_stat_reg,error_w25q128jv_qspi_enable;
	EW25Q128JVErrorCode error_w25q128jv_fast_read_quad_io,error_w25q128jv_quad_input_page_program,error_w25q128jv_wait_until_busy_reset;
	EW25Q128JVErrorCode err_w25q128jv_erase,err_w25q128jv_read_unique_id,errw25q128jv_read_jedec_id;
	OW25Q128JV_Hdle.qspi_command_send	=	wrap_qspi_command_send;
	OW25Q128JV_Hdle.qspi_receive	=wrap_qspi_receive;
	OW25Q128JV_Hdle.qspi_transmit=wrap_qspi_transmit;
	OW25Q128JV_Hdle.qspi_auto_polling=wrap_qspi_auto_polling;
	uint8_t status_register_1;
	uint8_t status_register_2;
	uint8_t readbuff[256]={0},txbuf[260];
	sprintf(txbuf,"0123456789101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899100101102103104105106107108109110111112113114115116117118119120121");
	uint64_t uid=0;
	SJEDEC_ID jedec;



	err_w25q128jv_erase=w25q128jv_erase_4kb(&OW25Q128JV_Hdle,0);
		error_w25q128jv_fast_read_quad_io=w25q128jv_fast_read_quad_io(&OW25Q128JV_Hdle,0,readbuff,256);
		sprintf(output,"\r\n fast read quad io after erase \r\n");
			uart_transmission=START;
			if(HAL_UART_Transmit_IT(&huart1,output,strlen(output))	!=	HAL_OK)
			{
				Error_Handler();
			}
			else
			{
				while(uart_transmission!=END);
			}


				uart_transmission=START;
				if(HAL_UART_Transmit_IT(&huart1,readbuff,256)	!=	HAL_OK)
				{
					Error_Handler();
				}
				else
				{
					while(uart_transmission!=END);
				}
				error_w25q128jv_quad_input_page_program=w25q128jv_quad_input_page_program(&OW25Q128JV_Hdle,0,txbuf,256);

				error_w25q128jv_fast_read_quad_io=w25q128jv_fast_read_quad_io(&OW25Q128JV_Hdle,0,readbuff,256);
					sprintf(output,"\r\n fast read quad io after erase \r\n");
						uart_transmission=START;
						if(HAL_UART_Transmit_IT(&huart1,output,strlen(output))	!=	HAL_OK)
						{
							Error_Handler();
						}
						else
						{
							while(uart_transmission!=END);
						}


							uart_transmission=START;
							if(HAL_UART_Transmit_IT(&huart1,readbuff,256)	!=	HAL_OK)
							{
								Error_Handler();
							}
							else
							{
								while(uart_transmission!=END);
							}

	while (1)
	{

		HAL_Delay(1000);
		HAL_GPIO_TogglePin(USR_LED_GPIO_Port,USR_LED_Pin);
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

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 180;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Activate the Over-Drive mode
	 */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		Error_Handler();
	}
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
