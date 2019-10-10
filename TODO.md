# Todo's (As parsed by QT Creator)
<pre>
Kernel/etl/include/etl/hash.h:// TODO Fix #include <stdlib.h>
Kernel/etl/include/etl/to_string.h:// TODO REMOVE #include <math.h>
Kernel/etl/include/etl/private/to_string_helper.h:// TODO REMOVE #include <math.h>
Kernel/Arch/i386/CMakeLists.txt:# // TODO Investigate how to specficy explicit interfaces for each Arch to implement. As of right now they are totally implicit. (Virtuals are slow and do not allow common constructors. CRTP perhaps?)
Kernel/Arch/i386/Public/Terminal.cpp:        /// \note: // TODO The idea of the T parameter was to be able to access sizeof(T) chunk at a time.
Kernel/Arch/i386/Public/Terminal.cpp:        /// \note: // TODO The idea of the T parameter was to be able to access sizeof(T) chunk at a time.
Kernel/Arch/i386/Public/Terminal.cpp:    // Todo Optimize to copy 4 bytes at the time instead of 1. Perhaps an general memcpy implementation is the way to go?
Kernel/Arch/i386/Public/Terminal.cpp:    // TODO This is f*cking ugly.
Kernel/Arch/i386/Public/Terminal.cpp:                // Todo Optimize to copy 4 bytes at the time instead of 1. Perhaps an general memcpy implementation is the way to go?
Kernel/Arch/i386/Public/Terminal.cpp:        // TODO We should ignore cursor as long as we do not accept input.
Kernel/Arch/i386/Public/Interrupt.hpp:/// // TODO How do I test this?
Kernel/Arch/i386/Public/Serialport.hpp:/// \note // TODO Configuration should be parameterized.
Kernel/Arch/i386/Public/Log.cpp:    // TODO Research: Could these be inlined in header file? Right now placed in cpp to ensure a single copy across translations units.
Kernel/Arch/i386/Internal/Framebuffer.hpp:    // TODO Should somehow be datadriven so the terminal driver can be unittested.
Kernel/Arch/i386/Internal/Serialport.hpp:/// \note // TODO This stuff should be parameterized.
Kernel/Arch/i386/Internal/Serialport.hpp:		// TODO Transmit more than 1 byte at the time.
Kernel/BLibC/String.cpp:    // TODO Copy 4 byte at the time.
Kernel/BLibC/String.cpp:    // TODO Copy 4 byte at the time.
Kernel/BLibC/Float.hpp:// TODO Implement
Kernel/Utility/Log/Logger.hpp:        // TODO Why the f*ck does this work with "int" and not "int32_t"
Kernel/Utility/Vga.hpp:// TODO Research whether this is really cross platform or only specific to some platforms.
Kernel/Utility/Types.cpp:// TODO Remove this file as soon as the UtilityLib contains another translation unit so that CMake recognises it as a lib.
</pre>
22 Todo's
