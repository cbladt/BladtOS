#include "Serialport.hpp"
#include <io.h>

/* All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different values.
 */

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 */
constexpr auto SerialLineEnableDLAB = 0x80;

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
    OutByte(SERIAL_LINE_COMMAND_PORT(_comPort), SerialLineEnableDLAB);
    OutByte(SERIAL_DATA_PORT(_comPort), (SerialLineDivisor >> 8) & 0x00FF);
    OutByte(SERIAL_DATA_PORT(_comPort), SerialLineDivisor & 0x00FF);

    OutByte(SERIAL_LINE_COMMAND_PORT(_comPort), SerialLineDefaultConfig);

    OutByte(SERIAL_FIFO_COMMAND_PORT(_comPort), SerialLineFifoConfig);

    OutByte(SERIAL_MODEM_COMMAND_PORT(_comPort), SerialLineModemConfig);
}

bool Serialport::ReadyForTransmit()
{
    return InByte(SERIAL_LINE_STATUS_PORT(_comPort)) & 0x20;
}

void Serialport::Write(const char *str)
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

        OutByte(SERIAL_DATA_PORT(_comPort), c);
    }
}
