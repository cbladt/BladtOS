#pragma once
#include <etl/cstring.h>
#include <etl/string_view.h>
#include <etl/to_string.h>

namespace Log
{
    namespace __internal
    {
        enum class Level
        {
          Debug = 0,
          Error = 1
        };

        /**
        * @brief Current loglevel as compiletime constant.
        */
        #ifndef LOG_DEBUG
        constexpr const Level LogLevel = Level::Debug;
        #else
        constexpr const Level LogLevel = Level::Error;
        #endif

        constexpr bool IsEnabled(const Level myLevel)
        {
          return myLevel >= LogLevel;
        }
    }

    constexpr const char NewLine[] = { '\n' };

    template <typename printer_t>
    class Logger
    {
    public:
        Logger() = default;
        ~Logger() = default;

        template <typename T>
        Logger& Append(const T& message)
        {
            auto* begin = reinterpret_cast<etl::string_view::const_pointer>(message.begin());

            etl::string_view view(begin, message.size());

            printer_t::Print(view);

            return *this;
        }

        template <typename ValueType, size_t N>
        Logger& Append(const ValueType value)
        {
          etl::string<N> str;
          etl::to_string(value, str);
          return Append(str);
        }

        template <typename T>
        Logger& operator <<(const T& message)
        {
          return Append(message);
        }

        Logger& operator <<(const char* msg)
        {
          etl::string_view view(msg);
          return Append(view);
        }

        Logger& operator <<(const bool value)
        {
          if (value)
          {
            etl::string<5> str("True");
            return Append(str);
          }
          else
          {
            etl::string<6> str("False");
            return Append(str);
          }
        }

        Logger& operator <<(const int8_t value)
        {          
          return Append<int8_t, 5>(value);
        }

        Logger& operator <<(const uint8_t value)
        {          
          return Append<uint8_t, 4>(value);
        }

        Logger& operator <<(const int16_t value)
        {          
          return Append<int16_t, 7>(value);
        }

        Logger& operator <<(const uint16_t value)
        {          
          return Append<uint16_t, 6>(value);
        }

        // TODO Why the f*ck does this work with "int" and not "int32_t"
        Logger& operator <<(const int value)
        {          
          return Append<int32_t, 12>(value);
        }

        Logger& operator <<(const uint32_t value)
        {          
          return Append<uint32_t, 11>(value);
        }

        Logger& operator <<(const int64_t& value)
        {          
          return Append<int64_t, 21>(value);
        }

        Logger& operator <<(const uint64_t& value)
        {          
          return Append<uint64_t, 20>(value);
        }

        Logger& operator <<(const float& value)
        {
          // Set the decimal precision.
          etl::format_spec format;
          format.precision(7);
          // Limit string length to 15 characters
          etl::string<15> str;
          etl::to_string(value, str, format);
          return Append(str);
        }

        Logger& operator <<(const double& value)
        {
          // Set the decimal precision
          etl::format_spec format;
          format.precision(7);
          // Limit string length to 15 characters
          etl::string<15> str;
          etl::to_string(value, str, format);
          return Append(str);
        }

    private:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;
    };
} // Namespace Log.
