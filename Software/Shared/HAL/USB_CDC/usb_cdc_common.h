#ifndef USB_CDC_COMMON_H
#define USB_CDC_COMMON_H

#include <cstdint>
#include <cstddef>

#define MAX_SIZE_USB_CDC_MESSAGE 64U

struct UsbCdcMessage
{
    size_t size;
    uint8_t data[MAX_SIZE_USB_CDC_MESSAGE];
};

#endif