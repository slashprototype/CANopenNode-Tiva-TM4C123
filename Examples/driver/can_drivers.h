#ifndef CAN_DRIVERS_H_
#define CAN_DRIVERS_H_

#include "301/CO_driver.h"
#include "CO_app_TM4C123.h"

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
