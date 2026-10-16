#ifndef CAN_COMMON_H_
#define CAN_COMMON_H_

#include <stdint.h>

enum class CanBaubrate: uint8_t
{
    BAUD_125,           /* 125 kbps  */
    BAUD_250,           /* 250 kbps  */
    BAUD_500,           /* 500 kbps  */
    BAUD_1000           /* 1000 kbps */
};

struct CanMessage
{
	uint32_t id;        /* Message ID  */
	uint8_t	length;     /* Data length */
    uint8_t data[8];    /* Data        */
};

#endif /* CAN_COMMON_H_ */
