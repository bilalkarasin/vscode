#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct Student {
    char *name[MAX_NAME_LENGTH];
    char *surname[MAX_NAME_LENGTH];
    int hakemSayisi;
    int *hakemPuan;
    float performans;
};

float puanHesap(struct Student ogrenci) {
    int i;
    float sonuc = 0;
    float max = 0.0;
    float min = 6.0;

    for (i = 0; i < ogrenci.hakemSayisi; i++) {
        if (ogrenci.hakemPuan[i] > max) {
            max = ogrenci.hakemPuan[i];
        }
        if (ogrenci.hakemPuan[i] < min) {
            min = ogrenci.hakemPuan[i];
        }

        sonuc += ogrenci.hakemPuan[i];
    }

    sonuc = (sonuc) / (ogrenci.hakemSayisi);
    return sonuc;
}

int main() {
    int hakem;
    int b;
    char filename[MAX_NAME_LENGTH];
    int *Student;
    Student=(struct Student*)malloc(14*sizeof(struct Student));

    printf("Dosya adını giriniz: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Dosya oluşturulamadı. Çıkış yapılıyor.\n");
        return 1;
    }

    printf("Ogrenci bilgilerini giriniz (q tuşu programı sonlandırır):\n");

    while (1) {
        struct Student student;

        printf("Isim: ");
        if (scanf("%s", student.name) == 1) {
            if (strcmp(student.name, "q") == 0) {
                printf("Çıkış yapılıyor.\n");
                break;
            }
        } else {
            printf("Çıkış yapılıyor.\n");
            break;
        }

        printf("Soyisim: ");
        if (scanf("%s", student.surname) == 1) {
            if (strcmp(student.surname, "q") == 0) {
                printf("Çıkış yapılıyor.\n");
                break;
            }
        } else {
            printf("Çıkış yapılıyor.\n");
            break;
        }

        printf("Hakem sayisi: ");
        if (scanf("%d", &student.hakemSayisi) != 1) {
            printf("Çıkış yapılıyor.\n");
            break;
        }

        student.hakemPuan = (int *)malloc(student.hakemSayisi * sizeof(int));
        for (b = 0; b < student.hakemSayisi; b++) {
            printf("%d. Hakemin puanı: ", b + 1);
            if (scanf("%d", &student.hakemPuan[b]) != 1) {
                printf("Çıkış yapılıyor.\n");
                break;
            }
        }

        student.performans = puanHesap(student);
        printf("Yarışmacının performans puani = %.3f\n", student.performans);

        fprintf(file, "Ad:%s Soyad:%s Performans Puanı:%.3f", student.name, student.surname),student.hakemPuan;
        
        fprintf(file, "\n");

        free(student.hakemPuan);
    }

    fclose(file);
     free(Student);

    return 0;
}