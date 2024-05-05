#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int numara;
    char ad[50];
    char soyad[50];
    struct Node* next;
};

struct Node* head = NULL;

int size = 0;

struct Node* newNode(int numara, char* ad, char* soyad) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->numara = numara;
    strcpy(newNode->ad, ad);
    strcpy(newNode->soyad, soyad);
    newNode->next = NULL;
    return newNode;
}


void listele() {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d#%s#%s\n", current->numara, current->ad, current->soyad);
        current = current->next;
    }
}

void ara(char* soyad) {
    struct Node* current = head;
    int bulundu = 0;
    int pozisyon = 1;

    while (current != NULL) {
        if (strcmp(current->soyad, soyad) == 0) {
            bulundu = 1;
            printf("%d#%s#%s (Listenin %d. sirasinda bulundu)\n", current->numara, current->ad, current->soyad, pozisyon);

            printf("Aramak istediginiz kayit bulunduysa 'e' bulunmadiysa 'h' giriniz: ");
            char cevap;
            scanf(" %c", &cevap);
            if (cevap == 'e' || cevap == 'E') {
                return;
            }
        }

        current = current->next;
        pozisyon++;
    }

    if (!bulundu) {
        printf("Aranilan kayit bulunamadi.\n");
    }
}

void ekle(int numara, char* ad, char* soyad) {
    if (head == NULL) {
        head = newNode(numara, ad, soyad);
    }
    else {
        struct Node* current = head;
        while (current->next != NULL) {
            if (current->numara == numara) {
                printf("Ayni numaraya sahip kayit eklenemez.\n");
                return;
            }
            current = current->next;
        }
        current->next = newNode(numara, ad, soyad);
    }
    size++;
}

void sil(int numara) {
    if (head == NULL) {
        printf("Liste bos, silme islemi yapilamadi.\n");
        return;
    }

    struct Node* temp = head;
    if (temp->numara == numara) {
        head = temp->next;
        free(temp);
        size--;
        return;
    }

    struct Node* prev = NULL;
    while (temp != NULL && temp->numara != numara) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Aranilan kayit bulunamadi.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    size--;
}

void tasima(int numara, int pozisyon) {
    if (pozisyon <= 0 || pozisyon > size + 1) {
        printf("Liste boyutunun disinda bir deger girdiniz.\n");
        return;
    }

    struct Node* temp = head;
    struct Node* prev = NULL;

    while (temp != NULL && temp->numara != numara) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Aranilan kayit bulunamadi.\n");
        return;
    }

    if (prev != NULL) {
        prev->next = temp->next;
    }
    else {
        head = temp->next;
    }

    if (pozisyon == 1) {
        temp->next = head;
        head = temp;
    }
    else {
        struct Node* current = head;
        for (int i = 1; i < pozisyon - 1; i++) {
            current = current->next;
        }
        temp->next = current->next;
        current->next = temp;
    }

    printf("Kayit tasima islemi basarili.\n");
}

void dosyaGuncelle() {
    FILE* dosya = fopen("veriler.txt", "w");
    if (dosya == NULL) {                         
        printf("Dosya acma hatasi.\n");           
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        fprintf(dosya, "%d#%s#%s\n", current->numara, current->ad, current->soyad);
        current = current->next;
    }

    fclose(dosya);
    printf("Dosya guncelleme islemi basarili.\n");
}

int main() {

    FILE* dosya = fopen("veriler.txt", "r");     // ide txt dosyasini bazen aciyor bazen ise dosya acma hatasi veriyor
    if (dosya == NULL) {                         // actigini varsayarak koda devam ediyorum
        printf("Dosya acma hatasi.\n");
        return 1;
    }

    char satir[50];
    while (fgets(satir, sizeof(satir), dosya)) {
        int numara;
        char ad[50];
        char soyad[50];
        sscanf(satir, "%d#%49[^#]#%49[^#]", &numara, ad, soyad);
        ekle(numara, ad, soyad);
    }
    fclose(dosya);

    int secim;
    do {
        printf("\nLutfen bir islem secin:\n");
        printf("1. Listeleme\n");
        printf("2. Ekleme\n");
        printf("3. Arama\n");
        printf("4. Silme\n");
        printf("5. Tasima\n");
        printf("6. Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        switch (secim) {
        case 1:
            printf("\nKayitlar:\n");
            listele();
            break;
        case 2:
            printf("Numara: ");
            int numara;
            scanf("%d", &numara);

            char yeniAd[50];
            char yeniSoyad[50];
            printf("Ad: ");
            scanf("%s", yeniAd);
            printf("Soyad: ");
            scanf("%s", yeniSoyad);
            ekle(numara, yeniAd, yeniSoyad);
            break;
        case 3:
            printf("Aranacak soyad: ");
            char arananSoyad[50];
            scanf("%s", arananSoyad);
            ara(arananSoyad);
            break;
        case 4:
            printf("Silinecek numara: ");
            int silinecekNumara;
            scanf("%d", &silinecekNumara);
            sil(silinecekNumara);
            break;
        case 5:
            printf("Tasinacak numara: ");
            int tasimanumarasi;
            int pozisyon;
            scanf("%d", &tasimanumarasi);
            printf("Tasinacak pozisyon: ");
            scanf("%d", &pozisyon);
            tasima(tasimanumarasi, pozisyon);
            break;
        case 6:
            dosyaGuncelle();
            break;
        default:
            printf("Gecersiz secim yaptiniz. Lutfen tekrar deneyin.\n");
        }
    } while (secim != 6);

    return 0;
}
