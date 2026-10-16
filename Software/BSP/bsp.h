#ifndef BSP_H_
#define BSP_H_

#include <cstddef>
#include <cassert>

#include "stm32f3xx_hal.h"


#include "can_common.h"
//#include "uart_common.h"
#include "usb_cdc_common.h"

namespace BSP
{

    /* Uart interrupt priorities */
    constexpr uint32_t UART1_IRQ_PRIO = 10U; /* UART1 IRQ priority */

    /* CAN interrupt priorities */
    constexpr uint32_t CAN_IRQ_PRIO = 5U; /* CAN1 IRQ priority  */

    /* Uart Rx and Tx callbacks pointer typedef */
    /* using SerialTxCallback = void (*)();
    using SerialRxCallback = void (*)(UartMessage *); */

    using UsbCdcTxCallback = void (*)();
    using UsbCdcRxCallback = void (*)(UsbCdcMessage *);

    /* Can Rx and Tx callbacks pointer typedef */
    using CanTxCallback = void (*)();
    using CanRxCallback = void (*)(CanMessage *);

    using CallbackType = void (*)();

    /* static void Error_Handler(void)
    {
        __disable_irq();
        while (1)
        {
        }
    } */

}

#endif /* BSP_H_ */
