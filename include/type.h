#ifndef __TYPE_H
#define __TYPE_H

#define true            ((unsigned char)1)
#define false           ((unsigned char)0)
#define NULL            (void *)0
#define NUL             '\0'

typedef long long int64;
typedef unsigned long long uint64;
typedef int             int32;
typedef unsigned int    uint32;
typedef short           int16;
typedef unsigned short  uint16;
typedef char            int8;
typedef unsigned char   uint8;
typedef char *          pstr;
typedef char *          pchar;
typedef unsigned char   byte;
typedef unsigned char   bool;

//中断服务程序启动后要保留的寄存器信息结构
struct regs
{
    uint32 gs, fs, es, ds;//压入上一个段
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;//由pusha来压栈
    uint32 int_no, err_code;//由push  byte和编码压入
    uint32 eip, cs, eflags, useresp, ss;//处理器自动压入
};

#endif

