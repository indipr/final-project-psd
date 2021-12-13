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
        rootPtr->left = insert(rootPtr->left, kode, nama, harga);
    } else {
        rootPtr->right = insert(rootPtr->right, kode, nama, harga);
    }

    return rootPtr;
}

// contoh memasukkan data ke bst
// bisa dihapus kalo gak sesuai nanti
node *insertBarang(node *rootPtr) {
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

// buat tampilan header di sini
// int header() {
    
// }

// buat tampilan menu pertama di sini
// return menu yg dipilih (int)
// int menu1() {
    
// }

// buat fungsi untuk menampilkan bst
// pake tree traversal
// void tampilkanBarang() {
    
// }

int main() {
    // deklarasi root dari bst
    node *rootPtr = NULL;

    // masukkan data ke bst
    rootPtr = insertBarang(rootPtr);

    // contoh mencari barang
    int kode;
    printf("masukkan kode barang: ");
    scanf("%d", &kode);

    // masukkan hasil pencarian ke variabel untuk dicetak nantinya
    node *dataRetrieved = search(rootPtr, kode);
    if(dataRetrieved == NULL) {
        printf("data tidak ada\n");
    } else {
        printf("%d\n", dataRetrieved->kodeBarang);
        printf("%s\n", dataRetrieved->namaBarang);
        printf("%d\n", dataRetrieved->hargaBarang);
        printf("%d\n", dataRetrieved->stokBarang);
    }

    return 0;
}
