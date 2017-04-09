#ifndef __IDT_H__
#define __IDT_H__

#include <type.h>

#define TASK_GATE       (BIT0 | BIT2)
#define INTERRUPT_GATE  (BIT1 | BIT2 | BIT3)
#define TRAP_GATE       (BIT0 | BIT1 | BIT2 | BIT3 )
#define CALL_GATE       (BIT2 | BIT3)
#define TSS_BUSY        (BIT0 | BIT1 | BIT3)
#define TSS_A           (BIT0 | BIT3)

//IDT描述符
struct idt_entry
{
    uint16 base_lo;   //组成OFFSET
    uint16 sel;       //段选择子（TSS），我们在目前只有内核段
    uint8 always0;    //一般设为0
    uint8 flags;      //描述符标志，由三部分组成，DPL占用两个字节， 调用门：|P|DPL|00101| 中断门： |P|DPL|01111|  陷阱门：|P|DPL|01110|
    uint16 base_hi;
} __attribute__((packed));

//IDTR，使用LIDT装载的结构
struct idt_ptr
{
    uint16 limit;
    uint32 base;
} __attribute__((packed));

//idt.c
void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags);
void idt_init();

#endif
