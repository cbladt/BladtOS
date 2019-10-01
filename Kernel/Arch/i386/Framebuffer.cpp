#include "Framebuffer.hpp"
#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

namespace
{
    constexpr int TERMROWS = 22;
    constexpr int TERMCOLS = 160;
    char* _address;
    unsigned short _index;
    unsigned short _count;

    void Scroll()
    {
        for (int n = 0; n < TERMCOLS * TERMROWS; n++)
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

        for (int n = 0; n <= TERMROWS; n++)
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
        unsigned short pos = _count - 1;
        OutByte(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
        OutByte(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
        OutByte(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
        OutByte(FB_DATA_PORT,    pos & 0x00FF);
    }
}

namespace Framebuffer
{
    void Init()
    {
        _address = (char*) 0x000B8000;
        _index = 0;
        _count = 0;

        for (int n = 0; n < TERMCOLS * TERMROWS; n++)
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

