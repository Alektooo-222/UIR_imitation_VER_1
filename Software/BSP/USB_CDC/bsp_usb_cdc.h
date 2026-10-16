#ifndef BSP_USB_CDC_H
#define BSP_USB_CDC_H

#include "bsp.h"

namespace BSP
{
    class Usb_Cdc
    {
    public:
        static void init(UsbCdcRxCallback, UsbCdcTxCallback);
        static bool send(UsbCdcMessage *);
        static void copy_rx_buf(UsbCdcMessage *Msg);

        static inline UsbCdcRxCallback rxCompleteCallback = nullptr;
        static inline UsbCdcTxCallback txCompleteCallback = nullptr;
    };
}
#endif