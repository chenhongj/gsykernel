#ifndef __STRING_H__
#define __STRING_H__

#include <type.h>

void itoa(int in, char * buf);
void utoa(uint32 in, char * buf);
int strlen(char * str);
uint8 *memcpy(uint8 *dest, const uint8 *src, int count);
uint8 *memset(uint8 *dest, uint8 val, int count);
uint16 *memsetw(uint16 *dest, uint16 val, int count);

#endif
