#include <Kernel.hpp>

extern "C"
{
    [[ noreturn ]] void KernelPanic(void)
    {
        Kernel::Panic();
    }

    void KernelInit()
    {
        Kernel::Init();
    }

    void KernelMain()
    {
        Kernel::Main();
    }
}


