

#include "bsp_usb_cdc.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

extern uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

void BSP::Usb_Cdc::init(UsbCdcRxCallback RxCallback, UsbCdcTxCallback TxCallback)
{

    GPIO_InitTypeDef GPIO_InitStruct = {};

    rxCompleteCallback = RxCallback;
    txCompleteCallback = nullptr;

    // инициализируем пин DP как выход
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); // прижимаем DP к "земле"
    for (uint16_t i = 0; i < 10000; i++)
    {
    }; // немного ждём

    // переинициализируем пин для работы с USB
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    for (uint16_t i = 0; i < 10000; i++)
    {
    }; // немного ждём

    MX_USB_DEVICE_Init();
    uint32_t a1 = SYSCFG->CFGR1;
    uint32_t a2 = USB->CNTR;
    uint32_t a3 = USB->ISTR;
    uint32_t a5 = 4;

    return;
}

bool BSP::Usb_Cdc::send(UsbCdcMessage *msg)
{
    if (CDC_Transmit_FS(msg->data, msg->size) != HAL_OK)
    {
        return false;
    }

    return true;
}

void BSP::Usb_Cdc::copy_rx_buf(UsbCdcMessage *Msg)
{
    memcpy(Msg->data, UserRxBufferFS, Msg->size);
    return;
}