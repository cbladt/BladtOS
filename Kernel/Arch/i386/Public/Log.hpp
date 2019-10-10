#pragma once
#include <Terminal.hpp>
#include <Serialport.hpp>
#include <Log/DummyLogger.hpp>
#include <Log/Logger.hpp>

namespace Log
{
    namespace __internal
    {        
        namespace
        {
            Serialport<ComPort::Com1, 1> _debugSerialPort;
        }

        class Printer
        {
        public:
            static void Print(const etl::string_view& string)
            {
                Terminal::Print(string);
                _debugSerialPort.Write(string);
            }
        };

        namespace
        {
            Logger<Printer> _debugLogger;
            Logger<Printer> _errorLogger;
            DummyLogger _dummmyLogger;
        }
    }

    inline auto& Debug()
    {
        if constexpr (IsEnabled(__internal::Level::Debug))
        {
            return __internal::_debugLogger;
        }
        else
        {
            return __internal::_dummmyLogger;
        }
    }

    inline auto& Error()
    {
        if constexpr (IsEnabled(__internal::Level::Error))
        {
            return __internal::_errorLogger;
        }
        else
        {
            return __internal::_dummmyLogger;
        }
    }
}


