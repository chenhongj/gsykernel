#include <stdio.h>
#include <string.h>
#include <video.h>

//输出字符串
void puts(char* str)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        putch(str[i]);
    }
}

int printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int index;
    uint32 tmp;
    char buf[128];

    //unpack string fomat
    for(index = 0;; index++)
    {
        if( *(format + index) == NUL)
            break;
        else if( *(format + index) == '%' )
        {
            switch(*(format + ++index))
            {
                case 'd':
                    tmp = va_arg(args, int32);
                    itoa(tmp, buf);
                    puts(buf);
                    break;
                case 's':
                    tmp = PTOU32(va_arg(args, char*));
                    puts((char*)tmp);
                    break;
                case 'c':
                    tmp = va_arg(args, char);
                    putch(tmp);
                    break;
                case 'u':
                    tmp = va_arg(args, uint32);
                    utoa(tmp, buf);
                    puts(buf);
                    break;
                case '%':
                    putch('%');
                    break;
                default:
                    break;
            }
        }
        else
            putch(*(format + index));

    }

    va_end(args);
    return 1;
}
