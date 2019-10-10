#include "Terminal.hpp"
#include <../Internal/Io.hpp>
#include <../Internal/Framebuffer.hpp>
#include <Types.hpp>
#include <Vga.hpp>

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

        ///
        /// \note: // TODO The idea of the T parameter was to be able to access sizeof(T) chunk at a time.
        /// obviously has some index issues to be resolved first - like index = index / sizeof(T) ish
        ///
        template <typename T>
        void WriteAtIndex(size_t index, T value)
        {
            // There should be no performance penalty using reinterpret_cast,
            // but it seems that it prevents GCC to do some optimizations.
            reinterpret_cast<T*>(Framebuffer::Address)[index] = value;
        }

        ///
        /// \note: // TODO The idea of the T parameter was to be able to access sizeof(T) chunk at a time.
        /// obviously has some index issues to be resolved first - like index = index / sizeof(T) ish
        ///
        template <typename T>
        T ReadAtIndex(size_t index)
        {
            // There should be no performance penalty using reinterpret_cast,
            // but it seems that it prevents GCC to do some optimizations.
            return reinterpret_cast<T*>(Framebuffer::Address)[index];
        }

        ///
        /// \note index, Consider a private field with get/set properties as usual best practice.
        ///
        size_t index;

        ///
        /// \note index, Consider a private field with get/set properties as usual best practice.
        ///
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

    // TODO This is f*cking ugly.
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

    ///
    /// \brief MoveCursor, Move Cursor to the last displayed character on screen.
    /// \note Perhaps make an asm function to move cursor to desired location instead 4 calls to OutByte?
    ///
    /*void MoveCursor()
    {
        uint16_t pos = static_cast<uint16_t>(_data.count - 1);
        OutByte(Framebuffer::CommandPort, Framebuffer::HighByteCommand);
        OutByte(Framebuffer::DataPort,    static_cast<uint8_t>((pos >> 8) & 0x00FF));
        OutByte(Framebuffer::CommandPort, Framebuffer::LowByteCommand);
        OutByte(Framebuffer::DataPort,    static_cast<uint8_t>(pos & 0x00FF));
    }*/
}

namespace Terminal
{
    void Print(const etl::string_view& string)
    {                        
        for (auto n = string.begin(); n != string.end(); n++)
        {
            auto& c = n[0];

            if (c == '\n')
            {
                GoToNextLine();
                continue;
            }

            _data.WriteAtIndex(_data.index, c);
            _data.WriteAtIndex(_data.index + 1, Vga::CreateColorByte(Vga::Color::White, Vga::Color::Black));

            _data.count += 1;
            _data.index += 2;
        }

        // TODO We should ignore cursor as long as we do not accept input.
        //MoveCursor();

        _data.count = (_data.index / 2);
    }
}

