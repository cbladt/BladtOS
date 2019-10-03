#include "Terminal.hpp"
#include <io.h>
#include <Types.hpp>
#include <Vga.hpp>
#include <Framebuffer.hpp>

namespace
{
    namespace Terminal
    {
        constexpr size_t Rows = 24;
        constexpr size_t Columns = 160;
    }

    ///
    /// \brief The DataFields class provides initialization of its members construction time.
    ///
    class DataFields
    {
    public:
        DataFields() :
            index(0),
            count(0)
        {
            for (size_t n = 0; n < Terminal::Columns * Terminal::Rows; n += sizeof(uint8_t))
            {
                WriteAtIndex<uint8_t>(n, 0x0);
            }
        }

        DataFields(const DataFields&) = delete;
        DataFields& operator=(const DataFields&) = delete;

        template <typename T>
        void WriteAtIndex(size_t index, T value)
        {
            // There should be no performance penalty using reinterpret_cast,
            // but it seems that it prevents GCC to do some optimizations.
            reinterpret_cast<T*>(Framebuffer::Address)[index] = value;
        }

        template <typename T>
        T ReadAtIndex(size_t index)
        {
            // There should be no performance penalty using reinterpret_cast,
            // but it seems that it prevents GCC to do some optimizations.
            return reinterpret_cast<T*>(Framebuffer::Address)[index];
        }

        size_t index;
        size_t count;
    };

    DataFields _data;

    // Todo Optimize to copy 4 bytes at the time instead of 1. Perhaps an general memcpy implementation is the way to go?
    void Scroll()
    {
        for (size_t n = 0; n < Terminal::Columns * Terminal::Rows; n += sizeof(uint8_t))
        {
            auto v = _data.ReadAtIndex<uint8_t>(n + Terminal::Columns);
            _data.WriteAtIndex(n, v);
        }

        _data.index -= Terminal::Columns;
    }

    // TODO This is ugly.
    void GoToNextLine()
    {
        if (_data.index > Terminal::Columns * (Terminal::Rows - 1))
        {
            Scroll();
        }

        for (size_t n = 0; n <= Terminal::Rows; n++)
        {
            if (_data.index <= Terminal::Columns * n)
            {
                // Todo Optimize to copy 4 bytes at the time instead of 1. Perhaps an general memcpy implementation is the way to go?
                for (; _data.index < Terminal::Columns * n; _data.index++)
                {
                    _data.WriteAtIndex(_data.index, static_cast<uint8_t>(0x0));
                }

                break;
            }
        }
    }

    void MoveCursor()
    {
        uint16_t pos = static_cast<uint16_t>(_data.count - 1);
        OutByte(Framebuffer::CommandPort, Framebuffer::HighByteCommand);
        OutByte(Framebuffer::DataPort,    static_cast<uint8_t>((pos >> 8) & 0x00FF));
        OutByte(Framebuffer::CommandPort, Framebuffer::LowByteCommand);
        OutByte(Framebuffer::DataPort,    static_cast<uint8_t>(pos & 0x00FF));
    }
}

namespace Terminal
{
    void Print(const char* str)
    {
        for(auto n = 0;; n++)
        {
            auto& c = str[n];

            if (c == '\0')
            {
                break;
            }

            _data.WriteAtIndex(_data.index, c);
            _data.WriteAtIndex(_data.index + 1, Vga::CreateColorByte(Vga::Color::White, Vga::Color::Black));

            _data.count += 1;
            _data.index += 2;
        }

        MoveCursor();

        GoToNextLine();

        _data.count = (_data.index / 2);
    }
}

