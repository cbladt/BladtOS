#pragma once
#include <Terminal.hpp>
#include <Log/DummyLogger.hpp>
#include <Log/Logger.hpp>

namespace Log
{
    namespace __internal
    {
        class Printer
        {
        public:
            static void Print(const etl::string_view& string)
            {
                Terminal::Print(string);
            }
        };

        Logger<Printer>& GetDebugLogger();

        Logger<Printer>& GetErrorLogger();

        DummyLogger& GetDummyLogger();
    }

    inline auto& Debug()
    {
        if constexpr (IsEnabled(__internal::Level::Debug))
        {
            return __internal::GetDebugLogger();
        }
        else
        {
            return __internal::GetDummyLogger();
        }
    }

    inline auto& Error()
    {
        if constexpr (IsEnabled(__internal::Level::Error))
        {
            return __internal::GetErrorLogger();
        }
        else
        {
            return __internal::GetDummyLogger();
        }
    }
}


