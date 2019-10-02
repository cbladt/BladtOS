#include <Terminal.hpp>
#include <Serialport.hpp>
#include <stddef.h>

void Sleep()
{
    for (int n = 0; n < 5000000; n++)
    {
        volatile int i = n;
        (void)i;
    }
}

void fix(char n)
{
    const char* cstr = " Hrello";
    char* str = const_cast<char*>(cstr);
    str[0] = n;
    Terminal::Print(str);
    Sleep();
}

void TerminalTest()
{
    for (char n = 65; n <= 90; n++)
    {
        fix(n);
    }

    for (char n = 97; n <= 122; n++)
    {
        fix(n);
    }

    Terminal::Print("Done..");
}

extern "C"
{
    void KernelInit()
    {
    }

    void KernelMain()
    {
        TerminalTest();

        /*Serialport sp(0x3F8);
        const char* str = "Never gonna give you up never gonna let you down never gonna run around and desert you never gonna make you cry never gonna say goodbye never gonna tell a lie and hurt you.";

        sp.Write(reinterpret_cast<const uint8_t*>(str));*/
    }
}


