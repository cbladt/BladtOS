#pragma once

namespace GDT
{
    struct _gdt;
}

extern "C"
{
    void _DoLoadGDT(GDT::_gdt* gdt);
}

namespace GDT
{
    struct _gdt
    {
        unsigned int address;
        unsigned short size;
    } __attribute__((packed));

    void Load()
    {
        _gdt table {0, 0};
        _DoLoadGDT(&table);
    }
}
