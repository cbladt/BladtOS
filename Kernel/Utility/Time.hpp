#pragma once
#include <Types.hpp>

namespace Time
{
    class Microseconds
    {
    public:
      using ValueType = uint64_t;

      explicit constexpr Microseconds(ValueType ms) : _ms{ms}
      {}

      constexpr ValueType Get() const
      {
        return _ms;
      }

    private:
      ValueType _ms;
    };

    /// \brief Microseconds.
    constexpr Microseconds operator "" _us(uint64_t us)
    {
        return Microseconds { us };
    }

    /// \brief Miliseconds.
    constexpr Microseconds operator "" _ms(uint64_t ms)
    {
      return Microseconds{ ms * 1000 };
    }

    /// \brief Seconds.
    constexpr Microseconds operator "" _s(uint64_t seconds)
    {
      return Microseconds{ seconds * 1000 * 1000 };
    }
}
