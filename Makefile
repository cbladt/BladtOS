SOURCE = Boot/Boot.o Kernel/KernelMain.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T Build/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

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

%.o: Boot/%.c Kernel/%.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: Boot/%.s Kernel/%.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o Boot/*.o Kernel/*.o kernel.elf os.iso bochslog.txt *.save
