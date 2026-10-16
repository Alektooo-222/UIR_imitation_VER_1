#ifndef HAL_USB_CDC_H
#define HAL_USB_CDC_H

#include "usb_cdc_common.h"

#include "status.h"

namespace HAL
{
    using UsbCdcTxCallback = void (*)();
    using UsbCdcRxCallback = void (*)(UsbCdcMessage *);

    template <class HwModule>
    class Usb_Cdc
    {
    public:
        static void init(UsbCdcRxCallback rxCallback, UsbCdcTxCallback txCallback)
        {
            HwModule::init(rxCallback, txCallback);
        }

        static inline Status send(UsbCdcMessage * mes)
        {
            Status status = Status::BUSY;

            if(HwModule::send(mes) == true)
            {
                status = Status::OK;
            }
            
            return status;
        }
    };
}

#endif