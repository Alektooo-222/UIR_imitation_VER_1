#include <stdint.h>

double calc_i_1_mA(double r1, double r);
double calc_i_2_mA(double r1, double r);
double calc_i_3_mA(double r1, double r);
double calc_U_UIR_V(int16_t Shunt_Volage_row, double r);
double calc_U_ADC_V(double r1, double r);
double calc_U_UIR_for_i_mA(double i);
uint16_t imitation_i_mA(double i);
uint16_t imitation_r_Ohm(int16_t Shunt_Volage_row, double r);
uint16_t imitation_U_V(double u);
uint16_t imitation_U_mV(uint16_t u);