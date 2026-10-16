#ifndef DEVICE_COMMON_H_
#define DEVICE_COMMON_H_

enum class Status : signed
{
    ERROR       = -1,
    OK          =  0,
    BUSY        =  1,
    NO_CONNECT  =  2,
    OVERFLOW    =  3,
    NOT_FOUND   =  4,
    EMPTY       =  5
};

#endif /* DEVICE_COMMON_H_ */
