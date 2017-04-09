#ifndef __TYPE_H
#define __TYPE_H

#define true            ((unsigned char)1)
#define false           ((unsigned char)0)
#define NULL            ((void *)0)
#define NUL             ('\0')

#define BIT0            0x1
#define BIT1            0x2
#define BIT2            0x4
#define BIT3            0x8
#define BIT4            0x10
#define BIT5            0x20
#define BIT6            0x40
#define BIT7            0x80
#define BIT8            0x100
#define BIT9            0x200
#define BIT10           0x400
#define BIT11           0x800
#define BIT12           0x1000
#define BIT13           0x2000
#define BIT14           0x4000
#define BIT15           0x8000
#define BIT16           0x10000
#define BIT17           0x20000
#define BIT18           0x40000
#define BIT19           0x80000
#define BIT20           0x100000
#define BIT21           0x200000
#define BIT22           0x400000
#define BIT23           0x800000
#define BIT24           0x1000000
#define BIT25           0x2000000
#define BIT26           0x4000000
#define BIT27           0x8000000
#define BIT28           0x10000000
#define BIT29           0x20000000
#define BIT30           0x40000000
#define BIT31           0x80000000

#define PTOU32(x)    ((uint32)((void *)(x)))

typedef long long           int64;
typedef unsigned long long  uint64;
typedef int                 int32;
typedef unsigned int        uint32;
typedef short               int16;
typedef unsigned short      uint16;
typedef char                int8;
typedef unsigned char       uint8;
typedef char *              pstr;
typedef char *              pchar;
typedef unsigned char       byte;
typedef unsigned char       bool;

#endif
