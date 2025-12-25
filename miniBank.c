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

// Bagian Nabiel
// Buat nyari nasabah pake ID, jangan diubah dulu
int cariIndexNasabahById(Nasabah daftarNasabah[], int jumlahNasabah, int idDicari) {
for (int i = 0; i < jumlahNasabah; i++) {
if (daftarNasabah[i].id == idDicari) {
return i; // ini kalo ketemu
}
}
return -1; // kalo misalnya ga ketemu
}

void tambahNasabah(Nasabah daftarNasabah[], int *jumlahNasabah) {
if (*jumlahNasabah >= MAKS_NASABAH) {
printf("Data penuh. Tidak bisa tambah nasabah lagi.\n");
return;
}

Nasabah n;

// Input ID
printf("Masukkan No. Rekening: ");
scanf("%d", &n.id);
bersihkanBuffer();

if (cariIndexNasabahById(daftarNasabah, *jumlahNasabah, n.id) != -1) {
printf("ID sudah terpakai. Gagal menambahkan nasabah.\n");
return;
}

// Input nama
printf("Masukkan Nama: ");
fgets(n.nama, PANJANG_NAMA, stdin);
hapusEnter(n.nama);

// Input saldo awal
printf("Masukkan Saldo Awal: ");
scanf("%lf", &n.saldo);
bersihkanBuffer();

if (n.saldo < 0) {
printf("Saldo awal tidak boleh negatif.\n");
return;
}

// Simpan ke array
daftarNasabah[*jumlahNasabah] = n;
(*jumlahNasabah)++;

printf("Nasabah berhasil ditambahkan!\n");
}

void tampilSemuaNasabah(Nasabah daftarNasabah[], int jumlahNasabah) {
if (jumlahNasabah == 0) {
printf("Belum ada data nasabah.\n");
return;
}

printf("\n===== DAFTAR NASABAH =====\n");
printf("%-10s | %-20s | %-15s\n", "ID", "Nama", "Saldo");
printf("----------------------------------------------------\n");

for (int i = 0; i < jumlahNasabah; i++) {
printf("%-10d | %-20s | Rp %-12.2f\n",
daftarNasabah[i].id,
daftarNasabah[i].nama,
daftarNasabah[i].saldo);
}

printf("----------------------------------------------------\n");
printf("Total Nasabah: %d\n", jumlahNasabah);
}

void cariNasabah(Nasabah daftarNasabah[], int jumlahNasabah) {
if (jumlahNasabah == 0) {
printf("Belum ada data nasabah untuk dicari.\n");
return;
}

int idDicari;
printf("Masukkan ID yang ingin dicari: ");
scanf("%d", &idDicari);
bersihkanBuffer();

int index = cariIndexNasabahById(daftarNasabah, jumlahNasabah, idDicari);

if (index == -1) {
printf("Nasabah dengan ID %d tidak ditemukan.\n", idDicari);
} else {
printf("\n=== DATA NASABAH DITEMUKAN ===\n");
printf("ID : %d\n", daftarNasabah[index].id);
printf("Nama : %s\n", daftarNasabah[index].nama);
printf("Saldo : Rp %.2f\n", daftarNasabah[index].saldo);
}
}

// Bagian Priji
void transaksi(Nasabah daftarNasabah[], int jumlahNasabah) {
    if (jumlahNasabah == 0) {
        printf("Belum ada data nasabah.\n");
        return;
    }

    int id;
    printf("Masukkan ID nasabah: ");
    scanf("%d", &id);
    bersihkanBuffer();

    int index = cariIndexNasabahById(daftarNasabah, jumlahNasabah, id);
    if (index == -1) {
        printf("Nasabah dengan ID %d tidak ditemukan.\n", id);
        return;
    }

    printf("\nNasabah: %s (Saldo: Rp %.2f)\n", daftarNasabah[index].nama, daftarNasabah[index].saldo);
    printf("1. Setor Uang\n");
    printf("2. Tarik Uang\n");
    printf("Pilih transaksi: ");

    int pilihTransaksi;
    scanf("%d", &pilihTransaksi);
    bersihkanBuffer();

    double jumlah;
    printf("Masukkan jumlah uang: ");
    scanf("%lf", &jumlah);
    bersihkanBuffer();

    if (jumlah <= 0) {
        printf("Jumlah uang harus lebih dari 0.\n");
        return;
    }

    if (pilihTransaksi == 1) {
        // Setor
        daftarNasabah[index].saldo += jumlah;
        printf("Setor berhasil.\n");
        printf("Saldo sekarang: Rp %.2f\n", daftarNasabah[index].saldo);

    } else if (pilihTransaksi == 2) {
        // Tarik
        if (jumlah > daftarNasabah[index].saldo) {
            printf("Saldo tidak cukup. Transaksi dibatalkan.\n");
            printf("Saldo sekarang: Rp %.2f\n", daftarNasabah[index].saldo);
            return;
        }
        daftarNasabah[index].saldo -= jumlah;
        printf("Tarik berhasil.\n");
        printf("Saldo sekarang: Rp %.2f\n", daftarNasabah[index].saldo);

    } else {
        printf("Pilihan transaksi tidak valid.\n");
    }
}
void urutkanSaldo(Nasabah daftarNasabah[], int jumlahNasabah) {
    if (jumlahNasabah < 2) {
        printf("Data nasabah kurang untuk diurutkan.\n");
        return;
    }

    Nasabah temp;

    // Bubble Sort
    for (int i = 0; i < jumlahNasabah - 1; i++) {
        for (int j = 0; j < jumlahNasabah - i - 1; j++) {
            if (daftarNasabah[j].saldo > daftarNasabah[j + 1].saldo) {
                // Tukar data
                temp = daftarNasabah[j];
                daftarNasabah[j] = daftarNasabah[j + 1];
                daftarNasabah[j + 1] = temp;
            }
        }
    }

    printf("Data nasabah berhasil diurutkan berdasarkan saldo (kecil ke besar).\n");
}

void simpanData(Nasabah daftarNasabah[], int jumlahNasabah) {
    FILE *fp = fopen(NAMA_FILE, "w"); // "w" = overwrite file
    if (fp == NULL) {
        printf("Gagal membuka file untuk menyimpan.\n");
        return;
    }

    // Ini buat masukin ke file CSV: id,nama,saldo
    for (int i = 0; i < jumlahNasabah; i++) {
        fprintf(fp, "%d,%s,%.2f\n",
                daftarNasabah[i].id,
                daftarNasabah[i].nama,
                daftarNasabah[i].saldo);
    }

    fclose(fp);
    printf("Data berhasil disimpan ke file: %s\n", NAMA_FILE);
}

void muatData(Nasabah daftarNasabah[], int *jumlahNasabah) {
    FILE *fp = fopen(NAMA_FILE, "r"); // "r" = read file
    if (fp == NULL) {
        printf("File belum ada / tidak bisa dibuka: %s\n", NAMA_FILE);
        return;
    }

    // Buat reset data yee
    *jumlahNasabah = 0;

    char baris[200];
    while (fgets(baris, sizeof(baris), fp) != NULL) {
        if (*jumlahNasabah >= MAKS_NASABAH) {
            printf("Peringatan: data di file melebihi kapasitas. Sisanya diabaikan.\n");
            break;
        }
        Nasabah n;
      
        int hasil = sscanf(baris, "%d,%49[^,],%lf", &n.id, n.nama, &n.saldo);

        if (hasil == 3) {
            daftarNasabah[*jumlahNasabah] = n;
            (*jumlahNasabah)++;
        }
        // Kalau format baris rusak, kita skip aja biar program aman
    }

    fclose(fp);
    printf("Data berhasil dimuat. Total nasabah: %d\n", *jumlahNasabah);
}

