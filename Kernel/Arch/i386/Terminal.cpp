#include "Terminal.hpp"
#include <io.h>
#include <stddef.h>

namespace
{    
    constexpr uint16_t FramebufferCommandPort = 0x3D4;
    constexpr uint16_t FramebufferDataPort = 0x3D5;
    constexpr uint8_t FramebufferHighByteCommand = 14;
    constexpr uint8_t FramebufferLowByteCommand = 15;

    constexpr size_t TerminalRows = 24;
    constexpr size_t TerminalColumns = 160;

    enum class VgaColor
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
        White = 15,
    };

    constexpr uint8_t CreateVgaColorByte(VgaColor text, VgaColor background)
    {
        return static_cast<uint8_t>(((static_cast<uint8_t>(background) & 0x0F) << 4) | (static_cast<uint8_t>(text) & 0x0F));
    }

    ///
    /// \brief The DataFields class provides initialization of its members construction time.
    ///
    class DataFields
    {
    public:
        DataFields() :
            index(0),
            count(0),
            _address(reinterpret_cast<void*>(0x000B8000))
        {
            for (size_t n = 0; n < TerminalColumns * TerminalRows; n += sizeof(uint8_t))
            {
                WriteAtIndex<uint8_t>(n, 0x0);
            }
        }        

        DataFields(const DataFields&) = delete;
        DataFields& operator=(const DataFields&) = delete;

        template <typename T>
        void WriteAtIndex(size_t index, T value)
        {
            static_cast<T*>(_address)[index] = value;
        }

        template <typename T>
        T ReadAtIndex(size_t index)
        {
            return static_cast<T*>(_address)[index];
        }

        size_t index;
        size_t count;

    private:
        void* _address;
    };

    DataFields _data;

    void Scroll()
    {
        for (size_t n = 0; n < TerminalColumns * TerminalRows; n += sizeof(uint8_t))
        {            
            auto v = _data.ReadAtIndex<uint8_t>(n + TerminalColumns);
            _data.WriteAtIndex(n, v);
        }

        _data.index -= TerminalColumns;
    }

    // TODO This is ugly.
    void GoToNextLine()
    {
        if (_data.index > TerminalColumns * (TerminalRows - 1))
        {
            Scroll();
        }

        for (size_t n = 0; n <= TerminalRows; n++)
        {
            if (_data.index <= TerminalColumns * n)
            {
                // Could increment with 32 bits per iteration ..
                for (; _data.index < TerminalColumns * n; _data.index++)
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
        OutByte(FramebufferCommandPort, FramebufferHighByteCommand);
        OutByte(FramebufferDataPort,    static_cast<uint8_t>((pos >> 8) & 0x00FF));
        OutByte(FramebufferCommandPort, FramebufferLowByteCommand);
        OutByte(FramebufferDataPort,    static_cast<uint8_t>(pos & 0x00FF));
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
            _data.WriteAtIndex(_data.index + 1, CreateVgaColorByte(VgaColor::White, VgaColor::Black));

            _data.count += 1;
            _data.index += 2;
        }

        MoveCursor();

        GoToNextLine();

        _data.count = (_data.index / 2);
    }
}

