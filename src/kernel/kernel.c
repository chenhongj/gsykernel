#include <arch.h>
#include <klog.h>
#include <kevent.h>

void kernel_init()
{
    arch_init();

//    kernel_log_init();

//    kernel_event_init();

    while(1);
}
