#ifndef UIR_H
#define UIR_H

#include "bsp_uir.h"
#include "hal_uir.h"

extern "C"
{
/* FreeRTOS */
#include "FreeRTOS.h"
#include "stream_buffer.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
}

class UIR
{
public:
    enum UIR_type : uint8_t
    {
        VOLTAGE,
        CURRENT,
        RESISTANCE
    };

    static void init()
    {
        if (pdPASS != xTaskCreate(UIR_processTask, "UIR_processTask", configMINIMAL_STACK_SIZE * 3U,
                                  NULL, tskIDLE_PRIORITY + 4, &UIR_processHandle))
        {
            assert(false);
        }

        UIRPort::init();
        return;
    }

    static void set_voltage_mV(uint16_t voltage)
    {
        UIR::voltage = voltage;
        // UIRPort::set_voltage_mV(voltage);
        return;
    }

    static void set_current_mA(float current)
    {
        UIR::current = current;
        // UIRPort::set_current_mA(current);
        return;
    }

    static void set_resistance_Ohm(uint16_t resistance)
    {
        UIR::resistance = resistance;
        // UIRPort::set_resistance_Ohm(resistance);
        return;
    }

    static int16_t get_current()
    {
        // return UIRPort::get_current();
        return current_fact;
    }

    static void set_uir_type(UIR_type type)
    {
        UIR::type = type;
        return;
    }

    static UIR_type get_uir_type()
    {
        return type;
    }

private:
    using UIRPort = HAL::UIR<BSP::UIR>;

    static inline UIR_type type = UIR_type::VOLTAGE;

    static inline uint16_t voltage = 1500;
    static inline float current = 1.0f;
    static inline uint16_t resistance = 10;

    static inline int16_t current_fact = 0;

    static inline TaskHandle_t UIR_processHandle;

    static void UIR_processTask(void *pvParameters)
    {
        TickType_t xLastWakeTime;
        const TickType_t xFrequency = pdMS_TO_TICKS(100); // Период 100 мс
        xLastWakeTime = xTaskGetTickCount();

        for (;;)
        {
            current_fact = UIRPort::get_current();

            switch (static_cast<uint8_t>(type))
            {
            case 0: // Voltage
                UIRPort::set_voltage_mV(voltage);
                break;
            case 1:
                UIRPort::set_current_mA(current);
                break;
            case 2:
                UIRPort::set_resistance_Ohm(resistance);
                break;
            }

            vTaskDelayUntil(&xLastWakeTime, xFrequency);
        }
    }
};
#endif