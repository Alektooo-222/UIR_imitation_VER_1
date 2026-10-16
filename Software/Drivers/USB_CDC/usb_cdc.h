#ifndef USB_CDC_H
#define USB_CDC_H

#include <assert.h>

#include "hal_usb_cdc.h"
#include "bsp_usb_cdc.h"
#include "status.h"

#include "usb_cdc_common.h"

#include "USB_CDC_Handlers.h"

extern "C"
{
/* FreeRTOS */
#include "FreeRTOS.h"
#include "stream_buffer.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
}

class Usb_Cdc
{
public:
    static void init(void)
    {
        /* Create transmit queue */
        txQueue = xQueueCreate(txQueueLength, sizeof(UsbCdcMessage));
        assert(txQueue != nullptr);

        /* Create receive queue */
        rxQueue = xQueueCreate(rxQueueLength, sizeof(UsbCdcMessage));
        assert(rxQueue != nullptr);

        /* Create transmit thread */
        if (pdPASS != xTaskCreate(txTask, "UsbCdcTx", configMINIMAL_STACK_SIZE,
                                  NULL, tskIDLE_PRIORITY + 4, NULL))
        {
            assert(false);
        }

        /* Create transmit thread */
        if (pdPASS != xTaskCreate(rxTask, "UsbCdcRx", configMINIMAL_STACK_SIZE * 3U,
                                  NULL, tskIDLE_PRIORITY + 4, NULL))
        {
            assert(false);
        }

        UsbCdcPort::init(UsbCdcRxCallback, nullptr);
    };

    /* Config the speed and start */
    /* static Status begin()
    {
        Status status = Status::OK;
        UsbCdcPort::begin();
        return status;
    }; */

    static Status send(UsbCdcMessage *message)
    {
        Status status = Status::OK;

        assert(txQueue != nullptr);

        /* Call from IRQ or Thread */
        if ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) == 0U)
        {
            if (xQueueSend(txQueue, (void *)message, (TickType_t)0U) != pdPASS)
            {
                /* Failed to post the message */
                status = Status::BUSY;
            }
        }
        else
        {
            portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

            if (xQueueSendFromISR(txQueue, (void *)message, &xHigherPriorityTaskWoken) != pdPASS)
            {
                /* Failed to post the message */
                status = Status::BUSY;
            }

            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }

        return status;
    };

    /* Receive the message */
    static Status receive(CanMessage *message)
    {
        Status status = Status::OK;

        assert(rxQueue != nullptr);

        /* Call from IRQ or Thread */
        if ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) == 0U)
        {
            if (xQueueReceive(rxQueue, (void *)message, (TickType_t)0U) != pdPASS)
            {
                /* Failed to post the message */
                status = Status::EMPTY;
            }
        }
        else
        {
            portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

            if (xQueueReceiveFromISR(rxQueue, (void *)message, &xHigherPriorityTaskWoken) != pdPASS)
            {
                /* Failed to post the message */
                status = Status::EMPTY;
            }

            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }

        return status;
    };

private:
    using UsbCdcPort = HAL::Usb_Cdc<BSP::Usb_Cdc>;

    static constexpr uint32_t txQueueLength = 32U;
    static constexpr uint32_t rxQueueLength = 32U;

    static inline QueueHandle_t txQueue = nullptr;
    static inline QueueHandle_t rxQueue = nullptr;

    /* CAN receive callback */
    static void UsbCdcRxCallback(UsbCdcMessage *message)
    {
        portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
        UsbCdcMessage dummyMessage;

        /* Check available space */
        if (uxQueueMessagesWaitingFromISR(rxQueue) == rxQueueLength)
        {
            /* Delete older messge from queue */
            xQueueReceiveFromISR(rxQueue, (void *)&dummyMessage, &xHigherPriorityTaskWoken);
        }

        /* Put the received message in to queue */
        xQueueSendFromISR(rxQueue, (void *)message, &xHigherPriorityTaskWoken);

        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    };

    /* Transmit task */
    static void txTask(void *pvParameters)
    {
        UsbCdcMessage txMessage = {};

        for (;;)
        {
            /* Wait tx message */
            xQueueReceive(txQueue, &txMessage, portMAX_DELAY);
            /* Send message */
            while (UsbCdcPort::send(&txMessage) != Status::OK)
            {
                vTaskDelay(1U);
            }
        }
    }

    /* Transmit task */
    static void rxTask(void *pvParameters)
    {
        UsbCdcMessage rxMessage = {};
        UBaseType_t watermark;

        for (;;)
        {
            /* Wait tx message */
            xQueueReceive(rxQueue, &rxMessage, portMAX_DELAY);

            watermark = uxTaskGetStackHighWaterMark(nullptr);

            UsbCdcCommmandHandler(&rxMessage);

            
            watermark = uxTaskGetStackHighWaterMark(nullptr);
        }
    }
};

#endif