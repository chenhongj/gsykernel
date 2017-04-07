bits    32
section .text

extern kernel_init
global _start
_start:
    ;初始化堆栈寄存器
    ;注意，此时堆栈段使用的起始地址为0，偏移为_sys_stack，在reload GDT之后，需要保证堆栈段不变，因为中间有函数调用
    mov eax, _sys_stack
    mov esp, eax
    mov ebp, eax

    mov ax, 0x0010      ;初始化数据寄存器
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call kernel_init    ;进入C程序入口
    jmp $

;gdt_load函数定义
global gdt_load
extern gdtp
gdt_load:
    lgdt [gdtp]
    jmp 0x08:flush2
flush2:
    ret

;将"idtp"中定义的IDT加载到处理器
;这里在C代码中声明为 'extern void idt_load();'
global idt_load
extern idtp
idt_load:
     lidt [idtp]
     ret

;给系统堆栈预留8KB内存
SECTION .bss
   resb 0x2000
_sys_stack:
