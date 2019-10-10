#pragma once
#include <../Internal/Serialport.hpp>

///
/// \brief SerialPort serves as a proxy to __internal::Serialportimpl, to provide an easier overview of the interface.
/// \note // TODO Configuration should be parameterized.
template <const uint16_t ComPort, const uint16_t Divisor>
class Serialport
{
public:
    Serialport() = default;
    ~Serialport() = default;

    Serialport(const Serialport&) = delete;
    Serialport& operator=(const Serialport&) = delete;

    Serialport(Serialport&&) = delete;
    Serialport& operator=(Serialport&&) = delete;

    void Write(const etl::string_view& string)
    {
        _impl.Write(string);
    }

private:
    __internal::SerialportImpl<ComPort, Divisor> _impl;
};

