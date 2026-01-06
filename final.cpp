#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;

struct Barang {
    string kode;
    string nama;
    int jumlah;
    int harga;
    string lokasi;
};

// === Fungsi Sorting ===
bool sortByNama(const Barang &a, const Barang &b) { return a.nama < b.nama; }
bool sortByJumlah(const Barang &a, const Barang &b) { return a.jumlah < b.jumlah; }
bool sortByHarga(const Barang &a, const Barang &b) { return a.harga < b.harga; }

// === Fungsi Simpan ke File ===
void simpanData(Barang gudang[], int total) {
    ofstream file("Inventaris.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan data!\n";
        return;
    }

    file << "================= DATA INVENTARIS GUDANG PAK BUDI =================\n";
    file << left << setw(10) << "Kode"
         << setw(25) << "Nama Barang"
         << setw(10) << "Jumlah"
         << setw(15) << "Harga"
         << setw(15) << "Lokasi" << endl;
    file << string(80, '=') << endl;

    for (int i = 0; i < total; i++) {
        file << left << setw(10) << gudang[i].kode
             << setw(25) << gudang[i].nama
             << setw(10) << gudang[i].jumlah
             << setw(15) << gudang[i].harga
             << setw(15) << gudang[i].lokasi << endl;
    }
    file.close();
}

// === Fungsi Muat Data dari File (opsional sederhana) ===
int muatData(Barang gudang[]) {
    ifstream file("Inventaris.txt");
    if (!file.is_open()) {
        cout << "Belum ada file Inventaris.txt, mulai dengan data kosong.\n";
        return 0;
    }
    file.close();
    return 0;
}

// === Fungsi memperbarui kode otomatis ===
void perbaruiKode(Barang gudang[], int total) {
    for (int i = 0; i < total; i++) {
        gudang[i].kode = to_string(i + 1);
    }
}

// === PROGRAM UTAMA ===
int main() {
    Barang gudang[0];
    int total = 0;
    int pilihan;

    total = muatData(gudang);

    do {
        cout << "\n===== SISTEM INVENTARIS GUDANG PAK BUDI =====\n";
        cout << "1. Menambah Barang Baru\n";
        cout << "2. Menampilkan Data Barang\n";
        cout << "3. Mengubah Data Barang\n";
        cout << "4. Menghapus Barang\n";
        cout << "5. Mencari Barang\n";
        cout << "6. Mengurutkan Barang\n";
        cout << "7. Keluar\n";
        cout << "=============================================\n";
        cout << "Pilih menu (1-7): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        // === TAMBAH BARANG BARU ===
        case 1: {
            Barang baru;
            baru.kode = to_string(total + 1);

            cout << "\nMasukkan data barang baru:\n";
            cout << "Nama Barang  : ";
            getline(cin, baru.nama);

            // Cek duplikat nama
            bool duplikat = false;
            for (int i = 0; i < total; i++) {
                if (gudang[i].nama == baru.nama) {
                    duplikat = true;
                    break;
                }
            }

            if (duplikat) {
                cout << "Nama barang sudah ada! Gunakan menu ubah data.\n";
                break;
            }

            cout << "Jumlah Barang: ";
            cin >> baru.jumlah;
            cout << "Harga Barang : ";
            cin >> baru.harga;
            cin.ignore();
            cout << "Lokasi Rak   : ";
            getline(cin, baru.lokasi);

            gudang[total] = baru;
            total++;
            simpanData(gudang, total);
            cout << "Barang berhasil ditambahkan!\n";
            break;
        }

        // === TAMPILKAN BARANG ===
        case 2: {
            if (total == 0) {
                cout << "\nBelum ada data barang.\n";
                break;
            }

            cout << "\n================= DAFTAR BARANG DI GUDANG =================\n";
            cout << left << setw(10) << "Kode"
                 << setw(25) << "Nama Barang"
                 << setw(10) << "Jumlah"
                 << setw(15) << "Harga"
                 << setw(15) << "Lokasi" << endl;
            cout << string(80, '-') << endl;

            for (int i = 0; i < total; i++) {
                cout << left << setw(10) << gudang[i].kode
                     << setw(25) << gudang[i].nama
                     << setw(10) << gudang[i].jumlah
                     << setw(15) << gudang[i].harga
                     << setw(15) << gudang[i].lokasi << endl;
            }
            break;
        }

        // === UBAH DATA BARANG ===
        case 3: {
            if (total == 0) {
                cout << "\nBelum ada data untuk diubah.\n";
                break;
            }

            string kodeCari;
            cout << "\nMasukkan kode barang yang ingin diubah: ";
            getline(cin, kodeCari);

            bool ditemukan = false;
            for (int i = 0; i < total; i++) {
                if (gudang[i].kode == kodeCari) {
                    ditemukan = true;
                    int opsi;
                    cout << "\nBarang ditemukan:\n";
                    cout << "1. Ubah Nama Barang\n";
                    cout << "2. Ubah Jumlah Barang\n";
                    cout << "3. Ubah Harga Barang\n";
                    cout << "4. Ubah Lokasi Barang\n";
                    cout << "Pilih (1-4): ";
                    cin >> opsi;
                    cin.ignore();

                    switch (opsi) {
                    case 1:
                        cout << "Nama Baru: ";
                        getline(cin, gudang[i].nama);
                        break;
                    case 2:
                        cout << "Jumlah Baru: ";
                        cin >> gudang[i].jumlah;
                        cin.ignore();
                        break;
                    case 3:
                        cout << "Harga Baru: ";
                        cin >> gudang[i].harga;
                        cin.ignore();
                        break;
                    case 4:
                        cout << "Lokasi Baru: ";
                        getline(cin, gudang[i].lokasi);
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                    }
                    simpanData(gudang, total);
                    cout << "Data berhasil diubah!\n";
                    break;
                }
            }

            if (!ditemukan)
                cout << "Barang tidak ditemukan.\n";
            break;
        }

        // === HAPUS BARANG ===
        case 4: {
            if (total == 0) {
                cout << "Belum ada data.\n";
                break;
            }

            string kodeHapus;
            cout << "Masukkan kode barang yang ingin dihapus: ";
            getline(cin, kodeHapus);

            bool ditemukan = false;
            for (int i = 0; i < total; i++) {
                if (gudang[i].kode == kodeHapus) {
                    for (int j = i; j < total - 1; j++)
                        gudang[j] = gudang[j + 1];
                    total--;
                    perbaruiKode(gudang, total);
                    simpanData(gudang, total);
                    cout << "Barang berhasil dihapus.\n";
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan)
                cout << "Barang tidak ditemukan.\n";
            break;
        }

        // === CARI BARANG ===
        case 5: {
            if (total == 0) {
                cout << "Belum ada data.\n";
                break;
            }

            string cari;
            cout << "Masukkan nama atau kode barang: ";
            getline(cin, cari);

            bool ditemukan = false;
            for (int i = 0; i < total; i++) {
                if (gudang[i].kode == cari || gudang[i].nama == cari) {
                    cout << "\nBarang ditemukan!\n";
                    cout << "Kode   : " << gudang[i].kode << endl;
                    cout << "Nama   : " << gudang[i].nama << endl;
                    cout << "Jumlah : " << gudang[i].jumlah << endl;
                    cout << "Harga  : " << gudang[i].harga << endl;
                    cout << "Lokasi : " << gudang[i].lokasi << endl;
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan)
                cout << "Barang tidak ditemukan.\n";
            break;
        }

        // === SORT BARANG ===
        case 6: {
            if (total == 0) {
                cout << "Belum ada data.\n";
                break;
            }

            int sortPilihan;
            cout << "\nPilih metode sorting:\n";
            cout << "1. Berdasarkan Nama\n";
            cout << "2. Berdasarkan Jumlah\n";
            cout << "3. Berdasarkan Harga\n";
            cout << "Pilih (1-3): ";
            cin >> sortPilihan;
            cin.ignore();

            switch (sortPilihan) {
            case 1: sort(gudang, gudang + total, sortByNama); break;
            case 2: sort(gudang, gudang + total, sortByJumlah); break;
            case 3: sort(gudang, gudang + total, sortByHarga); break;
            default: cout << "Pilihan tidak valid.\n"; break;
            }

            simpanData(gudang, total);
            cout << "Data berhasil diurutkan!\n";
            break;
        }

        // === KELUAR ===
        case 7:
            cout << "\nTerima kasih! Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 7);

    return 0;
}