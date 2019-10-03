#include <Terminal.hpp>
#include <Serialport.hpp>
#include <stddef.h>

extern "C"
{
    void KernelInit()
    {
    }

    void KernelMain()
    {        
        Serialport<0x3F8, 1> sp;

        const char* str = "Kage";
        sp.Write(reinterpret_cast<const uint8_t*>(str));

        Terminal::Print("Done");
    }
}


