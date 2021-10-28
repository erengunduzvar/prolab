#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");

    char adana[5];
    gets(adana);

    for(int a=1;a<6/*string boyutu+1*/;a++)
    {
        printf("%d)",a);
        for(int b=0;b<a;b++)
        {
            printf("%c",adana[b]);
        }
        printf("\n");
    }



    return 0;
}
