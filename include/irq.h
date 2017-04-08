#ifndef __IRQ_H__
#define __IRQ_H__

#include <type.h>

void irq_init();
void irq_handler(struct regs *r);
void irq_set_handle(int32 irq, void (*handle)(struct regs *r));
void irq_reset_handle(int32 irq);
void irq_remap(void);

#endif

