#pragma once

#include <stdint.h>
#include <stddef.h>

namespace BLibC
{
    void* MemorySet(void* vsource, uint8_t c, size_t count);

    void* MemoryMove(void* vdestination, void* vsource, size_t count);
}
