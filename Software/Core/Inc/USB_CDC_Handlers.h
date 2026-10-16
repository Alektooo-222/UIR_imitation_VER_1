#pragma once

#include <cstdio>

#include "usb_cdc_common.h"

void UsbCdcCommmandHandler(UsbCdcMessage *uart_rx_message);

#define NUMBER_OF_USB_CDC_HANDLERS 7U