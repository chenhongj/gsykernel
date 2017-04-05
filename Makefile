CC=gcc
ASM=nasm

MBR=bin/mbr.bin
HEAD=bin/head.bin

DISK=tools/10M.img
ASMFLAGS=-f bin

all:mbr head

disk:
	dd if=/dev/zero of=$(DISK) bs=512 count=20160

mbr:
	$(ASM) $(ASMFLAGS) src/boot/mbr.s -o $(MBR)
mbrcp:
	$(CC) tools/mbrcp.c -o tools/mbrcp

head:
	$(ASM) $(ASMFLAGS) src/boot/head.s -o $(HEAD)
headcp:
	$(CC) tools/headcp.c -o tools/headcp

install:mbr mbrcp head headcp
	tools/mbrcp $(MBR) $(DISK)
	tools/headcp $(HEAD) $(DISK)

run:install
	bochs -qf tools/my.boshrc
clean:
	rm -rf $(MBR) tools/mbrcp bx_enh_dbg.ini
