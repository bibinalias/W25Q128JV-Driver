/*
 * W25Q128JV_QSPI_Instructions.h
 *
 *  Created on: 13-Nov-2020
 *      Author: Bibin
 */

#ifndef INC_W25Q128JV_H_
#define INC_W25Q128JV_H_
#include "inttypes.h"
#include "qspi_structure.h"
#include "error_codes.h"
#include "jedec.h"

#define PGM_MAX_TIME	3
#define WR_STAT_REG_MAX_TIME	15
#define RD_STAT_REG_MAX_TIME	10

#define ERASE_4KB_MAX_TIME	400
#define ERASE_32KB_MAX_TIME	1600
#define ERASE_64KB_MAX_TIME	2000
#define ERASE_CHIP_MAX_TIME	200000

typedef enum
{

	W25Q128JV_INS_WRITE_ENABLE	=0X06,
	W25Q128JV_INS_WRITE_DISABLE	=0X04,
	W25Q128JV_INS_VOL_STATUS_REG_WRITE_ENABLE	=0X50,
	W25Q128JV_INS_READ_STATUS_REG_1	=0X05,
	W25Q128JV_INS_READ_STATUS_REG_2	=0X35,
	W25Q128JV_INS_READ_STATUS_REG_3	=0X15,
	W25Q128JV_INS_WRITE_STATUS_REG_1	=	0X01,
	W25Q128JV_INS_WRITE_STATUS_REG_2	=	0X31,
	W25Q128JV_INS_WRITE_STATUS_REG_3	=	0X11,
	W25Q128JV_INS_FAST_READ_QUAD_IO		=	0XEB,
	W25Q128JV_INS_QUAD_INPUT_PAGE_PGM	=	0X32,

	W25Q128JV_INS_SECT_ERASE_4KB		=	0x20,
	W25Q128JV_INS_BLK_ERASE_32KB		=	0x52,
	W25Q128JV_INS_BLK_ERASE_64KB		=	0xD8,
	W25Q128JV_INS_CHIP_ERASE1			=	0xC7,
	W25Q128JV_INS_CHIP_ERASE2			=	0x60,
	W25Q128JV_INS_READ_UID				=	0X4B,
	W25Q128JV_INS_READ_JEDEC_ID			=	0X9F



}EW25Q128JV_Instruction;

typedef enum
{
	ERR_W25Q128JV_NO_ERROR			=	0,
	ERR_W25Q128JV_INIT_FAIL			=	0x1001,
	ERR_W25Q128JV_QSPI_INIT_FAIL,
	ERR_W25Q128JV_QSPI_DEINIT_FAIL,
	ERR_W25Q128JV_QSPI_TX_FAIL,
	ERR_W25Q128JV_QSPI_RX_FAIL,
	ERR_W25Q128JV_QSPI_CMD_FAIL,
	ERR_W25Q128JV_JEDEC_ID_MISMATCH,
	ERR_W25Q128JV_CMD_TOUT,
	ERR_W25Q128JV_UNKNOWN_ERASE_CMD,
	ERR_W25Q128JV_REG_NO_OUT_OF_RANGE,
	ERR_W25Q128JV_REG_SPE_CMD_FRAME_ERR,
	ERR_W25Q128JV_REG_SPE_CMD_ERR,
	ERR_W25Q128JV_REG_SPI_COM_ERR,
	ERR_W25Q128JV_QSPI_AUTOPOL_FAIL
}EW25Q128JVErrorCode;

typedef enum
{
	STATUS_REG_1=1,
	STATUS_REG_2,
	STATUS_REG_3

}EW25Q128JVStatusRegister;
typedef struct
{
	int32_t init_cnt;

	EErrorCode(*qspi_init)(void);
	EErrorCode(*qspi_deinit)(void);

	EErrorCode (*qspi_command_send)(TS_QSPI_CommandTypeDef *sCommand,uint32_t timeout);
	EErrorCode (*qspi_receive)(uint8_t *pRdBuffer,uint32_t timeout);
	EErrorCode (*qspi_transmit)(uint8_t *pTdBuffer,uint32_t timeout);
	EErrorCode (*qspi_auto_polling)(TS_QSPI_CommandTypeDef *sCommand,TS_QSPI_AutoPollingTypeDef *sAutopol,uint32_t timeout);




}SW25Q128JV_Handle;
static inline EW25Q128JVErrorCode w25q128jv_error_cnvrt(EErrorCode err_code);
void w25q32jv_get_uid_string(uint64_t UID, char *pUIDStr);
EW25Q128JVErrorCode w25q128jv_erase_chip(SW25Q128JV_Handle *pHdle);
EW25Q128JVErrorCode w25q128jv_erase_64kb(SW25Q128JV_Handle *pHdle,uint32_t blk_address);
EW25Q128JVErrorCode w25q128jv_erase_32kb(SW25Q128JV_Handle *pHdle,uint32_t blk_address);
EW25Q128JVErrorCode w25q128jv_erase_4kb(SW25Q128JV_Handle *pHdle,uint32_t blk_address);
EW25Q128JVErrorCode w25q128jv_read_jedec_id(SW25Q128JV_Handle *pHdle, SJEDEC_ID *pJEDEC);
EW25Q128JVErrorCode w25q128jv_read_unique_id(SW25Q128JV_Handle *pHdle, uint64_t *pUid);
EW25Q128JVErrorCode w25q128jv_erase(SW25Q128JV_Handle *pHdle,uint8_t cmd,uint32_t blk_address);
static inline EW25Q128JVErrorCode w25q128jv_read_stat_reg(SW25Q128JV_Handle *pHdle,EW25Q128JVStatusRegister stat_reg,uint8_t *pRegVal);
static inline EW25Q128JVErrorCode w25q128jv_write_enable_vol_stat_reg(SW25Q128JV_Handle *pHdle);
static inline EW25Q128JVErrorCode w25q128jv_write_enable(SW25Q128JV_Handle *pHdle);
static inline EW25Q128JVErrorCode w25q128jv_write_disable(SW25Q128JV_Handle *pHdle);
static inline EW25Q128JVErrorCode w25q128jv_write_stat_reg(SW25Q128JV_Handle *pHdle,EW25Q128JVStatusRegister stat_reg,uint8_t *pRegVal);
static inline EW25Q128JVErrorCode w25q128jv_qspi_enable(SW25Q128JV_Handle *pHdle);
EW25Q128JVErrorCode w25q128jv_fast_read_quad_io(SW25Q128JV_Handle *pHdle,uint32_t RdAddress,uint8_t *pRdBuffer, uint32_t RdSize);
EW25Q128JVErrorCode w25q128jv_quad_input_page_program(SW25Q128JV_Handle *pHdle,uint32_t TdAddress,uint8_t *pTdBuffer, uint32_t TdSize);
static inline EW25Q128JVErrorCode w25q128jv_wait_until_busy_reset(SW25Q128JV_Handle *pHdle, uint32_t interval);
#endif /* INC_W25Q128JV_H_ */
