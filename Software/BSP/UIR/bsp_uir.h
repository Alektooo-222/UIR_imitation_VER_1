#ifndef BSP_UIR_H
#define BSP_UIR_H

#include "main.h"

namespace BSP
{
    class UIR
    {
    public:
        static void init();
        static void set_voltage_mV(uint16_t voltage);
        static void set_current_mA(float current);
        static void set_resistance_Ohm(uint16_t resistance);
        static uint16_t get_current();
    private:
    };
}
#endif