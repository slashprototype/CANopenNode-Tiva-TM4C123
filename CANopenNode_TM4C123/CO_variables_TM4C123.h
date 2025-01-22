/*
 * Project      CANopen TM4C Library
 * @file        co_variables.h
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

#ifndef CO_VARIABLES_H
#define CO_VARIABLES_H

#include "301/CO_ODinterface.h"

typedef enum co_var_error_t
{
	NO_CO_VAR_ERROR,
	ERR_CO_VAR_NULL_PARAMETER_SUPPLIED,
	ERR_CO_VAR_OD_IO_INIT_FAILURE,
	ERR_CO_VAR_IDX_NOT_EXIST,
	ERR_CO_VAR_INCORRECT_BUFF_SIZE,
	NUM_CO_VAR_ERRORS
} co_var_error_t;

typedef struct co_variable
{
	OD_entry_t *od_entry;
	OD_extension_t od_extension;
	OD_IO_t	od_io;
	/* A flag to indicate if the Change of State of this variable should Trigger a TPDO
	 * Transmission Event */
	bool is_event_trigger;
} co_variable_t;

/**
 * Initialize Object Dictionary variables with @ref od_extension and
 * COS (Change Of State) functionalities automated
 *
 * @param index 16 bit index number related with OD dictionary mapping
 * @param subIndex subIndex of the OD variable.
 * @param is_event_trigger condition to know if extension and COS
 * functionalities should be enabled, if is True the application will
 * request a TPDO transmission in the next cycle
 * @param variable special variable type @ref co_variable_t that
 * includes special read/write operations for super power application
 *
 * @return Return NO_CO_VAR_ERROR of @ref co_var_error_t enum if the
 * initialization was completed successfully
 */
co_var_error_t co_variableInit( uint32_t index, uint8_t subindex,
								bool is_event_trigger, co_variable_t *variable);

/**
 * Special Write function for @ref co_variable_t secure writing operation
 * to use this function the variable should be already initialized in
 * @ref co_variableInit()
 *
 * @param variable a pointer to @ref co_variable_t application variable created
 * by user
 * @param value just the new value to set into OD_RAM using common Stream IO
 * methods, if value doesn't match in length it will be casted
 *
 * @return Return NO_CO_VAR_ERROR of @ref co_var_error_t if write was success
 */							
co_var_error_t co_variableWrite( co_variable_t *variable, uint32_t value );
/**
 * Special Read function for @ref co_variable_t secure reading operation
 * to use this function the variable should be already initialized in
 * @ref co_variableInit()
 *
 * @param variable a pointer to @ref co_variable_t application variable created
 * by user
 * @param value a pointer to store the value received by Stream IO methods
 *
 * @return Return NO_CO_VAR_ERROR of @ref co_var_error_t if read was success
 */							
co_var_error_t co_variableRead( co_variable_t *variable, uint32_t *value );

#endif

