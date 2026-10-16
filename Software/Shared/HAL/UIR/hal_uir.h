#ifndef HAL_UIR_H
#define HAL_UIR_H

namespace HAL
{
    template <class HwModule>
    class UIR
    {
    public:
        static void init()
        {
            HwModule::init();
            return;
        }

        static void set_voltage_mV(uint16_t voltage)
        {
            HwModule::set_voltage_mV(voltage);
            return;
        }

        static void set_current_mA(float current)
        {
            HwModule::set_current_mA(current);
            return;
        }

        static void set_resistance_Ohm(uint16_t resistance)
        {
            HwModule::set_resistance_Ohm(resistance);
            return;
        }

        static uint16_t get_current()
        {
            return HwModule::get_current();
        }
    };
}

#endif