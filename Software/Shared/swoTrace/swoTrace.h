#pragma once

#include <stm32f3xx.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

#define SWO_STLINK_V2_MAX_SPEED 2250000u

/*
* @brief  Initialize SWO trace
* @param  portMask: 0xFFFFFFFF to enable all ports
* @param  cpuCoreFreqHz: CPU core frequency in Hz
* @param  baudrate: SWO baudrate in Hz
* @retval None
* @note   The SWO baudrate must be less than or equal to 2.25MHz for ST-LINK V2
*/
void swoInit(uint32_t portMask, uint32_t cpuCoreFreqHz, uint32_t baudrate);

/*
* @brief  Send a character to the specified channel
* @param  channel: 0 to 31
* @param  symbol: character to send
* @retval symbol
* @note   The channel must be enabled in the ITM->TER register
*/
uint32_t ITM_SendCharToChannel(uint32_t channel, uint32_t symbol);

/*
* @brief  Send a string to the specified channel
* @param  channel: 0 to 31
* @param  symbol: string to send
* @retval None
* @note   The channel must be enabled in the ITM->TER register
*/
void printString(uint32_t channel, char *symbol);

#ifdef __cplusplus
extern "C" {
#endif

/*
* @brief  Log Info function
* @param  msg: message to log like printf
*/
void LOGI(const char *msg, ...);

/*
* @brief  Log Warning function
* @param  msg: message to log like printf
*/
void LOGW(const char *msg, ...);

/*
* @brief  Log Error function
* @param  msg: message to log like printf
*/
void LOGE(const char *msg, ...);


/*
* @brief  Log Value function
* @param  channel: 0 to 31
* @param  value: value to log
* @note   This function is used for the plotter
*/
void LOGV(uint32_t channel, int32_t value);

#ifdef __cplusplus
}
#endif
