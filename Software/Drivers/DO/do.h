#ifndef DO_H
#define DO_H

#include "bsp_do.h"
#include "hal_do.h"

class DO
{
public:
    enum DO_Config_Output_Type : uint8_t
    {
        DISCRETE = 0U,
        FREQ,
    };

    enum DO_State_Output : uint8_t
    {
        LOW,
        HIGH,
    };

    static void init()
    {
        DOPort::init();
        DOPort::disable_pull_up();
        DOPort::disable_nv();
        return;
    }

    static void enable_pull_up()
    {
        DOPort::enable_pull_up();
        return;
    }

    static void disable_pull_up()
    {
        DOPort::disable_pull_up();
        return;
    }

    static void enable_nv()
    {
        DOPort::enable_nv();
        return;
    }

    static void disable_nv()
    {
        DOPort::disable_nv();
        return;
    }

    static void set_duty(uint8_t duty)
    {
        DO::duty = duty;
        DOPort::set_signal(DO::freq, DO::duty);
        return;
    }

    static void set_freq(uint16_t freq)
    {
        DO::freq = freq;
        if (config_output == DO_Config_Output_Type::FREQ)
        {
            DOPort::set_signal(DO::freq, DO::duty);
        }
        return;
    }

    static uint16_t get_freq()
    {
        return freq;
    }

    static void set_config_output(DO_Config_Output_Type type_output)
    {
        config_output = type_output;
        if (type_output == DO_Config_Output_Type::DISCRETE)
        {
            if (static_cast<bool>(state_output))
            {
                DOPort::set_signal(100U, 100U);
            }
            else
            {
                DOPort::set_signal(100U, 0U);
            }
        }
        else if (type_output == DO_Config_Output_Type::FREQ)
        {
            DOPort::set_signal(DO::freq, DO::duty);
        }
        return;
    }

    static DO_Config_Output_Type get_config_output()
    {
        return config_output;
    }

    static void set_state_output(DO_State_Output state_output)
    {
        DO::state_output = state_output;

        if ((state_output == DO_State_Output::HIGH) && (config_output == DO_Config_Output_Type::DISCRETE))
        {
            DOPort::set_signal(100U, 0U);
        }
        else if ((state_output == DO_State_Output::LOW) && (config_output == DO_Config_Output_Type::DISCRETE))
        {
            DOPort::set_signal(100U, 100U);
        }
        return;
    }

    static DO_State_Output get_state_output()
    {
        return state_output;
    }

private:
    using DOPort = HAL::DO<BSP::DO>;
    static inline uint8_t duty = 60;
    static inline uint16_t freq = 0;
    static inline DO_Config_Output_Type config_output = DO_Config_Output_Type::DISCRETE;
    static inline DO_State_Output state_output = DO_State_Output::LOW;
};

#endif