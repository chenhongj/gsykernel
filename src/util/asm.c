#include <asm.h>

inline uint8 inb(uint16 port)
{
    uint8 rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

inline void outb(uint16 port, uint8 data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

inline void outw (uint16 port, uint16 data)
{
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (port), "a" (data));
}

inline uint16 inw (uint16 port)
{
    uint16 rv;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

inline void cli()
{
    __asm__ __volatile__ ("cli");
}

inline void sti()
{
    __asm__ __volatile__ ("sti");
}

inline void hlt()
{
    __asm__ __volatile__ ("hlt");
}
