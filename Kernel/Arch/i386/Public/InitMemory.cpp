#include "InitMemory.hpp"

namespace Memory
{
    struct gdt
    {
        unsigned int address;
        unsigned short size;
    } __attribute__((packed));

    void Load()
    {

    }
}
