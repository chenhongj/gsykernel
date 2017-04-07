#ifndef __ARCH_H
#define __ARCH_H

#include <type.h>
#include <gdt.h>
#include <idt.h>

#define _BIOS_MMAP_SIZE 20
struct BIOS_MMAP
{
    uint64 mem_addr;
    uint64 mem_size;
    uint32 mem_type;
};

void arch_init();


#endif
