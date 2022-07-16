/*
 * wrap.c
 *
 *  Created on: 17-Nov-2020
 *      Author: Bibin
 */


#include "wrap.h"
#include "quadspi.h"
#include "callback.h"


extern volatile enum DATA_TRANSFER qspi_transmission,qspi_reception,qspi_cmd_transmission;
extern volatile enum STATUS_MATCH qspi_status_match;

EErrorCode wrap_qspi_command_send(TS_QSPI_CommandTypeDef *sCommand,uint32_t timeout)
{
	EErrorCode err_code = ERR_NO_ERROR;
	QSPI_CommandTypeDef scommand;


	scommand.Address=sCommand->Address;
	scommand.Instruction=sCommand->Instruction;
	scommand.AlternateBytes=sCommand->AlternateBytes;
	scommand.DummyCycles=sCommand->DummyCycles;
	scommand.NbData=sCommand->NbData;


	switch(sCommand->AddressSize)
	{
	case TS_QSPI_ADDRESS_8_BITS:scommand.AddressSize=QSPI_ADDRESS_8_BITS;
	break;
	case TS_QSPI_ADDRESS_16_BITS:scommand.AddressSize=QSPI_ADDRESS_16_BITS;
	break;
	case TS_QSPI_ADDRESS_24_BITS:scommand.AddressSize=QSPI_ADDRESS_24_BITS;
	break;
	case TS_QSPI_ADDRESS_32_BITS:scommand.AddressSize=QSPI_ADDRESS_32_BITS;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}
	switch(sCommand->AddressMode)
	{
	case TS_QSPI_ADDRESS_NONE:scommand.AddressMode=QSPI_ADDRESS_NONE;
	break;
	case TS_QSPI_ADDRESS_1_LINE:scommand.AddressMode=QSPI_ADDRESS_1_LINE;
	break;
	case TS_QSPI_ADDRESS_2_LINES:scommand.AddressMode=QSPI_ADDRESS_2_LINES;
	break;
	case TS_QSPI_ADDRESS_4_LINES:scommand.AddressMode=QSPI_ADDRESS_4_LINES;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}
	switch(sCommand->AlternateByteMode)
	{
	case TS_QSPI_ALTERNATE_BYTES_NONE:scommand.AlternateByteMode=QSPI_ALTERNATE_BYTES_NONE;
	break;
	case TS_QSPI_ALTERNATE_BYTES_1_LINE:scommand.AlternateByteMode=QSPI_ALTERNATE_BYTES_1_LINE;
	break;
	case TS_QSPI_ALTERNATE_BYTES_2_LINES:scommand.AlternateByteMode=QSPI_ALTERNATE_BYTES_2_LINES;
	break;
	case TS_QSPI_ALTERNATE_BYTES_4_LINES:scommand.AlternateByteMode=QSPI_ALTERNATE_BYTES_4_LINES;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}
	switch(sCommand->AlternateBytesSize)
	{
	case TS_QSPI_ALTERNATE_BYTES_8_BITS:scommand.AlternateBytesSize=QSPI_ALTERNATE_BYTES_8_BITS;
	break;
	case TS_QSPI_ALTERNATE_BYTES_16_BITS:scommand.AlternateBytesSize=QSPI_ALTERNATE_BYTES_16_BITS;
	break;
	case TS_QSPI_ALTERNATE_BYTES_24_BITS:scommand.AlternateBytesSize=QSPI_ALTERNATE_BYTES_24_BITS;
	break;
	case TS_QSPI_ALTERNATE_BYTES_32_BITS:scommand.AlternateBytesSize=QSPI_ALTERNATE_BYTES_32_BITS;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}

	switch(sCommand->DataMode)
	{
	case TS_QSPI_DATA_NONE:scommand.DataMode=QSPI_DATA_NONE;
	break;
	case TS_QSPI_DATA_1_LINE:scommand.DataMode=QSPI_DATA_1_LINE;
	break;
	case TS_QSPI_DATA_2_LINES:scommand.DataMode=QSPI_DATA_2_LINES;
	break;
	case TS_QSPI_DATA_4_LINES:scommand.DataMode=QSPI_DATA_4_LINES;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}
	switch(sCommand->InstructionMode)
	{
	case  TS_QSPI_INSTRUCTION_NONE:scommand.InstructionMode=QSPI_INSTRUCTION_NONE;
	break;
	case TS_QSPI_INSTRUCTION_1_LINE:scommand.InstructionMode=QSPI_INSTRUCTION_1_LINE;
	break;
	case TS_QSPI_INSTRUCTION_2_LINES:scommand.InstructionMode=QSPI_INSTRUCTION_2_LINES;
	break;
	case TS_QSPI_INSTRUCTION_4_LINES:scommand.InstructionMode=QSPI_INSTRUCTION_4_LINES;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}

	switch(sCommand->DdrMode)
	{
	case TS_QSPI_DDR_MODE_DISABLE:scommand.DdrMode=QSPI_DDR_MODE_DISABLE;
	break;
	case TS_QSPI_DDR_MODE_ENABLE:scommand.DdrMode=QSPI_DDR_MODE_ENABLE;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}

	switch (sCommand->DdrHoldHalfCycle)
	{
	case TS_QSPI_DDR_HHC_ANALOG_DELAY:scommand.DdrHoldHalfCycle=QSPI_DDR_HHC_ANALOG_DELAY;
	break;
	case TS_QSPI_DDR_HHC_HALF_CLK_DELAY:scommand.DdrHoldHalfCycle=QSPI_DDR_HHC_HALF_CLK_DELAY;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}
	switch(sCommand->SIOOMode)
	{
	case TS_QSPI_SIOO_INST_EVERY_CMD:scommand.SIOOMode=QSPI_SIOO_INST_EVERY_CMD;
	break;
	case TS_QSPI_SIOO_INST_ONLY_FIRST_CMD:scommand.SIOOMode=QSPI_SIOO_INST_ONLY_FIRST_CMD;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}






	qspi_cmd_transmission	=	START;
	if (HAL_QSPI_Command_IT(&hqspi,&scommand)!=	HAL_OK)
	{
		return ERR_PCOM_QSPI_IT_CMD_FAIL;
	}
	else
	{
		if(sCommand->NbData==0)
		{
			while(qspi_cmd_transmission != END);
		}
		err_code = ERR_NO_ERROR;
	}
	return err_code;

}

EErrorCode wrap_qspi_receive(uint8_t *pRdBuffer,uint32_t timeout)
{
	EErrorCode err_code = ERR_NO_ERROR;

	qspi_reception	=	START;
	if(HAL_QSPI_Receive_DMA(&hqspi,pRdBuffer)!=HAL_OK)
	{
		return ERR_PCOM_QSPI_DMA_RX_FAIL;
	}
	else
	{
		while(qspi_reception	!=	END);
		err_code = ERR_NO_ERROR;
	}

	return err_code;



}


EErrorCode wrap_qspi_transmit(uint8_t *pTdBuffer,uint32_t timeout)
{

	EErrorCode err_code = ERR_NO_ERROR;


	qspi_transmission	=	START;
	if(HAL_QSPI_Transmit_DMA(&hqspi,pTdBuffer)!=HAL_OK)
	{
		return ERR_PCOM_QSPI_DMA_TX_FAIL;
	}
	else
	{
		while(qspi_transmission	!=	END);
		 err_code = ERR_NO_ERROR;
	}
	return err_code;
}

EErrorCode wrap_qspi_auto_polling(TS_QSPI_CommandTypeDef *sCommand,TS_QSPI_AutoPollingTypeDef *sAutopol,uint32_t timeout)
{

	EErrorCode err_code = ERR_NO_ERROR;
	QSPI_CommandTypeDef scommand;
	QSPI_AutoPollingTypeDef sautopol;

	sautopol.Interval	=sAutopol->Interval;
	sautopol.Mask	=sAutopol->Mask;
	sautopol.Match	=sAutopol->Match;
	sautopol.StatusBytesSize	=sAutopol->StatusBytesSize;


	switch(sAutopol->AutomaticStop)
	{
	case TS_QSPI_AUTOMATIC_STOP_DISABLE:sautopol.AutomaticStop=QSPI_AUTOMATIC_STOP_DISABLE;
	break;
	case TS_QSPI_AUTOMATIC_STOP_ENABLE:sautopol.AutomaticStop=QSPI_AUTOMATIC_STOP_ENABLE;
	break;

	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}

	switch(sAutopol->MatchMode)
	{
	case TS_QSPI_MATCH_MODE_AND:sautopol.MatchMode=QSPI_MATCH_MODE_AND;
	break;
	case TS_QSPI_MATCH_MODE_OR:sautopol.MatchMode=QSPI_MATCH_MODE_OR;
	break;

	default:return ERR_PCOM_QSPI_STRUCT_FAIL;

	}

	scommand.Address=sCommand->Address;
	scommand.Instruction=sCommand->Instruction;
	scommand.AlternateBytes=sCommand->AlternateBytes;
	scommand.DummyCycles=sCommand->DummyCycles;
	scommand.NbData=sCommand->NbData;


	switch(sCommand->AddressSize)
	{
	case TS_QSPI_ADDRESS_8_BITS:scommand.AddressSize=QSPI_ADDRESS_8_BITS;
	break;
	case TS_QSPI_ADDRESS_16_BITS:scommand.AddressSize=QSPI_ADDRESS_16_BITS;
	break;
	case TS_QSPI_ADDRESS_24_BITS:scommand.AddressSize=QSPI_ADDRESS_24_BITS;
	break;
	case TS_QSPI_ADDRESS_32_BITS:scommand.AddressSize=QSPI_ADDRESS_32_BITS;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}
	switch(sCommand->AddressMode)
	{
	case TS_QSPI_ADDRESS_NONE:scommand.AddressMode=QSPI_ADDRESS_NONE;
	break;
	case TS_QSPI_ADDRESS_1_LINE:scommand.AddressMode=QSPI_ADDRESS_1_LINE;
	break;
	case TS_QSPI_ADDRESS_2_LINES:scommand.AddressMode=QSPI_ADDRESS_2_LINES;
	break;
	case TS_QSPI_ADDRESS_4_LINES:scommand.AddressMode=QSPI_ADDRESS_4_LINES;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}
	switch(sCommand->AlternateByteMode)
	{
	case TS_QSPI_ALTERNATE_BYTES_NONE:scommand.AlternateByteMode=QSPI_ALTERNATE_BYTES_NONE;
	break;
	case TS_QSPI_ALTERNATE_BYTES_1_LINE:scommand.AlternateByteMode=QSPI_ALTERNATE_BYTES_1_LINE;
	break;
	case TS_QSPI_ALTERNATE_BYTES_2_LINES:scommand.AlternateByteMode=QSPI_ALTERNATE_BYTES_2_LINES;
	break;
	case TS_QSPI_ALTERNATE_BYTES_4_LINES:scommand.AlternateByteMode=QSPI_ALTERNATE_BYTES_4_LINES;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}
	switch(sCommand->AlternateBytesSize)
	{
	case TS_QSPI_ALTERNATE_BYTES_8_BITS:scommand.AlternateBytesSize=QSPI_ALTERNATE_BYTES_8_BITS;
	break;
	case TS_QSPI_ALTERNATE_BYTES_16_BITS:scommand.AlternateBytesSize=QSPI_ALTERNATE_BYTES_16_BITS;
	break;
	case TS_QSPI_ALTERNATE_BYTES_24_BITS:scommand.AlternateBytesSize=QSPI_ALTERNATE_BYTES_24_BITS;
	break;
	case TS_QSPI_ALTERNATE_BYTES_32_BITS:scommand.AlternateBytesSize=QSPI_ALTERNATE_BYTES_32_BITS;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}

	switch(sCommand->DataMode)
	{
	case TS_QSPI_DATA_NONE:scommand.DataMode=QSPI_DATA_NONE;
	break;
	case TS_QSPI_DATA_1_LINE:scommand.DataMode=QSPI_DATA_1_LINE;
	break;
	case TS_QSPI_DATA_2_LINES:scommand.DataMode=QSPI_DATA_2_LINES;
	break;
	case TS_QSPI_DATA_4_LINES:scommand.DataMode=QSPI_DATA_4_LINES;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}
	switch(sCommand->InstructionMode)
	{
	case  TS_QSPI_INSTRUCTION_NONE:scommand.InstructionMode=QSPI_INSTRUCTION_NONE;
	break;
	case TS_QSPI_INSTRUCTION_1_LINE:scommand.InstructionMode=QSPI_INSTRUCTION_1_LINE;
	break;
	case TS_QSPI_INSTRUCTION_2_LINES:scommand.InstructionMode=QSPI_INSTRUCTION_2_LINES;
	break;
	case TS_QSPI_INSTRUCTION_4_LINES:scommand.InstructionMode=QSPI_INSTRUCTION_4_LINES;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}

	switch(sCommand->DdrMode)
	{
	case TS_QSPI_DDR_MODE_DISABLE:scommand.DdrMode=QSPI_DDR_MODE_DISABLE;
	break;
	case TS_QSPI_DDR_MODE_ENABLE:scommand.DdrMode=QSPI_DDR_MODE_ENABLE;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}

	switch (sCommand->DdrHoldHalfCycle)
	{
	case TS_QSPI_DDR_HHC_ANALOG_DELAY:scommand.DdrHoldHalfCycle=QSPI_DDR_HHC_ANALOG_DELAY;
	break;
	case TS_QSPI_DDR_HHC_HALF_CLK_DELAY:scommand.DdrHoldHalfCycle=QSPI_DDR_HHC_HALF_CLK_DELAY;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}
	switch(sCommand->SIOOMode)
	{
	case TS_QSPI_SIOO_INST_EVERY_CMD:scommand.SIOOMode=QSPI_SIOO_INST_EVERY_CMD;
	break;
	case TS_QSPI_SIOO_INST_ONLY_FIRST_CMD:scommand.SIOOMode=QSPI_SIOO_INST_ONLY_FIRST_CMD;
	break;
	default:return ERR_PCOM_QSPI_STRUCT_FAIL;
	}


	qspi_status_match =NOT_MATCH;
	if(HAL_QSPI_AutoPolling_IT(&hqspi,&scommand,&sautopol)!=HAL_OK)
	{
		return ERR_PCOM_QSPI_IT_AUTOPOL_FAIL;
	}
	else
	{
	while(qspi_status_match !=MATCH);
	err_code = ERR_NO_ERROR;

	}
	return err_code;
}

