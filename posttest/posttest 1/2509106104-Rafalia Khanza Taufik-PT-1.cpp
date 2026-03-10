#include <iostream>
#include <string>
using namespace std;

int main() {

    string nama_input, pass_input;
    bool login_berhasil = false;
    int percobaan = 0;

    string nama_valid = "rafa";
    string pass_valid = "104";

    cout << endl;
    cout << "  --------------------------------------------" << endl;
    cout << "  |         PROGRAM KONVERSI WAKTU           |" << endl;
    cout << "  |       Algoritma Pemrograman Lanjut       |" << endl;
    cout << "  |          Kelas C25 Informatika           |" << endl;
    cout << "  --------------------------------------------" << endl;

    cout << endl;
    cout << "  --------------------------------------------" << endl;
    cout << "  |                  LOGIN                   |" << endl;
    cout << "  --------------------------------------------" << endl;
    cout << "  |     Masukkan Nama dan Password Anda      |" << endl;
    cout << "  --------------------------------------------" << endl;

    while (percobaan < 3) {
        percobaan++;

        cout << endl;
        cout << "Percobaan ke-" << percobaan << " dari 3" << endl;
        cout << "Nama     :";
        cin >> nama_input;

        bool pass_oke = false;
        while (pass_oke == false) {
            cout << "Password : ";
            cin >> pass_input;

        bool digit_pertama = (pass_input[0] >= '0' && pass_input[0] <= '9');  
        bool digit_kedua   = (pass_input[1] >= '0' && pass_input[1] <= '9');  
        bool digit_ketiga  = (pass_input[2] >= '0' && pass_input[2] <= '9');  
        bool panjang_tepat = (pass_input[3] == '\0');                         

            if (digit_pertama && digit_kedua && digit_ketiga && panjang_tepat) {
                pass_oke = true;
            } 
            
            else {
                cout << "Password harus 3 digit angka!" << endl;
            }
        }

        if (nama_input == nama_valid && pass_input == pass_valid) {
            login_berhasil = true;

            break;

        } else {
            int sisa = 3 - percobaan;
            if (sisa > 0) {
                cout << endl;
                cout << "Nama atau password salah. Silahkan coba lagi" << endl;
                cout << "Sisa Percobaan: " << sisa << "x" << endl;
            }
        }
    }

    if (login_berhasil == false) {
        cout << endl;
        cout << "  --------------------------------------------" << endl;
        cout << "  |  Login gagal! Program Dihentikan.        |" << endl;
        cout << "  --------------------------------------------" << endl;
        cout << endl;

        return 0;
    }

    cout << endl;
    cout << "  --------------------------------------------" << endl;
    cout << "  |      Login Berhasil! Selamat Datang      |" << endl;
    cout << "  --------------------------------------------" << endl;

    int pilihan = 0;

    while (pilihan != 4) {

        cout << endl;
        cout << "  --------------------------------------------------------------" << endl;
        cout << "  |  Halo, " << nama_input << "! Pilih Menu Konversi Anda      |" << endl;
        cout << "  --------------------------------------------------------------" << endl;
        cout << "  |  [1] Konversi Jam    --> Menit & Detik                     |" << endl;
        cout << "  |  [2] Konversi Menit  --> Jam & Detik                       |" << endl;
        cout << "  |  [3] Konversi Detik  --> Jam & Menit                       |" << endl;
        cout << "  |  [4] Keluar                                                |" << endl;
        cout << "  --------------------------------------------------------------" << endl;
        cout << "Pilih Menu Anda [1-4]:";
        cin >> pilihan;

        if (pilihan == 1) {

            float jam;
            cout << endl;
            cout << "  --------------------------------------------" << endl;
            cout << "  |      KONVERSI JAM --> MENIT & DETIK      |" << endl;
            cout << "  --------------------------------------------" << endl;
            cout << "Masukkan Nilai Jam: ";
            cin >> jam;

            float menit = jam * 60;
            float detik = jam * 3600;

            cout << endl;
            cout << "  Hasil:" << endl;
            cout << "  " << jam << " Jam  =  " << menit << " Menit" << endl;
            cout << "  " << jam << " Jam  =  " << detik << " Detik" << endl;
            cout << "  --------------------------------------------" << endl;

        } else if (pilihan == 2) {

            float menit;
            cout << endl;
            cout << "  --------------------------------------------" << endl;
            cout << "  |      KONVERSI MENIT --> JAM & DETIK      |" << endl;
            cout << "  --------------------------------------------" << endl;
            cout << "Masukkan Nilai Menit: ";
            cin >> menit;

            float jam   = menit / 60;
            float detik = menit * 60;

            cout << endl;
            cout << "  Hasil:" << endl;
            cout << "  " << menit << " Menit  =  " << jam   << " Jam"   << endl;
            cout << "  " << menit << " Menit  =  " << detik << " Detik" << endl;
            cout << "  --------------------------------------------" << endl;

        } else if (pilihan == 3) {

            float detik;
            cout << endl;
            cout << "  --------------------------------------------" << endl;
            cout << "  |      KONVERSI DETIK --> JAM & MENIT      |" << endl;
            cout << "  --------------------------------------------" << endl;
            cout << "Masukkan Nilai Detik: ";
            cin >> detik;

            float jam   = detik / 3600;
            float menit = detik / 60;

            cout << endl;
            cout << "  Hasil:" << endl;
            cout << "  " << detik << " Detik  =  " << jam   << " Jam"   << endl;
            cout << "  " << detik << " Detik  =  " << menit << " Menit" << endl;
            cout << "  --------------------------------------------" << endl;

        } else if (pilihan == 4) {

            cout << endl;
            cout << "  --------------------------------------------" << endl;
            cout << "  |     Terima kasih! Program Selesai.       |" << endl;
            cout << "  --------------------------------------------" << endl;
            cout << endl;

        } else {
            cout << endl;
            cout << "  ! Pilihan tidak valid. Masukkan angka 1-4." << endl;
        }
    }

    return 0;
}