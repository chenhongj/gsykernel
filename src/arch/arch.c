#include <arch.h>
#include <asm.h>
#include <video.h>

void arch_init()
{
    cli();
    gdt_init();
    video_init();
    idt_init();
    irq_init();
    sti();
}
