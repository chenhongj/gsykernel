#include <video.h>
#include <string.h>
#include <asm.h>

static uint16 *textmemptr;
static int32 csr_x = 0, csr_y = 0;
static uint16 blank = ' ' | 0x0700;
//低8位为ascaii码，高8位为属性
//属性高4字节设置背景，低4字节设置前景

//字符界面大小为80x25
//滚屏
void scroll(void)
{
    if(csr_y >= 25)//该滚屏了
    {
        //把视频内存中整体转移，覆盖掉了第一行，就达到滚屏的目的，两个字节确定一个像素点
        int temp = csr_y - 25 + 1;
        memcpy ((uint8 *)textmemptr, (uint8 *)(textmemptr + temp * 80), (25 - temp) * 80 * 2);

        //设置最后的空余全为黑色
        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

//更新光标的位置
void move_csr(void)
{
    uint16 temp = csr_y * 80 + csr_x;//二维光标位置转化为一维表示

    //http://www.brackeen.com/home/vga
    //通过分别写入高八位和低八位的方式来设置光标位置
    outb(0x3D4, 14);
    outb(0x3D5, temp >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, temp);
}

//清屏
void cls()
{
    //用blank覆盖调视频的内存位置
    for(int i = 0; i < 25; i++)
        memsetw (textmemptr + i * 80, blank, 80);
    //清屏后重设光标位置
    csr_x = 0;
    csr_y = 0;
    move_csr();
}

//输出一个字符
void putch(int8 c)
{
    uint16 *where;
    if(c == '\b')           //退格字符,退一格
    {
        if(csr_x > 0)
            csr_x--;
        where = textmemptr + (csr_y * 80 + csr_x);
        *where =  blank;
    }
    else if(c == '\t')      //制表符，设置成8个格
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    else if(c == '\r')      //回车符，回到行首
    {
        csr_x = 0;
    }
    else if(c == '\n')      //换行符，到下一行
    {
        csr_x = 0;
        csr_y++;
    }
    else                    //其他任何字符直接输出
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | 0x0700;
        csr_x++;
    }

    if(csr_x >= 80)         //回车且换行
    {
        csr_x = 0;
        csr_y++;
    }

    //显示到屏幕上，并移动光标
    scroll();
    move_csr();
}

//设置video所在内存地址
void video_init(void)
{
    textmemptr = (uint16 *)0xB8000;
    cls();
}
