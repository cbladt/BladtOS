#include "Framebuffer.hpp"

#include <io.h>
#include <Types.hpp>

constexpr auto FramebufferCommandPort = 0x3D4;
constexpr auto FramebufferDataPort = 0x3D5;

constexpr auto FramebufferHighByteCommand = 14;
constexpr auto FramebufferLowByteCommand = 15;

namespace
{
    constexpr uint16_t TERMROWS = 22;
    constexpr uint16_t TERMCOLS = 160;
    int8_t* _address;
    uint16_t _index;
    uint16_t _count;

    void Scroll()
    {
        for (size_t n = 0; n < TERMCOLS * TERMROWS; n++)
        {
            _address[n] = _address[n + TERMCOLS];
        }

        _index -= TERMCOLS;
    }

    void GoToNextLine()
    {
        if (_index > TERMCOLS * (TERMROWS - 1))
        {
            Scroll();
        }

        for (size_t n = 0; n <= TERMROWS; n++)
        {
            if (_index <= TERMCOLS * n)
            {
                for (; _index < TERMCOLS * n; _index++)
                {
                    _address[_index] = 0x0;
                }

                break;
            }
        }
    }

    void MoveCursor()
    {
        uint16_t pos = static_cast<uint16_t>(_count - 1);
        OutByte(FramebufferCommandPort, FramebufferHighByteCommand);
        OutByte(FramebufferDataPort,    ((pos >> 8) & 0x00FF));
        OutByte(FramebufferCommandPort, FramebufferLowByteCommand);
        OutByte(FramebufferDataPort,    pos & 0x00FF);
    }
}

namespace Framebuffer
{
    void Init()
    {
        _address = (char*) 0x000B8000;
        _index = 0;
        _count = 0;

        for (size_t n = 0; n < TERMCOLS * TERMROWS; n++)
        {
            _address[n] = 0x0;
        }
    }

    void Print(const char* str)
    {
        for(auto n = 0;; n++)
        {
            auto& c = str[n];

            if (c == '\0')
            {
                break;
            }

            _address[_index] = c;
            _address[_index + 1] = ((0 & 0x0F) << 4) | (15 & 0x0F);

            _count += 1;
            _index += 2;
        }

        MoveCursor();

        GoToNextLine();

        _count = (_index / 2);
    }
}

