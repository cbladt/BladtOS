#include "String.hpp"
extern "C" void KernelPanic(void);

namespace BLibC
{
    // TODO Copy 4 byte at the time.
    void* MemorySet(void* vsource, uint8_t c, size_t count)
    {
        auto* source = reinterpret_cast<uint8_t*>(vsource);
        while(count--)
        {
            *source = c;
        }

        return source;
    }

    // TODO Copy 4 byte at the time.
    void* MemoryMove(void* vdestination, void* vsource, size_t count)
    {
        constexpr size_t Size = 1024;

        if (count > Size)
        {
            KernelPanic();
        }

        auto* source = reinterpret_cast<uint8_t*>(vsource);
        auto* destination = reinterpret_cast<uint8_t*>(vdestination);

        uint8_t buffer[Size];

        for (size_t n = 0; n < count; n++)
        {
            buffer[n] = source[n];
        }

        for (size_t n = 0; n < count; n++)
        {
            destination[n] = buffer[n];
        }

        return vdestination;
    }
}
