#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        puts("need 2 argument");
        puts("mbrcp src dst");
        return 1;
    }

    FILE *src = NULL;
    FILE *dst = NULL;
    
    src = fopen(argv[1], "rb");
    if(src == NULL)
    {
        perror(argv[1]);
        return 1;
    }
    
    dst = fopen(argv[2], "rb+");
    if(dst == NULL)
    {
        perror(argv[2]);
        return 1;
    }
    
    fseek(dst, 512, SEEK_SET);
    
    int ch = 0;
    while(1)
    {
        ch = fgetc(src);
        if (ch == EOF)
            break;
        fputc(ch, dst);
    }
    
    fclose(src);
    fclose(dst);
    return 0;
}

