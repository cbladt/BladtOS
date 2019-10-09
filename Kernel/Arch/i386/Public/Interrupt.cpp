#include "Interrupt.hpp"

namespace
{
    void DoDisableInterrupt()
    {
        asm("sti");
    }

    void DoEnableInterrupt()
    {
        asm("cli");
    }
}

DisableInterrupt::DisableInterrupt()
{
    DoDisableInterrupt();
}

DisableInterrupt::~DisableInterrupt()
{
    DoEnableInterrupt();
}
