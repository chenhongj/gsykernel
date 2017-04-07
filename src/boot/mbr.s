 ;MBR
org     0x7c00
bits    16

;在0x600 0x601 两字节保存总内存大小
;0x602一个字节保存扫描到的布局数
;0x603开始保存布局信息
;
section .text
;扫描内存布局
probe_mem:
    ;先获取总内存大小
    mov ah, 0x88
    int 0x15
    mov [0x600], ax
    
    ;扫描布局
    mov bx, cs
    mov es, bx                ;目标段基址
    mov di, 0x603             ;从0x603开始，0x602保存扫描到的布局个数，0x600-0x601保存总内存大小
probe_start:    
    mov eax, 0xe820           ;e820中断
    mov edx, "PAMS"           ;'SMAP'
    mov ecx, 20               ;使用20个字节储存数据
    
    int 0x15
    jc bios_error
    
    cmp ebx, 0
    je load_head
    
    add di, 20
    mov [0x602], bl            ;保存个数
    jmp probe_start
    
;从硬盘加载内核到0x10000处
load_head:
    mov dh, 0       ;磁头
    mov ch, 0       ;柱面
    mov cl, 0x02    ;扇区,扇区编号从1开始
    mov dl, 0x80    ;0号硬盘
    mov ax, 0x1000  ;计算地址时需要左移4位
    mov es, ax
    xor bx, bx      ;内核读入到es：bx
    mov ah, 0x02    ;13号中断的02功能
    mov al, 10      ;读入的扇区数量
    int 0x13
    jc bios_error   ;读取失败就死机
    
;进入32位保护模式
ok:
    lidt [idtr_p]
    lgdt [gdtr_p]
    
    mov ax, 0x0001
    lmsw ax             ;置位保护模式，已经进入保护模式，下面使用段选择符来跳转到
    jmp dword 0x00000008:0x00010000

bios_error:
    jmp $

gdt:
    ;描述符0。
    dw 0,0,0,0  ;空描述符

    ;描述符1。
    dw 0x07FF   ;长度，给8M，进入保护模式再换
    dw 0x0000   ;基址
    dw 0x9A00   ;代码段，可读可执行
    dw 0x00c0   ;粒度，4KB
    
    ;描述符2。
    dw 0x07FF   ;长度，给8M，进入保护模式再换
    dw 0x0000   ;基址
    dw 0x9200   ;数据段，可读可写
    dw 0x00c0   ;粒度，4KB

gdtr_p: 
    dw ($-gdt)    ;存放3个描述符的长度
    dd gdt ;基地址

idtr_p:
    dw 0
    dd 0
    
    times 510 - ($-$$) db 0
    dw 0xAA55;bootable
