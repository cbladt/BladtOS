#include "Framebuffer.hpp"

Framebuffer::Framebuffer() :
    _address((char*)0x000B8000),
    _index(0)
{}

void Framebuffer::Print(const char* string)
{
    for(auto n = 0;; n++)
    {
        auto& c = string[n];

        if (c == '\0')
        {
            break;
        }

        if (c == '\n')
        {
            GoToNextLine();
            continue;
        }

        _address[_index] = c;
        _address[_index + 1] = ((0 & 0x0F) << 4) | (15 & 0x0F);

        _index += 2;
    }

    GoToNextLine();
}

void Framebuffer::GoToNextLine()
{
    for (int n = 0; n <= 25; n++)
    {
        if (_index <= 160 * n)
        {
            for (; _index < 160*n; _index++)
            {
                _address[_index] = 0x0;
            }

            break;
        }
    }
}
