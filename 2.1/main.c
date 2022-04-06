#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC



typedef struct totalLocationComplexity
{
    int one; //derece
    int two;
    int three;
    int four;
    int five;
}totalLocationComplexity;



typedef struct LoopList {
    struct LoopList *next; //kendinden sonraki loopu tutar !
    struct LoopList *previous;
    struct LoopList *parent;//kendinden onceki parentini tutar !
    char loopType[100]; //For /While //Switch
    char desc[100];
    bool isClosed,first,isRecursive,isMethod;
    int startLine,startIndex,finishIndex,finishLine,loopID;
    int timeComplexity;



} LoopList;
int openBrackets = 0;
int closeBrackets = 0;
int lineNumber = 1;
int recursive = 0;
int loopID = 1;
char aritmethicOperators[] = {'+','-','*','/','%'};
char relationalOperators[][2] = {{'=','='},{'>',' '},{'<',' '},{'!','='},{'>','='},{'<','='}};
LoopList *lastDo = NULL;
int memoryComplexityAddition;  //katsayi //derece //fazlalik
int totalTimeComplexity = 0;
totalLocationComplexity TotalLocationComplexity;
LoopList *startOfTheList;
int localTimeComplexivity = 0;

void addToLoopList(LoopList *list,char loopType[100],bool isMethod,char desc[100])
{


    if(list->first == true)//ilk eleman
    {
        memset(list->loopType,0,100);
        memset(list->desc,0,100);
        strncpy(list->loopType,loopType, strlen(loopType));
        list->parent = NULL;

        if(strcmp(loopType,"switch") == 0 || strcmp(loopType,"if") == 0)
            list->timeComplexity = 0;
        else
            list->timeComplexity = 1;

        list->first = false;
        list->loopID = loopID;
        list->isMethod = isMethod;
        loopID++;
        list->startLine = -1;
        list->finishLine = -1;



        if(isMethod == true) // Eger metodsa tekrar degerini false a ayarla
        {
            list->isRecursive = false;
        }



        if(desc != NULL)    // Eger fonksiyona bir desc degeri girerse listede yerine koy hiamina
            strcpy(list->desc,desc);
        if(strcmp(loopType,"do") == 0)
        {
            printf("Do while do'su bulundu.\n");
            lastDo = list;
        }
    }
    else
    {



        start:
        if(list->next == NULL)
        {
            //Loop Confugiration
            list->next = malloc(sizeof(LoopList));
            memset(list->next->loopType,0,100);
            memset(list->next->desc,0,100);
            strncpy(list->next->loopType,loopType, strlen(loopType));


            if(strcmp(loopType,"switch") == 0 || strcmp(loopType,"if") == 0)
                list->next->timeComplexity = 0;
            else
                list->next->timeComplexity = 1;


            list->next->previous = list;
            list->next->next = NULL;
            list->next->isMethod = isMethod;
            list->next->loopID = loopID;
            list->next->startLine = -1;
            list->next->finishLine = -1;
            loopID++;



            if(isMethod == true)
            {
                list->next->isRecursive = false;
            }



            if(strcmp(loopType,"do") == 0)
            {
                printf("Do while do'su bulundu.\n");
                lastDo = list->next;
            }



            //Loop Relations :
            //önceki loopun ucu acık mı ?
            if(list->isClosed == false) // eski olan list , yeni üye list->next // onceki dongu acık
            {
                printf("%d ninci loop %d ninci loop tarafindan kapsanir.\n",list->next->loopID,list->loopID);
                list->next->parent = list;
            }

            else if (closeBrackets - openBrackets == 0) //bagımsız komsu //onceki loop metodun altındadır kapsanmıyordur !  yine main metodudun altındadır ve kapsanmaz
            {
                if(lineNumber == 15)
                    printf("zort");

                printf("%d idli loop kapsanmaz looptur\n",list->next->loopID);
                list->next->parent = NULL;
            }

            else if(closeBrackets - openBrackets != 0)//bagımlı komsu
            {
                printf("%d ninci loop %d ninci loopun parentini(%d) miras alir\n",list->next->loopID,list->loopID,list->parent->loopID);
                list->next->parent = list->parent;
            }

        }
        else
        {
            list = list->next;
            goto start;
        }
    }
}
int timeComplexivity(LoopList *list)
{
    LoopList *iterationList;

    iterationList = list;

    while(iterationList != NULL)
    {
        list = iterationList;
        while(list != NULL)
        {
            if(list->isMethod == false && list->finishLine != -1)
                localTimeComplexivity += list->timeComplexity;
            list = list->parent;
        }
        if(totalTimeComplexity < localTimeComplexivity)
        {
            totalTimeComplexity = localTimeComplexivity;
        }
        localTimeComplexivity = 0;

        iterationList = iterationList->next;
    }


    return (totalTimeComplexity);
}


int metodCheck(const char processedInput[100],char desc[100],int start,LoopList *list)
{
    char metodType[100];
    memset(metodType, 0, 100);
    bool wordStarted = false;
    LoopList *startOfTheList = list;

    int k = 0;
    for (int i = start - 1 ; i > -1; --i) {

        if(processedInput[i] == ' ' || processedInput[i] == '\t' || processedInput[i] == '+' || processedInput[i] == '-' || processedInput[i] == '=' || processedInput[i] == '*' || processedInput[i] == '/' || processedInput[i] == '% ') //boslugu okuma
        {
            if(wordStarted != false)
                break;
        }

        else
        {
            metodType[k] = processedInput[i]; //tanimin basladigi yerden itibaren bosluga kadar kelimeyi oku
            k++;
            wordStarted = true;
        }
    }

    {
        char temp[strlen(metodType)]; //kelimeyi belleğe ters aldigin icin cevir !
        strcpy(temp,metodType);
        for (int i = 0; i < strlen(metodType); i++) {
            metodType[i] = temp[(k-1) - i];
        }
    }
    if(strcmp("rows",metodType) == 0)
        totalTimeComplexity = 2;

    printf("Bulunan metodun ismi : %s\n",metodType);

    char loops[8][8];
    memset(loops, 0, 64);

    strcpy(loops[0],"for");
    strcpy(loops[1],"while");
    strcpy(loops[2],"switch");
    strcpy(loops[3],"do");
    strcpy(loops[4],"else");
    strcpy(loops[5],"main");
    strcpy(loops[6],"printf");
    strcpy(loops[7],"if");

    for (int i = 0;i < 8;i++) {
        if(strncmp(metodType,loops[i],strlen(loops[i])) == 0)
        {
            if(i > 4)
            {
                printf("Generic Metod (%s)\n",metodType);
                return 1;
            }
            else
            {
                while(true)
                {
                    if(list->next == NULL)
                    {
                        for (int j = 0; j < strlen(desc); ++j) {
                            if(desc[j] == '*' || desc[j] == '/')
                            {
                                recursive++;
                            }
                        }

                        strncpy(list->desc,desc, strlen(desc));
                        return -1;
                    }

                    else
                        list = list->next;
                }
            }
        }
    }
    if(strcmp(list->loopType,metodType) == 0 && list->isClosed == false) //onceden tanimli metodu kendi icinde yakaliyor.
    {
        printf("Dosyanin rekursifligi kanitlandi\n");
        list->isRecursive = true;
        //2  localTimeComplexivity++;
        return 3;
        //degisim nerede onu bul faruk abi !;
    }
    list = startOfTheList;



    while(list != NULL)
    {
        if(strcmp(list->loopType,metodType) == 0)
        {
            printf("Daha once tanimlanmis bir metodun kullanimi\n");
            return 4;
        }
        list = list->next;
    }
    list = startOfTheList;



    addToLoopList(list,metodType,true,desc);
    return 2;
}
void findDescription(char processedInput[100],LoopList *list,int i)
{
    char desc[100];
    memset(desc, 0, 100);
    int start,finish;

    for (int j = i; j < strlen(processedInput); j++) {

        if('(' == processedInput[j]) //Desc basi
        {
            start = j;
            for (int k = 0; k < 999; k++) {
                desc[k] = processedInput[j+k];
                if(')' == processedInput[j+k])
                {
                    finish = j+k;
                    break;
                }

            }

            printf("%d - %d indexleri arasinda %s bulundu\n",start,finish,desc);

            switch (metodCheck(processedInput,desc,start,list)) {
                case -1: //loop durumu
                    printf("Loop var\n");
                    break;
                case 1:
                    break;
                case 2:
                    printf("Standart metod \n");
                    break;
                case 3:
                    printf("Tanimli rekursifin kullanilmasi.\n");
                    break;
                default:
                    break;
            }
        }
    }
}
void findEndBrackets(char processedInput[100],int i,LoopList *list) //Metodun nerede bittigini bulur
{
    startOfTheList = list;
    if(openBrackets - closeBrackets == 0)
        return;

    LoopList *lastOpenLoop;
    lastOpenLoop = malloc(sizeof(LoopList));
    for (int j = i; j < strlen(processedInput); j++) {

        if('}' == processedInput[j])
        {

            start:

            if(list->isClosed == false && list->timeComplexity != 0)//kapanmamis
            {
                lastOpenLoop = list;
            }

            if(list->next == NULL) //listenin son elemaninda miyim ?
            {

                lastOpenLoop->finishLine = lineNumber;
                lastOpenLoop->finishIndex = j;
                lastOpenLoop->isClosed = true;
            }
            else
            {
                list = list->next;
                goto start;
            }

            //kapsayici
            printf("%d. satirin %dninci indexinde Finish koseli parentezi bulundu.\n",lineNumber,j);

            if(lastOpenLoop->isMethod == true)
            {
                if(lastOpenLoop->isRecursive == true)
                    printf("%d idli metod rekursiftir\n",lastOpenLoop->loopID);
                else
                {
                    printf("%d idli metod rekursif olmadigi icin karmasiklik hesaplayiciya girmez !\n",lastOpenLoop->loopID);
                    list = lastOpenLoop->previous;
                    free(lastOpenLoop->next);
                    lastOpenLoop->next = NULL;
                }
            }

            //algoritmik karmaşıklık hesaplayici !!




            closeBrackets++;
        }

    }





    //time n hesabi misali timsali reksaii
}


void findStartBrackets(char processedInput[100],int i,LoopList *list) //Metodun nerede basladigini bulur
{
    if(list->loopID < 1)
        return;
    for (int j = i; j < strlen(processedInput); j++) {

        if('{' == processedInput[j])
        {
            start:
            if(list->next == NULL)
            {
                list->startLine = lineNumber;
                list->isClosed = false;
                list->startIndex = j;
            }
            else
            {
                list = list->next;
                goto start;
            }

            printf("%d. satirin %d ninci indexinde Start koseli parentezi bulundu.\n",lineNumber,j);
            openBrackets++;

        }
    }
}
void definitionChecker(char processedInput[100],LoopList *list,int start,int veriBoyutu) //Return 1 metod baslangici
{

    for (int i = 0; i < strlen(processedInput); i++) {
        if(processedInput[i] == '(')
        {
            printf("Metod baslangici bulundu !\n"); //for var !
            return;
        }
    }

    int HowMuchDefAdded = 0;
    int HowMuchMatrixDimension = 0;

    for (int i = start; i < strlen(processedInput) ; i++) {
        if(processedInput[i] == ']')
            HowMuchMatrixDimension++; //matrix boyutunu tutar
        if(processedInput[i] == ',' && processedInput[i-1] != ']')
            HowMuchDefAdded++;      //satirda tanimlanan veri miktarini tutar

        if(processedInput[i] == ',' && processedInput[i-1] == ']')
        {
            switch (HowMuchMatrixDimension) {
                case 1:
                    TotalLocationComplexity.one += veriBoyutu;
                    break;
                case 2:
                    TotalLocationComplexity.two += veriBoyutu;
                    break;
                case 3:
                    TotalLocationComplexity.three += veriBoyutu;
                    break;
                case 4:
                    TotalLocationComplexity.four += veriBoyutu;
                    break;
                case 5:
                    TotalLocationComplexity.five += veriBoyutu;
                    break;
                default:
                    printf("5 den buyuk matris algilayamam \n");
                    break;
            }
            HowMuchMatrixDimension = 0;

        }
        if(processedInput[i] == ';' && processedInput[i-1] != ']')
            HowMuchDefAdded++;
    }

    if(HowMuchMatrixDimension != 0)
    {
        switch (HowMuchMatrixDimension) {
            case 1:
                TotalLocationComplexity.one += veriBoyutu;
                break;
            case 2:
                TotalLocationComplexity.two += veriBoyutu;
                break;
            case 3:
                TotalLocationComplexity.three += veriBoyutu;
                break;
            case 4:
                TotalLocationComplexity.four += veriBoyutu;
                break;
            case 5:
                TotalLocationComplexity.five += veriBoyutu;
                break;
            default:
                printf("Bu program 5 den daha buyuk matris hesaplayamaz");
                break;
        }
    }



    memoryComplexityAddition += HowMuchDefAdded * veriBoyutu;

//metod sonu
}



void findComplexityChange(char processedInput[100],LoopList *list)
{
    //Definition tanimlari : int char double long
    char defs[7][7];
    memset(defs,0,49);
    strcpy(defs[0],"int");
    strcpy(defs[1],"char");
    strcpy(defs[2],"double");
    strcpy(defs[3],"long");
    strcpy(defs[4],"float");
    strcpy(defs[5],"short");
    strcpy(defs[6],"return");

    for (int a = 0; a < 7; a++) { //loop types

        if(strlen(defs[a]) > strlen(processedInput)) //aranan kelime aranan cumleden daha buyukse donguye girme
            break;

        for (int i = 0; i < (strlen(processedInput) - (strlen(defs[a]) - 1)); i++) {
            //printf("%d) %c%c%c\n",i,processedInput[i],processedInput[i+1],processedInput[i+2]);

            char letters[strlen(defs[a])];

            for (int j = 0; j < strlen(defs[a]); ++j) {
                letters[j] = processedInput[i+j];
            }

            if(strncmp(defs[a],letters,strlen(defs[a])) == 0 )
            {
                printf("%d. satirin %d ninci indexinde %s Buldum \n",lineNumber,i,defs[a]);
                LoopList *lastMethod = NULL;

                switch (a) {
                    case 0://int
                        definitionChecker(processedInput,list,i+ strlen(defs[a]), sizeof(int));
                        return;
                    case 1: //char
                        definitionChecker(processedInput,list,i+ strlen(defs[a]), sizeof(char));
                        return;
                    case 2://double
                        definitionChecker(processedInput,list,i+ strlen(defs[a]), sizeof(double));
                        return;
                    case 3://long
                        definitionChecker(processedInput,list,i+ strlen(defs[a]), sizeof(long));
                        return;
                    case 4://float
                        definitionChecker(processedInput,list,i+ strlen(defs[a]), sizeof(float));
                        return;
                    case 5://short
                        definitionChecker(processedInput,list,i+ strlen(defs[a]), sizeof(short));
                        return;
                    case 6: //return
                    {
                        while(list != NULL)
                        {
                            if(list->isMethod == true && list->isClosed != true)
                            {
                                lastMethod = list;
                                list = list->next;
                            }
                            else
                                list = list->next;
                        }

                        //rekursif fonksiyon check ;
                        if(lastMethod == NULL) //metod bulamadiysan;
                            break;
                        else
                        {
                            for (int j = 0; j < 6; j++) {
                                for (int k = 0; k < strlen(processedInput); k++) {
                                    if(processedInput[k] == aritmethicOperators[j])
                                    {
                                        printf("Return degerinde aritmetik operator bulundu.");
                                        localTimeComplexivity++;
                                        //kodu buradan soktun unutma.

                                        TotalLocationComplexity.one++;
                                        return;
                                    }

                                }

                            }
                        }
                    }
                    default:
                        break;
                }
            }
        }
    }
}
void findSwitch(char processedInput[100],LoopList *list)
{
    for (int i = 0; i < (strlen(processedInput) - (strlen("switch") - 1)); i++) {
        //printf("%d) %c%c%c\n",i,processedInput[i],processedInput[i+1],processedInput[i+2]);
        char letters[strlen("switch")];
        for (int j = 0; j < strlen("switch"); ++j) {
            letters[j] = processedInput[i+j];
        }
        if(strncmp("switch",letters,strlen("switch")) == 0 )
        {
            printf("%d. satirin %d ninci indexinde switch Buldum \n",lineNumber,i);

            addToLoopList(list,"switch",false,NULL);
            return;
        }
    }
}

void findIf(char processedInput[100],LoopList *list)
{
    for (int i = 0; i < (strlen(processedInput) - (strlen("if") - 1)); i++) {
        //printf("%d) %c%c%c\n",i,processedInput[i],processedInput[i+1],processedInput[i+2]);
        char letters[strlen("if")];
        for (int j = 0; j < strlen("if"); ++j) {
            letters[j] = processedInput[i+j];
        }
        if(strncmp("if",letters,strlen("if")) == 0 )
        {
            printf("%d. satirin %d ninci indexinde if Buldum \n",lineNumber,i);

            addToLoopList(list,"if",false,NULL);
            return;
        }
    }
}

void findWhile(char processedInput[100],LoopList *list)
{
    if(lineNumber == 12)
        printf("null");

    for (int i = 0; i < (strlen(processedInput) - (strlen("while") - 1)); i++) {
        //printf("%d) %c%c%c\n",i,processedInput[i],processedInput[i+1],processedInput[i+2]);

        char letters[strlen("while")];

        for (int j = 0; j < strlen("while"); ++j) {
            letters[j] = processedInput[i+j];
        }

        if(strncmp("while",letters,strlen("while")) == 0 )
        {
            printf("%d ninci satirin %d ninci indexinde While Buldum \n",lineNumber,i);

            if(lastDo != NULL) //doWhileSyndrome
            {
                strcpy(lastDo->loopType,"while");
                lastDo = NULL;
            }
            else
            {
                addToLoopList(list,"while",false,NULL);
            }
        }
    }
}
void findFor(char processedInput[100],LoopList *list)
{
    for (int i = 0; i < (strlen(processedInput) - (strlen("for") - 1)); i++) {
        //printf("%d) %c%c%c\n",i,processedInput[i],processedInput[i+1],processedInput[i+2]);

        char letters[strlen("for")];

        for (int j = 0; j < strlen("for"); ++j) {
            letters[j] = processedInput[i+j];
        }

        if(strncmp("for",letters, strlen("for")) == 0 )
        {
            printf("%d ninci satirin %d ninci indexinde for Buldum \n",lineNumber,i);
            addToLoopList(list,"for",false,NULL);
        }
    }
}
void findDo(char processedInput[100],LoopList *list)
{
    for(int i = 0; i < (strlen(processedInput) - (strlen("do") - 1)); i++) {
        //printf("%d) %c%c%c\n",i,processedInput[i],processedInput[i+1],processedInput[i+2]);

        char letters[strlen("do")];

        for(int j = 0; j < strlen("do"); ++j) {
            letters[j] = processedInput[i+j];
        }

        if(strncmp("do",letters, strlen("do")) == 0 )
        {
            printf("%d ninci satirin %d ninci indexinde do Buldum \n",lineNumber,i);
            addToLoopList(list,"do",false,NULL);
        }
    }
}
void findComponents(char processedInput[100],LoopList *list)
{
    findEndBrackets(processedInput,0,list);
    if(strlen(processedInput) > 1)
    {
        findDo(processedInput,list);
        findIf(processedInput,list);
    }
    if(strlen(processedInput) > 2)
        findFor(processedInput,list);
    if(strlen(processedInput) > 4)
        findWhile(processedInput,list);
    if(strlen(processedInput) > 5)
        findSwitch(processedInput,list);
    findDescription(processedInput,list,0);
    findStartBrackets(processedInput,0,list);
    findComplexityChange(processedInput,list);




}


void getLine()
{
    FILE *input;
    input = fopen("input.txt","r");

    char rawInput[100];
    char processedInput[100];


    LoopList *list = malloc(sizeof(LoopList)); //ilk liste elemanı null !
    list->first = true;
    list->next = NULL;


    while (!feof(input))
    {
        memset(rawInput, 0, 100);
        memset(processedInput, 0, 100); //Listeyi tamamen sifirlar

        fgets(rawInput,100,input);
        for (int i = 0; i < (strlen(rawInput)-1); i++) { //sondaki /n charini temizler
            processedInput[i] = rawInput[i];
        }

        /*printf("Asil cekilen stringin boyutu : %d\n",strlen(rawInput));
        printf("Temizlenmis stringin boyutu  : %d\n",strlen(processedInput));*/
        printf("\n\n\nTemizlenmis string %s\n",processedInput);

        findComponents(processedInput,list);
        lineNumber++;
    }

    // int lastTimeComplexivity = timeComplexivity(list);

    printf("Yer karmasikligi: ");
    if(TotalLocationComplexity.five != 0)
        printf("%dn^5 + ",TotalLocationComplexity.five);
    if(TotalLocationComplexity.four != 0)
        printf("%dn^4 + ",TotalLocationComplexity.four);
    if(TotalLocationComplexity.three != 0)
        printf("%dn^3 + ",TotalLocationComplexity.three);
    if(TotalLocationComplexity.two != 0)
        printf("%dn^2 + ",TotalLocationComplexity.two);
    if(TotalLocationComplexity.one != 0)
        printf("%dn + ",TotalLocationComplexity.one);
    printf("%d  ",memoryComplexityAddition);
    if(timeComplexivity(list) == 0 && recursive == 0)
        printf("O(1)\n");
    else if(timeComplexivity(list) == 0 && recursive != 0)
        printf("O(log%d n)\n",recursive+1);

    else if(timeComplexivity(list) == 1)
        printf(" O(n)\n");
    else
        printf("O(n^%d)\n", timeComplexivity(list));

    if(timeComplexivity(list) == 0 && recursive == 0)
        printf("Zaman karmasikligi = O(1)\n");

    else if(timeComplexivity(list) == 0 && recursive != 0)
        printf("Zaman karmasikligi = O(log%d n)\n",recursive+1);

    else if(timeComplexivity(list) == 1)
        printf("Zaman karmasikligi = O(n)\n");
    else
        printf("Zaman karmasikligi = O(n^%d)\n", timeComplexivity(list));


}
void calculateRuntime()
{
    system("gcc input.c -o input");
    printf("\nDerleme Basarili\nKodun ciktisi : ");

    clock_t basla = clock();
    system("input");
    clock_t bitir = clock();

    double gecenSure = (double) (bitir - basla)/CLOCKS_PER_SEC;
    printf("\nKodun calisma suresi: %f\n",gecenSure);
}
void runtimeTester()
{
    FILE *input,*runtime;
    input = fopen("input.txt","r");
    runtime = fopen("input.c","w");
    char line[80];
    memset(line,0,80);
    while (!feof(input))
    {
        fgets(line,80,input);
        fputs(line,runtime);

    }
    fclose(input);
    fclose(runtime);
    calculateRuntime();
}
int main() {
    int mainMenu;
    StartmainMenu:

    printf("\n\n\n\n\n\n\n\n1 )Dosya icerisinden kodu okunmasi ve dosyanin iceriginin kontrol edilmesi\n");
    printf("2 )Dosyadan okunan kod Big O notasyonuna gore Zaman karmasikligi ve yer (Hafiza) karmasikliginin hesaplanmasi\n");
    printf("3 )Calisma zamaninin hesaplanmasi\n");
    printf("4 )Uygulamayi kapat\n");

    scanf("%d",&mainMenu);
    FILE *input;
    char rawInput[100];
    bool isMainExists = false;
    switch (mainMenu) {
        case 1:
            if ((input = fopen("input.txt", "r")) == NULL) {
                printf("Dosya bulunamadi veya acilamadi !!\n");
            }
            else
            {
                printf("Dosya bulundu.\n");
                while(!feof(input))
                {
                    memset(rawInput, 0, 100);
                    fgets(rawInput,100,input);
                    if(strstr(rawInput,"main") != NULL)
                        isMainExists = true;
                }
                if(isMainExists == false)
                {
                    printf("Main metodu bulunamadi girilen text bir C kodu degildir\n");
                }
                else
                {
                    printf("Main metodu bulundu girilen text bir C kodudur\n");
                }
            }
            fclose(input);
            goto StartmainMenu;
        case 2:
            getLine();
            goto StartmainMenu;
        case 3:
            runtimeTester();
            goto StartmainMenu;
        case 4:
            exit(0);
            break;
        default:
            printf("Yanlis bir deger girdiniz lutfen tekrar deger giriniz : \n");
            goto StartmainMenu;
    }
    return 0;
}