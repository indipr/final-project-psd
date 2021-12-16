#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// deklarasi bst
// node diurutkan berdasarkan kode barang (int)
typedef struct node {
    int kodeBarang;
    char namaBarang[50];
    int modalBarang;
    int hargaBarang;
    int stokBarang;
    struct node *left;
    struct node *right;
} node;

int totalpenjualan;
int totalpengeluaran;
int jumlahtransaksi;

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
    int kode, jumlah,totalHarga = 0;
    int ulang = 0;
    node *data; // var untuk menampung barang yg dicari
    do {
        printf("\nMasukkan Kode Barang Yang Ingin Dibeli: ");
        scanf("%d", &kode);
        printf("\nMasukkan Jumlah Barang Yang Ingin Dibeli: ");
        scanf("%d", &jumlah);

        // cari harga berdasarkan kodenya
        data = search(rootPtr, kode);
        if(data == NULL || data->stokBarang < jumlah) {
            printf("\nOops... Barang/Stok Tidak Ada\n");
        } else {
            totalHarga += data->hargaBarang * jumlah;
            totalpengeluaran += data->modalBarang * jumlah;
            data->stokBarang -= jumlah;
            puts("\nDetail Barang Yang Anda Beli : ");
            printf("Nama Barang %s Harga Barang %d Dan Jumlah %s Yang Dibeli %d\n",data->namaBarang,data->hargaBarang,data->namaBarang,jumlah);
        }
        printf("\nKetik 1 Jika Ingin Menambah Pembelian, 0 Jika Ingin Membayar ");
        scanf("%d", &ulang);
    } while(ulang == 1);

    int bayar, kembalian;
    printf("\nTotal Belanja Yang Harus Dibayar = %d\n", totalHarga);
    do {
        printf("\nMasukkan Nominal Pembayaran = ");
        scanf("%d", &bayar);
        if(bayar >= totalHarga) {
            kembalian = bayar - totalHarga;
            printf("\nKembalian = %d\n", kembalian);
            totalpenjualan += totalHarga;
            jumlahtransaksi++;
        } else {
            printf("\nOops.. Uang Tidak Cukup\nMasukkan Nominal Yang Sesuai...\n");
        }
    } while(bayar < totalHarga);
}

// tampilan menu pertama
// mengembalikan menu yg dipilih (int)
// kalo ini diubah, inget ubah yg di switch case di fungsi main
int menu1() {
    puts("\n=============================================");
    puts("\n        SELAMAT DATANG DI Chuanzzzz          ");
    puts("\n---------------------------------------------");
    puts("\n               1. Lihat Barang");
    puts("\n               2. Beli Barang");
    puts("\n               3. Keluar\n");

    int pilih;
    printf("Pilih menu: ");
    scanf("%d", &pilih);

    return pilih;
}

// inorder traversal
// menu lihat barang untuk umum
void tampilkanBarang(node *rootPtr){
	if(rootPtr!=NULL){
		tampilkanBarang(rootPtr->left);
        printf("| %-4d | %-15s | %-7d |\n", rootPtr->kodeBarang, rootPtr->namaBarang, rootPtr->hargaBarang);
		tampilkanBarang(rootPtr->right);
	}
}

// lihat barang untuk owner, menampilkan semua elemen
void tampilkanstok(node *rootPtr){
	if(rootPtr!=NULL){
		tampilkanstok(rootPtr->left);
        printf("| %-4d | %-5d | %-7d | %-3d  | %-15s |\n", rootPtr->kodeBarang,rootPtr->modalBarang,rootPtr->hargaBarang,rootPtr->stokBarang,rootPtr->namaBarang);
		tampilkanstok(rootPtr->right);
	}
}

void tambahstok(node *rootPtr)
{
    node *data;
    int kode,stok;
    printf("Masukan Kode Barang Yang Stoknya Ingin Ditambahkan : ");
    scanf("%d",&kode);
    data = search(rootPtr, kode);
    if(data == NULL) {
        puts("Data Tidak Ditemukan..");
        return;
    }
    printf("| %d | %d | %d | %d  | %s |\n",data->kodeBarang,data->modalBarang,data->hargaBarang,data->stokBarang,data->namaBarang);
    printf("Masukan Jumlah Stok Yang Ingin Ditambahkan : ");
    scanf("%d",&stok);
    data->stokBarang += stok;
    puts("Stok Berhasil Ditambahkan!");
}

void tambahBarang(node *rootPtr) {
    int kode, modal, harga, stok;
    char nama[20];

    printf("\nMasukkan Kode Barang: ");
    scanf("%d", &kode);
    if(search(rootPtr, kode) != NULL) {
        puts("Kode Barang Sudah Ada...");
        return;
    }
    printf("\nMasukkan Modal: ");
    scanf("%d", &modal);
    printf("\nMasukkan Harga Jual: ");
    scanf("%d", &harga);
    printf("\nMasukkan Stok: ");
    scanf("%d", &stok);
    printf("\nMasukkan Nama Barang: ");
    scanf("\n");
    scanf("%[^\n]s", nama);

    rootPtr = insert(rootPtr, kode, nama, modal, harga, stok);
}

// cari nilai minimum di bst
node *findMin(node *rootPtr) {
    while(rootPtr->left != NULL) {
        rootPtr = rootPtr->left;
    }
    return rootPtr;
}

// hapus menggunakan rekursif
node *hapusBarang(node *rootPtr, int kode) {
    if(rootPtr == NULL) {
        return NULL;
    } else if(kode < rootPtr->kodeBarang) {
        rootPtr->left = hapusBarang(rootPtr->left, kode);
    } else if(kode > rootPtr->kodeBarang) {
        rootPtr->right = hapusBarang(rootPtr->right, kode);
    } else {    // sudah siap delete
        // tidak ada child
        if(rootPtr->left == NULL && rootPtr->right == NULL) {
            free(rootPtr);
            rootPtr = NULL;
        }
        // 1 child
        else if(rootPtr->left == NULL) {
            node *temp = rootPtr;
            rootPtr = rootPtr->right;
            free(temp);
        } else if(rootPtr->right == NULL) {
            node *temp = rootPtr;
            rootPtr = rootPtr->left;
            free(temp);
        }
        // 2 children
        else {
            node *temp = findMin(rootPtr->right);

            // copy elemen temp ke root
            rootPtr->kodeBarang = temp->kodeBarang;
            rootPtr->modalBarang = temp->modalBarang;
            rootPtr->hargaBarang = temp->hargaBarang;
            rootPtr->stokBarang = temp->stokBarang;
            strcpy(rootPtr->namaBarang, temp->namaBarang);

            rootPtr->right = hapusBarang(rootPtr->right, temp->kodeBarang);
        }
    }
    return rootPtr;
}

node *stokbarang(node *rootPtr)
{
    int pil;
    int kode;
    int cont;

    while(1) {
        puts("Stok barang : ");
        puts("1. Tampilkan Stok");
        puts("2. Tambah Barang");
        puts("3. Tambah Stok");
        puts("4. Hapus Barang");
        puts("5. Kembali");
        printf("Masukan Pilihan Anda : ");
        scanf("%d",&pil);

        switch(pil)
        {
            case 1:
                printf("\n");
                printf("+------+-------+---------+------+-----------------+\n");
                printf("| Kode | Modal |  Harga  | Stok |   Nama Barang   |\n");
                printf("+------+-------+---------+------+-----------------+\n");
                tampilkanstok(rootPtr);
                printf("+------+-------+---------+------+-----------------+\n");
                break;
            case 2: // tambah barang
                tambahBarang(rootPtr);
                break;
            case 3:
                tambahstok(rootPtr);
                break;
            case 4: // hapus barang
                printf("Masukkan Kode Barang Yang Mau Dihapus: ");
                scanf("%d", &kode);

                if(search(rootPtr, kode) == NULL) {
                    puts("Kode Tidak Ditemukan...");
                    break;
                }

                rootPtr = hapusBarang(rootPtr, kode);
                puts("Penghapusan Berhasil");
                break;
            case 5:
                return rootPtr;
            default:
                puts("Menu Yang Dipilih Tidak Ada...");
        }
        printf("\nKetik Angka 1 Lalu Enter Untuk Melanjutkan : ");
        scanf("%d", &cont);
    }
}

void rekap()
{
    int keuntungan;
    keuntungan = totalpenjualan - totalpengeluaran;
    printf("Total Penjualan : %d\n",totalpenjualan);
    printf("Total Pengeluaran : %d\n",totalpengeluaran);
    printf("Total Keuntungan : %d\n",keuntungan);
    printf("Jumlah Transaksi : %d\n",jumlahtransaksi);
}

int main() {


    // deklarasi root dari bst
    node *rootPtr = NULL;

    // masukkan data ke bst
    rootPtr = insertBarang(rootPtr);

    int cont;   // var untuk pause sebelum lanjut ke loop berikutnya
    int secpilih;   // var untuk pilih menu di owner privilege
    int ulang;  // var untuk ulang menu secret code

    // perulangan menu utama
    // infinity loop sampai user pilih keluar
    while (1)
    {
        // user memilih menu tiap perulangan
        // system("clear");
        switch(menu1()) {
            case 1: // lihat barang
                printf("\n");
                printf("Daftar Barang");
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
                 printf("Daftar Barang");
                printf("\n");
                printf("+------+-----------------+---------+\n");
                printf("| Kode |   Nama Barang   |  Harga  |\n");
                printf("+------+-----------------+---------+\n");
                tampilkanBarang(rootPtr);
                printf("+------+-----------------+---------+\n");

                beliBarang(rootPtr);
                break;
            case 3:
                // update stok di file
                updateData(rootPtr);
                remove("data_barang.txt");
                rename("data_barang_new.txt", "data_barang.txt");
                printf("\nTerimakasih Telah Berbelanja di Tempat Kami ^^\n\n");
                exit(0);
	        case 220602:    // case secret code
                do {
                    system("cls");
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
                        rootPtr = stokbarang(rootPtr);
                        //break;
                    }else if(secpilih==3){
                        rekap();
                        //break;
                    }
                    printf("\nKetik Angka 1 Untuk Ke Owner Privilage,Ketik 0 Untuk Ke Menu Utama Lalu Enter ");
                    scanf("%d", &ulang);
                } while(ulang == 1);
                break;
            default:
                puts("\nMenu Yang Dipilih Tidak Ada...\n");
        }

        printf("\nKetik Angka 1 Lalu Enter Untuk Melanjutkan : ");
        scanf("%d", &cont);
        system("cls");
    }
}
