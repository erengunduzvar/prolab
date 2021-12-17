#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct flightInfo {
    struct flightInfo *nextFlight; //Bir sonraki ucagin bilgisini tutar
    struct flightInfo *previousFlight; //Bir onceki ucagin bilgisini tutar
    int priority;//Ucagin onem sirasi
    int flightId;//ucagin Id numarasi
    int desiredLandingTime;//ucagin inmek istedigi saat
    int delayCounter;//Ucagin bekledigi saat 0 1 2 3
    int status;//0 inmedi 1 iniyor 2 kilitlendi 3 yonlendirildi
    bool isLast;//Ucak listedeki son ucak mi !

} flightInfo;
void writeTxt(flightInfo *planeList)
{
    if(planeList->nextFlight->flightId < 30 && planeList->nextFlight->flightId > 0)
    {
        FILE *output;
        output = fopen("output.txt","w");
        planeList = planeList->nextFlight;
        functionStart1:
        if (planeList->isLast != true) {
            fprintf(output,"ID : %d\tPRIORITY : %d\t DESIRED LAND TIME : %d\tLANDTIME : %d\tDELAYTIME : %d\tDEPART TIME : %d\n", planeList->flightId, planeList->priority,planeList->desiredLandingTime-planeList->delayCounter,planeList->desiredLandingTime, planeList->delayCounter,planeList->desiredLandingTime+1);
            planeList = planeList->nextFlight;
            goto functionStart1;
        } else {
            fprintf(output,"ID : %d\tPRIORITY : %d\t DESIRED LAND TIME : %d\tLANDTIME : %d\tDELAYTIME : %d\tDEPART TIME : %d\n", planeList->flightId, planeList->priority,planeList->desiredLandingTime-planeList->delayCounter,planeList->desiredLandingTime, planeList->delayCounter,planeList->desiredLandingTime+1);
            fclose(output);
            return;
        }
    }
    else
        return;

}

void showList(flightInfo *planeList) { //Listenin elemanlarini gosterir ya da devam eder
    int userInput;
    planeList = planeList->nextFlight;
    printf("\n\n\n\n1) Listeyi goruntule\n2) Bir sonraki ucaga gec\nGirdiniz :");
    scanf("%d", &userInput);

    switch (userInput) {
        case 1:
            break;
        case 2:
            return;
        default:
            printf("Girdiginiz sayi bir isleme karsilik gelmiyor !");
            showList(planeList);
            return;
    }
    functionStart:
    if (planeList->isLast != true) {
        printf("ID : %d\tPRIORITY : %d\t DESIRED LAND TIME : %d\tLANDTIME : %d\tDELAYTIME : %d\tDEPART TIME : %d\n", planeList->flightId, planeList->priority,planeList->desiredLandingTime-planeList->delayCounter,planeList->desiredLandingTime, planeList->delayCounter,planeList->desiredLandingTime+1);
        planeList = planeList->nextFlight;
        goto functionStart;
    } else {
        printf("ID : %d\tPRIORITY : %d\t DESIRED LAND TIME : %d\tLANDTIME : %d\tDELAYTIME : %d\tDEPART TIME : %d\n", planeList->flightId, planeList->priority,planeList->desiredLandingTime-planeList->delayCounter,planeList->desiredLandingTime, planeList->delayCounter,planeList->desiredLandingTime+1);
        return;
    }
}
int statusCheck(int status, int delayCounter, int flightId) {
    if (delayCounter == 3) {
        if (status == 1)//Ucak kilitlenir
        {
            printf("\n\n Bu ucak daha fazla ertelenemez :%d \n\n", flightId);
            return 2;
        }
    }
    if (delayCounter == 4) {
        if (status == 0) {
            return 3;
        }

    }
    return status; //Ayni degeri geri yolla
}
flightInfo change(flightInfo *planeList, flightInfo newPlane) {
    flightInfo temp;
    temp = newPlane;

    newPlane.flightId = planeList->flightId;
    newPlane.priority = planeList->priority;
    newPlane.desiredLandingTime = planeList->desiredLandingTime;
    newPlane.delayCounter = planeList->delayCounter;
    newPlane.status = planeList->status;

    planeList->flightId = temp.flightId;
    planeList->priority = temp.priority;
    planeList->desiredLandingTime = temp.desiredLandingTime;
    planeList->delayCounter = temp.delayCounter;
    planeList->status = temp.status;

    newPlane.desiredLandingTime++;
    newPlane.delayCounter++;
    newPlane.status = statusCheck(newPlane.status, newPlane.delayCounter, newPlane.flightId);


    printf("\n%d Id li ucak %d Id li ucagin yerine eklendi O(%d) S(%d) D(%d)\n", planeList->flightId, newPlane.flightId,
           planeList->priority, planeList->desiredLandingTime, planeList->delayCounter);
    return newPlane;
}
flightInfo compareFlights(flightInfo *planeList, flightInfo newPlane) {
    if (planeList->status == 2) //Kontrol edilen ucak kitli maalesef
    {
        newPlane.desiredLandingTime++;
        newPlane.delayCounter++;
        newPlane.status = statusCheck(newPlane.status, newPlane.delayCounter, newPlane.flightId);
        printf("\n%d Id li ucak (%d) idli ucak yuzunden ertelendi O(%d) S(%d) D(%d)\n", newPlane.flightId,
               planeList->flightId, newPlane.priority, newPlane.desiredLandingTime, newPlane.delayCounter);
        return newPlane;
    } else if (newPlane.status == 2) {
        return change(planeList, newPlane);
    } else if (newPlane.status == 3) {
        printf("Sabiha Gokcen Havalimani maalsef");
        return newPlane;
    } else if (newPlane.priority < planeList->priority) {
        return change(planeList, newPlane);
    } else if (newPlane.priority == planeList->priority && newPlane.flightId < planeList->flightId) {
        return change(planeList, newPlane);
    } else {
        newPlane.desiredLandingTime++;
        newPlane.delayCounter++;
        newPlane.status = statusCheck(newPlane.status, newPlane.delayCounter, newPlane.flightId);
        printf("\n%d Id li ucak (%d) idli ucak yuzunden ertelendi O(%d) S(%d) D(%d)\n", newPlane.flightId,
               planeList->flightId, newPlane.priority, newPlane.desiredLandingTime, newPlane.delayCounter);
        return newPlane;
    }
}
void addFlight(flightInfo *planeList, flightInfo newPlane) {
    flightInfo *firstFlightAddress = planeList;
    showList(planeList);
    writeTxt(planeList);
    nextFlight:
    if (planeList->isLast == true) //Son ucak durumu
    {
        planeList->isLast = false;
        planeList->nextFlight = malloc(sizeof(flightInfo));
        planeList->nextFlight->previousFlight = planeList;
        planeList = planeList->nextFlight;
        planeList->flightId = newPlane.flightId;
        planeList->priority = newPlane.priority;
        planeList->desiredLandingTime = newPlane.desiredLandingTime;
        planeList->delayCounter = newPlane.delayCounter;
        if (newPlane.status == 0) {
            planeList->status = 1;
        } else {
            planeList->status = newPlane.status;
        }
        planeList->status = statusCheck(planeList->status, planeList->delayCounter, planeList->flightId);
        planeList->isLast = true;
        printf("\n%d Id li ucak eklendi O(%d) S(%d) D(%d)\n", planeList->flightId, planeList->priority,
               planeList->desiredLandingTime, planeList->delayCounter);
    } else        //Son ucak olmama durumu
    {
        planeList = planeList->nextFlight;
        //  printf("(%d,%d)\t",newPlane.flightId,planeList->flightId); //Kontrol edilenler
        if (planeList->desiredLandingTime == newPlane.desiredLandingTime) {
            printf("tuttu\t");
            flightInfo Result = compareFlights(planeList, newPlane);
            if (Result.status == 3) {
                printf("\n\nSabiha Gokcen havalimanina yonlendirildi (%d)\n\n", Result.flightId);
                return;
            } else {
                newPlane = Result;
                planeList = firstFlightAddress;
            }
        }
        goto nextFlight;
    }
}

void startPlaneList() {
    FILE *input;
    input = fopen("input.txt", "r");
    flightInfo *planeList;
    planeList = malloc(sizeof(flightInfo));
    bool once = false;
    int planeCounter = 0;
    while (!feof(input)) {
        flightInfo newPlane;
        fscanf(input, "%d %d %d\n", &newPlane.priority, &newPlane.flightId, &newPlane.desiredLandingTime);
        if (newPlane.flightId == 17) {
            //  printf("Zsaofasf");
        }
        newPlane.delayCounter = 0;
        newPlane.status = 0;
        if (once == false) {
            planeList->priority = newPlane.priority;
            planeList->flightId = newPlane.flightId;
            planeList->desiredLandingTime = newPlane.desiredLandingTime;
            planeList->delayCounter = 0;
            planeList->isLast = true;
            once = true;
        }
        addFlight(planeList, newPlane);
        planeCounter++;
    }
    printf("Liste bitti \n");
    showList(planeList);
}
int main() {
    startPlaneList();
    return 0;
}
