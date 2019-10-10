#include "Assert.hpp"
extern "C" void KernelPanic(void);

namespace BLibC
{
    void Assert(bool condition)
    {
        if (!condition)
        {
            KernelPanic();
        }
    }
}

