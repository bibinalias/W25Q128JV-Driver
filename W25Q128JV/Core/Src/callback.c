/*
 * callback.c
 *
 *  Created on: 05-Nov-2020
 *      Author: Bibin
 */
#include "main.h"
#include "callback.h"

extern volatile enum DATA_TRANSFER uart_transmission,qspi_transmission,qspi_reception,qspi_cmd_transmission;
extern volatile enum STATUS_MATCH qspi_status_match;
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

	uart_transmission	=	END;

}

void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	qspi_reception	=	END;



}
void HAL_QSPI_ErrorCallback(QSPI_HandleTypeDef *hqspi)
{
	while(1)
	{
		HAL_Delay(300);
		HAL_GPIO_TogglePin(USR_LED_GPIO_Port,USR_LED_Pin);
	}

}
void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	qspi_transmission	=	END;

}
void HAL_QSPI_CmdCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	qspi_cmd_transmission	=	END;


}



void HAL_QSPI_StatusMatchCallback(QSPI_HandleTypeDef *hqspi)
{
  qspi_status_match =MATCH;
}
