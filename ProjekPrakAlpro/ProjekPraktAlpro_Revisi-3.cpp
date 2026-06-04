// Kelompok 7 : 123250007, 123250013

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

struct Mobil
{
    string NoMobil;
    string NamaMobil;
    string JenisMobil;
    int TahunMobil;
    int HargaSewa;
    string StatusMobil;
};

Mobil dataMobil[100];
int n = 0;

// FUNGSI CEK DUPLIKAT PLAT NOMOR
bool isDuplikat(string noMobil, int kecualiIndex = -1)
{
    for (int i = 0; i < n; i++)
    {
        if (i == kecualiIndex)
            continue;
        if (dataMobil[i].NoMobil == noMobil)
        {
            return true;
        }
    }
    return false;
}

void simpanKeFile()
{
    ofstream fileKeluar("data_mobil.txt");
    if (!fileKeluar)
    {
        cout << "File gagal dibuat !\n";
        return;
    }

    fileKeluar << n << endl;

    for (int i = 0; i < n; i++)
    {
        fileKeluar << dataMobil[i].NoMobil << endl;
        fileKeluar << dataMobil[i].NamaMobil << endl;
        fileKeluar << dataMobil[i].JenisMobil << endl;
        fileKeluar << dataMobil[i].TahunMobil << endl;
        fileKeluar << dataMobil[i].HargaSewa << endl;
        fileKeluar << dataMobil[i].StatusMobil << endl;
    }

    fileKeluar.close();
    cout << "Data berhasil disimpan ke file data_mobil.txt !\n";
}

void bacaDariFile()
{
    ifstream fileMasuk("data_mobil.txt");
    if (!fileMasuk)
    {
        cout << "File tidak ditemukan ! Silakan input data terlebih dahulu.\n";
        return;
    }

    fileMasuk >> n;

    if (n < 0 || n > 100)
    {
        cout << "Data pada file tidak valid!\n";
        n = 0;
        fileMasuk.close();
        return;
    }
    fileMasuk.ignore();

    for (int i = 0; i < n; i++)
    {
        getline(fileMasuk, dataMobil[i].NoMobil);
        getline(fileMasuk, dataMobil[i].NamaMobil);
        getline(fileMasuk, dataMobil[i].JenisMobil);
        fileMasuk >> dataMobil[i].TahunMobil;
        fileMasuk >> dataMobil[i].HargaSewa;
        fileMasuk.ignore();
        getline(fileMasuk, dataMobil[i].StatusMobil);
    }

    fileMasuk.close();
    cout << "Data berhasil dibaca dari file data_mobil.txt !\n";
}

void inputData()
{
    system("cls");

    int jumlahBaru;

    cout << "INPUT DATA\n";
    cout << "=================================\n";
    cout << "Jumlah data yang akan ditambahkan : ";

    while (!(cin >> jumlahBaru) || jumlahBaru < 1)
    {
        cout << "Input harus berupa angka positif!\n";
        cout << "Jumlah data yang akan ditambahkan : ";

        cin.clear();
        cin.ignore(1000, '\n');
    }

    if (n + jumlahBaru > 100)
    {
        cout << "Kapasitas maksimal 100 data!\n";
        return;
    }

    cin.ignore(1000, '\n');

    for (int i = n; i < n + jumlahBaru; i++)
    {

        cout << "\nData ke-" << i + 1 << endl;

        string inputNoMobil;

        do
        {
            cout << "No Mobil (Plat)\t\t: ";
            getline(cin, inputNoMobil);

            if (inputNoMobil.empty())
                cout << "Plat nomor tidak boleh kosong!\n";

            else if (isDuplikat(inputNoMobil))
                cout << "Plat nomor sudah digunakan!\n";

        } while (inputNoMobil.empty() || isDuplikat(inputNoMobil));

        dataMobil[i].NoMobil = inputNoMobil;

        cout << "Nama Mobil\t\t: ";
        getline(cin, dataMobil[i].NamaMobil);

        cout << "Jenis Mobil\t\t: ";
        getline(cin, dataMobil[i].JenisMobil);

        cout << "Tahun Mobil\t\t: ";

        while (!(cin >> dataMobil[i].TahunMobil) || dataMobil[i].TahunMobil < 1900 || dataMobil[i].TahunMobil > 2026)
        {

            cout << "Tahun tidak valid! Input ulang : ";

            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Harga Sewa/Hari (Rp)\t: ";

        while (!(cin >> dataMobil[i].HargaSewa) || dataMobil[i].HargaSewa <= 0)
        {

            cout << "Harga harus lebih dari 0! Input ulang : ";

            cin.clear();
            cin.ignore(1000, '\n');
        }

        cin.ignore(1000, '\n');

        do
        {
            cout << "Status (Tersedia/Disewa): ";
            getline(cin, dataMobil[i].StatusMobil);

            if (dataMobil[i].StatusMobil != "Tersedia" &&
                dataMobil[i].StatusMobil != "Disewa")
            {

                cout << "Status hanya boleh Tersedia atau Disewa!\n";
            }

        } while (dataMobil[i].StatusMobil != "Tersedia" &&
                 dataMobil[i].StatusMobil != "Disewa");
    }

    n += jumlahBaru;

    simpanKeFile();
}

void lihatData()
{
    if (n == 0)
    {
        cout << "\n[!] Data tidak ditemukan ! Silakan input data kembali.\n";
        return;
    }

    cout << "\n"
         << setfill('=') << setw(100) << "" << endl;
    cout << setfill(' ');
    cout << left << setw(15) << "No Mobil"
         << setw(20) << "Nama Mobil"
         << setw(15) << "Jenis"
         << setw(10) << "Tahun"
         << setw(20) << "Harga/Hari"
         << setw(15) << "Status" << endl;
    cout << setfill('=') << setw(100) << "" << endl;
    cout << setfill(' ');

    for (int j = 0; j < n; j++)
    {
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
bool compare(Mobil a, Mobil b, int kriteria)
{
    if (kriteria == 1)
        return a.NoMobil > b.NoMobil;
    if (kriteria == 2)
        return a.NamaMobil > b.NamaMobil;
    if (kriteria == 3)
        return a.HargaSewa > b.HargaSewa;
    return false;
}

// SELECTION SORT
void selectionSort(int n, int kriteria)
{
    for (int i = 0; i < n - 1; i++)
    {
        int indexMin = i;
        for (int j = i + 1; j < n; j++)
        {
            if (compare(dataMobil[indexMin], dataMobil[j], kriteria))
            {
                indexMin = j;
            }
        }
        Mobil temp = dataMobil[i];
        dataMobil[i] = dataMobil[indexMin];
        dataMobil[indexMin] = temp;
    }
}

// INSERTION SORT
void insertionSort(int n, int kriteria)
{
    for (int i = 1; i < n; i++)
    {
        Mobil kunci = dataMobil[i];
        int j = i - 1;
        while (j >= 0 && compare(dataMobil[j], kunci, kriteria))
        {
            dataMobil[j + 1] = dataMobil[j];
            j--;
        }
        dataMobil[j + 1] = kunci;
    }
}

// FUNGSI SORTING DATA
void sortingData()
{
    if (n == 0)
    {
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

    while (cin.fail())
    {
        cout << "Input harus berupa angka!\n";
        cout << "Pilih : ";

        cin.clear();
        cin.ignore(1000, '\n');

        cin >> alg;
    }

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

    if (alg == 1)
        selectionSort(n, kriteria);
    else if (alg == 2)
        insertionSort(n, kriteria);
    else
    {
        cout << "Pilihan algoritma tidak ada!\n";
        return;
    }
    cout << "\nData berhasil diurutkan!\n";
    lihatData();

    simpanKeFile();
}

// SEQUENTIAL SEARCH
void cariDataSequensial()
{
    string cari;
    bool found = false;
    int i = 0;
    cin.ignore(1000, '\n');

    if (n == 0)
    {
        cout << "Data kosong! Silakan input data terlebih dahulu.\n";
        return;
    }

    cout << "SEQUENSIAL SEARCH \n"
         << "================================= \n";
    cout << "No Mobil yang anda cari : ";
    getline(cin, cari);

    while (!found && i < n)
    {
        if (dataMobil[i].NoMobil == cari)
        {
            cout << "Data anda sudah ditemukan ! \n";
            cout << "No Mobil \t: " << dataMobil[i].NoMobil << endl;
            cout << "Nama Mobil \t: " << dataMobil[i].NamaMobil << endl;
            cout << "Jenis Mobil \t: " << dataMobil[i].JenisMobil << endl;
            cout << "Tahun Mobil \t: " << dataMobil[i].TahunMobil << endl;
            cout << "Harga Sewa \t: Rp" << dataMobil[i].HargaSewa << "/hari" << endl;
            cout << "Status \t\t: " << dataMobil[i].StatusMobil << endl;
            found = true;
        }
        else
        {
            i++;
        }
    }

    if (!found)
    {
        cout << "No Mobil yang anda cari : " << cari << endl;
        cout << cari << " tidak ditemukan ! \n";
    }
}

// BINARY SEARCH
void cariDataBinary()
{
    string cari;
    bool found = false;
    int i, j, k;
    j = n - 1;
    i = 0;

    if (n == 0)
    {
        cout << "Data kosong! Silakan input data terlebih dahulu.\n";
        return;
    }

    cout << "BINARY SEARCH \n"
         << "================================= \n";
    cout << "No Mobil yang anda cari : ";
    getline(cin, cari);

    selectionSort(n, 1); // Diurutkan berdasarkan plat nomor terlebih dahulu

    while ((!found) && (i <= j))
    {
        k = (i + j) / 2;
        if (dataMobil[k].NoMobil == cari)
        {
            cout << "Data anda sudah ditemukan ! \n";
            cout << "No Mobil \t: " << dataMobil[k].NoMobil << endl;
            cout << "Nama Mobil \t: " << dataMobil[k].NamaMobil << endl;
            cout << "Jenis Mobil \t: " << dataMobil[k].JenisMobil << endl;
            cout << "Tahun Mobil \t: " << dataMobil[k].TahunMobil << endl;
            cout << "Harga Sewa \t: Rp" << dataMobil[k].HargaSewa << "/hari" << endl;
            cout << "Status \t\t: " << dataMobil[k].StatusMobil << endl;
            found = true;
        }
        else
        {
            if (dataMobil[k].NoMobil > cari)
                j = k - 1;
            else
                i = k + 1;
        }
    }

    if (!found)
    {
        cout << "No Mobil yang anda cari : " << cari << endl;
        cout << cari << " tidak ditemukan ! \n";
    }
}

void ubahStatusMobil(Mobil *pMobil, string statusBaru)
{
    pMobil->StatusMobil = statusBaru;
}

void naikkanHarga(Mobil *pMobil, int jumlahNaik)
{
    pMobil->HargaSewa = pMobil->HargaSewa + jumlahNaik;
}

void kelolaDataPointer()
{
    if (n == 0)
    {
        cout << "Data kosong! Silakan input data terlebih dahulu.\n";
        return;
    }

    int pilihPointer;
    string noMobil;
    system("cls");
    cout << "KELOLA DATA DENGAN POINTER \n"
         << "================================= \n"
         << "1. Ubah Status Mobil\n"
         << "2. Naikkan Harga Sewa\n"
         << "================================= \n"
         << "Pilih : ";
    cin >> pilihPointer;
    cin.ignore(1000, '\n');

    if (pilihPointer == 1 || pilihPointer == 2)
    {
        cout << "Masukkan No Mobil yang ingin diubah : ";
        getline(cin, noMobil);

        int posisi = -1;
        for (int idx = 0; idx < n; idx++)
        {
            if (dataMobil[idx].NoMobil == noMobil)
            {
                posisi = idx;
                break;
            }
        }

        if (posisi == -1)
        {
            cout << "No Mobil " << noMobil << " tidak ditemukan !\n";
            return;
        }

        if (pilihPointer == 1)
        {
            string statusBaru;
            cout << "Status baru (Tersedia/Disewa) : ";
            getline(cin, statusBaru);

            ubahStatusMobil(&dataMobil[posisi], statusBaru);

            cout << "Status mobil berhasil diubah !\n";
            cout << "No Mobil \t: " << dataMobil[posisi].NoMobil << endl;
            cout << "Nama Mobil \t: " << dataMobil[posisi].NamaMobil << endl;
            cout << "Status Baru \t: " << dataMobil[posisi].StatusMobil << endl;
        }
        else if (pilihPointer == 2)
        {
            int jumlahNaik;
            cout << "Jumlah kenaikan harga (Rp) : ";
            cin >> jumlahNaik;

            while (cin.fail()) //digunkn untuk menangani error input jika user memasukkan selain angka
            {
                cout << "Input harus berupa angka!\n";
                cout << "Jumlah kenaikan harga : ";

                cin.clear();
                cin.ignore(1000, '\n');

                cin >> jumlahNaik;
            }

            naikkanHarga(&dataMobil[posisi], jumlahNaik);

            cout << "Harga sewa berhasil diperbarui !\n";
            cout << "No Mobil \t: " << dataMobil[posisi].NoMobil << endl;
            cout << "Nama Mobil \t: " << dataMobil[posisi].NamaMobil << endl;
            cout << "Harga Baru \t: Rp" << dataMobil[posisi].HargaSewa << "/hari" << endl;
        }
        simpanKeFile();
    }
    else
    {
        cout << "Pilihan tidak tersedia !\n";
        return;
    }
}

int main()
{
    int pilih;
    char y;
    int pilihSearching;
    bool kembaliMenuUtama = true;

    bacaDariFile();

    do
    {
        cout << "\nMENU RENTAL MOBIL : \n"
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
        cin >> pilih;

        while (cin.fail())
        {
            cout << "Input harus berupa angka!\n";
            cout << "Pilih : ";

            cin.clear();
            cin.ignore(1000, '\n');

            cin >> pilih;
        }

        switch (pilih)
        {
        case 1:
            inputData();
            break;

        case 2:
            lihatData();
            break;

        case 3:
            cout << "\nMENU SEARCHING : \n "
                 << "================================= \n "
                 << " 1. SEQUENSIAL SEARCH \n "
                 << " 2. BINARY SEARCH \n "
                 << " 3. Kembali ke Menu Utama \n "
                 << "================================= \n ";
            cout << "Pilih : ";
            cin >> pilihSearching;

            while (cin.fail())
            {
                cout << "Input harus berupa angka!\n";
                cout << "Pilih : ";

                cin.clear();
                cin.ignore(1000, '\n');

                cin >> pilihSearching;
            }
            cin.ignore(1000, '\n');

            switch (pilihSearching)
            {
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

        if (kembaliMenuUtama == true)
        {
            cout << "\nApakah anda ingin mengulang ? (y/t) : ";
            cin >> y;
            cin.ignore(1000, '\n');

            if (y != 'y' && y != 'Y')
            {
                kembaliMenuUtama = false;
            }
        }

    } while (kembaliMenuUtama == true);

    cout << "Terima kasih !";
    return 0;
}