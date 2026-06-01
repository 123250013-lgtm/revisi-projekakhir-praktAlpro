#include <iostream>
#include <cmath>
#include <iomanip>

// Fungsi sesuai soal nomor 12: f(x) = sqrt(x^3 + 1)
double f(double x) {
    return std::sqrt(std::pow(x, 3) + 1);
}

// Rumus Riemann Kanan yang sudah diperbaiki akurasinya
double hitungRiemann(double a, double b, double deltaX) {
    double totalLuas = 0.0;
    int n = static_cast<int>(std::round((b - a) / deltaX));
    if (n <= 0) return 0.0; 

    for (int i = 1; i <= n; ++i) {
        double x_i = a + i * deltaX; // Titik sampel kanan
        totalLuas += f(x_i) * deltaX;
    }
    return totalLuas;
}

int main() {
    char pilihanMenu;
    do {
        std::cout << "\n====================================================\n";
        std::cout << "   PROGRAM PERBANDINGAN RIEMANN: f(x) = sqrt(x^3 + 1) \n";
        std::cout << "====================================================\n";
        
        double a, b;
        std::cout << "Masukkan Batas Bawah (a) : ";
        std::cin >> a;
        std::cout << "Masukkan Batas Atas (b)  : ";
        std::cin >> b;
        
        if (a >= b) {
            std::cout << "\n[Error] Batas bawah (a) harus lebih kecil dari batas atas (b)!\n";
        } else {
            double dx_kasar = 1.0;
            double dx_tipis = 0.01;
            
            double hasilKasar = hitungRiemann(a, b, dx_kasar);
            double hasilTipis = hitungRiemann(a, b, dx_tipis);
            double selisih = std::abs(hasilKasar - hasilTipis);
            
            std::cout << std::fixed << std::setprecision(5);
            std::cout << "----------------------------------------------------\n";
            std::cout << "HASIL KOMPUTASI NYATA:\n";
            std::cout << "----------------------------------------------------\n";
            std::cout << "1. Skenario Partisi Kasar (dx = 1.00000)\n";
            std::cout << "   -> Jumlah Kotak (n)   : " << static_cast<int>(std::round((b - a) / dx_kasar)) << "\n";
            std::cout << "   -> Hasil Riemann      : " << hasilKasar << "\n\n";
            
            std::cout << "2. Skenario Partisi Tipis (dx = 0.01000)\n";
            std::cout << "   -> Jumlah Kotak (n)   : " << static_cast<int>(std::round((b - a) / dx_tipis)) << "\n";
            std::cout << "   -> Hasil Riemann      : " << hasilTipis << "\n";
            std::cout << "----------------------------------------------------\n";
            std::cout << "-> Selisih Penyimpangan  : " << selisih << "\n";
            std::cout << "----------------------------------------------------\n";
        }

        std::cout << "\nApakah Anda ingin mencoba angka lain? (y/t): ";
        std::cin >> pilihanMenu;

    } while (pilihanMenu == 'y' || pilihanMenu == 'Y');

    std::cout << "\nTerima kasih! Program selesai.\n";
    return 0;
}