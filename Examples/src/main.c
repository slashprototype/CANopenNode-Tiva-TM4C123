#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driver/can_drivers.h"
#include "can_variables.h"

int main(void)
{
    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_OSC | SYSCTL_SYSDIV_2_5); /*40 MHz*/
    uint32_t sys_clock_value = SysCtlClockGet();
    /* Use a similar function to initialize your OD variables*/
    initODVariables();
    /* CANopenNode for TM4C123 instance*/
    co_node_tm4c_t co_node_tm4c;
    /* The CAN module needs a sys_clock to realize HW configurations*/
    canopenInit(&co_node_tm4c, sys_clock_value);

    IntMasterEnable();
    
    while (true)
    {
        CO_appProcess();
    }
}
