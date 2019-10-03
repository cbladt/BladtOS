#pragma once
#include <Types.hpp>

namespace Vga
{
    enum class Color
    {
        Black = 0,
        Blue = 1,
        Green  = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        Grey = 7,
        DarkGrey = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        LightBrown = 14,
        White = 15
    };

    constexpr uint8_t CreateColorByte(Color text, Color background)
    {
        return static_cast<uint8_t>(((static_cast<uint8_t>(background) & 0x0F) << 4) | (static_cast<uint8_t>(text) & 0x0F));
    }
}
