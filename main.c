#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// deklarasi bst
// node diurutkan berdasarkan kode barang (int)
typedef struct node {
    int kodeBarang;
    char namaBarang[20];
    int modalBarang;
    int hargaBarang;
    int stokBarang;
    struct node *left;
    struct node *right;
} node;

FILE *fp = NULL;    // pointer untuk file data barang
// FILE *fp1 = NULL;   // pointer untuk file backup

// alokasi node
node *getNewNode(int kode, char nama[], int modal, int harga, int stok) {
    // pemberian alamat ke node baru
    node *newNode = (node*)malloc(sizeof(node));

    // copy parameter ke elemen dari node baru
    newNode->kodeBarang = kode;
    strcpy(newNode->namaBarang, nama);
    newNode->modalBarang = modal;
    newNode->hargaBarang = harga;
    newNode->stokBarang = stok;

    newNode->left = newNode->right = NULL;

    return newNode;
}

// tambah node ke bst
node *insert(node *rootPtr, int kode, char nama[], int modal, int harga, int stok) {
    if(rootPtr == NULL) {
        rootPtr = getNewNode(kode, nama, modal, harga, stok);
    } else if(kode <= rootPtr->kodeBarang) {
        rootPtr->left = insert(rootPtr->left, kode, nama, modal, harga, stok);
    } else {
        rootPtr->right = insert(rootPtr->right, kode, nama, modal, harga, stok);
    }

    return rootPtr;
}

// memasukkan data dari file data_barang ke bst
node *insertBarang(node *rootPtr) {
    // var untuk menampung sementara data dari file
    int kode_f, modal_f, harga_f, stok_f;
    char nama_f[20];

    fp = fopen("data_barang.txt", "r");
    while(fscanf(fp, "%d %d %d %d %[^\n]s", &kode_f, &modal_f, &harga_f, &stok_f, nama_f) != EOF) {
        rootPtr = insert(rootPtr, kode_f, nama_f, modal_f, harga_f, stok_f);
    }
    fclose(fp);

    return rootPtr;
}

// update file data barang dgn memasukkan data dari bst
void updateData(node *rootPtr) {
    fp = fopen("data_barang_new.txt", "a");

    // preorder traversal
    if(rootPtr != NULL) {
        fprintf(fp, "%d %d %d %d %s\n", rootPtr->kodeBarang, rootPtr->modalBarang, rootPtr->hargaBarang, rootPtr->stokBarang, rootPtr->namaBarang);
        updateData(rootPtr->left);
        updateData(rootPtr->right);
    }

    fclose(fp);
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

void beliBarang(node *rootPtr) {
    int kode, jumlah, totalHarga = 0;
    int ulang = 0;
    node *data; // var untuk menampung barang yg dicari
    do {
        printf("\nMasukkan kode barang: ");
        scanf("%d", &kode);
        printf("Masukkan jumlah: ");
        scanf("%d", &jumlah);

        // cari harga berdasarkan kodenya
        data = search(rootPtr, kode);
        if(data == NULL || data->stokBarang < jumlah) {
            printf("\nOops... Barang/stok tidak ada\n");
        } else {
            totalHarga += data->hargaBarang * jumlah;
            data->stokBarang -= jumlah;
            // masukin ke struk
        }

        printf("\nKetik 1 jika ingin membeli yg lain, 0 jika selesai ");
        scanf("%d", &ulang);
    } while(ulang == 1);

    int bayar, kembalian;
    printf("\nTotal belanja = %d\n", totalHarga);
    do {
        printf("\nNominal pembayaran = ");
        scanf("%d", &bayar);
        if(bayar >= totalHarga) {
            kembalian = bayar - totalHarga;
            printf("\nKembalian = %d\n", kembalian);
            // abistu masukin ke struk
        } else {
            printf("\nOops.. uang tidak cukup\nSilakan ulang...\n");
        }
    } while(bayar < totalHarga);
}

// tampilan menu pertama
// mengembalikan menu yg dipilih (int)
// kalo ini diubah, inget ubah yg di switch case di fungsi main
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

// inorder traversal
// menu lihat barang untuk umum, tidak menampilkan stok
void tampilkanBarang(node *rootPtr){
	if(rootPtr!=NULL){
		tampilkanBarang(rootPtr->left);
        printf("| %-4d | %-15s | %-7d |\n", rootPtr->kodeBarang, rootPtr->namaBarang, rootPtr->hargaBarang);
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
                // tampilkan barang dulu
                printf("\n");
                printf("+------+-----------------+---------+\n");
                printf("| Kode |   Nama Barang   |  Harga  |\n");
                printf("+------+-----------------+---------+\n");
                tampilkanBarang(rootPtr);
                printf("+------+-----------------+---------+\n");

                // fungsi beli barang di sini
                beliBarang(rootPtr);
                break;
            case 3:
                // update stok di file
                updateData(rootPtr);
                remove("data_barang.txt");
                rename("data_barang_new.txt", "data_barang.txt");
                printf("\nTerimakasih Telah Berbelanja di Tempat Kami ^^\n\n"); // bisa diedit
                exit(0);
	        case 220602:    // case secret code
                system("clear");
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
}
