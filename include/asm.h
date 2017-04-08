 #ifndef __ASM_H
 #define __ASM_H

 #include <type.h>

 uint8 inb(uint16 _port);
 void outb(uint16 _port, uint8 _data);
 uint16 inw (uint16 port);
 void outw (uint16 port, uint16 data);

 void hlt();
 void sti();
 void cli();

 #endif
