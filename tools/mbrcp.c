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
    
    int ch = 0;
    for (int i = 0; i < 512; i++)
    {
        ch = fgetc(src);
        fputc(ch, dst);
    }
    
    fclose(src);
    fclose(dst);
    return 0;
}
