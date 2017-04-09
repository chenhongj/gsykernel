#include <string.h>

void itoa(int32 in, char* buf)
{
    if(in < 0)
    {
        buf[0] = '-';
        in *= -1;
    }

    int len;
    for(len=0; in != 0; len++)
    {
        buf[len] = '0' + (in % 10);
        in /= 10;
    }

    int t = len / 2;
    for(int i=0; i<t; i++)
    {
        char tmp;
        tmp = buf[i];
        buf[i] = buf[len - 1 - i];
        buf[len - 1 - i] = tmp;

    }
    buf[len] = NUL;
}

void utoa(uint32 in, char* buf)
{
    int len;
    for(len=0; in != 0; len++)
    {
        buf[len] = '0' + (in % 10);
        in /= 10;
    }

    int t = len / 2;
    for(int i=0; i<t; i++)
    {
        char tmp;
        tmp = buf[i];
        buf[i] = buf[len - 1 - i];
        buf[len - 1 - i] = tmp;

    }
    buf[len] = NUL;

}

int strlen(char* str)
{
    int len = 0;
    while(*(str++))
        len++;
    return len;
}

//实际复制字节数（目标地址， 源地址， 字节数）
inline uint8 *memcpy(uint8 *dest, const uint8 *src, int size)
{
    while(size--)
        *(dest++)=*(src++);
    return NULL;
}

inline uint8 *memset(uint8 *dest, uint8 val, int count)
{
    while(count--)
        *(dest++)=val;
    return NULL;
}

inline uint16 *memsetw(uint16 *dest, uint16 val, int count)
{
    while(count--)
        *(dest++)=val;
    return NULL;
}
