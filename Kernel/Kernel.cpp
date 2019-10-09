#include "Kernel.hpp"
#include <Interrupt.hpp>

namespace Kernel
{
    void Panic()
    {        
        DisableInterrupt d;

        while (true)
        {
            volatile auto doNotOptimize = 0;
            (void)doNotOptimize;
        }
    }

}
