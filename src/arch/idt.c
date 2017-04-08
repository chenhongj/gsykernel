#include <idt.h>

//加载IDT，位于head.s
extern void idt_load();

//256个IDT，留给中断使用
struct idt_entry idt[256];
struct idt_ptr idtp;

//设置IDT
void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags)
{
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].flags = flags;
    idt[num].always0 = 0;
}

//初始化IDT
void idt_init()
{
    //IDT位置和大小
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (uint32)((void *)(&idt));
    //清空
    //memset((uint8 *)&idt, 0, sizeof(struct idt_entry) * 256);

    //装载IDT
    idt_load();
}
