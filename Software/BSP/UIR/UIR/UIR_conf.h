#define BU 1

#define Udd 5.0
#define Udd_DAC 5.015

#if BU

#define r1_i (double)0.221
#define r2_i (double)28
#define r3_i (double)51
#define r2 (uint16_t)28000
#define r3 (uint16_t)51000
#define p_i (double)1.012
#define p_r_1000 (uint16_t)6
#define p_r_10000 (uint16_t)5
#define p_u (double)0.03
#define bit_depth (uint16_t)4095

#else

#endif