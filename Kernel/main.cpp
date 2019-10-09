#include <Log.hpp>


extern "C"
{
    void KernelInit()
    {
        // Init heap and stuff.
    }

    void KernelMain()
    {
        Log::Debug() << "Debug: " << "Hrello World" << " " << 1337 << Log::NewLine;
        Log::Error() << "Error: " << "Hrello World" << " " << 1337 << Log::NewLine;
        Log::Debug() << "This is" << Log::NewLine << "newline";
    }
}


