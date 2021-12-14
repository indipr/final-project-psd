#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// deklarasi bst
// node diurutkan berdasarkan kode barang (int)
typedef struct node {
    int kodeBarang;
    char namaBarang[20];
    int hargaBarang;
    int stokBarang;
    struct node *left;
    struct node *right;
} node;

// alokasi node
node *getNewNode(int kode, char nama[], int harga, int stok) {
    // pemberian alamat ke node baru
    node *newNode = (node*)malloc(sizeof(node));

    // copy parameter ke elemen dari node baru
    newNode->kodeBarang = kode;
    strcpy(newNode->namaBarang, nama);
    newNode->hargaBarang = harga;
    newNode->stokBarang = stok;

    newNode->left = newNode->right = NULL;

    return newNode;
}

// tambah node ke bst
node *insert(node *rootPtr, int kode, char nama[], int harga, int stok) {
    if(rootPtr == NULL) {
        rootPtr = getNewNode(kode, nama, harga, stok);
    } else if(kode <= rootPtr->kodeBarang) {
        rootPtr->left = insert(rootPtr->left, kode, nama, harga, stok);
    } else {
        rootPtr->right = insert(rootPtr->right, kode, nama, harga, stok);
    }

    return rootPtr;
}

// contoh memasukkan data ke bst
// bisa dihapus kalo gak sesuai nanti
node *insertBarang(node *rootPtr) {
    //                      kode  | nama    |  harga | stok 
    rootPtr = insert(rootPtr, 112, "Penghapus", 2000, 10);
    rootPtr = insert(rootPtr, 111, "Pensil", 3500, 25);
    rootPtr = insert(rootPtr, 113, "Pulpen", 3000, 15);

    return rootPtr;
}

// pencarian berdasarkan kode barang
node *search(node *rootPtr, int kode) {
    if(rootPtr == NULL) {
        return NULL;   // tidak ditemukan
    } else if(rootPtr->kodeBarang == kode) {
        return rootPtr;   // ditemukan
    } else if(kode <= rootPtr->kodeBarang) {
        return search(rootPtr->left, kode);
    } else {
        return search(rootPtr->right, kode);
    }
}

// tampilan menu pertama
// mengembalikan menu yg dipilih (int)
// kalo ini diubah, inget ubah yg di switch case di fungsi main (line 119)
int menu1() {
    puts("\n");
    puts("\n=============================================");
    puts("\n        SELAMAT DATANG DI Chuanzzzz          ");
    puts("\n---------------------------------------------");
    puts("\n               1. Lihat Barang");
    puts("\n               2. Beli Barang");
    puts("\n               3. Keluar\n\n");

    int pilih;
    printf("Pilih menu: ");
    scanf("%d", &pilih);

    return pilih;
}

// menu lihat barang untuk umum
void tampilkanBarang(node *rootPtr){
	if(rootPtr!=NULL){
		tampilkanBarang(rootPtr->left);
        printf("| %-4d | %-15s | %-7d |\n", rootPtr->kodeBarang, rootPtr->namaBarang, rootPtr->hargaBarang);
		// printf("%d ", rootPtr->kodeBarang);
		// printf("%s ", rootPtr->namaBarang);
		// printf("%d ", rootPtr->hargaBarang);
		// printf("%d\n", rootPtr->stokBarang);
		tampilkanBarang(rootPtr->right);
	}
}

// menu lihat barang untuk owner


int main() {
    // system("clear");

    // deklarasi root dari bst
    node *rootPtr = NULL;

    // masukkan data ke bst
    rootPtr = insertBarang(rootPtr);

    // perulangan menu utama
    // infinity loop sampai user pilih keluar
    int cont;   // var untuk pause sebelum lanjut ke loop berikutnya
    int secpilih;   // var untuk pilih menu di owner privilege
    while (1)
    {
        // user memilih menu tiap perulangan
        // system("clear");
        switch(menu1()) {
            case 1: // lihat barang
                printf("\n");
                printf("+------+-----------------+---------+\n");
                printf("| Kode |   Nama Barang   |  Harga  |\n");
                printf("+------+-----------------+---------+\n");
                tampilkanBarang(rootPtr);
                printf("+------+-----------------+---------+\n");
                break;
            case 2: // beli barang
                // tampilkanBarang(rootPtr);
                // fungsi beli barang di sini
                break;
            case 3:
                printf("\nTerimakasih Telah Berbelanja di Tempat Kami ^^\n\n"); // bisa diedit
                exit(0);
	    case 220602:    // case secret code
		
                printf("\n=============================================");
                printf("\n            Owner Privilage Menu             ");
                printf("\n=============================================");
                printf("\n         1. Kembali Ke Menu Utama");
                printf("\n         2. Stok Barang");
                printf("\n         3. Rekapan\n");
                printf("\nMasukan Pilihan anda: ");
                scanf("%d", &secpilih);
                if(secpilih==1){
                    break;
                }else if(secpilih==2){
                    //fungsi stok barang
                    break;
                }else if(secpilih==3){
                    //fungsi rekapan
                    break;
                }
            default:
                puts("\nMenu tidak valid...\n"); // bisa diedit
        }

        printf("\nKetik 1 untuk lanjut ");
        scanf("%d", &cont);
    }
    
    // contoh mencari barang
    // int kode;
    // printf("masukkan kode barang: ");
    // scanf("%d", &kode);

    // masukkan hasil pencarian ke variabel untuk dicetak nantinya
    // node *dataRetrieved = search(rootPtr, kode);
    // if(dataRetrieved == NULL) {
    //     printf("data tidak ada\n");
    // } else {
    //     printf("%d\n", dataRetrieved->kodeBarang);
    //     printf("%s\n", dataRetrieved->namaBarang);
    //     printf("%d\n", dataRetrieved->hargaBarang);
    //     printf("%d\n", dataRetrieved->stokBarang);
    // }
}
