/**
* \file     max6675k.c
* \brief    This is the source code for the module name driver
*
*	Created on: 20 feb. 2022
* 		Author: Gonzalo Rivera
*/
/******************************************************************************
        Interfaces
 ******************************************************************************/
#include "stdbool.h"
#include "string.h"
#include "stdint.h"
#include "esp_log.h"

#include "max6675k.h"
/******************************************************************************
        Defines and constants
 ******************************************************************************/
static const char * MODULE_NAME 	= "[max6675k]";
static const char * DRIVER_VERSION 	= "fw_v1.0.0";

/******************************************************************************
        Data types
 ******************************************************************************/

/******************************************************************************
        Local function prototypes
 ******************************************************************************/
static int max6675k_calculatetemp(max6675k_t *max6675k);
/******************************************************************************
        Local variables
 ******************************************************************************/

/******************************************************************************
        Public function definitions
 ******************************************************************************/
int max6675k_readtemperature(max6675k_t *max6675k)
{
	int ret = MAX6675K_OK;
	uint16_t temp;

	ret = max6675k->spi_read(&temp);
	if(ret != MAX6675K_OK)
	{
		ESP_LOGE(MODULE_NAME, "spi read failed");
	}
		return ret;

	max6675k->temp_raw = temp;

	ret = max6675k_calculatetemp(max6675k);

	return ret;
}
/******************************************************************************
        Private function definitions
 ******************************************************************************/
static int max6675k_calculatetemp(max6675k_t *max6675k)
{
	int ret = 0;

	//TODO

	return ret;
}
/* End of file ***************************************************************/

