#ifndef HAL_DI_H_
#define HAL_DI_H_

#include <cstdint>

namespace HAL
{
    using CallbackType = void (*)();

    template <class HwModule, class CONSTType, class FilterType>
    class DI
    {
    public:
        static void init(CallbackType ADCCallback, CallbackType TIMCallback)
        {
            HwModule::init(ADCCallback, TIMCallback);
            return;
        }

        static const uint16_t *get_adc_buffer_pointer()
        {
            return HwModule::get_adc_buffer_pointer();
        }

        static const uint16_t *get_freq_buffer_pointer()
        {
            return HwModule::get_freq_buffer_pointer();
        }

        static const uint16_t *get_duty_cycle_buffer_pointer()
        {
            return HwModule::get_duty_cycle_buffer_pointer();
        }

        static void start_measurement(uint16_t number_of_measurement)
        {
            return HwModule::start_measurement(number_of_measurement);
        }

        static void stop_measurement()
        {
            return HwModule::stop_measurement();
        }

        static bool get_pin_state()
        {
            return HwModule::get_pin_state();
        }
    };
}
#endif