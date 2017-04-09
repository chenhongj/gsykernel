CC=gcc
ASM=nasm
LD=ld

VPATH=src/boot/:src/kernel/:src/arch:src/util:src/driver
MBR=bin/mbr.bin
DISK=tools/10M.img
KERNEL_ELF=bin/kernel.elf
KERNEL_BIN=bin/kernel.bin

OBJDIR=obj/
INCDIR=include

MYASMFLAGS=-f elf
MYCFLAGS=-Wall -Werror -O0 -m32 -finline-functions -nostdinc -fno-builtin -I$(INCDIR)
MYLDFLAGS=-T link.ld -m elf_i386

OBJ=head.o kernel.o asm.o string.o video.o stdio.o arch.o gdt.o idt.o irq.o
OBJS= $(addprefix $(OBJDIR), $(OBJ))
DEPS= $(wildcard include/*.h) Makefile

all:mbr $(KERNEL_BIN) tools

disk:
	dd if=/dev/zero of=$(DISK) bs=512 count=20160
mbr:
	$(ASM)	-f bin src/boot/mbr.s -o $(MBR)

$(KERNEL_ELF):$(OBJS)
	$(LD)	$(MYLDFLAGS) $^ -o $@

$(KERNEL_BIN):$(KERNEL_ELF)
	objcopy -R .comment -R .eh_frame -I elf32-i386 -O binary $(KERNEL_ELF) $(KERNEL_BIN)

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC)	$(MYCFLAGS) -c $< -o $@

$(OBJDIR)%.o: %.s $(DEPS)
	$(ASM)	$(MYASMFLAGS) $< -o $@

tools:tools/mbrcp tools/kernelcp
	$(CC)	tools/mbrcp.c -o tools/mbrcp
	$(CC)	tools/kernelcp.c -o tools/kernelcp

install:all
	tools/mbrcp $(MBR) $(DISK)
	tools/kernelcp $(KERNEL_BIN) $(DISK)

run:install
	/home/gsy/myroot/bin/bochs -qf tools/my.boshrc

clean:
	rm	-rf $(MBR) tools/mbrcp $(OBJS) $(KERNEL_ELF) $(KERNEL_BIN)
