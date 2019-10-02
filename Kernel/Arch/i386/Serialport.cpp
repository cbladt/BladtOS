#include "Serialport.hpp"
#include <io.h>

/* All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different values.
 */

namespace
{
    constexpr uint16_t SerialDataPort(uint16_t base)
    {
        return base;
    }

    constexpr uint16_t SerialFifoCommandPort(uint16_t base)
    {
        return static_cast<uint16_t>(base + 2);
    }

    constexpr uint16_t SerialLineCommandPort(uint16_t base)
    {
        return static_cast<uint16_t>(base + 2);
    }

    constexpr uint16_t SerialModemCommandPort(uint16_t base)
    {
        return static_cast<uint16_t>(base + 2);
    }

    constexpr uint16_t SerialLineStatusPort(uint16_t base)
    {
        return static_cast<uint16_t>(base + 2);
    }
}

// Tell port to expect 16bit data - 8 higher bits first.
constexpr uint8_t SerialLineEnableDLAB = 0x80;

// Baud divisor.
constexpr uint16_t SerialLineDivisor = 1;

/* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
 * Content: | d | b | prty  | s | dl  |
 * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
 */
constexpr uint8_t SerialLineDefaultConfig = 0x03;

/* FIFO
We use the value 0xC7 = 11000111 that:
Enables FIFO
Clear both receiver and transmission FIFO queues
Use 14 bytes as size of queue */
constexpr uint8_t SerialLineFifoConfig = 0xC7;

/* Modem
We don’t need to enable interrupts, because we won’t handle any received data.
Therefore we use the configuration value 0x03 = 00000011 (RTS = 1 and DTS = 1).*/
constexpr uint8_t SerialLineModemConfig = 0x03;

Serialport::Serialport(uint16_t comPort) :
    _comPort(comPort)
{
    OutByte(SerialLineCommandPort(_comPort), SerialLineEnableDLAB);
    OutByte(SerialDataPort(_comPort), (SerialLineDivisor >> 8) & 0x00FF);
    OutByte(SerialDataPort(_comPort), SerialLineDivisor & 0x00FF);

    OutByte(SerialLineCommandPort(_comPort), SerialLineDefaultConfig);

    OutByte(SerialFifoCommandPort(_comPort), SerialLineFifoConfig);

    OutByte(SerialModemCommandPort(_comPort), SerialLineModemConfig);
}

bool Serialport::ReadyForTransmit()
{
    return InByte(SerialLineStatusPort(_comPort)) & 0x20;
}

void Serialport::Write(const uint8_t *str)
{
    for(auto n = 0;; n++)
    {
        auto& c = str[n];

        if (c == '\0')
        {
            break;
        }

        while(!ReadyForTransmit())
        {}

        OutByte(SerialDataPort(_comPort), c);
    }
}
