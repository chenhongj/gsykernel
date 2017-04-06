bits    32
section .text

extern kernel_init
global _start
_start:
    ;进入32位环境后初始化所有寄存器
    mov ax, 0x0010      ;初始化数据寄存器
    mov ds, ax
    mov ss, ax
                        ;初始化堆栈寄存器
    mov eax, _sys_stack
    mov esp, eax
    mov ebp, eax
    call kernel_init    ;进入C程序入口
    jmp $

;给系统堆栈预留8KB内存
SECTION .bss
   resb 0x2000
_sys_stack:
