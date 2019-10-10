#pragma once
#include <Types.hpp>

namespace Framebuffer
{
    constexpr uint16_t CommandPort = 0x3D4;
    constexpr uint16_t DataPort = 0x3D5;
    constexpr uint8_t  HighByteCommand = 14;
    constexpr uint8_t  LowByteCommand = 15;
    // TODO Should somehow be datadriven so the terminal driver can be unittested.
    constexpr size_t   Address = 0x000B8000;
}
