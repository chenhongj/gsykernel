#ifndef __GDT_H__
#define __GDT_H__

#include <type.h>

//定义GDT(段描述符)
struct gdt_entry
{
    uint16 limit_low;
    uint16 base_low;
    uint8 base_middle;
    uint8 access;
    uint8 granularity;
    uint8 base_high;
} __attribute__((packed));

//GDTR，使用LGDT装载的结构
struct gdt_ptr
{
    uint16 limit;
    uint32 base;
} __attribute__((packed));

//gdt.c
void gdt_set_gate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran);
void gdt_init();

#endif
