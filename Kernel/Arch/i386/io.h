#pragma once
#include <stdint.h>

extern "C"
{
    void OutByte(uint16_t port, uint8_t data);
    uint8_t InByte(uint16_t port);
}
