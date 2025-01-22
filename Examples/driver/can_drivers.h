/*
 * Project      Hemodialysis Machine - slave node
 * @file        can_drivers.h
 * 
 * @brief
 * Header file
 * 
 * @details
 * Include the module details here
 * 
 * @date        19 sep 2023
 * @version     3.0.0
 * @author      Luis Juarez
 * @copyright   CIDESI� 2023
 * 
*/

#ifndef CAN_DRIVERS_H_
#define CAN_DRIVERS_H_

#include "301/CO_driver.h"
#include "libs/co_app_tm4c.h"

extern volatile uint32_t sys_timer;
/*Hardware configurations required for CAN module initialization*/
void setCANClock(uint32_t sys_clock);
/* Enable the peripherals selected in "can_config.h" for CAN controller*/
void canHwInit(void);
/* Function called inside CO_CANmodule_init when CAN Controller need to be start/reset */
void canControllerInit(co_node_tm4c_t* p_node);
/* Special routine to start CANopen application this build the required structures and variables*/
CO_ReturnError_t canopenInit(co_node_tm4c_t* p_node, uint32_t sys_clock_rate);

#endif /* CAN_DRIVERS_H_ */
