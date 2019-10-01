#include <Framebuffer.hpp>
#include <Serialport.hpp>

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

        Serialport sp(0x3F8);
        sp.Write("Never gonna give you up never gonna let you down never gonna run around and desert you never gonna make you cry never gonna say goodbye never gonna tell a lie and hurt you.");
    }
}


