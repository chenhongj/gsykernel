#ifndef __IRQ_H__
#define __IRQ_H__

#include <type.h>

//中断服务程序启动后要保留的寄存器信息结构
//
struct regs
{
    uint32 gs, fs, es, ds;//压入上一个段
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;//由pusha来压栈
    uint32 int_no, err_code;//由push  byte和编码压入
    uint32 eip, cs, eflags, useresp, ss;//处理器自动压入
};

void irq_init();
void irq_handler(struct regs *r);
void irq_set_handle(int32 irq, void (*handle)(struct regs *r));
void irq_reset_handle(int32 irq);
void irq_remap(void);

#endif

