#include "Kernel.hpp"
#include <Interrupt.hpp>
#include <Log.hpp>

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
        Log::Debug() << "Debug: " << "Hrello World" << " " << 1337 << Log::NewLine;
        Log::Error() << "Error: " << "Hrello World" << " " << 1337 << Log::NewLine;
        Log::Debug() << "This is" << Log::NewLine << "newline";
    }
}
