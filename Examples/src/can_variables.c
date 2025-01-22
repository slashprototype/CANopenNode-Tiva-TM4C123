#include "can_variables.h"
#include "CO_variables_TM4C123.h"

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
