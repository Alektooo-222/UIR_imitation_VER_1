#include "main.h"
#include "mcp4725.h"


extern I2C_HandleTypeDef hi2c1;
static float vRef = 5.0f;

void MCP4725_Init(float ref)
{
    /* Enable I2C clock */
    //crm_periph_clock_enable(CRM_I2C1_PERIPH_CLOCK, TRUE);
    /* Enable GPIO clock */
    //crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

    vRef = ref;

    //hi2c1.i2cx = I2C1;

    /* I2C config */
    //i2c_config(&hi2c1);
}

// ������ �������� � MCP4725 [0 ... 4095]
void MCP4725_SetValue(uint8_t i2c_addr, uint16_t value)
{
    uint8_t data[2U];

    if(value > 4095) value = 4095;

    // C0 = 0, C1 = 0, C2 = 0, PD1 = 0, PD0 = 0 (Normal Mode)
    data[0U] = (value >> 8) & 0x0F;
    data[1U] = value & 0xFF;

    //i2c_master_transmit(&hi2c1, i2c_addr, data, 2U, 0xFFFFF);
    //HAL_I2C_Mem_Write(&hi2c1, i2c_addr, )
    HAL_I2C_Master_Transmit(&hi2c1, i2c_addr, data, 2U, 0xFFFFF);
}

void MCP4725_SetVoltage(uint8_t i2c_addr, float voltage)
{
    if(voltage < 0.0f) voltage = 0.0f;
    if(voltage > vRef) voltage = vRef;

    float value = voltage * 4095.0f / vRef;

    MCP4725_SetValue(i2c_addr, (uint16_t)value);
}
