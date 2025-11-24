#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// Struktur Data Karyawan
struct Karyawan {
    string nama;
    float target;
    float realisasi;
    int pelanggaran;
    float persentase;
    string status;
    string rekomendasi;
};

// ======== Deklarasi Fungsi ========
float hitungPersentase(float target, float realisasi);
string tentukanRekomendasi(float persentase, int pelanggaran);
void inputData(Karyawan dataKaryawan[], int &jumlahKaryawan);
void urutkanKinerja(Karyawan dataKaryawan[], int jumlahKaryawan);
void tampilkanHasil(Karyawan dataKaryawan[], int jumlahKaryawan);
void tampilkanFilter(Karyawan dataKaryawan[], int jumlahKaryawan, string filterStatus);
void tampilkanMenu();


//Fungsi Validasi Input Angka
float inputFloat(string pesan) {
    float nilai;
    while (true) {
        cout << pesan;
        cin >> nilai;

        if (cin.fail()) {  // input bukan angka
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "⚠️ Input harus berupa angka! Coba lagi.\n";
            continue;
        }
        return nilai;
    }
}

int inputInt(string pesan) {
    int nilai;
    while (true) {
        cout << pesan;
        cin >> nilai;

        if (cin.fail()) {  
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "⚠️ Input harus bilangan bulat! Coba lagi.\n";
            continue;
        }
        return nilai;
    }
}


// ======== Fungsi Menghitung Persentase ========
float hitungPersentase(float target, float realisasi) {
    if (target > 0)
        return (realisasi / target) * 100;
    else
        return 0;
}

// ======== Fungsi Menentukan Rekomendasi ========
string tentukanRekomendasi(float persentase, int pelanggaran) {
    if (persentase > 100 && pelanggaran == 0)
        return "Bonus";
    else if (persentase < 80 || pelanggaran > 0)
        return "Potongan";
    else
        return "Aman";
}

// ======== Fungsi Input Data ========
void inputData(Karyawan dataKaryawan[], int &jumlahKaryawan) {
    cout << "\nMasukkan jumlah karyawan: ";
    cin >> jumlahKaryawan;
    cin.ignore();

    for (int i = 0; i < jumlahKaryawan; i++) {
        cout << "\nData Karyawan ke-" << i + 1 << endl;

        do {
            cout << "Nama: ";
            getline(cin, dataKaryawan[i].nama);
            if (dataKaryawan[i].nama.empty()) {
                cout << "⚠️ Nama tidak boleh kosong!\n";
            }
        } while (dataKaryawan[i].nama.empty());

        do {
            dataKaryawan[i].target = inputFloat("Target Penjualan (Rp): ");
            if (dataKaryawan[i].target <= 0) {
                cout << "⚠️ Target harus lebih dari 0!\n";
            }
        } while (dataKaryawan[i].target <= 0);

        do {
            dataKaryawan[i].realisasi = inputFloat("Realisasi Penjualan (Rp): ");
            if (dataKaryawan[i].realisasi < 0) {
                cout << "⚠️ Realisasi tidak boleh negatif!\n";
            }
        } while (dataKaryawan[i].realisasi < 0);

        do {
            dataKaryawan[i].pelanggaran = inputInt("Jumlah Pelanggaran: ");
            if (dataKaryawan[i].pelanggaran < 0) {
                cout << "⚠️ Pelanggaran tidak boleh negatif!\n";
            }
        } while (dataKaryawan[i].pelanggaran < 0);

        // Hitung otomatis
        dataKaryawan[i].persentase = hitungPersentase(dataKaryawan[i].target, dataKaryawan[i].realisasi);
        dataKaryawan[i].status = (dataKaryawan[i].persentase >= 100) ? "Tercapai" : "Tidak Tercapai";
        dataKaryawan[i].rekomendasi = tentukanRekomendasi(dataKaryawan[i].persentase, dataKaryawan[i].pelanggaran);
    }

    // Urutkan setelah input
    urutkanKinerja(dataKaryawan, jumlahKaryawan);
}

// ======== Fungsi Pengurutan (Bubble Sort Desc) ========
void urutkanKinerja(Karyawan dataKaryawan[], int jumlahKaryawan) {
    for (int i = 0; i < jumlahKaryawan - 1; i++) {
        for (int j = 0; j < jumlahKaryawan - i - 1; j++) {
            if (dataKaryawan[j].persentase < dataKaryawan[j + 1].persentase) {
                Karyawan temp = dataKaryawan[j];
                dataKaryawan[j] = dataKaryawan[j + 1];
                dataKaryawan[j + 1] = temp;
            }
        }
    }
}

// ======== Fungsi Menampilkan Tabel ========
void tampilkanHasil(Karyawan dataKaryawan[], int jumlahKaryawan) {
    if (jumlahKaryawan == 0) {
        cout << "\n⚠️  Belum ada data karyawan!\n";
        return;
    }

    cout << "\n=======================================================================" << endl;
    cout << "                HASIL REKAP KINERJA KARYAWAN (TERURUT)                 " << endl;
    cout << "=======================================================================" << endl;
    cout << left << setw(10) << "No"
         << setw(20) << "Nama Karyawan"
         << setw(15) << "Persentase"
         << setw(15) << "Status"
         << setw(15) << "Rekomendasi" << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    for (int i = 0; i < jumlahKaryawan; i++) {
        cout << left << setw(10) << i + 1
             << setw(20) << dataKaryawan[i].nama
             << setw(15) << fixed << setprecision(2) << dataKaryawan[i].persentase
             << setw(15) << dataKaryawan[i].status
             << setw(15) << dataKaryawan[i].rekomendasi << endl;
    }
    cout << "=======================================================================" << endl;
}

// ======== Fungsi Menampilkan Filter ========
void tampilkanFilter(Karyawan dataKaryawan[], int jumlahKaryawan, string filterStatus) {
    bool ditemukan = false;
    cout << "\n=======================================================================" << endl;
    cout << "      DAFTAR KARYAWAN DENGAN STATUS: " << filterStatus << endl;
    cout << "=======================================================================" << endl;

    cout << left << setw(10) << "No"
         << setw(20) << "Nama Karyawan"
         << setw(15) << "Persentase"
         << setw(15) << "Status"
         << setw(15) << "Rekomendasi" << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    int no = 1;
    for (int i = 0; i < jumlahKaryawan; i++) {
        if (dataKaryawan[i].status == filterStatus) {
            ditemukan = true;
            cout << left << setw(10) << no++
                 << setw(20) << dataKaryawan[i].nama
                 << setw(15) << fixed << setprecision(2) << dataKaryawan[i].persentase
                 << setw(15) << dataKaryawan[i].status
                 << setw(15) << dataKaryawan[i].rekomendasi << endl;
        }
    }

    if (!ditemukan)
        cout << "Tidak ada karyawan dengan status \"" << filterStatus << "\".\n";

    cout << "=======================================================================" << endl;
}

// ======== Menu Utama ========
void tampilkanMenu() {
    cout << "\n====================== MENU UTAMA ======================" << endl;
    cout << "1. Input Data Karyawan" << endl;
    cout << "2. Tampilkan Semua Data" << endl;
    cout << "3. Filter Berdasarkan Status" << endl;
    cout << "4. Keluar Program" << endl;
    cout << "========================================================" << endl;
}

// ======== Program Utama ========
int main() {
    Karyawan dataKaryawan[100];
    int jumlahKaryawan = 0;
    int pilihan;

    do {
        tampilkanMenu();
        pilihan = inputInt("Pilih menu (1-6): ");


        switch (pilihan) {
        case 1:
            inputData(dataKaryawan, jumlahKaryawan);
            break;
        case 2:
            tampilkanHasil(dataKaryawan, jumlahKaryawan);
            break;
        case 3: {
            if (jumlahKaryawan == 0) {
                cout << "\n⚠️  Belum ada data karyawan!\n";
                break;
            }
            cout << "\nFilter status: " << endl;
            cout << "1. Tercapai" << endl;
            cout << "2. Tidak Tercapai" << endl;
            cout << "Pilih: ";
            int pilihStatus;
            cin >> pilihStatus;
            if (pilihStatus == 1)
                tampilkanFilter(dataKaryawan, jumlahKaryawan, "Tercapai");
            else if (pilihStatus == 2)
                tampilkanFilter(dataKaryawan, jumlahKaryawan, "Tidak Tercapai");
            else
                cout << "Pilihan tidak valid!" << endl;
            break;
        }
        case 4:
            cout << "\nTerima kasih! Program selesai.\n";
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 4);

    return 0;
}
