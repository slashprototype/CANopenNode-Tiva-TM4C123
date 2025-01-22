/*
 * Project      CANopen TM4C Library
 * @file        can_variables.h
 * 
 * @brief
 * Example Header file
 * 
 * @details
 * 
 * 
 * @date        19 sep 2023
 * @version     3.0.0
 * @author      Luis Juarez
 * @copyright   CIDESI� 2023
 * 
*/

#ifndef CANOPEN_TM4C_EXAMPLES_CAN_VARIABLES_H_
#define CANOPEN_TM4C_EXAMPLES_CAN_VARIABLES_H_

#include "can_variables.h"



extern co_variable_t my_speed;
extern co_variable_t my_temperature;

/* EXAMPLE OF USE
 * You can use @ref co_var_error_t to handle invalid
 * OD variables configurations and errors before start
 * the CANopen Stack Initialization
 * 
 * co_var_error_t var_error;
 * var_error = initODVariables();
 *
*/
co_var_error_t initODVariables(void);

#endif /* CANOPEN_TM4C_EXAMPLES_CAN_VARIABLES_H_ */
