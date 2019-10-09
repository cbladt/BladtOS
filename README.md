# Setting up QT Creator
[Latest QT Creator](http://download.qt.io/official_releases/qtcreator/)

## Run "Build/prerequisites.sh" on your host machine.

## Configure kit as following - note "CMake Configuration" at the bottom.
Which is 

CMAKE_TOOLCHAIN_FILE:STRING=/home/cab/Projects/BladtOS/Kernel/Arch/i386/i386.cmake
TOOLCHAINPREFIX:STRING=/home/cab/opt/cross/bin/i386-elf

[This toolchain is used](https://drive.google.com/file/d/0Bw6lG3Ej2746STJaM2dNbC05elE/view?usp=sharing)  
[.. And that toolchain is found at the bottom of this article](https://wiki.osdev.org/GCC_Cross-Compiler)
![Kit Config](/Docs/QTCreatorKitConfig.png)

## Open "Kernel/CMakeLists.txt" as project.

## Left menu -> Projects -> Build & Run -> Run - Configure as following
![Run Config](/Docs/QTCreatorRunConfig.png)


... Profit!
