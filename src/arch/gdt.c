#include <gdt.h>

//使用3个段
struct gdt_entry gdt[3];
struct gdt_ptr gdtp;

extern void gdt_load();

//初始化最开始的三个段描述符
void gdt_set_gate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
    //描述符基地址
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    //段长度
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    //段可用标志
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

//内核最开始启动时必须初始化
void gdt_init()
{
    //GDT位置和长度信息
    gdtp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdtp.base = (uint32)((void *)(&gdt));   //通过这种方式不报错，符合逻辑

    //NULL
    gdt_set_gate(0, 0, 0, 0, 0);

    //4G大小，从0到0xFFFFFFFF，代码段
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    //4G大小，从0到0xFFFFFFFF，数据段
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    //装载GDT
    gdt_load();
}
