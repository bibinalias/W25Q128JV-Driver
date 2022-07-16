/*
 * jedec.h
 *
 *  Created on: Jul 4, 2019
 *      Author: asus
 */

#ifndef C_PROGRAMMING_LIBRARY_DRIVERS_CHIP_DRIVERS_JEDEC_H_
#define C_PROGRAMMING_LIBRARY_DRIVERS_CHIP_DRIVERS_JEDEC_H_

#include <stdint.h>

typedef struct
{
	uint8_t mf_id;		//Manufacturer ID
	uint16_t dev_id;	//Deice ID
}SJEDEC_ID;

#endif /* C_PROGRAMMING_LIBRARY_DRIVERS_CHIP_DRIVERS_JEDEC_H_ */
