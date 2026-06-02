// Kelompok 8 : 123250008, 123250013

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

typedef struct {
    char NoMobil[15];          
    char NamaMobil[30];
    char JenisMobil[20];
    int  TahunMobil;
    int  HargaSewa;
    char StatusMobil[15];      
} Mobil;

Mobil dataMobil[100];
int n = 0;

//FUNGSI CEK DUPLIKAT PLAT NOMOR
bool isDuplikat(const char *noMobil, int kecualiIndex = -1) {
    for (int i = 0; i < n; i++) {
        if (i == kecualiIndex) continue;
        if (strcmp(dataMobil[i].NoMobil, noMobil) == 0) {
            return true;
        }
    }
    return false;
}

void simpanKeFile() {
    FILE *pf;
    pf = fopen("data_mobil.txt", "wb");
    if (pf == NULL) {
        cout << "File gagal dibuat !\n";
        return;
    }
    fwrite(&n,          sizeof(int),   1, pf);
    fwrite(dataMobil,   sizeof(Mobil), n, pf);
    fclose(pf);
    cout << "Data berhasil disimpan ke file data_mobil.txt !\n";
}
void bacaDariFile() {
    FILE *pf;
    pf = fopen("data_mobil.txt", "rb");
    if (pf == NULL) {
        cout << "File tidak ditemukan ! Silakan input data terlebih dahulu.\n";
        return;
    }
    fread(&n,         sizeof(int),   1, pf);
    fread(dataMobil,  sizeof(Mobil), n, pf);
    fclose(pf);
    cout << "Data berhasil dibaca dari file data_mobil.txt !\n";
}

void inputData() {
    system("cls");
    cout << "INPUT DATA \n"
         << "================================= \n";
    cout << "Jumlah data (Maksimal 10) : ";
    cin  >> n;

    while (n > 10 || n < 1) {
        cout << "Maaf, kapasitas data hanya 10 ! \n"
             << "Masukan Jumlah data ulang : ";
        cin  >> n;
    }

    for (int i = 0; i < n; i++) {
        cout << "Data ke-" << i + 1 << endl;

        char inputNoMobil[15];
        do {
            cout << "No Mobil (Plat) \t: ";
            cin.ignore();
            fgets(inputNoMobil, 15, stdin);
            inputNoMobil[strcspn(inputNoMobil, "\n")] = 0;
            if (isDuplikat(inputNoMobil, i)) {
                cout << "[!] Plat nomor \"" << inputNoMobil
                     << "\" sudah ada! Masukkan plat nomor yang berbeda.\n";
            }
        } while (isDuplikat(inputNoMobil, i));
        strcpy(dataMobil[i].NoMobil, inputNoMobil);

        cout << "Nama Mobil \t\t: ";
        fgets(dataMobil[i].NamaMobil,  30, stdin);
        dataMobil[i].NamaMobil[strcspn(dataMobil[i].NamaMobil, "\n")] = 0;
        cout << "Jenis Mobil \t\t: ";
        fgets(dataMobil[i].JenisMobil, 20, stdin);
        dataMobil[i].JenisMobil[strcspn(dataMobil[i].JenisMobil, "\n")] = 0;
        cout << "Tahun Mobil \t\t: ";
        cin  >> dataMobil[i].TahunMobil;
        cout << "Harga Sewa/Hari (Rp) \t: ";
        cin  >> dataMobil[i].HargaSewa;
        cout << "Status (Tersedia/Disewa): ";
        cin.ignore();
        fgets(dataMobil[i].StatusMobil, 15, stdin);
        dataMobil[i].StatusMobil[strcspn(dataMobil[i].StatusMobil, "\n")] = 0;
    }
    cout << "===================================== \n";

    simpanKeFile();
}

void lihatData() {
    if (n == 0) {
        cout << "\n[!] Data tidak ditemukan ! Silakan input data kembali.\n";
        return;
    }

    cout << "\n" << setfill('=') << setw(100) << "" << endl;
    cout << setfill(' ');
    cout << left << setw(15) << "No Mobil"
         << setw(20) << "Nama Mobil"
         << setw(15) << "Jenis"
         << setw(10) << "Tahun"
         << setw(20) << "Harga/Hari"
         << setw(15) << "Status" << endl;
    cout << setfill('=') << setw(100) << "" << endl;
    cout << setfill(' ');

    for (int j = 0; j < n; j++) {
        cout << left << setw(15) << dataMobil[j].NoMobil
            << setw(20) << dataMobil[j].NamaMobil
            << setw(15) << dataMobil[j].JenisMobil
            << setw(10) << dataMobil[j].TahunMobil
            << "Rp" << setw(17) << dataMobil[j].HargaSewa
            << setw(15) << dataMobil[j].StatusMobil << endl;
    }

    cout << setfill('=') << setw(100) << "" << endl;
    cout << setfill(' ');
}

// FUNGSI PEMBANTU PERBANDINGAN
bool compare(Mobil a, Mobil b, int kriteria) {
    if (kriteria == 1) return strcmp(a.NoMobil, b.NoMobil) > 0; 
    if (kriteria == 2) return strcmp(a.NamaMobil, b.NamaMobil) > 0; 
    if (kriteria == 3) return a.HargaSewa > b.HargaSewa;            
    return false;
}

// SELECTION SORT
void selectionSort(int n, int kriteria) {
    for (int i = 0; i < n - 1; i++) {
        int indexMin = i;
        for (int j = i + 1; j < n; j++) {
            if (compare(dataMobil[indexMin], dataMobil[j], kriteria)) {
                indexMin = j;
            }
        }
        Mobil temp          = dataMobil[i];
        dataMobil[i]        = dataMobil[indexMin];
        dataMobil[indexMin] = temp;
    }
}

// INSERTION SORT
void insertionSort(int n, int kriteria) {
    for (int i = 1; i < n; i++) {
        Mobil kunci = dataMobil[i];
        int   j     = i - 1;
        while (j >= 0 && compare(dataMobil[j], kunci, kriteria)) {
            dataMobil[j + 1] = dataMobil[j];
            j--;
        }
        dataMobil[j + 1] = kunci;
    }
}

// FUNGSI SORTING DATA
void sortingData() {
    if (n == 0) {
        cout << "Data kosong! Silakan input data terlebih dahulu.\n";
        return;
    }
    int alg, kriteria;
    system("cls");
    cout << "PILIH ALGORITMA SORTING \n"
         << "================================= \n"
         << "1. Selection Sort\n"
         << "2. Insertion Sort\n"
         << "================================= \n"
         << "Pilih : ";
    cin >> alg;

    system("cls");
    cout << "URUTKAN BERDASARKAN \n"
         << "================================= \n"
         << "1. No. Mobil\n"
         << "2. Nama Mobil\n"
         << "3. Harga Sewa\n"
         << "================================= \n"
         << "Pilih : ";
    cin >> kriteria;

    cout << "\nData sebelum diurutkan:\n";
    lihatData();

    if      (alg == 1) selectionSort(n, kriteria);
    else if (alg == 2) insertionSort(n, kriteria);
    else {
        cout << "Pilihan algoritma tidak ada!\n";
        return;
    }
    cout << "\nData berhasil diurutkan!\n";
    lihatData();

    simpanKeFile();
}

// SEQUENTIAL SEARCH
void cariDataSequensial() {
    // [REVISI 1] Variabel cari diubah menjadi char array
    char cari[15];
    bool found = false;
    int  i     = 0;

    if (n == 0) {
        cout << "Data kosong! Silakan input data terlebih dahulu.\n";
        return;
    }

    cout << "SEQUENSIAL SEARCH \n"
         << "================================= \n";
    cout << "No Mobil yang anda cari : ";
    cin.ignore();
    fgets(cari, 15, stdin);
    cari[strcspn(cari, "\n")] = 0;

    while (!found && i < n) {
        if (strcmp(cari, dataMobil[i].NoMobil) == 0) {
            cout << "Data anda sudah ditemukan ! \n";
            cout << "No Mobil \t: " << dataMobil[i].NoMobil    << endl;
            cout << "Nama Mobil \t: " << dataMobil[i].NamaMobil  << endl;
            cout << "Jenis Mobil \t: " << dataMobil[i].JenisMobil << endl;
            cout << "Tahun Mobil \t: " << dataMobil[i].TahunMobil << endl;
            cout << "Harga Sewa \t: Rp" << dataMobil[i].HargaSewa << "/hari" << endl;
            cout << "Status \t\t: " << dataMobil[i].StatusMobil << endl;
            found = true;
        } else {
            i++;
        }
    }

    if (i == n) {
        cout << "No Mobil yang anda cari : " << cari << endl;
        cout << cari << " tidak ditemukan ! \n";
    }
}

// BINARY SEARCH
void cariDataBinary() {
    char cari[15];
    bool found = false;
    int  i, j, k;
    j = n - 1;
    i = 0;

    if (n == 0) {
        cout << "Data kosong! Silakan input data terlebih dahulu.\n";
        return;
    }

    cout << "BINARY SEARCH \n"
         << "================================= \n";
    cout << "No Mobil yang anda cari : ";
    cin.ignore();
    fgets(cari, 15, stdin);
    cari[strcspn(cari, "\n")] = 0;

    selectionSort(n, 1);

    while ((!found) && (i <= j)) {
        k = (i + j) / 2;
        int cmpResult = strcmp(cari, dataMobil[k].NoMobil);
        if (cmpResult == 0) {
            cout << "Data anda sudah ditemukan ! \n";
            cout << "No Mobil \t: " << dataMobil[k].NoMobil    << endl;
            cout << "Nama Mobil \t: " << dataMobil[k].NamaMobil  << endl;
            cout << "Jenis Mobil \t: " << dataMobil[k].JenisMobil << endl;
            cout << "Tahun Mobil \t: " << dataMobil[k].TahunMobil << endl;
            cout << "Harga Sewa \t: Rp" << dataMobil[k].HargaSewa << "/hari" << endl;
            cout << "Status \t\t: " << dataMobil[k].StatusMobil << endl;
            found = true;
        } else {
            if (cmpResult < 0)
                j = k - 1;
            else
                i = k + 1;
        }
    }

    if (!found) {
        cout << "No Mobil yang anda cari : " << cari << endl;
        cout << cari << " tidak ditemukan ! \n";
    }
}


void ubahStatusMobil(Mobil *pMobil, char *statusBaru) {
    strcpy(pMobil->StatusMobil, statusBaru);
}

void naikkanHarga(Mobil *pMobil, int jumlahNaik) {
    pMobil->HargaSewa = pMobil->HargaSewa + jumlahNaik;
}

void kelolaDataPointer() {
    if (n == 0) {
        cout << "Data kosong! Silakan input data terlebih dahulu.\n";
        return;
    }

    int pilihPointer;
    char noMobil[15];
    system("cls");
    cout << "KELOLA DATA DENGAN POINTER \n"
         << "================================= \n"
         << "1. Ubah Status Mobil\n"
         << "2. Naikkan Harga Sewa\n"
         << "================================= \n"
         << "Pilih : ";
    cin >> pilihPointer;

    if(pilihPointer == 1 || pilihPointer == 2) {
        cout << "Masukkan No Mobil yang ingin diubah : ";
        cin.ignore();
        fgets(noMobil, 15, stdin);
        noMobil[strcspn(noMobil, "\n")] = 0;

        int posisi = -1;
        for (int idx = 0; idx < n; idx++) {
    
            if (strcmp(dataMobil[idx].NoMobil, noMobil) == 0) {
                posisi = idx;
                break;
            }
        }

        if (posisi == -1) {
            cout << "No Mobil " << noMobil << " tidak ditemukan !\n";
            return;
        }

        if (pilihPointer == 1) {
            char statusBaru[15];
            cout << "Status baru (Tersedia/Disewa) : ";
            fgets(statusBaru, 15, stdin);
            statusBaru[strcspn(statusBaru, "\n")] = 0;

            ubahStatusMobil(&dataMobil[posisi], statusBaru);

            cout << "Status mobil berhasil diubah !\n";
            cout << "No Mobil \t: " << dataMobil[posisi].NoMobil    << endl;
            cout << "Nama Mobil \t: " << dataMobil[posisi].NamaMobil  << endl;
            cout << "Status Baru \t: " << dataMobil[posisi].StatusMobil << endl;

        } else if (pilihPointer == 2) {
            int jumlahNaik;
            cout << "Jumlah kenaikan harga (Rp) : ";
            cin  >> jumlahNaik;

            naikkanHarga(&dataMobil[posisi], jumlahNaik);

            cout << "Harga sewa berhasil diperbarui !\n";
            // [REVISI 1] NoMobil ditampilkan sebagai string
            cout << "No Mobil \t: " << dataMobil[posisi].NoMobil   << endl;
            cout << "Nama Mobil \t: " << dataMobil[posisi].NamaMobil << endl;
            cout << "Harga Baru \t: Rp" << dataMobil[posisi].HargaSewa << "/hari" << endl;

        } else {
            cout << "Pilihan tidak tersedia !\n";
            return;
        }

        simpanKeFile();
    } else {
        cout << "Pilihan tidak tersedia !\n";
        return;
    }
}

int main() {
    int  pilih;
    char y;
    int  pilihSearching;
    bool kembaliMenuUtama = true;

    // Coba baca data dari file saat program pertama dijalankan (Modul VII)
    bacaDariFile();

    do {
        cout << "MENU RENTAL MOBIL : \n"
             << "================================= \n";
        cout << "1. Input Data \n"
             << "2. Tampil Data \n"
             << "3. Searching \n"
             << "4. Sorting \n"
             << "5. Kelola Data (Pointer) \n"
             << "6. Simpan ke File \n"
             << "7. Baca dari File \n"
             << "8. Exit \n"
             << "================================= \n";
        cout << "Pilih : ";
        cin  >> pilih;

        switch (pilih) {
            case 1:
                inputData();
                break;

            case 2:
                lihatData();
                break;

            case 3:
                cout << " MENU SEARCHING : \n "
                     << "================================= \n "
                     << " 1. SEQUENSIAL SEARCH \n "
                     << " 2. BINARY SEARCH \n "
                     << " 3. Kembali ke Menu Utama \n "
                     << "================================= \n ";
                cout << "Pilih : ";
                cin  >> pilihSearching;
                switch (pilihSearching) {
                    case 1:
                        cariDataSequensial();
                        break;
                    case 2:
                        cariDataBinary();
                        break;
                    case 3:
                        break;
                    default:
                        cout << "Maaf pilihan yang anda pilih tidak tersedia !";
                }
                break;

            case 4:
                sortingData();
                break;

            case 5:
                kelolaDataPointer();
                break;

            case 6:
                simpanKeFile();
                break;

            case 7:
                bacaDariFile();
                lihatData();
                break;

            case 8:
                kembaliMenuUtama = false;
                break;

            default:
                cout << "Maaf tidak ada pilihan yang sesuai anda pilih !";
                break;
        }

        if (kembaliMenuUtama == true) {
            cout << "Apakah anda ingin mengulang ? (y/t) : ";
            cin  >> y;

            if (y != 'y' && y != 'Y') {
                cout << "Terima kasih !";
                kembaliMenuUtama = false;
            }
        }

    } while (kembaliMenuUtama == true);

    cout << "Terima kasih !";
    return 0;
}