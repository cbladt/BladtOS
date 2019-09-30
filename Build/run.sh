#!/bin/bash
rm iso/boot/kernel.elf
cp $1 iso/boot/kernel.elf

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

bochs -rc bochsdb.txt -f bochsrc.txt -q

