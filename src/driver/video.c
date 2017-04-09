#include <video.h>


uint16 *textmemptr;
int32 attrib = 0x0F;
int32 csr_x = 0, csr_y = 0;

//字符界面大小为80x25
//看看是不是需要滚屏
void scroll(void)
{
    int32 blank, temp;

    //黑色背景
    blank = 0x20 | (attrib << 8);

    //该滚屏了
    if(csr_y >= 25)
    {
        //我们把视频内存中整体转移，覆盖掉了第一行，就达到滚屏的目的，两个字节确定一个像素点
        temp = csr_y - 25 + 1;
        memcpy ((uint8 *)textmemptr, (uint8 *)(textmemptr + temp * 80), (25 - temp) * 80 * 2);

        //设置最后的空余全为黑色
        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

//更新光标的位置
void move_csr(void)
{
    uint32 temp;

    //二维光标位置转化为一维表示
    temp = csr_y * 80 + csr_x;

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
    uint32 blank;
    int32 i;

    //当然用黑色来清屏拉
    blank = 0x20 | (attrib << 8);

    //实际上就是用黑色覆盖调视频的内存位置
    for(i = 0; i < 25; i++)
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
    uint32 att = attrib << 8;

    //退格字符,退一格
    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
         where = textmemptr + (csr_y * 80 + csr_x);
        *where = ' ' | att;	/* Character AND attributes: color */
    }
    //TAB字符，我们设置成8个格
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    //回车符，回到行首
    else if(c == '\r')
    {
        csr_x = 0;
    }
    //换行符，到下一行
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    //其他任何字符直接输出
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }

    //输出到头了，我们要换行
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    //显示到屏幕上，并移动光标
    scroll();
    move_csr();
}

//输出字符串
void puts(char * text)
{
    int32 i;
    int32 l = strlen(text);

    for (i = 0; i < l; i++)
    {
        putch(text[i]);
    }
}

//设置背景和前景颜色
void settextcolor(uint8 forecolor, uint8 backcolor)
{
    //高4字节设置背景，低4字节设置前景
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

//设置video所在内存地址
void init_video(void)
{
    textmemptr = (uint16 *)0xB8000;
    cls();
}
