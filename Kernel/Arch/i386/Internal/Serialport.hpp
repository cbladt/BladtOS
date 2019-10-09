#pragma once

#include <Types.hpp>
#include <../Internal/Io.h>

///
/// \brief __internal contains constexpr stuff, because the class cannot contain constexpr stuff.
/// \note // TODO This stuff should be parameterized.
///
namespace __internal
{
    // Tell port to expect 16bit data - 8 higher bits first.
    constexpr uint8_t EnableDLAB = 0x80;

    // 8 Databit, No Paruty, 1 Stopbit, no flowcontrol
    // http://wiki.osdev.org/Serial_ports½
    constexpr uint8_t DefaultConfig = 0x03;

    // Enable FIFO, Clear transmission queues, 14 byte queuesize.
    // http://en.wikibooks.org/wiki/Serial_Programming/%20%20%20%20%20%208250_UART_Programming
    constexpr uint8_t FifoConfig = 0xC7;

    // No interrupts, RTS = 1, DTS = 1
    constexpr uint8_t ModemConfig = 0x03;

    template <const uint16_t Port>
    constexpr uint16_t DataPort()
    {
	return Port;
    }

    template <const uint16_t ComPort>
    constexpr uint16_t FifoCommandPort()
    {
	return static_cast<uint16_t>(ComPort + 2);
    }

    template <const uint16_t ComPort>
    constexpr uint16_t LineCommandPort()
    {
	return static_cast<uint16_t>(ComPort + 2);
    }

    template <const uint16_t ComPort>
    constexpr uint16_t ModemCommandPort()
    {
	return static_cast<uint16_t>(ComPort + 2);
    }

    template <const uint16_t ComPort>
    constexpr uint16_t LineStatusPort()
    {
	return static_cast<uint16_t>(ComPort + 2);
    }

    template <const uint16_t ComPort, const uint16_t Divisor>
    class SerialportImpl
    {
    public:
	SerialportImpl()
	{
	    SetDivisor();

	    SetConfig();

	    SetFifoConfig();

	    SetModemConfig();
	}
	~SerialportImpl() = default;

	SerialportImpl(const SerialportImpl&) = delete;
	SerialportImpl& operator=(const SerialportImpl&) = delete;

	SerialportImpl(SerialportImpl&&) = delete;
	SerialportImpl& operator=(SerialportImpl&&) = delete;

	void Write(const uint8_t* str)
	{
	    for(auto n = 0;; n++)
	    {
		auto& c = str[n];

		if (c == '\0')
		{
		    break;
		}

		// TODO Transmit more than 1 byte at the time.
		WaitForReadyForTransmit();

		WriteByte(c);
	    }
	}

    private:
	uint16_t _comPort;

	void DoEnableDLAB()
	{
	    OutByte(LineCommandPort<ComPort>(), EnableDLAB);
	}

	void SetDivisor()
	{
	    DoEnableDLAB();

	    OutByte(DataPort<ComPort>(), (Divisor >> 8) & 0x00FF);

	    OutByte(DataPort<ComPort>(), Divisor & 0x00FF);
	}

	void SetConfig()
	{
	    OutByte(LineCommandPort<ComPort>(), DefaultConfig);
	}

	void SetFifoConfig()
	{
	    OutByte(FifoCommandPort<ComPort>(), FifoConfig);
	}

	void SetModemConfig()
	{
	    OutByte(ModemCommandPort<ComPort>(), ModemConfig);
	}

	void WriteByte(uint8_t b)
	{
	    OutByte(DataPort<ComPort>(), b);
	}

	void WaitForReadyForTransmit() const
	{
	    while(!ReadyForTransmit())
	    {
		volatile int doNotOptimizeOut = 1;
		(void)doNotOptimizeOut;
	    }
	}

	bool ReadyForTransmit() const
	{
	    return InByte(LineStatusPort<ComPort>()) & 0x20;
	}
    };
}
