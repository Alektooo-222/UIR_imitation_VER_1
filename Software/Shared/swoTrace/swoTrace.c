#include "swoTrace.h"

#define    DWT_CONTROL   *(volatile uint32_t*)0xE0001000
#define    SCB_DEMCR     *(volatile uint32_t*)0xE000EDFC

char buffer[1024];

void swoInit(uint32_t portMask, uint32_t cpuCoreFreqHz, uint32_t baudrate)
{
    uint32_t SWOPrescaler = (cpuCoreFreqHz / baudrate) - 1u ;   // baudrate in Hz, note that cpuCoreFreqHz is expected to match the CPU core clock
    
    CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk;      // Debug Exception and Monitor Control Register (DEMCR): enable trace in core debug
    DBGMCU->CR	= 0x00000027u;                          // DBGMCU_CR : TRACE_IOEN DBG_STANDBY DBG_STOP 	DBG_SLEEP
    TPI->SPPR	= 0x00000002u;                          // Selected PIN Protocol Register: Select which protocol to use for trace output (2: SWO)
    TPI->ACPR	= SWOPrescaler;                         // Async Clock Prescaler Register: Scale the baud rate of the asynchronous output
    ITM->LAR	= 0xC5ACCE55u;                          // ITM Lock Access Register: C5ACCE55 enables more write access to Control Register 0xE00 :: 0xFFC
    ITM->TCR	= 0x0001000Du;                          // ITM Trace Control Register
    ITM->TPR	= ITM_TPR_PRIVMASK_Msk;                 // ITM Trace Privilege Register: All stimulus ports
    ITM->TER	= portMask;                             // ITM Trace Enable Register: Enabled tracing on stimulus ports. One bit per stimulus port.
    DWT->CTRL	= 0x400003FEu;                          // Data Watchpoint and Trace Register
    TPI->FFCR	= 0x00000100u;                          // Formatter and Flush Control Register
}

uint32_t ITM_SendCharToChannel(uint32_t channel, uint32_t symbol)
{
    if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) &&      /* ITM enabled */
        ((ITM->TER & (1UL << channel)  ) != 0UL)   )     /* ITM Port enabled */
    {
    /* while (ITM->PORT[channel].u32 == 0UL)
    {
        __NOP();
    } */
    ITM->PORT[channel].u8 = (uint8_t)symbol;
    }
    return (symbol);
}

void printString(uint32_t channel, char *symbol)
{
    while (*symbol != 0)
    {
        ITM_SendCharToChannel(channel, *symbol);
        symbol++;
    }
    ITM_SendCharToChannel(channel, '\n');
}

void LOGI(const char *msg, ...)  // Info
{
    va_list args;
    va_start(args, msg);
    vsprintf(buffer, msg, args);
    va_end(args);
    printString(0, buffer);
}

void LOGW(const char *msg, ...)  // Warning
{
    va_list args;
    va_start(args, msg);
    vsprintf(buffer, msg, args);
    va_end(args);
    printString(1, buffer);
}

void LOGE(const char *msg, ...)  // Error
{
    va_list args;
    va_start(args, msg);
    vsprintf(buffer, msg, args);
    va_end(args);
    printString(2, buffer);
}

void LOGV (uint32_t channel, int32_t value)    // Value for plotter
{
    if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) &&      /* ITM enabled */
        ((ITM->TER & (1UL << channel)  ) != 0UL)   )     /* ITM Port enabled */
    {
    /* while (ITM->PORT[channel].u32 == 0UL)
    {
        __NOP();
    } */
    ITM->PORT[channel].u32 = value;
    }
}
