#include <stdlib.h>
#include "UIR.h"
#include "UIR_conf.h"

double calc_U_UIR_for_i_mA(double i)
{
    double a1 = i * r1_i * p_i;
    double a2 = (r2 + r3) / (r1_i + r2 + r3);
    return a1 * a2;
}

double calc_i_1_mA(double r1, double r)
{
    return calc_i_2_mA(r1, r) + calc_i_3_mA(r1, r);
}

double calc_i_2_mA(double r1, double r)
{
    double a1 = (Udd * r) / (r1 + r);
    double a2 = ((r1 * r) / (r1 + r)) + r2 + r3;
    double a3 = a1 / a2;
    return a3;
}

double calc_i_3_mA(double r1, double r)
{
    double a1 = (Udd * (r2 + r3)) / (r1 + r2 + r3);
    double a2 = ((r1 * (r2 + r3)) / (r1 + r2 + r3)) + r;
    double a3 = a1 / a2;
    return a3;
}

double calc_U_UIR_V(int16_t Shunt_Volage_row, double r)
{
    uint32_t r1;

    if (abs(Shunt_Volage_row) < 1000)
    {
        r1 = 10000;
    }
    else
    {
        r1 = 1000;
    }

    double i_2 = calc_i_2_mA(r1, r) * (r2 + r3);

    return i_2;
}

double calc_U_ADC_V(double r1, double r)
{
    double i_2 = calc_i_2_mA(r1, r);
    return i_2 * r3;
}

uint16_t imitation_i_mA(double i)
{
    return (calc_U_UIR_for_i_mA(i) / Udd_DAC) * bit_depth;
}

uint16_t imitation_r_Ohm(int16_t Shunt_Volage_row, double r)
{
    uint16_t r1 = 0;
    uint16_t value = (calc_U_UIR_V(Shunt_Volage_row, r) / Udd_DAC) * bit_depth;

    if (abs(Shunt_Volage_row) < 1000)
    {
        r1 = 10000;
    }
    else
    {
        r1 = 1000;
    }

    if (r < 500)
    {
        value += p_r_1000;
    }

    if (r1 == 10000 && r < 3500)
    {
        value += p_r_10000;
    }

    return value;
}

uint16_t imitation_U_V(double u)
{
    u += p_u;
    return (u / Udd_DAC) * bit_depth;
}


uint16_t imitation_U_mV(uint16_t u)
{
    u += p_u;
    return (u / (Udd_DAC * 1000U)) * bit_depth;
}