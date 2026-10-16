#ifndef MCP4725_H_
#define MCP4725_H_

#include <stdint.h>
//#include "i2c_application.h"

#define MCP4725_ADDR1  0xC0  // ����� MCP4725 (A0 = 0)
#define MCP4725_ADDR2  0xC2  // ����� MCP4725 (A0 = 1)

/* ref - ���������� ������� ������ ��� (��������, 5.0f ��� 3.3f) */
void MCP4725_Init(float ref);

/* i2c_addr - I2C ������ ���������� ���: MCP4725_ADDR1 ��� MCP4725_ADDR2
   value - �������� ������������ � �������� ������� ���: 0 ... 4095 */
void MCP4725_SetValue(uint8_t i2c_addr, uint16_t value);

/* i2c_addr - I2C ������ ���������� ���: MCP4725_ADDR1 ��� MCP4725_ADDR2
   voltage - �������� ���������� � �������: 0 ... ref */
void MCP4725_SetVoltage(uint8_t i2c_addr, float voltage);

//extern i2c_handle_type hi2c1;
#endif
