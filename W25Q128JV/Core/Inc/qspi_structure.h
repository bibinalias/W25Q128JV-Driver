/*
 * qspi_structure.h
 *
 *  Created on: 17-Nov-2020
 *      Author: Bibin
 */

#ifndef INC_QSPI_STRUCTURE_H_
#define INC_QSPI_STRUCTURE_H_

typedef struct
{
  uint32_t Instruction;        /* Specifies the Instruction to be sent
                                  This parameter can be a value (8-bit) between 0x00 and 0xFF */
  uint32_t Address;            /* Specifies the Address to be sent (Size from 1 to 4 bytes according AddressSize)
                                  This parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
  uint32_t AlternateBytes;     /* Specifies the Alternate Bytes to be sent (Size from 1 to 4 bytes according AlternateBytesSize)
                                  This parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
  uint32_t AddressSize;        /* Specifies the Address Size
                                  This parameter can be a value of @ref QSPI_AddressSize */
  uint32_t AlternateBytesSize; /* Specifies the Alternate Bytes Size
                                  This parameter can be a value of @ref QSPI_AlternateBytesSize */
  uint32_t DummyCycles;        /* Specifies the Number of Dummy Cycles.
                                  This parameter can be a number between 0 and 31 */
  uint32_t InstructionMode;    /* Specifies the Instruction Mode
                                  This parameter can be a value of @ref QSPI_InstructionMode */
  uint32_t AddressMode;        /* Specifies the Address Mode
                                  This parameter can be a value of @ref QSPI_AddressMode */
  uint32_t AlternateByteMode;  /* Specifies the Alternate Bytes Mode
                                  This parameter can be a value of @ref QSPI_AlternateBytesMode */
  uint32_t DataMode;           /* Specifies the Data Mode (used for dummy cycles and data phases)
                                  This parameter can be a value of @ref QSPI_DataMode */
  uint32_t NbData;             /* Specifies the number of data to transfer. (This is the number of bytes)
                                  This parameter can be any value between 0 and 0xFFFFFFFF (0 means undefined length
                                  until end of memory)*/
  uint32_t DdrMode;            /* Specifies the double data rate mode for address, alternate byte and data phase
                                  This parameter can be a value of @ref QSPI_DdrMode */
  uint32_t DdrHoldHalfCycle;   /* Specifies if the DDR hold is enabled. When enabled it delays the data
                                  output by one half of system clock in DDR mode.
                                  This parameter can be a value of @ref QSPI_DdrHoldHalfCycle */
  uint32_t SIOOMode;           /* Specifies the send instruction only once mode
                                  This parameter can be a value of @ref QSPI_SIOOMode */
}TS_QSPI_CommandTypeDef;

/**
  * @brief  QSPI Auto Polling mode configuration structure definition
  */
typedef struct
{
  uint32_t Match;              /* Specifies the value to be compared with the masked status register to get a match.
                                  This parameter can be any value between 0 and 0xFFFFFFFF */
  uint32_t Mask;               /* Specifies the mask to be applied to the status bytes received.
                                  This parameter can be any value between 0 and 0xFFFFFFFF */
  uint32_t Interval;           /* Specifies the number of clock cycles between two read during automatic polling phases.
                                  This parameter can be any value between 0 and 0xFFFF */
  uint32_t StatusBytesSize;    /* Specifies the size of the status bytes received.
                                  This parameter can be any value between 1 and 4 */
  uint32_t MatchMode;          /* Specifies the method used for determining a match.
                                  This parameter can be a value of @ref QSPI_MatchMode */
  uint32_t AutomaticStop;      /* Specifies if automatic polling is stopped after a match.
                                  This parameter can be a value of @ref QSPI_AutomaticStop */
}TS_QSPI_AutoPollingTypeDef;

/** @defgroup QSPI_MatchMode QSPI Match Mode
  * @{
  */
#define TS_QSPI_MATCH_MODE_AND            0                /*!<AND match mode between unmasked bits*/
#define TS_QSPI_MATCH_MODE_OR             1 /*!<OR match mode between unmasked bits*/
/**
  * @}
  */

/** @defgroup QSPI_AutomaticStop QSPI Automatic Stop
  * @{
  */
#define TS_QSPI_AUTOMATIC_STOP_DISABLE  	 0                 /*!<AutoPolling stops only with abort or QSPI disabling*/
#define TS_QSPI_AUTOMATIC_STOP_ENABLE     	 1 /*!<AutoPolling stops as soon as there is a match*/
/**
  * @}
  */
/** @defgroup QSPI_AddressSize QSPI Address Size
  * @{
  */
#define TS_QSPI_ADDRESS_8_BITS            0                      /*!<8-bit address*/
#define TS_QSPI_ADDRESS_16_BITS           1 /*!<16-bit address*/
#define TS_QSPI_ADDRESS_24_BITS           2 /*!<24-bit address*/
#define TS_QSPI_ADDRESS_32_BITS           3   /*!<32-bit address*/
/**
  * @}
  */

/** @defgroup QSPI_AlternateBytesSize QSPI Alternate Bytes Size
  * @{
  */
#define TS_QSPI_ALTERNATE_BYTES_8_BITS    0                     /*!<8-bit alternate bytes*/
#define TS_QSPI_ALTERNATE_BYTES_16_BITS   1 /*!<16-bit alternate bytes*/
#define TS_QSPI_ALTERNATE_BYTES_24_BITS   2 /*!<24-bit alternate bytes*/
#define TS_QSPI_ALTERNATE_BYTES_32_BITS   3  /*!<32-bit alternate bytes*/
/**
  * @}
  */

/** @defgroup QSPI_InstructionMode QSPI Instruction Mode
* @{
*/
#define TS_QSPI_INSTRUCTION_NONE          0                  /*!<No instruction*/
#define TS_QSPI_INSTRUCTION_1_LINE        1 /*!<Instruction on a single line*/
#define TS_QSPI_INSTRUCTION_2_LINES       2 /*!<Instruction on two lines*/
#define TS_QSPI_INSTRUCTION_4_LINES       3   /*!<Instruction on four lines*/
/**
  * @}
  */
/** @defgroup QSPI_AddressMode QSPI Address Mode
* @{
*/
#define TS_QSPI_ADDRESS_NONE              0                      /*!<No address*/
#define TS_QSPI_ADDRESS_1_LINE            1 /*!<Address on a single line*/
#define TS_QSPI_ADDRESS_2_LINES           2 /*!<Address on two lines*/
#define TS_QSPI_ADDRESS_4_LINES           3   /*!<Address on four lines*/
/**
  * @}
  */

/** @defgroup QSPI_AlternateBytesMode QSPI Alternate Bytes Mode
* @{
*/
#define TS_QSPI_ALTERNATE_BYTES_NONE      0                     /*!<No alternate bytes*/
#define TS_QSPI_ALTERNATE_BYTES_1_LINE    1 /*!<Alternate bytes on a single line*/
#define TS_QSPI_ALTERNATE_BYTES_2_LINES   2 /*!<Alternate bytes on two lines*/
#define TS_QSPI_ALTERNATE_BYTES_4_LINES  3   /*!<Alternate bytes on four lines*/
/**
  * @}
  */

/** @defgroup QSPI_DataMode QSPI Data Mode
  * @{
  */
#define TS_QSPI_DATA_NONE                0                   /*!<No data*/
#define TS_QSPI_DATA_1_LINE              1/*!<Data on a single line*/
#define TS_QSPI_DATA_2_LINES              2 /*!<Data on two lines*/
#define TS_QSPI_DATA_4_LINES              3   /*!<Data on four lines*/
/**
  * @}
  */

/** @defgroup QSPI_DdrMode QSPI DDR Mode
  * @{
  */
#define TS_QSPI_DDR_MODE_DISABLE         0               /*!<Double data rate mode disabled*/
#define TS_QSPI_DDR_MODE_ENABLE           1 /*!<Double data rate mode enabled*/
/**
  * @}
  */

/** @defgroup QSPI_DdrHoldHalfCycle QSPI DDR Data Output Delay
  * @{
  */
#define TS_QSPI_DDR_HHC_ANALOG_DELAY      0            /*!<Delay the data output using analog delay in DDR mode*/
#define TS_QSPI_DDR_HHC_HALF_CLK_DELAY    1 /*!<Delay the data output by one half of system clock in DDR mode*/
/**
  * @}
  */

/** @defgroup QSPI_SIOOMode QSPI Send Instruction Mode
  * @{
  */
#define TS_QSPI_SIOO_INST_EVERY_CMD       0                /*!<Send instruction on every transaction*/
#define TS_QSPI_SIOO_INST_ONLY_FIRST_CMD  1 /*!<Send instruction only for the first command*/
/**
  * @}
  */


#endif /* INC_QSPI_STRUCTURE_H_ */
