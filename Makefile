SOURCE = Boot.o KernelProxy.o Kernel/Main.o Kernel/VTableGuard.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -fno-rtti -fno-exceptions -o0
LDFLAGS = -T Link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

CRTI_OBJ=crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=crtn.o

#OBJECTS:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(SOURCE) $(CRTEND_OBJ) $(CRTN_OBJ)
OBJECTS:=$(SOURCE)

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
		    -b boot/grub/stage2_eltorito    \
		    -no-emul-boot                   \
		    -boot-load-size 4               \
		    -A os                           \
		    -input-charset utf8             \
		    -quiet                          \
		    -boot-info-table                \
		    -o os.iso                       \
		    iso

run: os.iso
	bochs -f bochsrc.txt -q

%.o: %.cpp Kernel/%.cpp
	$(CC) $(CFLAGS)  $< -o $@

%.o: KernelMain.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso bochslog.txt *.save
