#include "Assert.hpp"

namespace BLibC
{
    void Assert(bool condition)
    {
        if (condition < 1)
        {
            // TODO KernelPanic
        }
    }
}

