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
 ;32个cpu中断
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15
global irq16
global irq17
global irq18
global irq19
global irq20
global irq21
global irq22
global irq23
global irq24
global irq25
global irq26
global irq27
global irq28
global irq29
global irq30
global irq31
global irq32

;15个系统中断
global irq33
global irq34
global irq35
global irq36
global irq37
global irq38
global irq39
global irq40
global irq41
global irq42
global irq43
global irq44
global irq45
global irq46
global irq47

;  0: 除0异常
irq0:
    cli
    push byte 0
    push byte 0
    jmp irq_common_stub

;  1: 单步异常
irq1:
    cli
    push byte 0
    push byte 1
    jmp irq_common_stub

;  2: 非可屏蔽中断异常
irq2:
    cli
    push byte 0
    push byte 2
    jmp irq_common_stub

;  3: 断点异常
irq3:
    cli
    push byte 0
    push byte 3
    jmp irq_common_stub

;  4: 检测溢出异常
irq4:
    cli
    push byte 0
    push byte 4
    jmp irq_common_stub

;  5: 越界异常
irq5:
    cli
    push byte 0
    push byte 5
    jmp irq_common_stub

;  6: 无效操作码异常
irq6:
    cli
    push byte 0
    push byte 6
    jmp irq_common_stub

;  7: 无协处理器异常
irq7:
    cli
    push byte 0
    push byte 7
    jmp irq_common_stub

;  8:  	双重错误异常      此处CPU自动产生错误码，所以不需要手动再压入
irq8:
    cli
    push byte 8
    jmp irq_common_stub

;  9: 协处理器段溢出异常
irq9:
    cli
    push byte 0
    push byte 9
    jmp irq_common_stub

; 10: 损坏的任务状态段异常（TSS段）
irq10:
    cli
    push byte 10
    jmp irq_common_stub

; 11: 段不存在异常
irq11:
    cli
    push byte 11
    jmp irq_common_stub

; 12: 栈错误异常
irq12:
    cli
    push byte 12
    jmp irq_common_stub

; 13: 一般保护错误异常
irq13:
    cli
    push byte 13
    jmp irq_common_stub

; 14: 缺页异常
irq14:
    cli
    push byte 14
    jmp irq_common_stub

; 15: 未知中断异常
irq15:
    cli
    push byte 0
    push byte 15
    jmp irq_common_stub

; 16: 协处理器错误异常
irq16:
    cli
    push byte 0
    push byte 16
    jmp irq_common_stub

; 17: 对齐检查异常
irq17:
    cli
    push byte 0
    push byte 17
    jmp irq_common_stub

; 18: 机器检查异常
irq18:
    cli
    push byte 0
    push byte 18
    jmp irq_common_stub

; 19: 保留
irq19:
    cli
    push byte 0
    push byte 19
    jmp irq_common_stub

; 20: 保留
irq20:
    cli
    push byte 0
    push byte 20
    jmp irq_common_stub

; 21: 保留
irq21:
    cli
    push byte 0
    push byte 21
    jmp irq_common_stub

; 22: 保留
irq22:
    cli
    push byte 0
    push byte 22
    jmp irq_common_stub

; 23: 保留
irq23:
    cli
    push byte 0
    push byte 23
    jmp irq_common_stub

; 24: 保留
irq24:
    cli
    push byte 0
    push byte 24
    jmp irq_common_stub

; 25: 保留
irq25:
    cli
    push byte 0
    push byte 25
    jmp irq_common_stub

; 26: 保留
irq26:
    cli
    push byte 0
    push byte 26
    jmp irq_common_stub

; 27: 保留
irq27:
    cli
    push byte 0
    push byte 27
    jmp irq_common_stub

; 28: 保留
irq28:
    cli
    push byte 0
    push byte 28
    jmp irq_common_stub

; 29: 保留
irq29:
    cli
    push byte 0
    push byte 29
    jmp irq_common_stub

; 30: 保留
irq30:
    cli
    push byte 0
    push byte 30
    jmp irq_common_stub

; 31: 保留
irq31:
    cli
    push byte 0
    push byte 31
    jmp irq_common_stub

; 32 系统中断
irq32:
    cli
    push byte 0
    push byte 32
    jmp irq_common_stub
irq33:
    cli
    push byte 0
    push byte 33
    jmp irq_common_stub
irq34:
    cli
    push byte 0
    push byte 34
    jmp irq_common_stub
irq35:
    cli
    push byte 0
    push byte 35
    jmp irq_common_stub
irq36:
    cli
    push byte 0
    push byte 36
    jmp irq_common_stub
irq37:
    cli
    push byte 0
    push byte 37
    jmp irq_common_stub
irq38:
    cli
    push byte 0
    push byte 38
    jmp irq_common_stub
irq39:
    cli
    push byte 0
    push byte 39
    jmp irq_common_stub
irq40:
    cli
    push byte 0
    push byte 40
    jmp irq_common_stub
irq41:
    cli
    push byte 0
    push byte 41
    jmp irq_common_stub
irq42:
    cli
    push byte 0
    push byte 42
    jmp irq_common_stub
irq43:
    cli
    push byte 0
    push byte 43
    jmp irq_common_stub
irq44:
    cli
    push byte 0
    push byte 44
    jmp irq_common_stub
irq45:
    cli
    push byte 0
    push byte 45
    jmp irq_common_stub
irq46:
    cli
    push byte 0
    push byte 46
    jmp irq_common_stub
; 47: IRQ15
irq47:
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub

;IRQ handler
extern irq_handler
;IRQ中断入口函数
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

global test_int
test_int:
    int 35
    int 45
    ret

;给系统堆栈预留8KB内存
SECTION .bss
   resb 0x2000
_sys_stack:
