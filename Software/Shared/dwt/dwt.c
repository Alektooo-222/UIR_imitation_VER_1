#include "dwt.h"

/**
 * @brief  Initializes DWT_Clock_Cycle_Count
 * @return Error DWT counter
 *         1: clock cycle counter not started
 *         0: clock cycle counter works
 */
uint32_t dwtInit(void) {
  SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // разрешаем использовать DWT
  DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk;   // включаем счётчик
  DWT_CYCCNT = 0;                          // обнуляем счётчик

  /* Disable clock cycle counter */
  /* DWT_CONTROL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001; */
  /* Enable  clock cycle counter */
  /* DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk; // 0x00000001; */

  /* Reset the clock cycle counter value */
  /* DWT_CYCCNT = 0; */

  /* 3 NO OPERATION instructions */
  __asm volatile("NOP");
  __asm volatile("NOP");
  __asm volatile("NOP");

  /* Check if clock cycle counter has started */
  if (DWT_CYCCNT) {
    return 0; /*clock cycle counter started*/
  } else {
    return 1; /*clock cycle counter not started*/
  }
}

/**
 * @brief  Initializes DWT_Clock_Cycle_Count for DWT_Delay_us function
 * @return Error DWT counter
 *         1: clock cycle counter not started
 *         0: clock cycle counter works
 */
uint32_t DWT_Delay_Init(void) {
  /* Disable TRC */
  CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
  /* Enable TRC */
  CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

  /* Disable clock cycle counter */
  DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
  /* Enable  clock cycle counter */
  DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

  /* Reset the clock cycle counter value */
  DWT->CYCCNT = 0;

     /* 3 NO OPERATION instructions */
  __ASM volatile ("NOP");
  __ASM volatile ("NOP");
  __ASM volatile ("NOP");

  /* Check if clock cycle counter has started */
     if(DWT->CYCCNT)
     {
       return 0; /*clock cycle counter started*/
     }
     else
  {
    return 1; /*clock cycle counter not started*/
  }
}