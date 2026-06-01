// Kelompok 8 : 123250007, 123250013

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

typedef struct {
    int  NoMobil;
    char NamaMobil[30];
    char JenisMobil[20];
    int  TahunMobil;
    int  HargaSewa;
    char StatusMobil[15]; // "Tersedia" atau "Disewa"
} Mobil;

Mobil dataMobil[100];
Mobil dataTemp[100]; //Array global untuk menyimpan data sementara saat merge
int n = 0;

void simpanKeFile() {
    FILE *pf;
    pf = fopen("data_mobil.txt", "wb"); // buka file biner untuk ditulis
    if (pf == NULL) {
        cout << "File gagal dibuat !\n";
        return;
    }
    // Tulis jumlah data dulu, lalu tulis seluruh array per blok
    fwrite(&n,          sizeof(int),   1, pf);
    fwrite(dataMobil,   sizeof(Mobil), n, pf);
    fclose(pf);
    cout << "Data berhasil disimpan ke file data_mobil.txt !\n";
}

// Fungsi buat baca data dari file biner
// =============================================
void bacaDariFile() {
    FILE *pf;
    pf = fopen("data_mobil.txt", "rb"); // untuk buka file biner untuk dibaca
    if (pf == NULL) {
        cout << "File tidak ditemukan ! Silakan input data terlebih dahulu.\n";
        return;
    }
    // Baca jumlah data dulu, lalu baca seluruh array per blok
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
        cout << "No Mobil \t\t: ";
        cin  >> dataMobil[i].NoMobil;
        cout << "Nama Mobil \t\t: ";
        cin.ignore();
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

    // Otomatis menyimpan ke file setelah input
    simpanKeFile();
}

void lihatData() {
    if (n == 0) {
        cout << "\n[!] Data tidak ditemukan ! Silakan input data kembali.\n";
        return;
    }

    cout << "\n" << setfill('=') << setw(95) << "" << endl;
    cout << setfill(' ');
    cout << left << setw(5) << "No"
         << setw(20) << "Nama Mobil"
         << setw(15) << "Jenis"
         << setw(10) << "Tahun"
         << setw(20) << "Harga/Hari"
         << setw(15) << "Status" << endl;
    cout << setfill('=') << setw(95) << "" << endl;
    cout << setfill(' ');

    for (int j = 0; j < n; j++) {
        cout << left << setw(5) << dataMobil[j].NoMobil
            << setw(20) << dataMobil[j].NamaMobil
            << setw(15) << dataMobil[j].JenisMobil
            << setw(10) << dataMobil[j].TahunMobil
            << "Rp" << setw(17) << dataMobil[j].HargaSewa
            << setw(15) << dataMobil[j].StatusMobil << endl;
    }

    cout << setfill('=') << setw(95) << "" << endl;
    cout << setfill(' ');

}

// =============================================
// FUNGSI Untuk PEMBANTU PERBANDINGAN
// =============================================
bool compare(Mobil a, Mobil b, int kriteria) {
    if (kriteria == 1) return a.NoMobil   > b.NoMobil;              // No Mobil
    if (kriteria == 2) return strcmp(a.NamaMobil, b.NamaMobil) > 0; // Nama Mobil
    if (kriteria == 3) return a.HargaSewa > b.HargaSewa;            // Harga Sewa
    return false;
}

// =============================================
// BUBBLE SORT
// =============================================
void bubbleSort(int n, int kriteria) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(dataMobil[j], dataMobil[j + 1], kriteria)) {
                Mobil temp       = dataMobil[j];
                dataMobil[j]     = dataMobil[j + 1];
                dataMobil[j + 1] = temp;
            }
        }
    }
}

// =============================================
// SELECTION SORT
// =============================================
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

// =============================================
// INSERTION SORT
// =============================================
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

// =============================================
// MERGE SORT
// =============================================
void merge(int low, int mid, int high, int kriteria) {
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high) {
        if (!compare(dataMobil[i], dataMobil[j], kriteria)) {
            dataTemp[k] = dataMobil[i]; i++;
        } else {
            dataTemp[k] = dataMobil[j]; j++;
        }
        k++;
    }
    while (i <= mid)  { dataTemp[k] = dataMobil[i]; i++; k++; }
    while (j <= high) { dataTemp[k] = dataMobil[j]; j++; k++; }
    for (k = low; k <= high; k++) dataMobil[k] = dataTemp[k];
}

void mergeSort(int low, int high, int kriteria) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(low,     mid,  kriteria); // Belah kiri
        mergeSort(mid + 1, high, kriteria); // Belah kanan
        merge(low, mid, high, kriteria);    // Gabungkan
    }
}

// =============================================
// QUICK SORT
// =============================================
void quickSort(int low, int high, int kriteria) {
    if (low < high) {
        Mobil pivot = dataMobil[high];
        int   i     = low - 1;

        for (int j = low; j < high; j++) {
            if (!compare(dataMobil[j], pivot, kriteria)) {
                i++;
                Mobil temp   = dataMobil[i];
                dataMobil[i] = dataMobil[j];
                dataMobil[j] = temp;
            }
        }
        Mobil temp          = dataMobil[i + 1];
        dataMobil[i + 1]    = dataMobil[high];
        dataMobil[high]     = temp;

        int p = i + 1;
        quickSort(low,   p - 1, kriteria); // Urutkan kiri pivot
        quickSort(p + 1, high,  kriteria); // Urutkan kanan pivot
    }
}

// =============================================
// SHELL SORT
// =============================================
void shellSort(int n, int kriteria) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Mobil temp = dataMobil[i];
            int   j;
            for (j = i; j >= gap && compare(dataMobil[j - gap], temp, kriteria); j -= gap) {
                dataMobil[j] = dataMobil[j - gap];
            }
            dataMobil[j] = temp;
        }
    }
}

// =============================================
// FUNGSI SORTING DATA
// =============================================
void sortingData() {
    if (n == 0) {
        cout << "Data kosong! Silakan input data terlebih dahulu.\n";
        return;
    }
    int alg, kriteria;
    system("cls");
    cout << "PILIH ALGORITMA SORTING \n"
         << "================================= \n"
         << "1. Bubble Sort\n"
         << "2. Selection Sort\n"
         << "3. Insertion Sort\n"
         << "4. Merge Sort\n"
         << "5. Quick Sort\n"
         << "6. Shell Sort\n"
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

    if      (alg == 1) bubbleSort(n, kriteria);
    else if (alg == 2) selectionSort(n, kriteria);
    else if (alg == 3) insertionSort(n, kriteria);
    else if (alg == 4) mergeSort(0, n - 1, kriteria);
    else if (alg == 5) quickSort(0, n - 1, kriteria);
    else if (alg == 6) shellSort(n, kriteria);
    else {
        cout << "Pilihan algoritma tidak ada!\n";
        return;
    }

    cout << "\nData berhasil diurutkan!\n";
    lihatData();

    // Simpan hasil sorting ke file
    simpanKeFile();
}

// =============================================
// SEQUENTIAL SEARCH
// =============================================
void cariDataSequensial() {
    int  cari;
    bool found = false;
    int  i     = 0;

    if (n == 0) {
        cout << "Data kosong! Silakan input data terlebih dahulu.\n";
        return;
    }

    cout << "SEQUENSIAL SEARCH \n"
         << "================================= \n";
    cout << "No Mobil yang anda cari : ";
    cin  >> cari;

    while (!found && i < n) {
        if (cari == dataMobil[i].NoMobil) {
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

// =============================================
// BINARY SEARCH
// =============================================
void cariDataBinary() {
    int  cari;
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
    cin  >> cari;

    // Data diurutkan dulu sebelum Binary Search
    bubbleSort(n, 1);

    while ((!found) && (i <= j)) {
        k = (i + j) / 2;
        if (cari == dataMobil[k].NoMobil) {
            cout << "Data anda sudah ditemukan ! \n";
            cout << "No Mobil \t: " << dataMobil[k].NoMobil    << endl;
            cout << "Nama Mobil \t: " << dataMobil[k].NamaMobil  << endl;
            cout << "Jenis Mobil \t: " << dataMobil[k].JenisMobil << endl;
            cout << "Tahun Mobil \t: " << dataMobil[k].TahunMobil << endl;
            cout << "Harga Sewa \t: Rp" << dataMobil[k].HargaSewa << "/hari" << endl;
            cout << "Status \t\t: " << dataMobil[k].StatusMobil << endl;
            found = true;
        } else {
            if (cari < dataMobil[k].NoMobil)
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

// =============================================
// Fungsi mengubah status mobil menggunakan pointer
// Parameter formal berupa pointer yang menunjuk ke struct
// =============================================
void ubahStatusMobil(Mobil *pMobil, char *statusBaru) {
    // Akses field struct melalui pointer menggunakan operator ->
    strcpy(pMobil->StatusMobil, statusBaru);
}

// Fungsi menaikkan harga sewa menggunakan pointer
void naikkanHarga(Mobil *pMobil, int jumlahNaik) {
    // Nilai field diubah lewat pointer, bukan langsung dari variabel
    pMobil->HargaSewa = pMobil->HargaSewa + jumlahNaik;
}

// Menu kelola data dengan pointer
void kelolaDataPointer() {
    if (n == 0) {
        cout << "Data kosong! Silakan input data terlebih dahulu.\n";
        return;
    }

    int pilihPointer, noMobil;
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
    cin  >> noMobil;

    // Cari posisi data dengan Sequential Search
    int posisi = -1;
    for (int idx = 0; idx < n; idx++) {
        if (dataMobil[idx].NoMobil == noMobil) {
            posisi = idx;
            break;
        }
    }

    if (posisi == -1) {
        cout << "No Mobil " << noMobil << " tidak ditemukan !\n";
        return;
    }

    if (pilihPointer == 1) {
        char statusBaru[10];
        cout << "Status baru (Tersedia/Disewa) : ";
        cin.ignore();
        fgets(statusBaru, 10, stdin);
        statusBaru[strcspn(statusBaru, "\n")] = 0;

        // Kirim alamat elemen array ke fungsi (pointer ke struct)
        ubahStatusMobil(&dataMobil[posisi], statusBaru);

        cout << "Status mobil berhasil diubah !\n";
        cout << "No Mobil \t: " << dataMobil[posisi].NoMobil    << endl;
        cout << "Nama Mobil \t: " << dataMobil[posisi].NamaMobil  << endl;
        cout << "Status Baru \t: " << dataMobil[posisi].StatusMobil << endl;

    } else if (pilihPointer == 2) {
        int jumlahNaik;
        cout << "Jumlah kenaikan harga (Rp) : ";
        cin  >> jumlahNaik;

        // Kirim alamat elemen array ke fungsi (pointer ke struct)
        naikkanHarga(&dataMobil[posisi], jumlahNaik);

        cout << "Harga sewa berhasil diperbarui !\n";
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