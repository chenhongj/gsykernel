CC=gcc
ASM=nasm

MBR=bin/mbr.bin
DISK=tools/10M.img
ASMFLAGS=-f bin

all:mbr

disk:
	dd if=/dev/zero of=$(DISK) bs=512 count=20160
mbr:
	$(ASM) $(ASMFLAGS) src/boot/mbr.s -o $(MBR)
mbrcp:
	$(CC) tools/mbrcp.c -o tools/mbrcp
install:mbr mbrcp
	tools/mbrcp $(MBR) $(DISK)
run:install
	bochs -qf tools/my.boshrc
clean:
	rm -rf $(MBR) tools/mbrcp bx_enh_dbg.ini
