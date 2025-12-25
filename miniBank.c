#include <stdio.h>
#include <string.h>

#define MAKS_NASABAH 100
#define PANJANG_NAMA 50
#define NAMA_FILE "data_nasabah.csv"

// Bagian Abi
// Simpan data nasabah
typedef struct {
    int id;
    char nama[PANJANG_NAMA];
    double saldo;
} Nasabah;

void tampilMenu();
void jeda();
void bersihkanBuffer();

int cariIndexNasabahById(Nasabah daftarNasabah[], int jumlahNasabah, int idDicari);
void tambahNasabah(Nasabah daftarNasabah[], int *jumlahNasabah);
void hapusEnter(char teks[]);
void tampilSemuaNasabah(Nasabah daftarNasabah[], int jumlahNasabah);

void cariNasabah(Nasabah daftarNasabah[], int jumlahNasabah);
void transaksi(Nasabah daftarNasabah[], int jumlahNasabah);

void urutkanSaldo(Nasabah daftarNasabah[], int jumlahNasabah);

void simpanData(Nasabah daftarNasabah[], int jumlahNasabah);
void muatData(Nasabah daftarNasabah[], int *jumlahNasabah);

int main() {
    // Database nasabah
    Nasabah daftarNasabah[MAKS_NASABAH];
    int jumlahNasabah = 0, pilihan;
    muatData(daftarNasabah, &jumlahNasabah);

    do {
        tampilMenu();
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        bersihkanBuffer();

        switch (pilihan) {
            case 1:
                tambahNasabah(daftarNasabah, &jumlahNasabah);
                break;
            case 2:
                tampilSemuaNasabah(daftarNasabah, jumlahNasabah);
                break;
            case 3:
                transaksi(daftarNasabah, jumlahNasabah);
                break;
            case 4:
                cariNasabah(daftarNasabah, jumlahNasabah);
                break;
            case 5:
                urutkanSaldo(daftarNasabah, jumlahNasabah);
                break;
            case 6:
                simpanData(daftarNasabah, jumlahNasabah);
                break;
            case 7:
                muatData(daftarNasabah, &jumlahNasabah);
                break;
            case 0:
                printf("Program selesai. Terima kasih.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
        if (pilihan != 0) jeda();
    } while (pilihan != 0);
    return 0;
}

void tampilMenu() {
    printf("=================================\n");
    printf("        MINI BANK DATABASE\n");
    printf("=================================\n");
    printf("1. Tambah Nasabah\n");
    printf("2. Tampilkan Semua Nasabah\n");
    printf("3. Transaksi (Setor / Tarik)\n");
    printf("4. Cari Nasabah\n");
    printf("5. Urutkan Berdasarkan Saldo\n");
    printf("6. Simpan Data\n");
    printf("7. Muat Data\n");
    printf("0. Keluar\n");
    printf("=================================\n");
}

void jeda() {
    printf("\nTekan ENTER untuk lanjut...");
    getchar();
}

void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
// Ini biar ga ada enter yaa
void hapusEnter(char teks[]) {
    int panjang = strlen(teks);
    if (panjang > 0 && teks[panjang - 1] == '\n') {
        teks[panjang - 1] = '\0';
    }
}

// Bagian Nabil


// Bagian Priji
