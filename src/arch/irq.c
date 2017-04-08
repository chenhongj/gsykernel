#include <irq.h>
#include <idt.h>
#include <asm.h>

//设置中断字符串
char * exception_messages[] =
        {
                "Division By Zero",                 //0
                "Debug",                            //1
                "Non Maskable Interrupt",           //2
                "Breakpoint",                       //3
                "Into Detected Overflow",           //4
                "Out of Bounds",                    //5
                "Invalid Opcode",                   //6
                "No Coprocessor",                   //7
                "Double Fault",                     //8
                "Coprocessor Segment Overrun",      //9
                "Bad TSS",                          //10
                "Segment Not Present",              //11
                "Stack Fault",                      //12
                "General Protection Fault",         //13
                "Page Fault",                       //14
                "Unknown Interrupt",                //15
                "Coprocessor Fault",                //16
                "Alignment Check",                  //17
                "Machine Check",                    //18
                "Reserved",                         //19
                "Reserved",                         //20
                "Reserved",                         //21
                "Reserved",                         //22
                "Reserved",                         //23
                "Reserved",                         //24
                "Reserved",                         //25
                "Reserved",                         //26
                "Reserved",                         //27
                "Reserved",                         //28
                "Reserved",                         //29
                "Reserved",                         //30
                "Reserved"                          //31
        };

//中断服务程序，定义在start.s中
//32个cpu中断
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
extern void irq16();
extern void irq17();
extern void irq18();
extern void irq19();
extern void irq20();
extern void irq21();
extern void irq22();
extern void irq23();
extern void irq24();
extern void irq25();
extern void irq26();
extern void irq27();
extern void irq28();
extern void irq29();
extern void irq30();
extern void irq31();
extern void irq32();

//15个系统中断
extern void irq33();
extern void irq34();
extern void irq35();
extern void irq36();
extern void irq37();
extern void irq38();
extern void irq39();
extern void irq40();
extern void irq41();
extern void irq42();
extern void irq43();
extern void irq44();
extern void irq45();
extern void irq46();
extern void irq47();

//16个系统中断函数入口
void *irq_routines[16] = { 0 };

//设置触发某个中断后调用的函数
void irq_set_handle(int32 irq, void (*handle)(struct regs *r))
{
    irq_routines[irq] = handle;
}

//重置触发中断所调用的函数
void irq_reset_handle(int32 irq)
{
    irq_routines[irq] = 0;
}

//可编程中断控制器默认会使用0-15号中断。
//因为已经把0-31号中断已经分给cpu了，所以需要重新设置中断控制器
//设置成32-47号中断
void irq_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

//初始化IRQ
void irq_init()
{
    //0x08 code段在gdt偏移
    //加入段存在标志
    uint8 flags = BIT7 | TRAP_GATE;

    //CPU中断
    idt_set_gate(0, (uint32)irq0, 0x08, flags);
    idt_set_gate(1, (uint32)irq1, 0x08, flags);
    idt_set_gate(2, (uint32)irq2, 0x08, flags);
    idt_set_gate(3, (uint32)irq3, 0x08, flags);
    idt_set_gate(4, (uint32)irq4, 0x08, flags);
    idt_set_gate(5, (uint32)irq5, 0x08, flags);
    idt_set_gate(6, (uint32)irq6, 0x08, flags);
    idt_set_gate(7, (uint32)irq7, 0x08, flags);

    idt_set_gate(8, (uint32)irq8, 0x08, flags);
    idt_set_gate(9, (uint32)irq9, 0x08, flags);
    idt_set_gate(10, (uint32)irq10, 0x08, flags);
    idt_set_gate(11, (uint32)irq11, 0x08, flags);
    idt_set_gate(12, (uint32)irq12, 0x08, flags);
    idt_set_gate(13, (uint32)irq13, 0x08, flags);
    idt_set_gate(14, (uint32)irq14, 0x08, flags);
    idt_set_gate(15, (uint32)irq15, 0x08, flags);

    idt_set_gate(16, (uint32)irq16, 0x08, flags);
    idt_set_gate(17, (uint32)irq17, 0x08, flags);
    idt_set_gate(18, (uint32)irq18, 0x08, flags);
    idt_set_gate(19, (uint32)irq19, 0x08, flags);
    idt_set_gate(20, (uint32)irq20, 0x08, flags);
    idt_set_gate(21, (uint32)irq21, 0x08, flags);
    idt_set_gate(22, (uint32)irq22, 0x08, flags);
    idt_set_gate(23, (uint32)irq23, 0x08, flags);

    idt_set_gate(24, (uint32)irq24, 0x08, flags);
    idt_set_gate(25, (uint32)irq25, 0x08, flags);
    idt_set_gate(26, (uint32)irq26, 0x08, flags);
    idt_set_gate(27, (uint32)irq27, 0x08, flags);
    idt_set_gate(28, (uint32)irq28, 0x08, flags);
    idt_set_gate(29, (uint32)irq29, 0x08, flags);
    idt_set_gate(30, (uint32)irq30, 0x08, flags);
    idt_set_gate(31, (uint32)irq31, 0x08, flags);

    irq_remap();
    //系统中断
    idt_set_gate(32, (uint32)irq32, 0x08, flags);
    idt_set_gate(33, (uint32)irq33, 0x08, flags);
    idt_set_gate(34, (uint32)irq34, 0x08, flags);
    idt_set_gate(35, (uint32)irq35, 0x08, flags);
    idt_set_gate(36, (uint32)irq36, 0x08, flags);
    idt_set_gate(37, (uint32)irq37, 0x08, flags);
    idt_set_gate(38, (uint32)irq38, 0x08, flags);
    idt_set_gate(39, (uint32)irq39, 0x08, flags);
    idt_set_gate(40, (uint32)irq40, 0x08, flags);
    idt_set_gate(41, (uint32)irq41, 0x08, flags);
    idt_set_gate(42, (uint32)irq42, 0x08, flags);
    idt_set_gate(43, (uint32)irq43, 0x08, flags);
    idt_set_gate(44, (uint32)irq44, 0x08, flags);
    idt_set_gate(45, (uint32)irq45, 0x08, flags);
    idt_set_gate(46, (uint32)irq46, 0x08, flags);
    idt_set_gate(47, (uint32)irq47, 0x08, flags);
}

//中断handler
void irq_handler(struct regs *r)
{
    void (*handler)(struct regs *r);

    //如果是cpu中断
    if (r->int_no < 32)
    {
        //puts(exception_messages[r->int_no]);
        //puts("Exception. System Halted!\n");
        while(1);
    }
        //系统前8个中断
    else if (r->int_no >= 32 && r->int_no < 40)
    {
        handler = irq_routines[r->int_no - 32];
        if (handler)
        {
            handler(r);
        }
    }
        //后八个中断由另一个控制器控制，通知slave中断控制器
    else if (r->int_no >= 40 && r->int_no <= 47)
    {
        outb(0xA0, 0x20);
    }

    //告诉控制器，中断函数已经结束
    outb(0x20, 0x20);
}
