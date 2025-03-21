
#ifndef CO_DRIVER_TARGET_H_
#define CO_DRIVER_TARGET_H_

/* This file contains device and application specific definitions.
 * It is included from CO_driver.h, which contains documentation
 * for common definitions below. */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/can.h"
#include "inc/hw_memmap.h"

#include "can_config.h"
#ifdef CO_DRIVER_CUSTOM
#include "CO_driver_custom.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Stack configuration override default values.
 * For more information see file CO_config.h. */


/* Basic definitions. If big endian, CO_SWAP_xx macros must swap bytes. */
#define CO_LITTLE_ENDIAN
#define CO_SWAP_16(x) x
#define CO_SWAP_32(x) x
#define CO_SWAP_64(x) x
/* NULL is defined in stddef.h */
/* true and false are defined in stdbool.h */
/* int8_t to uint64_t are defined in stdint.h */
typedef uint_fast8_t            bool_t;
typedef float                   float32_t;
typedef double                  float64_t;

/* Macros for acces to specific MCU CAN Controller message structur, used to read received Messages*/
#define CO_CANrxMsg_readIdent(msg) ((uint16_t)(((tCANMsgObject*)(msg)))->ui32MsgID)
#define CO_CANrxMsg_readDLC(msg)   ((uint8_t)(((tCANMsgObject*)(msg)))->ui32MsgLen)
#define CO_CANrxMsg_readData(msg)  ((uint8_t*)(((tCANMsgObject*)(msg)))->pui8MsgData)

/* Received message object */
typedef struct {
    uint16_t ident;
    uint16_t mask;
    void *object;
    void (*CANrx_callback)(void *object, void *message);
} CO_CANrx_t;

/* Transmit message object */
typedef struct {
    uint32_t ident;
    uint8_t DLC;
    uint8_t data[8];
    volatile bool_t bufferFull;
    volatile bool_t syncFlag;
} CO_CANtx_t;

/* CAN module object */
typedef struct {
    void *CANptr;
    CO_CANrx_t *rxArray;
    uint16_t rxSize;
    CO_CANtx_t *txArray;
    uint16_t txSize;
    uint16_t CANerrorStatus;
    volatile bool_t CANnormal;
    volatile bool_t useCANrxFilters;
    volatile bool_t bufferInhibitFlag;
    volatile bool_t firstCANtxMessage;
    volatile uint16_t CANtxCount;
    uint32_t errOld;
} CO_CANmodule_t;


/* Data storage object for one entry */
typedef struct {
    void *addr;
    size_t len;
    uint8_t subIndexOD;
    uint8_t attr;
    /* Additional variables (target specific) */
    void *addrNV;
} CO_storage_entry_t;

void co_processRxIsr(CO_CANmodule_t *CANmodule);
void co_processTxIsr(CO_CANmodule_t *CANmodule);

/* (un)lock critical section in CO_CANsend() */
#define CO_LOCK_CAN_SEND(CAN_MODULE)\
   CANIntDisable(CAN_BASE, CAN_INT_MASTER)
#define CO_UNLOCK_CAN_SEND(CAN_MODULE)\
   CANIntEnable(CAN_BASE, CAN_INT_MASTER)

/* (un)lock critical section in CO_errorReport() or CO_errorReset() */
#define CO_LOCK_EMCY(CAN_MODULE)\
   CANIntDisable(CAN_BASE, CAN_INT_ERROR)
#define CO_UNLOCK_EMCY(CAN_MODULE)\
   CANIntEnable(CAN_BASE, CAN_INT_ERROR)

/* (un)lock critical section when accessing Object Dictionary */
#define CO_LOCK_OD(CAN_MODULE)\
   CANIntDisable(CAN_BASE, CAN_INT_MASTER)
#define CO_UNLOCK_OD(CAN_MODULE)\
    CANIntEnable(CAN_BASE, CAN_INT_MASTER)
//   CANIntEnable(((co_node_tm4c_t *)CAN_MODULE->CANptr)->can_int, CAN_INT_MASTER)

/* Synchronization between CAN receive and message processing threads. */
#define CO_MemoryBarrier()
#define CO_FLAG_READ(rxNew) ((rxNew) != NULL)
#define CO_FLAG_SET(rxNew) {CO_MemoryBarrier(); rxNew = (void*)1L;}
#define CO_FLAG_CLEAR(rxNew) {CO_MemoryBarrier(); rxNew = NULL;}


#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif /* CO_DRIVER_TARGET_H_ */
