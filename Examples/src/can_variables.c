/*
 * Project      CANopen TM4C Library
 * @file        can_variables.c
 * 
 * @brief
 * Example source file
 * 
 * @details
 * 
 * @date        19 sep 2023
 * @version     3.0.0
 * @author      Luis Juarez
 * @copyright   CIDESI� 2023
 * 
*/

#include "can_variables.h"

co_variable_t my_speed;
co_variable_t my_temperature;

co_var_error_t initODVariables(){
    co_var_error_t error = NO_CO_VAR_ERROR;

    if (error == NO_CO_VAR_ERROR)
    {
        error = co_variableInit(0x2000, 0, true, &my_speed);
    }

    if (error == NO_CO_VAR_ERROR)
    {
        error = co_variableInit(0x2000, 0, true, &my_temperature);
    }

    return error;
}
