#pragma once
#include <stdint.h>

class Serialport
{
public:
    Serialport(uint16_t comPort);
    ~Serialport() = default;

    Serialport(const Serialport&) = delete;
    Serialport& operator=(const Serialport&) = delete;

    Serialport(Serialport&&) = delete;
    Serialport& operator=(Serialport&&) = delete;

    void Write(const uint8_t* str);

private:
    uint16_t _comPort;

    bool ReadyForTransmit();
};
