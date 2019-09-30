#include "Arch/i386/Framebuffer.hpp"

extern "C"
{
    void KernelInit()
    {

    }

    void KernelMain()
    {
        Framebuffer fb;
        fb.Print("Never gonna give you up\n");
        fb.Print("Never gonna give you up\n");
        fb.Print("Never gonna give you up\n");
        fb.Print("Never gonna give you up\n");
        fb.Print("Never gonna give you up\n");
    }
}


