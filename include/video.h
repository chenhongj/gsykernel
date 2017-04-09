#ifndef __VIDEO_H
#define __VIDEO_H

#include <type.h>

void cls();
void putch(int8 c);
void puts(char * str);
void settextcolor(uint8 forecolor, uint8 backcolor);
void init_video();

#endif
