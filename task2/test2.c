#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Program basladi!!\n");

    FILE *input;
    input = fopen("katar.txt","r");


    //char sayisi hesaplama
    fseek(input, 0, SEEK_END); // dosyanin sonuna git
    int size = ftell(input); // gecerli dosyanýn sonundaki general.sizeu size'a kaydet
    fseek(input, 0, SEEK_SET); // basa geri donuyorum
    size = size /sizeof(char);
    char test[size];


 //okuma
    int sayac = 0;
    while(!feof(input))
    {
        fscanf(input,"%c",&test[sayac]);
        sayac++;
    }

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    int say = 0;
    while(size>say)
    {
        int a = say;
        printf("%d)",(say+1));

        for(;a<size;a++)
        {
            //katarın bir sonekinin her karakterini yazma
            printf("%c",test[a]);
        }

        //bir sonraki sonege gecis
        printf("\n");
        say++;
    }

    printf("Bu katarin sonek sayisi : %d",say);






    return 0;
}
