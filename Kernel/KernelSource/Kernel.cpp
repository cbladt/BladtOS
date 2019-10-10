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
        Log::Debug() << "Creating serialport" << Log::NewLine;
        Serialport<0x3F8, 1> sp;

        Log::Debug() << "Writing to serialport" << Log::NewLine;
        sp.Write("hrello!");
        Log::Debug() << "..done" << Log::NewLine;
    }
}
