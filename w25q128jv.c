/*
 * W25Q128JV_QSPI_Instructions.c
 *
 *  Created on: 13-Nov-2020
 *      Author: Bibin
 */


#include "w25q128jv.h"
#include "inttypes.h"
#include "qspi_structure.h"



#if !defined(CUST_SNPRINTF)

#if defined(__OCPU_COMPILER_GCC__)
#define CUST_SNPRINTF Ql_snprintf
#else
#define CUST_SNPRINTF snprintf
#endif

#endif



EW25Q128JVErrorCode w25q128jv_init(SW25Q128JV_Handle *pHdle)
{
	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;

	if(pHdle->init_cnt <= 0)
	{
		err_code = (*(pHdle->qspi_init))();

		if(err_code == ERR_W25Q128JV_NO_ERROR)
		{
			++(pHdle->init_cnt);
		}
		else
		{
			//DEBUG_PRINT("SPI init FAIL");
		}

	}

	return w25q128jv_error_cnvrt(err_code);

}
EW25Q128JVErrorCode w25q128jv_deinit(SW25Q128JV_Handle *pHdle)
{
	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;

	if(pHdle->init_cnt <= 1)
	{
		err_code = (*(pHdle->qspi_deinit))();

		if(err_code == ERR_W25Q128JV_NO_ERROR)
		{
			pHdle->init_cnt=0;
		}
	}
	else
	{
		err_code =  ERR_W25Q128JV_NO_ERROR;
		--(pHdle->init_cnt);
	}



	return w25q128jv_error_cnvrt(err_code);

}
EW25Q128JVErrorCode w25q128jv_erase_4kb(SW25Q128JV_Handle *pHdle,uint32_t blk_address)
{
	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	err_code	=	w25q128jv_erase(pHdle,W25Q128JV_INS_SECT_ERASE_4KB,blk_address);

	return w25q128jv_error_cnvrt(err_code);
}

EW25Q128JVErrorCode w25q128jv_erase_32kb(SW25Q128JV_Handle *pHdle,uint32_t blk_address)
{
	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	err_code	=	w25q128jv_erase(pHdle,W25Q128JV_INS_BLK_ERASE_32KB,blk_address);

	return w25q128jv_error_cnvrt(err_code);
}
EW25Q128JVErrorCode w25q128jv_erase_64kb(SW25Q128JV_Handle *pHdle,uint32_t blk_address)
{
	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	err_code	=	w25q128jv_erase(pHdle,W25Q128JV_INS_BLK_ERASE_64KB,blk_address);

	return w25q128jv_error_cnvrt(err_code);
}


EW25Q128JVErrorCode w25q128jv_erase_chip(SW25Q128JV_Handle *pHdle)
{
	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	err_code	=	w25q128jv_erase(pHdle,W25Q128JV_INS_CHIP_ERASE1,0X00);

	return w25q128jv_error_cnvrt(err_code);
}


EW25Q128JVErrorCode w25q128jv_erase(SW25Q128JV_Handle *pHdle,uint8_t cmd,uint32_t blk_address)
{
	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;

	TS_QSPI_CommandTypeDef sCommand;

	uint32_t timeout,interval;//Crash Protection Timeout

	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=

	if(err_code ==	ERR_W25Q128JV_NO_ERROR)
	{
		err_code	=	w25q128jv_write_enable(pHdle);
		if(err_code ==	ERR_W25Q128JV_NO_ERROR)
		{
			sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
			sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_NONE;
			sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_8_BITS;
			sCommand.AddressMode = TS_QSPI_ADDRESS_1_LINE;
			sCommand.DataMode    = TS_QSPI_DATA_NONE;
			sCommand.DummyCycles = 0;
			sCommand.NbData=0;
			sCommand.Instruction = (uint32_t)cmd;
			sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
			sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
			sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
			sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
			sCommand.Address     = blk_address;
			sCommand.AlternateBytes	=	0x00;
			interval=0xffff;

			switch(cmd)
			{
			case W25Q128JV_INS_SECT_ERASE_4KB:
				timeout=ERASE_4KB_MAX_TIME;



				break;
			case W25Q128JV_INS_BLK_ERASE_32KB:
				timeout=ERASE_32KB_MAX_TIME;



				break;
			case W25Q128JV_INS_BLK_ERASE_64KB:
				timeout=ERASE_64KB_MAX_TIME;



				break;
			case W25Q128JV_INS_CHIP_ERASE1	:
			case W25Q128JV_INS_CHIP_ERASE2	:
				timeout=ERASE_CHIP_MAX_TIME;

				sCommand.AddressMode = TS_QSPI_ADDRESS_NONE;

				break;
			default		:return ERR_W25Q128JV_UNKNOWN_ERASE_CMD;

			}





			err_code	=	(*(pHdle->qspi_command_send))( &sCommand,timeout);





		}
	}


	return w25q128jv_error_cnvrt(err_code);

}
static inline EW25Q128JVErrorCode w25q128jv_qspi_enable(SW25Q128JV_Handle *pHdle)
{
	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	uint8_t stat_reg_2;
	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=


	if(err_code ==	ERR_W25Q128JV_NO_ERROR)
	{
		err_code = w25q128jv_read_stat_reg(pHdle,STATUS_REG_2,&stat_reg_2);
		if(err_code	==	ERR_W25Q128JV_NO_ERROR)
		{
			if(stat_reg_2&0b10	!=	0b10)
			{

				err_code	=	w25q128jv_write_enable(pHdle);
				if(err_code	==	ERR_W25Q128JV_NO_ERROR)
				{

					stat_reg_2|=0b10;	//QE bit in Register 2 SET
					err_code = w25q128jv_write_stat_reg(pHdle,STATUS_REG_2,&stat_reg_2);

				}
			}
		}
	}


	return w25q128jv_error_cnvrt(err_code);
}
static inline EW25Q128JVErrorCode w25q128jv_write_enable(SW25Q128JV_Handle *pHdle)
{

	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	TS_QSPI_CommandTypeDef sCommand;

	uint32_t timeout;//Crash Protection Timeout

	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=

	if(err_code ==	ERR_W25Q128JV_NO_ERROR)
	{

		timeout=WR_STAT_REG_MAX_TIME;
		sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
		sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_NONE;
		sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_8_BITS;
		sCommand.Instruction = (uint32_t)W25Q128JV_INS_WRITE_ENABLE;
		sCommand.AddressMode = TS_QSPI_ADDRESS_NONE;
		sCommand.Address     = 0x0;
		sCommand.DataMode    = TS_QSPI_DATA_NONE;
		sCommand.DummyCycles = 0;
		sCommand.NbData=0;
		sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
		sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
		sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
		sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
		sCommand.AlternateBytes	=	0x00;


		err_code	=	(*(pHdle->qspi_command_send))( &sCommand,timeout);
	}


	return w25q128jv_error_cnvrt(err_code);


}
static inline EW25Q128JVErrorCode w25q128jv_write_disable(SW25Q128JV_Handle *pHdle)
{

	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	TS_QSPI_CommandTypeDef sCommand;

	uint32_t timeout;//Crash Protection Timeout

	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=

	if(err_code ==	ERR_W25Q128JV_NO_ERROR)
	{

		timeout=WR_STAT_REG_MAX_TIME;
		sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
		sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_NONE;
		sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_8_BITS;
		sCommand.Instruction = (uint32_t)W25Q128JV_INS_WRITE_DISABLE;
		sCommand.AddressMode = TS_QSPI_ADDRESS_NONE;
		sCommand.Address     = 0x0;
		sCommand.DataMode    = TS_QSPI_DATA_NONE;
		sCommand.DummyCycles = 0;
		sCommand.NbData=0;
		sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
		sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
		sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
		sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
		sCommand.AlternateBytes	=	0x00;


		err_code	=	(*(pHdle->qspi_command_send))( &sCommand,timeout);
	}


	return w25q128jv_error_cnvrt(err_code);


}
static inline EW25Q128JVErrorCode w25q128jv_write_enable_vol_stat_reg(SW25Q128JV_Handle *pHdle)
{

	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	TS_QSPI_CommandTypeDef sCommand;

	uint32_t timeout;//Crash Protection Timeout

	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=

	if(err_code ==	ERR_W25Q128JV_NO_ERROR)
	{


		timeout=WR_STAT_REG_MAX_TIME;
		sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
		sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_NONE;
		sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_8_BITS;
		sCommand.Instruction = (uint32_t)W25Q128JV_INS_VOL_STATUS_REG_WRITE_ENABLE;
		sCommand.AddressMode = TS_QSPI_ADDRESS_NONE;
		sCommand.Address     = 0x0;
		sCommand.DataMode    = TS_QSPI_DATA_NONE;
		sCommand.DummyCycles = 0;
		sCommand.NbData=0;
		sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
		sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
		sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
		sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
		sCommand.AlternateBytes	=	0x00;


		err_code	=	(*(pHdle->qspi_command_send))( &sCommand,timeout);
	}


	return w25q128jv_error_cnvrt(err_code);

}

static inline EW25Q128JVErrorCode w25q128jv_write_stat_reg(SW25Q128JV_Handle *pHdle,EW25Q128JVStatusRegister stat_reg,uint8_t *pRegVal)
{

	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	TS_QSPI_CommandTypeDef sCommand;

	uint32_t timeout;//Crash Protection Timeout

	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=

	if(err_code ==	ERR_W25Q128JV_NO_ERROR)
	{


		timeout=WR_STAT_REG_MAX_TIME;
		sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
		sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_NONE;
		sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_8_BITS;
		sCommand.Instruction = (uint32_t)(stat_reg==STATUS_REG_1)?W25Q128JV_INS_WRITE_STATUS_REG_1:((stat_reg==STATUS_REG_2)?W25Q128JV_INS_WRITE_STATUS_REG_2:W25Q128JV_INS_WRITE_STATUS_REG_3);
		sCommand.AddressMode = TS_QSPI_ADDRESS_NONE;
		sCommand.Address     = 0x0;
		sCommand.DataMode    = TS_QSPI_DATA_1_LINE;
		sCommand.DummyCycles = 0;
		sCommand.NbData=1;
		sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
		sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
		sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
		sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
		sCommand.AlternateBytes	=	0x00;


		err_code	=	(*(pHdle->qspi_command_send))( &sCommand,timeout);

		if(err_code	==	ERR_W25Q128JV_NO_ERROR)
		{
			err_code	=(*(pHdle->qspi_transmit))(pRegVal,timeout);
		}
	}


	return w25q128jv_error_cnvrt(err_code);

}
static inline EW25Q128JVErrorCode w25q128jv_read_stat_reg(SW25Q128JV_Handle *pHdle,EW25Q128JVStatusRegister stat_reg,uint8_t *pRegVal)
{

	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	TS_QSPI_CommandTypeDef sCommand;

	uint32_t timeout;//Crash Protection Timeout

	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=

	if(err_code ==	ERR_W25Q128JV_NO_ERROR)
	{

		timeout=RD_STAT_REG_MAX_TIME;
		sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
		sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_NONE;
		sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_8_BITS;
		sCommand.Instruction = (uint32_t)(stat_reg==STATUS_REG_1)?W25Q128JV_INS_READ_STATUS_REG_1:((stat_reg==STATUS_REG_2)?W25Q128JV_INS_READ_STATUS_REG_2:W25Q128JV_INS_READ_STATUS_REG_3);
		sCommand.AddressMode = TS_QSPI_ADDRESS_NONE;
		sCommand.Address     = 0x0;
		sCommand.DataMode    = TS_QSPI_DATA_1_LINE;
		sCommand.DummyCycles = 0;
		sCommand.NbData=1;
		sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
		sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
		sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
		sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
		sCommand.AlternateBytes	=	0x00;


		err_code	=	(*(pHdle->qspi_command_send))( &sCommand,timeout);

		if(err_code	==	ERR_W25Q128JV_NO_ERROR)
		{
			err_code	=(*(pHdle->qspi_receive))(pRegVal,timeout);
		}
	}


	return w25q128jv_error_cnvrt(err_code);

}


EW25Q128JVErrorCode w25q128jv_fast_read_quad_io(SW25Q128JV_Handle *pHdle,uint32_t RdAddress,uint8_t *pRdBuffer, uint32_t RdSize)
{

	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	TS_QSPI_CommandTypeDef sCommand;

	uint32_t timeout;//Crash Protection Timeout

	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=
	if(err_code == ERR_W25Q128JV_NO_ERROR)
	{

		err_code=w25q128jv_qspi_enable(pHdle);
		if(err_code	==	ERR_W25Q128JV_NO_ERROR)
		{

			if(err_code == ERR_W25Q128JV_NO_ERROR)
			{

				err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=

				if(err_code ==	ERR_W25Q128JV_NO_ERROR)
				{

					timeout=~0;
					sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
					sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_4_LINES;
					sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_8_BITS;
					sCommand.Instruction = (uint32_t)W25Q128JV_INS_FAST_READ_QUAD_IO;
					sCommand.AddressMode = TS_QSPI_ADDRESS_4_LINES;
					sCommand.Address     = RdAddress;
					sCommand.DataMode    = TS_QSPI_DATA_4_LINES;
					sCommand.DummyCycles = 4;
					sCommand.NbData=RdSize;
					sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
					sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
					sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
					sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
					sCommand.AlternateBytes	=	0xF0;


					err_code	=	(*(pHdle->qspi_command_send))( &sCommand,timeout);

					if(err_code	==	ERR_W25Q128JV_NO_ERROR)
					{
						err_code	=(*(pHdle->qspi_receive))(pRdBuffer,timeout);
					}
				}
			}
		}
	}

	return w25q128jv_error_cnvrt(err_code);

}
EW25Q128JVErrorCode w25q128jv_quad_input_page_program(SW25Q128JV_Handle *pHdle,uint32_t TdAddress,uint8_t *pTdBuffer, uint32_t TdSize)
{
	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	TS_QSPI_CommandTypeDef sCommand;

	uint32_t timeout;//Crash Protection Timeout

	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=
	if(err_code == ERR_W25Q128JV_NO_ERROR)
	{

		err_code=w25q128jv_qspi_enable(pHdle);
		if(err_code	==	ERR_W25Q128JV_NO_ERROR)
		{

			if(err_code == ERR_W25Q128JV_NO_ERROR)
			{

				err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=
				if(err_code == ERR_W25Q128JV_NO_ERROR)
				{

					err_code	=	w25q128jv_write_enable(pHdle);
					if(err_code	==	ERR_W25Q128JV_NO_ERROR)
					{

						timeout=PGM_MAX_TIME;
						sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
						sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_NONE;
						sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_8_BITS;
						sCommand.Instruction = (uint32_t)W25Q128JV_INS_QUAD_INPUT_PAGE_PGM;
						sCommand.AddressMode = TS_QSPI_ADDRESS_1_LINE;
						sCommand.Address     = TdAddress;
						sCommand.DataMode    = TS_QSPI_DATA_4_LINES;
						sCommand.DummyCycles = 0;
						sCommand.NbData=TdSize;
						sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
						sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
						sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
						sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
						sCommand.AlternateBytes	=	0xF0;


						err_code	=	(*(pHdle->qspi_command_send))( &sCommand,timeout);

						if(err_code	==	ERR_W25Q128JV_NO_ERROR)
						{
							err_code	=(*(pHdle->qspi_transmit))(pTdBuffer,timeout);
						}
					}
				}
			}
		}
	}


	return w25q128jv_error_cnvrt(err_code);
}

static inline EW25Q128JVErrorCode w25q128jv_wait_until_busy_reset(SW25Q128JV_Handle *pHdle, uint32_t interval)
{
	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	TS_QSPI_CommandTypeDef sCommand;
	TS_QSPI_AutoPollingTypeDef sAutopol;
	uint32_t timeout;//Crash Protection Timeout


	sAutopol.AutomaticStop=TS_QSPI_AUTOMATIC_STOP_ENABLE;
	sAutopol.Interval=interval;
	sAutopol.Mask=0X1;
	sAutopol.Match=0X0;
	sAutopol.MatchMode=TS_QSPI_MATCH_MODE_AND;
	sAutopol.StatusBytesSize=1;

	sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_NONE;
	sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.Instruction = W25Q128JV_INS_READ_STATUS_REG_1;
	sCommand.AddressMode = TS_QSPI_ADDRESS_NONE;
	sCommand.Address     = 0x0;
	sCommand.DataMode    = TS_QSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
	sCommand.NbData=1;
	sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
	sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
	sCommand.AlternateBytes	=	0x00;

	timeout=200000;

	err_code	= (*(pHdle->qspi_auto_polling))(&sCommand,&sAutopol,timeout);
	return w25q128jv_error_cnvrt(err_code);

}



EW25Q128JVErrorCode w25q128jv_read_unique_id(SW25Q128JV_Handle *pHdle, uint64_t *pUid)
{

	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	TS_QSPI_CommandTypeDef sCommand;

	uint32_t timeout;//Crash Protection Timeout

	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency=

	if(err_code ==	ERR_W25Q128JV_NO_ERROR)
	{

		timeout=RD_STAT_REG_MAX_TIME	*	8;
		sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
		sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_1_LINE;
		sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_32_BITS;
		sCommand.Instruction = (uint32_t)W25Q128JV_INS_READ_UID;
		sCommand.AddressMode = TS_QSPI_ADDRESS_NONE;
		sCommand.Address     = 0x0;
		sCommand.DataMode    = TS_QSPI_DATA_1_LINE;
		sCommand.DummyCycles = 0;
		sCommand.NbData=8;
		sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
		sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
		sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
		sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
		sCommand.AlternateBytes	=	0x00;


		err_code	=	(*(pHdle->qspi_command_send))( &sCommand,timeout);

		if(err_code	==	ERR_W25Q128JV_NO_ERROR)
		{
			err_code	=(*(pHdle->qspi_receive))(pUid,timeout);
		}
	}


	return w25q128jv_error_cnvrt(err_code);

}
EW25Q128JVErrorCode w25q128jv_read_jedec_id(SW25Q128JV_Handle *pHdle, SJEDEC_ID *pJEDEC)
{

	EW25Q128JVErrorCode err_code = ERR_W25Q128JV_NO_ERROR;
	TS_QSPI_CommandTypeDef sCommand;

	uint32_t timeout;//Crash Protection Timeout
	uint8_t jedec_id[3];

	err_code	=w25q128jv_wait_until_busy_reset(pHdle,0XFFFF);//Polling intervel is 0xffff*clock frequency

	if(err_code ==	ERR_W25Q128JV_NO_ERROR)
	{

		timeout=RD_STAT_REG_MAX_TIME * 3;
		sCommand.AddressSize       = TS_QSPI_ADDRESS_24_BITS;
		sCommand.AlternateByteMode = TS_QSPI_ALTERNATE_BYTES_NONE;
		sCommand.AlternateBytesSize=TS_QSPI_ALTERNATE_BYTES_32_BITS;
		sCommand.Instruction = (uint32_t)W25Q128JV_INS_READ_JEDEC_ID;
		sCommand.AddressMode = TS_QSPI_ADDRESS_NONE;
		sCommand.Address     = 0x00;
		sCommand.DataMode    = TS_QSPI_DATA_1_LINE;
		sCommand.DummyCycles = 0;
		sCommand.NbData=	3;
		sCommand.InstructionMode   = TS_QSPI_INSTRUCTION_1_LINE;
		sCommand.DdrMode           = TS_QSPI_DDR_MODE_DISABLE;
		sCommand.DdrHoldHalfCycle  = TS_QSPI_DDR_HHC_ANALOG_DELAY;
		sCommand.SIOOMode          = TS_QSPI_SIOO_INST_EVERY_CMD;
		sCommand.AlternateBytes	=	0x00;


		err_code	=	(*(pHdle->qspi_command_send))( &sCommand,timeout);

		if(err_code	==	ERR_W25Q128JV_NO_ERROR)
		{
			err_code	=(*(pHdle->qspi_receive))(jedec_id,timeout);

			if(err_code	==	ERR_W25Q128JV_NO_ERROR)
			{
				pJEDEC->mf_id	=	jedec_id[0];
				pJEDEC->dev_id	= (uint16_t)jedec_id[1]<<8;
				pJEDEC->dev_id	|=jedec_id[2];
				if( 	 	(pJEDEC->mf_id == 0xEF) && (pJEDEC->dev_id == 0x4018)  )	//W25Q128JV-IQ/JQ
				{
					err_code = ERR_W25Q128JV_NO_ERROR;
				}
				else
				{
					err_code = ERR_W25Q128JV_JEDEC_ID_MISMATCH;
				}
			}

		}
	}


	return w25q128jv_error_cnvrt(err_code);

}

static inline EW25Q128JVErrorCode w25q128jv_error_cnvrt(EErrorCode err_code)
{
	switch(err_code)
	{
	case ERR_NO_ERROR:return ERR_W25Q128JV_NO_ERROR;

	case ERR_PCOM_QSPI_NOT_SUPPORTED:return ERR_W25Q128JV_QSPI_INIT_FAIL;

	case ERR_PCOM_QSPI_INIT_FAIL:return	ERR_W25Q128JV_QSPI_INIT_FAIL;

	case ERR_PCOM_QSPI_DEINIT_FAIL:return ERR_W25Q128JV_QSPI_DEINIT_FAIL;

	case ERR_PCOM_QSPI_NOT_INITILIZED:return	ERR_W25Q128JV_INIT_FAIL;

	case ERR_PCOM_QSPI_DMA_TX_FAIL:return	ERR_W25Q128JV_QSPI_TX_FAIL;

	case ERR_PCOM_QSPI_DMA_TX_TIMEOUT:return ERR_W25Q128JV_QSPI_TX_FAIL;

	case ERR_PCOM_QSPI_DMA_RX_FAIL:return	ERR_W25Q128JV_QSPI_RX_FAIL;

	case ERR_PCOM_QSPI_DMA_RX_TIMEOUT:return  ERR_W25Q128JV_QSPI_RX_FAIL;

	case ERR_PCOM_QSPI_IT_CMD_FAIL:return ERR_W25Q128JV_QSPI_CMD_FAIL;

	case ERR_PCOM_QSPI_IT_CMD_TIMEOUT:return ERR_W25Q128JV_CMD_TOUT;

	case ERR_PCOM_QSPI_STRUCT_FAIL:return ERR_W25Q128JV_QSPI_CMD_FAIL;

	case ERR_PCOM_QSPI_IT_AUTOPOL_FAIL:return ERR_W25Q128JV_QSPI_AUTOPOL_FAIL;

	default:return err_code;
	}
}



void w25q32jv_get_uid_string(uint64_t UID, char *pUIDStr)
{
	CUST_SNPRINTF(pUIDStr,24,"%08X%08X",
			(uint32_t)(UID >> 32),
			(uint32_t)(UID & 0xFFFFFFFF) );

}

