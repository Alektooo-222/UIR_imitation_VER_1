#ifndef DRIVERS_H_
#define DRIVERS_H_

#include "board.h"

//#include "dac.h"
//#include "can.h"
//#include "uart.h"
#include "usb_cdc.h"
#include "uir.h"

class Drivers
{
public:
    static void init(void)
    {
        /* Board initialize */
        Board::init();
        //Dac::init();
        //Can::init();
        //Uart::init();
        //Usb_Cdc::init();
        UIR::init();
        Usb_Cdc::init();
        
    }
};
#endif