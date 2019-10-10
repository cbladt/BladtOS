#include "Kernel.hpp"
#include <Interrupt.hpp>
#include <Log.hpp>
#include <Serialport.hpp>

namespace Kernel
{
    void Panic()
    {        
        DisableInterrupt d;

        Log::Error() << "Kernel Panic!" << Log::NewLine;

        while (true)
        {
            volatile auto doNotOptimize = 0;
            (void)doNotOptimize;
        }
    }

    void Init()
    {
        // Init heap and stuff.
    }

    void Main()
    {
        for (auto n = 0; n < 1000; n++)
        {
            Log::Debug() << "Testing: " << n << Log::NewLine;

            for (auto i = 0; i < 1000000; i++)
            {
                volatile auto x = i;
                (void)x;
            }
        }
    }
}
