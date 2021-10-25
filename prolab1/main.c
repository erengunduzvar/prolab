//210201105 Asuman Kaplan
//190201058 Eren Gündüzvar
#include <stdio.h>
#include <stdlib.h>

//
FILE *index;
FILE *veri;
//Ogrenci bilgilerimi kaydettigim structu olusturuyorum
struct studentinfo
{
    int ogr_no;
    int ders_kodu;
    int puan;
    int anahtar;
};

//Kodun ilk girisinde yapacagi islemler icin bir fonksiyon tanımlıyorum
int start_menu()
{
    printf("studentinfo struct sekli ile yazilmis dosyaniz okunuyor\n");
    veri =  fopen("veri.bin","rb");
    // 0'i binary dosyasinin sonuna gidiyor ve sonuna kadar ki veri boyutunu olcuyor.
    // Buldugu degeri struct degerime bolunce fonksiyonda ki kisi sayisini buluyor.

    fseek(veri, 0, SEEK_END); // dosyanin sonuna git
    int size = ftell(veri); // gecerli dosyanın sonundaki boyutu size'a kaydet
    fseek(veri, 0, SEEK_SET); // basa geri donuyorum
    fflush(veri);

    size = size /sizeof(struct studentinfo);
    printf("Bin dosyanizin icerisindeki kisi sayisi: %d\n",size);
    fclose(veri);
    return size;

}
void indeksDosyasiniSil()
    {
if (remove("index.txt") == 0)
                    {
                        printf("Indeks dosyam basarili bir bicimde kaldirildi.\n");
                    }
                else
                    {
                        printf("Dosya silinemedi !\n");
                    }
    }
struct studentinfo kayit_bul(kisi_sayisi)
    {
    struct studentinfo info[kisi_sayisi];
    printf("Aranan ogrenci anahtarini giriniz\n");
    int aranan;
    scanf("%d",&aranan);

                for(int count = 0;count<kisi_sayisi;count++)
                {
                    //Bin dosyami okudum.
                    fread(&info[count], sizeof(struct studentinfo), 1, veri);

                    /*Eger aradigim anahtar numarisina esit bir anahtar numarali ogrenci bulursam teker teker tum degerlerini yazıp.
                    Kullaniciya sorarim eger aradigi kisi bu degilse ayni anahtara sahip diger ogrencimi goruntulerim.*/
                    if(info[count].anahtar == aranan)
                    {
                        printf("Aradiginiz kisi bu mu :\n");
                        printf("Ogrenci numaram %d  ||",info[count].ogr_no);
                        printf("ogrenci ders kodum %d  ||",info[count].ders_kodu);
                        printf("ogrenci puanim %d  ||",info[count].puan);
                        printf("ogrenci anahtarim %d\n\n",info[count].anahtar);


                        printf("Aradiginiz kisi buysa '1' aradiginiz kisi bu degilse '2' giriniz \n");
                        int tf;
                        scanf("%d",&tf);

                        if (tf == 1)
                        {
                            printf("Aranan kisi bulundu.\n");
                            //Arama fonksiyonum aranilan kisiyi buldugunda kisinin tum struct degerini dondurur.
                            //Boylece diger fonksiyonlarda kullanimi da islevsel olmus olur.
                            return info[count];
                        }
                    }
                    else {}
                }
                //Eger aradigim kisiyi bulamazsam fonksiyondan kullaniciya error ciktisi verip cikarim.
            printf("Aranan kisi bulunamadi.\n");
        }
void kayit_guncelle(kisi_sayisi)
    {
        FILE *veri2;
        struct studentinfo aranan = kayit_bul(kisi_sayisi);
        fflush(veri);
        fclose(veri);
        veri = fopen("veri.bin","rb");
        veri2 = fopen("veri2.bin","ab");
        int yeni_puan;
        printf("Yeni puani giriniz : ");
        scanf("%d",&yeni_puan);


         struct studentinfo info;
         while(fread(&info,sizeof(info),1,veri)==1)
        {
        if(aranan.ogr_no == info.ogr_no && aranan.ders_kodu == info.ders_kodu && aranan.puan == info.puan && aranan.anahtar == info.anahtar)
            {
            info.puan = yeni_puan;
            fwrite(&info,sizeof(info),1,veri2);
            }
        else
            {
            fwrite(&info,sizeof(info),1,veri2);
            }
        }
        fclose(veri);
        fclose(veri2);
        fflush(veri);
        fflush(veri2);
        veri = fopen("veri.bin","wb");
        veri2 = fopen("veri2.bin","rb");
        struct studentinfo info3[kisi_sayisi];
        for(int count3 = 0;count3<(kisi_sayisi);count3++)
            {
                fread(&info3[count3], sizeof(struct studentinfo), 1, veri2);
            }
        for(int count3 = 0;count3<(kisi_sayisi);count3++)
            {
                fwrite(&info3[count3], sizeof(struct studentinfo), 1, veri);
            }
        fclose(veri);
        fclose(veri2);
        fflush(veri);
        fflush(veri2);
        remove("veri2.bin");
        printf("Puan degistirildi \n");
    }
int kayit_sil(kisi_sayisi)
    {
    FILE *veri2;
     veri = fopen("veri.bin","rb");
    struct studentinfo aranan = kayit_bul(kisi_sayisi);
    fflush(veri);
    fclose(veri);
    veri = fopen("veri.bin","rb");
    veri2 = fopen("veri2.bin","ab");
    int bul;
    struct studentinfo info;
         while(fread(&info,sizeof(info),1,veri)==1)
    {
        if(aranan.ogr_no == info.ogr_no && aranan.ders_kodu == info.ders_kodu && aranan.puan == info.puan && aranan.anahtar == info.anahtar)
        {
           bul=1;
        }
        else
        {
           fwrite(&info,sizeof(info),1,veri2);
        }
    }
    if(!bul)
    {
        printf("Silinecek kayit bulunamadi.\n");
    }
    else
    {
        printf("Kayit silme islemi basarili.\n");
    }
    fclose(veri);
    fclose(veri2);
    fflush(veri);
    fflush(veri2);
    veri = fopen("veri.bin","wb");
    veri2 = fopen("veri2.bin","rb");
    struct studentinfo info3[kisi_sayisi-1];
    for(int count3 = 0;count3<(kisi_sayisi-1);count3++)
            {
                fread(&info3[count3], sizeof(struct studentinfo), 1, veri2);
            }
    for(int count3 = 0;count3<(kisi_sayisi-1);count3++)
            {
                fwrite(&info3[count3], sizeof(struct studentinfo), 1, veri);
            }
    fclose(veri);
    fclose(veri2);
    fflush(veri);
    fflush(veri2);
    remove("veri2.bin");
    kisi_sayisi--;
return kisi_sayisi;
}
void index_oku(int kisi_sayisi)
    {
       struct studentinfo info[kisi_sayisi];
                for(int count = 0;count<kisi_sayisi;count++)
                {
                    fscanf(index,"Ogrenci numaram %d  ||",&info[count].ogr_no);
                    fscanf(index,"ogrenci ders kodum %d  ||",&info[count].ders_kodu);
                    fscanf(index,"ogrenci puanim %d  ||",&info[count].puan);
                    fscanf(index,"ogrenci anahtarim %d\n",&info[count].anahtar);
                }
                for(int count2 = 0;count2<kisi_sayisi;count2++)
                {
                    printf("Ogrenci numaram %d  ||",info[count2].ogr_no);
                    printf("ogrenci ders kodum %d  ||",info[count2].ders_kodu);
                    printf("ogrenci puanim %d  ||",info[count2].puan);
                    printf("ogrenci anahtarim %d\n",info[count2].anahtar);
                }
    }
void index_dosya_olustur(int kisi_sayisi)
    {
        // start menuden aldigim kisi sayisini burada yazdirarak kullanciya ogrenci havuzunu hatirlatiyorum.
        printf("%d kisilik bir seriyi indexliyorum\n",kisi_sayisi);
         struct studentinfo info[kisi_sayisi];
         struct studentinfo temp;

         //binary dosyamdaki verileri struct degerimin icerisine yerlestiriyorum.
                for(int count = 0;count<kisi_sayisi;count++)
                {
                    fread(&info[count], sizeof(struct studentinfo), 1, veri);
                }
        //Düzenleme metodu : Her bir indeksi diger tum indekslerle karsilastirarak buyuk olani bir alt siraya yerlestiriyorum.
        for(int b=0;b<kisi_sayisi;b++)
        {
            for(int a=0;a<kisi_sayisi;a++)
            {
                if(info[a].anahtar > info[b].anahtar)
                {
                    // buyuk değerimi geciciye kaydettim
                    temp.anahtar   =    info[a].anahtar;
                    temp.ders_kodu =    info[a].ders_kodu;
                    temp.puan      =    info[a].puan;
                    temp.ogr_no    =    info[a].ogr_no;
                    // kucuk degerimi buyuk degere kaydettim
                    info[a].anahtar   = info[b].anahtar;
                    info[a].ders_kodu = info[b].ders_kodu;
                    info[a].puan      = info[b].puan;
                    info[a].ogr_no    = info[b].ogr_no;
                    // gecicide tuttugum buyuk degerimi kucuk degere kaydediyorum
                    info[b].anahtar   =   temp.anahtar;
                    info[b].ders_kodu =   temp.ders_kodu;
                    info[b].puan      =   temp.puan;
                    info[b].ogr_no    =   temp.ogr_no;
                }
                else{}
            }
        }
        //Dosyalarimi siraladiktan sonra indeks dosyamin icine yerlestiriyorum.
        for(int count;count<kisi_sayisi;count++)
                {
                    fprintf(index,"Ogrenci numaram %d  ||",info[count].ogr_no);
                    fprintf(index,"ogrenci ders kodum %d  ||",info[count].ders_kodu);
                    fprintf(index,"ogrenci puanim %d  ||",info[count].puan);
                    fprintf(index,"ogrenci anahtarim %d\n",info[count].anahtar);
                }
    }

int kayit_olustur(int kisi_sayisi)
    {
        //Dizimin dinamik olmasi icin bu fonksiyon hem halihazirdaki ogrenci sayisini istiyor hem de
        //islem bittikten sonra ogrenci sayisini arttirmasi icin donduruyor.
    printf("Kac kisilik kayit eklemek istiyorsunuz ?\n");
    int kayit_sayisi;
    //Kullanicidan eklemek istedigi ogrenci sayisini aliyorum
    scanf("%d",&kayit_sayisi);
    printf("Veri dosyasýna %d kisi ekliyorsunuz\n",kayit_sayisi);
    struct studentinfo gecici[kayit_sayisi];
    for(int addcounter;addcounter<kayit_sayisi;addcounter++)
    {
        printf("Ogrencinin anahtari :\t\n");
            scanf("%d",&gecici[addcounter].anahtar);
        printf("Ogrencinin numarasi :\t\n");
            scanf("%d",&gecici[addcounter].ogr_no);
        printf("Ogrencinin ders kodu :\t\n");
            scanf("%d",&gecici[addcounter].ders_kodu);
        printf("Ogrencinin puani :\t\n");
            scanf("%d",&gecici[addcounter].puan);
        fwrite(&gecici[addcounter], sizeof(struct studentinfo), 1, veri);
    }
    //halihazirdaki kisi sayimin ustune kayit sayisini da ekliyorum
    return kisi_sayisi+kayit_sayisi;
    }


void veri_dosyaoku (int kisi_sayisi)
    {
        struct studentinfo info[kisi_sayisi];

                for(int count;count<kisi_sayisi;count++)
                {
                    fread(&info[count], sizeof(struct studentinfo), 1, veri);
                    printf("Ogrenci numaram %d  ||",info[count].ogr_no);
                    printf("ogrenci ders kodum %d  ||",info[count].ders_kodu);
                    printf("ogrenci puanim %d  ||",info[count].puan);
                    printf("ogrenci anahtarim %d\n",info[count].anahtar);
                }
    }
int anamenu(int kisi_sayisi)
    {
        printf("\n\n\n\nGerceklestirmek istediginiz fonksiyonun kare icerisindeki numarasini giriniz.\nindexDosyasiOlustur:\t[1]\nkayitEkle:\t\t[2]\nkayitBul:\t\t[3]\nkayitSil:\t\t[4]\nkayitGuncelle:\t\t[5]\nveriDosyasiniGoster:\t[6]\nindeksDosyasiniGoster:\t[7]\nindeksDosyasiniSil:\t[8]\nprogramiKapat:\t\t[9]\n\n\n\n");
        int islem;
        scanf("%d",&islem);
        printf("Sectigin islem numarasi %d\n",islem);
        switch(islem)
        {
        case 1:
                printf("Sectiginiz islem indexDosyasiOlustur:\n");
                veri  =  fopen("veri.bin","rb");
                index =  fopen("index.txt","w");
                index_dosya_olustur(kisi_sayisi);
                fflush(veri);
                fclose(veri);
                fclose(index);
                break;
            case 2:
                printf("Sectiginiz islem kayitEkle:\n");
                veri  =  fopen("veri.bin","ab");
                kisi_sayisi = kayit_olustur(kisi_sayisi);
                fflush(veri);
                fclose(veri);
                break;
            case 3:
                veri  =  fopen("veri.bin","rb");
                printf("Sectiginiz islem kayitBul:\n");
                kayit_bul(kisi_sayisi);
                fflush(veri);
                fclose(veri);
                break;
            case 4:
                printf("Sectiginiz islem kayitSil:\n");
                veri  =  fopen("veri.bin","rb");
                kisi_sayisi = kayit_sil(kisi_sayisi);
                break;
            case 5:
                printf("Sectiginiz islem kayitGuncelle:\n");
                veri  =  fopen("veri.bin","rb");
                kayit_guncelle(kisi_sayisi);
                fflush(veri);
                fclose(veri);
                break;
            case 6:
                veri  =  fopen("veri.bin","rb");
                printf("Sectiginiz islem veriDosyasiniGoster:\n");
                veri_dosyaoku(kisi_sayisi);
                fflush(veri);
                fclose(veri);
                break;
            case 7:
                printf("Sectiginiz islem indeksDosyasiniGoster:\n");
                index =  fopen("index.txt","r");
                index_oku(kisi_sayisi);
                fclose(index);
                break;
            case 8:
                printf("Sectiginiz islem indeksDosyasiniSil:\n");
                indeksDosyasiniSil();
                break;
            case 9:
                printf("Program kapatiliyor...");
                exit(0);
            default:
                printf("Sectiginiz numarali bir islem yoktur");
        }
        return kisi_sayisi;
    }
int main()
{
    printf("PROGRAM BASLADI\n");
    int kisi_sayisi = start_menu();

    while (1)
    {
        kisi_sayisi = anamenu(kisi_sayisi);
    }
    return 0;
}
