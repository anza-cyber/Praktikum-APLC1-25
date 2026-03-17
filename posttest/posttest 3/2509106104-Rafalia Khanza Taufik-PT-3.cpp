#include <iostream>
#include <iomanip>

using namespace std;

struct Harga {
    double satuan;
    string matauang;
};
struct Stok {
    int    jumlah;
    string satuan;
};
struct Bunga {
    string nama;
    Harga  harga;
    Stok   stok;
    string warna;
    int    aktif;
};
struct Pengguna {
    string nama;
    string nim;
    string role;
    int    aktif;
};

int MAKS_PENGGUNA = 10;
int MAKS_BUNGA    = 100;

Pengguna dataPengguna[10];
Bunga    daftarBunga[100];

int jumlahPengguna = 0;
int totalBunga     = 0;

void menuAdmin(string namaUser);
void menuPelanggan(string namaUser);

string angkaKeStr(long long n) {
    if (n == 0) return "0";
    string s = "";
    while (n > 0) { s = char('0' + n % 10) + s; n /= 10; }
    return s;
}

string rupiahFormat(double angka) {
    string s = angkaKeStr((long long)angka);
    int n = s.size();
    string hasil = "";
    for (int i = 0; i < n; i++) {
        if (i > 0 && (n - i) % 3 == 0) hasil += ".";
        hasil += s[i];
    }
    return "Rp " + hasil;
}

int validAngka(string s) {
    if (s.size() == 0) return 0;
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] < '0' || s[i] > '9') return 0;
    return 1;
}

int bacaAngka(string s) {
    int hasil = 0;
    for (int i = 0; i < (int)s.size(); i++)
        hasil = hasil * 10 + (s[i] - '0');
    return hasil;
}

double bacaHarga(string s) {
    double h = 0;
    for (int i = 0; i < (int)s.size(); i++) h = h * 10 + (s[i] - '0');
    return h;
}

int tampilTabel(int stockOnly) {
    cout << "\n+----+--------------------+----------------+---------+-------------+\n";
    cout << "| No | Nama Bunga         | Harga          | Stok    | Warna       |\n";
    cout << "+----+--------------------+----------------+---------+-------------+\n";

    int no = 0, adaData = 0;
    for (int i = 0; i < totalBunga; i++) {
        if (daftarBunga[i].aktif == 0) continue;
        if (stockOnly == 1 && daftarBunga[i].stok.jumlah == 0) continue;
        no++;
        adaData = 1;
        cout << "| " << left << setw(3) << no
             << "| " << setw(19) << daftarBunga[i].nama
             << "| " << setw(15) << rupiahFormat(daftarBunga[i].harga.satuan)
             << "| " << setw(8)  << daftarBunga[i].stok.jumlah
             << "| " << setw(12) << daftarBunga[i].warna << "|\n";
    }
    if (adaData == 0)
        cout << "|               (belum ada data bunga)                        |\n";
    cout << "+----+--------------------+----------------+---------+-------------+\n";
    return no;
}

int pilihNomor(string aksi) {
    int peta[100], no = 0;
    for (int i = 0; i < totalBunga; i++)
        if (daftarBunga[i].aktif == 1) peta[no++] = i;

    tampilTabel(0);

    if (no == 0) { cout << "Yahh, Belum ada bunga nih...\n"; return -1; }

    string pilih;
    cout << "\nMau " << aksi << " bunga nomor berapa? ";
    getline(cin, pilih);

    if (validAngka(pilih) == 0) { cout << "Nomornya gak valid!\n"; return -1; }

    int nomor = bacaAngka(pilih);
    if (nomor < 1 || nomor > no) { cout << "Nomornya di luar jangkauan!\n"; return -1; }

    return peta[nomor - 1];
}

void tambahBunga() {
    cout << "\n--- Tambah Bunga Baru ---\n";

    if (totalBunga >= MAKS_BUNGA) {
        cout << "Data bunga udah penuh nih!\n";
        return;
    }

    Bunga bunga;
    string hargaStr, stokStr;

    cout << "Nama bunga  : "; getline(cin, bunga.nama);
    cout << "Harga (Rp)  : "; getline(cin, hargaStr);
    cout << "Stok        : "; getline(cin, stokStr);
    cout << "Warna       : "; getline(cin, bunga.warna);

    if (validAngka(hargaStr) == 0 || validAngka(stokStr) == 0) {
        cout << "Harga sama stok harus angka ya!\n";
        return;
    }

    bunga.harga.satuan   = bacaHarga(hargaStr);
    bunga.harga.matauang = "IDR";
    bunga.stok.jumlah    = bacaAngka(stokStr);
    bunga.stok.satuan    = "tangkai";
    bunga.aktif          = 1;

    daftarBunga[totalBunga++] = bunga;
    cout << "Bunga '" << bunga.nama << "' udah ditambahin!\n";
}

void lihatBunga() {
    cout << "\n--- Daftar Bunga di Toko Bunga Hias Rafalia ---";
    tampilTabel(0);
}

void editBunga() {
    cout << "\n--- Edit Data Bunga ---\n";
    int idx = pilihNomor("edit");
    if (idx == -1) return;

    Bunga& bunga = daftarBunga[idx];
    cout << "\nEdit '" << bunga.nama << "' (langsung Enter = gak berubah)\n\n";

    string namaBaru, hargaBaru, stokBaru, warnaBaru;

    cout << "Nama baru  [" << bunga.nama << "]: ";
    getline(cin, namaBaru);
    if (namaBaru.size() > 0) bunga.nama = namaBaru;

    cout << "Harga baru [" << rupiahFormat(bunga.harga.satuan) << "]: ";
    getline(cin, hargaBaru);
    if (hargaBaru.size() > 0) {
        if (validAngka(hargaBaru) == 1) bunga.harga.satuan = bacaHarga(hargaBaru);
        else cout << "Harga gak valid, gak diubah.\n";
    }

    cout << "Stok baru  [" << bunga.stok.jumlah << "]: ";
    getline(cin, stokBaru);
    if (stokBaru.size() > 0) {
        if (validAngka(stokBaru) == 1) bunga.stok.jumlah = bacaAngka(stokBaru);
        else cout << "Stok gak valid, gak diubah.\n";
    }

    cout << "Warna baru [" << bunga.warna << "]: ";
    getline(cin, warnaBaru);
    if (warnaBaru.size() > 0) bunga.warna = warnaBaru;

    cout << "Data berhasil diupdate!\n";
}

void hapusBunga() {
    cout << "\n--- Hapus Bunga ---\n";
    int idx = pilihNomor("hapus");
    if (idx == -1) return;

    string konfirm;
    cout << "\nYakin mau hapus '" << daftarBunga[idx].nama << "'? (y/n): ";
    getline(cin, konfirm);

    if (konfirm == "y" || konfirm == "Y") {
        cout << "Bunga '" << daftarBunga[idx].nama << "' udah dihapus!\n";
        daftarBunga[idx].aktif = 0;
    } else {
        cout << "Penghapusan dibatalkan.\n";
    }
}

void lihatKatalog() {
    cout << "\n--- Katalog Bunga Rafalia ---";
    tampilTabel(0);
}

void cariBunga() {
    cout << "\n--- Cari Bunga ---\n";
    string keyword;
    cout << "Mau cari bunga apa? ";
    getline(cin, keyword);

    for (int i = 0; i < (int)keyword.size(); i++) keyword[i] = tolower(keyword[i]);

    cout << "\n+----+--------------------+----------------+---------+-------------+\n";
    cout << "| No | Nama Bunga         | Harga          | Stok    | Warna       |\n";
    cout << "+----+--------------------+----------------+---------+-------------+\n";

    int ketemu = 0;
    for (int i = 0; i < totalBunga; i++) {
        if (daftarBunga[i].aktif == 0) continue;
        string namaBunga = daftarBunga[i].nama;
        for (int j = 0; j < (int)namaBunga.size(); j++) namaBunga[j] = tolower(namaBunga[j]);
        if (namaBunga.find(keyword) != string::npos) {
            ketemu++;
            cout << "| " << left << setw(3) << ketemu
                 << "| " << setw(19) << daftarBunga[i].nama
                 << "| " << setw(15) << rupiahFormat(daftarBunga[i].harga.satuan)
                 << "| " << setw(8)  << daftarBunga[i].stok.jumlah
                 << "| " << setw(12) << daftarBunga[i].warna << "|\n";
        }
    }
    if (ketemu == 0)
        cout << "|         Bunga yang dicari gak ketemu...                    |\n";
    cout << "+----+--------------------+----------------+---------+-------------+\n";
    if (ketemu > 0) cout << "Ditemukan " << ketemu << " bunga.\n";
}

void beliBunga() {
    cout << "\n--- Beli Bunga ---\n";

    int adaStok = 0;
    for (int i = 0; i < totalBunga; i++)
        if (daftarBunga[i].aktif == 1 && daftarBunga[i].stok.jumlah > 0) { adaStok = 1; break; }

    if (adaStok == 0) { cout << "Maaf ya, semua bunga lagi habis nih...\n"; return; }

    int peta[100], no = 0;
    for (int i = 0; i < totalBunga; i++)
        if (daftarBunga[i].aktif == 1 && daftarBunga[i].stok.jumlah > 0)
            peta[no++] = i;

    tampilTabel(1);

    string pilihanBeli, pilihanJumlah;
    cout << "\nMau beli yang nomor berapa? ";
    getline(cin, pilihanBeli);

    if (validAngka(pilihanBeli) == 0 || bacaAngka(pilihanBeli) < 1 || bacaAngka(pilihanBeli) > no) {
        cout << "Nomornya gak valid!\n"; return;
    }

    int idx = peta[bacaAngka(pilihanBeli) - 1];
    Bunga& bunga = daftarBunga[idx];

    cout << "Mau beli berapa " << bunga.nama << "? (stok ada: " << bunga.stok.jumlah << "): ";
    getline(cin, pilihanJumlah);

    if (validAngka(pilihanJumlah) == 0 || bacaAngka(pilihanJumlah) <= 0) {
        cout << "Jumlahnya gak valid!\n"; return;
    }

    int jumlah = bacaAngka(pilihanJumlah);
    if (jumlah > bunga.stok.jumlah) {
        cout << "Stok gak cukup! Cuma ada " << bunga.stok.jumlah << " " << bunga.stok.satuan << ".\n";
        return;
    }

    double total = bunga.harga.satuan * jumlah;
    bunga.stok.jumlah -= jumlah;

    cout << "\n--- Pembelian Berhasil! ---\n";
    cout << "  Bunga    : " << bunga.nama << "\n";
    cout << "  Warna    : " << bunga.warna << "\n";
    cout << "  Harga    : " << rupiahFormat(bunga.harga.satuan) << " / " << bunga.stok.satuan << "\n";
    cout << "  Jumlah   : " << jumlah << " " << bunga.stok.satuan << "\n";
    cout << "  --------------------------------\n";
    cout << "  Total    : " << rupiahFormat(total) << "\n";
    cout << "  Makasih udah belanja di Toko Bunga Hias Rafalia!\n";
}

void doRegister() {
    if (jumlahPengguna >= MAKS_PENGGUNA) {
        cout << "Yah, slot pengguna udah penuh nih!\n";
        return;
    }

    cout << "\n=== DAFTAR AKUN BARU ===\n";

    string nama, nim;

    cout << "Nama : ";
    getline(cin, nama);

    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].nama == nama) {
            cout << "Yah, nama itu udah dipake orang lain, pake nama lain ya!...\n";
            return;
        }
    }

    cout << "NIM : ";
    getline(cin, nim);

    dataPengguna[jumlahPengguna].nama  = nama;
    dataPengguna[jumlahPengguna].nim   = nim;
    dataPengguna[jumlahPengguna].role  = "pelanggan";
    dataPengguna[jumlahPengguna].aktif = 1;
    jumlahPengguna++;

    cout << "\nYes! Akun '" << nama << "' berhasil dibuat sebagai pelanggan!\n";
}

int doLogin() {
    int coba = 0;
    while (coba < 3) {
        cout << "\n=== LOGIN TOKO BUNGA HIAS RAFALIA ===\n";

        string inputNama, inputNim;
        cout << "Nama : "; getline(cin, inputNama);
        cout << "NIM  : "; getline(cin, inputNim);

        int ketemu = -1;
        for (int i = 0; i < jumlahPengguna; i++) {
            if (dataPengguna[i].aktif == 1 &&
                dataPengguna[i].nama  == inputNama &&
                dataPengguna[i].nim   == inputNim) {
                ketemu = i;
                break;
            }
        }

        if (ketemu != -1) {
            cout << "\nLogin berhasil! Hai " << dataPengguna[ketemu].nama << " :)\n";
            if (dataPengguna[ketemu].role == "admin")
                menuAdmin(dataPengguna[ketemu].nama);
            else
                menuPelanggan(dataPengguna[ketemu].nama);
            return 1;
        }

        coba++;
        cout << "\nLogin gagal. Nama atau NIM salah.\n";
        if (coba < 3)
            cout << "Kesempatan mencoba sisa " << (3 - coba) << " lagi\n";
    }

    cout << "\nTerlalu banyak percobaan login. Program berhenti.\n";
    return 0;
}

void menuAdmin(string namaUser) {
    string pilihan;
    while (true) {
        cout << "\n==================================================\n";
        cout << "       TOKO BUNGA HIAS RAFALIA - ADMIN\n";
        cout << "==================================================\n";
        cout << "  Halo, " << namaUser << "!\n\n";
        cout << "  [1] Tambah Bunga Baru\n";
        cout << "  [2] Lihat Semua Bunga\n";
        cout << "  [3] Edit Data Bunga\n";
        cout << "  [4] Hapus Bunga\n";
        cout << "  [0] Logout\n";
        cout << "==================================================\n";
        cout << "  Mau ngapain? (0-4): ";
        getline(cin, pilihan);

        if      (pilihan == "1") tambahBunga();
        else if (pilihan == "2") lihatBunga();
        else if (pilihan == "3") editBunga();
        else if (pilihan == "4") hapusBunga();
        else if (pilihan == "0") { cout << "Sampai jumpa lagi! BYE BYE\n"; return; }
        else cout << "Pilihan gak valid, coba lagi dong...\n";
    }
}

void menuPelanggan(string namaUser) {
    string pilihan;
    while (true) {
        cout << "\n==================================================\n";
        cout << "     TOKO BUNGA HIAS RAFALIA - PELANGGAN\n";
        cout << "==================================================\n";
        cout << "  Halo, " << namaUser << "!\n\n";
        cout << "  [1] Lihat Katalog Bunga\n";
        cout << "  [2] Cari Bunga Favorit\n";
        cout << "  [3] Beli Bunga\n";
        cout << "  [0] Keluar\n";
        cout << "==================================================\n";
        cout << "  Mau apa? (0-3): ";
        getline(cin, pilihan);

        if      (pilihan == "1") lihatKatalog();
        else if (pilihan == "2") cariBunga();
        else if (pilihan == "3") beliBunga();
        else if (pilihan == "0") { cout << "Makasih udah mampir! Sampai jumpa lagi ya :)\n"; return; }
        else cout << "Pilihan gak valid...\n";
    }
}

int main() {

    dataPengguna[jumlahPengguna].nama  = "Rafa";
    dataPengguna[jumlahPengguna].nim   = "104";
    dataPengguna[jumlahPengguna].role  = "admin";
    dataPengguna[jumlahPengguna].aktif = 1;
    jumlahPengguna++;

    dataPengguna[jumlahPengguna].nama  = "Tamu";
    dataPengguna[jumlahPengguna].nim   = "000";
    dataPengguna[jumlahPengguna].role  = "pelanggan";
    dataPengguna[jumlahPengguna].aktif = 1;
    jumlahPengguna++;

    cout << "\n=======================================================\n";
    cout << "|     Selamat Datang di Toko Bunga Hias Rafalia      |\n";
    cout << "=======================================================\n";

    string pilihan;
    int berjalan = 1;
    while (berjalan) {
        cout << "\n=======================================================\n";
        cout << "|             MENU UTAMA TOKO BUNGA HIAS             |\n";
        cout << "=======================================================\n";
        cout << "|  [1] Register  (Daftar Akun Baru)                  |\n";
        cout << "|  [2] Login     (Masuk ke Akun)                     |\n";
        cout << "|  [0] Keluar                                        |\n";
        cout << "=======================================================\n";
        cout << "Pilih menu (0-2): ";
        getline(cin, pilihan);

        if      (pilihan == "1") doRegister();
        else if (pilihan == "2") {
            int hasil = doLogin();
            if (hasil == 0) berjalan = 0;
        }
        else if (pilihan == "0") {
            cout << "\nTerima kasih udah mampir ke Toko Bunga Hias Rafalia!\n\n";
            berjalan = 0;
        }
        else cout << "Pilihan tidak valid. Silakan pilih 0-2.\n";
    }

    return 0;
}