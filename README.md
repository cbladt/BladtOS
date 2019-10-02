# Setting up QT Creator
## Run "Build/prerequisites.sh" on your host machine.

## Configure kit as following - note "CMake Configuration" at the bottom.
Which is 
CMAKE_TOOLCHAIN_FILE:STRING=/home/cab/Projects/BladtOS/Kernel/Arch/i386/i386.cmake
TOOLCHAINPREFIX:STRING=/home/cab/opt/cross/bin/i386-elf
![Kit Config](/Docs/QTCreatorKitConfig.png)

## Open "Kernel/CMakeLists.txt" as project.

## Left menu -> Projects -> Build & Run -> Run - Configure as following
![Run Config](/Docs/QTCreatorRunConfig.png)


... Profit!
