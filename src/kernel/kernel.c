#include <arch.h>
#include <klog.h>
#include <kevent.h>
#include <video.h>
#include <stdio.h>
#include <asm.h>

char a[10] = "qwer";
void kernel_init()
{
    arch_init();

    puts("all done\n");
    while(1);
}
