#pragma once

namespace Memory
{
    struct gdt;
    void Load();
}

extern "C"
{
    void _DoLoadGDT(Memory::gdt* gdt);
}
