#include <Framebuffer.hpp>

extern "C"
{
    void KernelInit()
    {
        Framebuffer::Init();
        Framebuffer::Print("KernelInit..");
    }

    void KernelMain()
    {        
        Framebuffer::Print("KernelMain..");
    }
}


