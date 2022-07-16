/*
 * wrap.h
 *
 *  Created on: 17-Nov-2020
 *      Author: Bibin
 */

#ifndef INC_WRAP_H_
#define INC_WRAP_H_
#include "inttypes.h"
#include "error_codes.h"
#include "qspi_structure.h"
#include "w25q128jv.h"
EErrorCode wrap_qspi_command_send(TS_QSPI_CommandTypeDef *sCommand,uint32_t timeout);
EErrorCode wrap_qspi_receive(uint8_t *pRdBuffer,uint32_t timeout);
EErrorCode wrap_qspi_transmit(uint8_t *pTdBuffer,uint32_t timeout);
EErrorCode wrap_qspi_auto_polling(TS_QSPI_CommandTypeDef *sCommand,TS_QSPI_AutoPollingTypeDef *sAutopol,uint32_t timeout);


#endif /* INC_WRAP_H_ */
