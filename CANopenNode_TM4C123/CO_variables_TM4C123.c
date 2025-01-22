/*
 * Project      CANopen TM4C Library
 * @file        co_variables.c
 * 
 * @brief
 * Source file
 * 
 * @details
 * Include the module details here
 * 
 * @date        9 Oct 2023
 * @version     3.0.0
 * @author      Carlos Ruiz
 * @copyright   CIDESI� 2023
 * 
*/

#include <stdint.h>
#include <stdbool.h>
#include "CO_variables_TM4C123.h"
#include "301/CO_ODinterface.h"
#include "OD.h"

extern OD_ATTR_OD OD_t *OD;

co_var_error_t co_variableInit( uint32_t index, uint8_t subindex, bool is_event_trigger, co_variable_t *variable)
{
	uint8_t flag_mask = 0;

	if( NULL == variable)
	{
		return ERR_CO_VAR_NULL_PARAMETER_SUPPLIED;
	}

	variable->is_event_trigger = is_event_trigger;
	variable->od_entry = OD_find( OD, index );

	if( NULL == variable->od_entry )
	{
		return ERR_CO_VAR_IDX_NOT_EXIST;
	}

	if( is_event_trigger )
	{
		flag_mask = 1 << (subindex & 0x07);
		variable->od_extension.flagsPDO[ subindex >> 3 ] |= flag_mask;
		variable->od_extension.object = variable->od_entry;
		variable->od_extension.read = OD_readOriginal;
		variable->od_extension.write = OD_writeOriginal;

		OD_extension_init( variable->od_entry, &(variable->od_extension) ); 
	}

	if( OD_getSub(variable->od_entry, subindex, &(variable->od_io), true) )
	{
		return ERR_CO_VAR_OD_IO_INIT_FAILURE;
	}

	return NO_CO_VAR_ERROR;
}

co_var_error_t co_variableWrite( co_variable_t *variable, uint32_t value )
{
	OD_size_t bytes_to_write;
	OD_size_t bytes_written; 
	uint8_t subindex = 0;

	if( NULL == variable )
	{
		return ERR_CO_VAR_NULL_PARAMETER_SUPPLIED;
	}

	bytes_to_write = variable->od_io.stream.dataLength;
	 

	if( variable->od_io.write(&(variable->od_io.stream), &value, bytes_to_write, &bytes_written) )
	{
		return ERR_CO_VAR_INCORRECT_BUFF_SIZE;
	}

	if( variable->is_event_trigger )
	{
	    subindex = variable->od_io.stream.subIndex;
		OD_requestTPDO( variable->od_entry, subindex );
	}

	return NO_CO_VAR_ERROR;
}

co_var_error_t co_variableRead( co_variable_t *variable, uint32_t *value )
{
	OD_size_t bytes_to_read;
	OD_size_t bytes_read;

	if( NULL == variable )
	{
		return ERR_CO_VAR_NULL_PARAMETER_SUPPLIED;
	}

	bytes_to_read = variable->od_io.stream.dataLength;

	if( variable->od_io.read(&(variable->od_io.stream), value, bytes_to_read, &bytes_read) )
	{
		return ERR_CO_VAR_INCORRECT_BUFF_SIZE;
	}

	return NO_CO_VAR_ERROR;
}
