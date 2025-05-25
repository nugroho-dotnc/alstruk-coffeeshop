#include <iostream>  // Untuk input/output seperti cout
#include <string>    // Untuk tipe data string
#include <iomanip>   // Untuk formatting output seperti setprecision

// Menggunakan namespace standar agar tidak perlu menulis std:: berulang kali
using namespace std;

// --- Struktur Data Produk (Node untuk Linked List di dalam Order) ---
struct Produk {
    string id_produk;
    string nama_produk;
    double harga_produk;
    int jumlah;
    double total; // Akan dihitung saat produk ditambahkan
    Produk* next; // Pointer ke produk berikutnya dalam list_produk

    // Konstruktor untuk inisialisasi Produk
    Produk(string id, string nama, double harga, int qty) {
        id_produk = id;
        nama_produk = nama;
        harga_produk = harga;
        jumlah = qty;
        total = harga_produk * jumlah;
        next = nullptr;
    }

    // Destruktor opsional: Untuk debugging, bisa diaktifkan
    // ~Produk() {
    //     cout << "DEBUG: Produk '" << nama_produk << "' dihapus.\n";
    // }
};

// --- Class LinkedListProduk (untuk list_produk di dalam Order) ---
class LinkedListProduk {
public:
    Produk* head; // Head dari linked list produk

    // Konstruktor
    LinkedListProduk() {
        head = nullptr;
    }

    // Destruktor
    // Penting: Destruktor ini akan menghapus semua objek Produk
    // yang ada di dalam list saat objek LinkedListProduk dihancurkan.
    ~LinkedListProduk() {
        Produk* current = head;
        while (current != nullptr) {
            Produk* next_node = current->next;
            delete current; // Hapus node Produk
            current = next_node;
        }
        head = nullptr; // Pastikan head null setelah semua dihapus
        // cout << "DEBUG: LinkedListProduk dihapus.\n"; // Untuk debugging
    }

    // Menambahkan produk ke akhir list_produk
    void addProduk(string id, string nama, double harga, int qty) {
        Produk* new_produk = new Produk(id, nama, harga, qty);
        if (head == nullptr) {
            head = new_produk;
        } else {
            Produk* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_produk;
        }
    }

    // --- FUNGSI BARU: Menghapus produk berdasarkan id_produk ---
    // Mengembalikan true jika produk ditemukan dan dihapus, false jika tidak.
    bool deleteProdukById(string id_produk_to_delete) {
        if (head == nullptr) {
            // cout << "  (List produk kosong, tidak ada yang dihapus)\n"; // Debugging
            return false;
        }

        // Jika produk yang dihapus adalah head
        if (head->id_produk == id_produk_to_delete) {
            Produk* temp = head;
            head = head->next;
            // cout << "  Produk '" << temp->nama_produk << "' (ID: " << id_produk_to_delete << ") dihapus dari list.\n"; // Debugging
            delete temp;
            return true;
        }

        Produk* current = head;
        Produk* prev = nullptr;
        while (current != nullptr && current->id_produk != id_produk_to_delete) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            // cout << "  Produk dengan ID '" << id_produk_to_delete << "' tidak ditemukan dalam list.\n"; // Debugging
            return false; // Produk tidak ditemukan
        } else {
            // Produk ditemukan, hapus
            prev->next = current->next;
            // cout << "  Produk '" << current->nama_produk << "' (ID: " << id_produk_to_delete << ") dihapus dari list.\n"; // Debugging
            delete current;
            return true;
        }
    }

    // Menampilkan semua produk dalam list_produk ini
    void displayProdukList() const {
        if (head == nullptr) {
            cout << "  (Tidak ada produk dalam order ini)\n";
            return;
        }
        Produk* current = head;
        int i = 1;
        while (current != nullptr) {
            cout << "    " << i << ". ID: " << current->id_produk
                 << ", Nama: " << current->nama_produk
                 << ", Harga: Rp" << fixed << setprecision(2) << current->harga_produk
                 << ", Jumlah: " << current->jumlah
                 << ", Total Produk: Rp" << fixed << setprecision(2) << current->total << "\n";
            current = current->next;
            i++;
        }
    }
};

// --- Struktur Data Order (Node untuk Queue) ---
struct Order {
    string nomor_order;
    LinkedListProduk list_produk; // LinkedListProduk untuk menyimpan produk-produk dalam order ini
    double subtotal;             // Subtotal order akan dihitung dari total produk dalam list_produk
    Order* next;                 // Pointer ke order berikutnya dalam Queue

    // Konstruktor untuk inisialisasi Order
    Order(string no_order) {
        nomor_order = no_order;
        subtotal = 0.0; // Awalnya 0, akan dihitung saat produk ditambahkan
        next = nullptr;
        // list_produk akan diinisialisasi secara otomatis oleh konstruktor defaultnya
    }

    // Metode untuk menambahkan produk ke order ini
    void addProdukToOrder(string id, string nama, double harga, int qty) {
        list_produk.addProduk(id, nama, harga, qty);
        subtotal += (harga * qty); // Perbarui subtotal order
    }

    // Metode untuk menghapus produk dari order ini dan memperbarui subtotal
    void removeProdukFromOrder(string id_produk_to_remove) {
        // Simpan subtotal produk yang akan dihapus sebelum dihapus
        double removed_product_total = 0.0;
        Produk* current = list_produk.head;
        while (current != nullptr) {
            if (current->id_produk == id_produk_to_remove) {
                removed_product_total = current->total;
                break;
            }
            current = current->next;
        }

        if (list_produk.deleteProdukById(id_produk_to_remove)) {
            subtotal -= removed_product_total; // Kurangi subtotal order
            cout << "  Produk '" << id_produk_to_remove << "' berhasil dihapus dari order " << nomor_order << ".\n";
        } else {
            cout << "  Produk dengan ID '" << id_produk_to_remove << "' tidak ditemukan dalam order " << nomor_order << ".\n";
        }
    }

    // Destruktor Order: Akan memanggil destruktor LinkedListProduk secara otomatis
    // ~Order() {
    //     cout << "DEBUG: Order '" << nomor_order << "' dihapus.\n";
    // }
};

// --- Class OrderQueue (Antrian Pesanan) ---
class OrderQueue {
private:
    Order* front; // Pointer ke node pertama (depan) dari antrian
    Order* rear;  // Pointer ke node terakhir (belakang) dari antrian

public:
    // Konstruktor
    OrderQueue() {
        front = nullptr;
        rear = nullptr;
    }

    // Destruktor (untuk membersihkan memori semua Order dan Produk di dalamnya)
    ~OrderQueue() {
        Order* current = front;
        while (current != nullptr) {
            Order* next_order = current->next;
            // Destruktor Order akan dipanggil secara otomatis,
            // yang akan memanggil destruktor LinkedListProduk,
            // dan menghapus semua Produk di dalamnya.
            delete current;
            current = next_order;
        }
        front = nullptr;
        rear = nullptr;
        // cout << "DEBUG: OrderQueue dihapus.\n"; // Untuk debugging
    }

    // 1. Operasi enqueue (menambahkan pesanan ke belakang antrian)
    void enqueue(Order* new_order) {
        if (new_order == nullptr) {
            cout << "Error: Tidak bisa menambahkan order NULL ke antrian.\n";
            return;
        }
        new_order->next = nullptr; // Pastikan order baru tidak menunjuk ke mana-mana
        if (rear == nullptr) { // Jika antrian kosong
            front = new_order;
            rear = new_order;
        } else {
            rear->next = new_order; // Tambahkan node baru di belakang 'rear'
            rear = new_order;       // Perbarui 'rear' ke node baru
        }
        cout << "Order '" << new_order->nomor_order << "' berhasil ditambahkan ke antrian.\n";
    }

    // 2. Operasi dequeue (mengambil pesanan dari depan antrian)
    void dequeue() {
        if (front == nullptr) {
            cout << "Antrian kosong, tidak ada order untuk di-dequeue.\n";
            return;
        }

        Order* temp = front; // Simpan pointer ke node yang akan dihapus
        cout << "Order '" << temp->nomor_order << "' dengan subtotal Rp"
             << fixed << setprecision(2) << temp->subtotal << " berhasil di-dequeue.\n";
        front = front->next; // Majukan 'front' ke order berikutnya

        if (front == nullptr) { // Jika antrian menjadi kosong setelah dequeue
            rear = nullptr;     // 'rear' juga harus disetel ke nullptr
        }
        // Destruktor 'temp' (Order) akan dipanggil di sini, yang akan membersihkan list_produk-nya.
        delete temp;
    }

    // 3. Operasi display (menampilkan semua pesanan dalam antrian beserta produknya)
    void displayQueue() const {
        if (front == nullptr) {
            cout << "Antrian order kosong.\n";
            return;
        }

        Order* current = front;
        cout << "\n--- Isi Antrian Order ---\n";
        int i = 1;
        while (current != nullptr) {
            cout << "Order " << i << ":\n";
            cout << "  Nomor Order: " << current->nomor_order << "\n";
            cout << "  Subtotal Order: Rp" << fixed << setprecision(2) << current->subtotal << "\n";
            cout << "  Produk dalam Order:\n";
            current->list_produk.displayProdukList(); // Menampilkan produk dalam order ini
            cout << "-------------------------\n";
            current = current->next;
            i++;
        }
    }

    // Fungsi bantu untuk mengecek apakah antrian kosong
    bool isEmpty() const {
        return front == nullptr;
    }
};

// --- Fungsi Utama (main) ---
int main() {
    cout << "Aplikasi Manajemen Order Dimulai!\n";

    OrderQueue antrian_pesanan;

    // --- Membuat Order 1 dan menambahkan produk ---
    Order* order1 = new Order("ORD-A101");
    order1->addProdukToOrder("P001", "Laptop Gaming", 15000000.00, 1);
    order1->addProdukToOrder("P002", "Mouse Wireless", 250000.00, 2);
    antrian_pesanan.enqueue(order1);

    // --- Membuat Order 2 dan menambahkan produk ---
    Order* order2 = new Order("ORD-B202");
    order2->addProdukToOrder("P003", "Keyboard Mekanik", 800000.00, 1);
    order2->addProdukToOrder("P004", "Monitor Ultrawide", 4500000.00, 1);
    order2->addProdukToOrder("P005", "Webcam HD", 400000.00, 1);
    antrian_pesanan.enqueue(order2);

    // Menampilkan semua order dan produk di dalamnya
    antrian_pesanan.displayQueue();

    // --- Contoh penghapusan produk dari sebuah order ---
    cout << "\nMencoba menghapus produk dari Order ORD-A101:\n";
    order1->removeProdukFromOrder("P002"); // Hapus Mouse Wireless dari order1
    order1->removeProdukFromOrder("P006"); // Coba hapus produk yang tidak ada
    antrian_pesanan.displayQueue(); // Tampilkan antrian setelah penghapusan

    cout << "\nMencoba menghapus produk dari Order ORD-B202:\n";
    order2->removeProdukFromOrder("P003"); // Hapus Keyboard Mekanik dari order2
    antrian_pesanan.displayQueue(); // Tampilkan antrian setelah penghapusan

    // --- Membuat Order 3 (dengan 1 produk saja) ---
    Order* order3 = new Order("ORD-C303");
    order3->addProdukToOrder("P006", "Headset Gaming", 700000.00, 1);
    antrian_pesanan.enqueue(order3);
    antrian_pesanan.displayQueue();

    // Dequeue order pertama
    antrian_pesanan.dequeue();
    antrian_pesanan.displayQueue(); // Tampilkan sisa antrian

    // Dequeue order berikutnya
    antrian_pesanan.dequeue();
    antrian_pesanan.displayQueue();

    // Dequeue order terakhir
    antrian_pesanan.dequeue();
    antrian_pesanan.displayQueue();

    // Coba dequeue saat antrian kosong
    antrian_pesanan.dequeue();

    cout << "\nAplikasi Manajemen Order Selesai.\n";

    return 0;
}