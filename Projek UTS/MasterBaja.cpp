#include <iostream>
#include <iomanip> // Library untuk manipulator output sehingga angka besar dapat ditampilkan pada output
#include <string>

using namespace std;

// Struct untuk merepresentasikan transaksi
struct Transaksi {
    string keterangan;
    string namaPembeli; // Menyimpan nama pembeli jika transaksi adalah pemasukan
    string tujuanPengeluaran; // Menyimpan tujuan pengeluaran jika transaksi adalah pengeluaran
    double jumlah;
};

// Node untuk Double Linked List
struct Node {
    Transaksi data;
    Node* next;
    Node* prev;
};

// Kelas untuk merepresentasikan list transaksi
class TransaksiList {
private:
    Node* head;
    Node* tail;
    double totalPemasukan;
    double totalPengeluaran;
public:
    TransaksiList() {
        head = NULL;
        tail = NULL;
        totalPemasukan = 0;
        totalPengeluaran = 0;
    }

    // Fungsi untuk menambah transaksi baru
    void tambahTransaksi(Transaksi transaksi) {
        Node* newNode = new Node;
        newNode->data = transaksi;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
            newNode->prev = NULL;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        if (transaksi.keterangan == "pemasukan") {
            totalPemasukan += transaksi.jumlah;
        } else if (transaksi.keterangan == "pengeluaran") {
            totalPengeluaran += transaksi.jumlah;
        }
    }

    // Fungsi untuk menampilkan semua transaksi
    void tampilkanTransaksi() {
        Node* current = head;
        int countPengeluaran = 0;
        while (current != NULL) {
            cout << "Keterangan: " << current->data.keterangan << ", ";
            if (current->data.keterangan == "pemasukan") {
                cout << "Nama Pembeli: " << current->data.namaPembeli;
            } else if (current->data.keterangan == "pengeluaran") {
                cout << "Tujuan Pengeluaran: " << current->data.tujuanPengeluaran;
                countPengeluaran++;
            }
            cout << ", Jumlah: " << fixed << setprecision(2) << current->data.jumlah << endl;
            current = current->next;
        }
    }

    // Fungsi untuk menghitung total pemasukan
    double getTotalPemasukan() {
        return totalPemasukan;
    }

    // Fungsi untuk menghitung total pengeluaran
    double getTotalPengeluaran() {
        return totalPengeluaran;
    }

    // Fungsi untuk menghitung selisih antara total pemasukan dan total pengeluaran
    double getSelisih() {
        return totalPemasukan - totalPengeluaran;
    }
};

// Fungsi untuk menampilkan garis pembatas
void tampilkanGaris(int panjang) {
    for (int i = 0; i < panjang; ++i) {
        cout << "-";
    }
    cout << endl;
}

int main() {
    const int MAX_TRANSAKSI = 100;
    Transaksi transaksi[MAX_TRANSAKSI];
    int jumlahTransaksi = 0;

    // Input data pemasukan
    cout << "Masukkan data pemasukan perusahaan Master Baja" << endl;
    while (true) {
        cout << "Pemasukan ke-" << jumlahTransaksi + 1 << endl;
        cout << "Nama Pembeli (ketik \"selesai\" untuk mengakhiri): ";
        string namaPembeli;
        cin.ignore();
        getline(cin, namaPembeli);

        if (namaPembeli == "selesai") {
            break;
        }

        cout << "Jumlah: ";
        double jumlah;
        cin >> jumlah;

        transaksi[jumlahTransaksi].keterangan = "pemasukan";
        transaksi[jumlahTransaksi].namaPembeli = namaPembeli;
        transaksi[jumlahTransaksi].jumlah = jumlah;

        jumlahTransaksi++;
    }

    // Input data pengeluaran
    cout << "\nMasukkan data pengeluaran perusahaan Master Baja" << endl;
    int countPengeluaran = 0;
    while (true) {
        cout << "Pengeluaran ke-" << countPengeluaran + 1 << endl;
        cout << "Tujuan Pengeluaran (ketik \"selesai\" untuk mengakhiri): ";
        string tujuanPengeluaran;
        cin.ignore();
        getline(cin, tujuanPengeluaran);

        if (tujuanPengeluaran == "selesai") {
            break;
        }

        cout << "Jumlah: ";
        double jumlah;
        cin >> jumlah;

        transaksi[jumlahTransaksi].keterangan = "pengeluaran";
        transaksi[jumlahTransaksi].tujuanPengeluaran = tujuanPengeluaran;
        transaksi[jumlahTransaksi].jumlah = jumlah;

        jumlahTransaksi++;
        countPengeluaran++;
    }

    // Membuat dan menambahkan transaksi ke dalam linked list
    TransaksiList transaksiLinkedList;
    for (int i = 0; i < jumlahTransaksi; ++i) {
        transaksiLinkedList.tambahTransaksi(transaksi[i]);
    }

    // Menampilkan transaksi dari linked list
    tampilkanGaris(60);
    cout << "Data pemasukan dan pengeluaran perusahaan Master Baja" << endl;
    tampilkanGaris(60);
    transaksiLinkedList.tampilkanTransaksi();

    // Menampilkan total pemasukan dan total pengeluaran
    tampilkanGaris(60);
    cout << "Total Pemasukan: Rp." << fixed << setprecision(2) << transaksiLinkedList.getTotalPemasukan() << endl;
    cout << "Total Pengeluaran: Rp." << fixed << setprecision(2) << transaksiLinkedList.getTotalPengeluaran() << endl;
    tampilkanGaris(60);

    // Menampilkan selisih pemasukan dan pengeluaran
    tampilkanGaris(60);
    cout << "Selisih Pemasukan dan Pengeluaran: Rp." << fixed << setprecision(2) << transaksiLinkedList.getSelisih() << endl;
    tampilkanGaris(60);

    return 0;
}
