# Proyek-Array-C-C2583207006
Aplikasi Sistem Monitoring Stok dan Penjualan Kantin Kampus menggunakan bahasa pemrograman C dengan penerapan array, fungsi, pencarian, pengurutan, dan pengelolaan transaksi penjualan.

* **Nama Lengkap:** Az Zahra Riesty Rizqullah
* **NIM:** C2583207006
* **Kelas:** PTI3B
* **Mata Kuliah:** Algoritma dan Pemrograman Lanjutan
* **Nama Proyek:** Sistem Monitoring Stok dan Penjualan Kantin Kampus

## Deskripsi Singkat
Aplikasi console berbasis bahasa C yang digunakan untuk membantu pengelola kantin kampus dalam memantau ketersediaan stok, mengelola data produk, memproses transaksi penjualan beberapa jenis produk sekaligus, serta menyajikan laporan penjualan dan produk terlaris secara akurat. Data disimpan secara sementara di memori selama program berjalan tanpa memerlukan database atau file eksternal.

## Daftar Fitur
1. **Lihat Daftar Produk:** Menampilkan nomor, nama produk, harga, stok, dan jumlah terjual untuk seluruh produk.
2. **Tambah Produk:** Menambahkan data produk baru hingga batas kapasitas maksimal 50 produk.
3. **Ubah Produk:** Memperbarui harga dan stok dari produk yang sudah terdaftar.
4. **Transaksi Penjualan:** Memproses pembelian beberapa jenis produk dalam satu transaksi, menghitung subtotal dan total bayar, mengurangi stok otomatis, serta menolak transaksi jika stok tidak mencukupi.
5. **Tambah Stok:** Menambahkan jumlah stok pada produk yang dipilih.
6. **Cari Produk:** Mencari data produk berdasarkan kata kunci nama produk.
7. **Urutkan Produk:** Mengurutkan daftar produk berdasarkan harga dari yang termurah atau berdasarkan jumlah terjual dari yang terbanyak.
8. **Laporan Penjualan:** Menampilkan rincian unit terjual per produk, total unit terjual keseluruhan, total pendapatan, serta produk paling laris.
9. **Cek Stok Menipis:** Menampilkan daftar produk yang memiliki sisa stok kurang dari 5 unit.

## Penjelasan Penggunaan Array
Program ini menerapkan **Array Paralel** dengan kapasitas maksimal **50 elemen** (`MAX_PRODUK = 50`) sebagai struktur data utama untuk menyimpan informasi yang saling terhubung melalui indeks yang sama:

* **Array Karakter Dua Dimensi:**
  * `char nama_produk[50][50]` — Digunakan untuk menyimpan daftar nama produk (maksimal 50 produk dengan panjang masing-masing hingga 49 karakter).
* **Array Satu Dimensi:**
  * `int harga[50]` — Digunakan untuk menyimpan harga satuan setiap produk.
  * `int stok[50]` — Digunakan untuk menyimpan jumlah sisa stok setiap produk.
  * `int terjual[50]` — Digunakan untuk mencatat total akumulasi unit yang terjual pada setiap produk.
* **Variabel Kontrol Indeks:**
  * `int jumlah_produk` — Digunakan untuk melacak jumlah data produk aktif yang sedang tersimpan di dalam array.

## Petunjuk Kompilasi dan Menjalankan Program

### Menggunakan Code::Blocks (Windows)
1. Pastikan aplikasi **Code::Blocks** (dengan compiler MinGW/GCC) sudah terpasang di komputer Anda.
2. Unduh berkas `main.c` dari repository ini dan buka menggunakan Code::Blocks.
3. Tekan tombol **F9** atau klik menu **Build > Build and Run** untuk melakukan kompilasi sekaligus menjalankan program di jendela terminal.

### Menggunakan Terminal / Command Prompt (GCC)
1. Buka terminal atau CMD dan arahkan ke direktori tempat file `main.c` disimpan.
2. Jalankan perintah kompilasi berikut:
   ```bash
   gcc main.c -o kantin

'''
<img width="1366" height="768" alt="Screenshot 2026-11-15 192649" src="https://github.com/user-attachments/assets/6b0cd68b-6e52-4143-9f56-e860d85fd374" />

<img width="1366" height="768" alt="Screenshot 2026-11-15 192656" src="https://github.com/user-attachments/assets/603e459a-f87e-4bb0-a812-2fe7f28b091b" />

<img width="1366" height="768" alt="Screenshot 2026-11-15 192708" src="https://github.com/user-attachments/assets/7dcfad6b-f97f-43e3-afd9-195452707781" />

<img width="1366" height="768" alt="Screenshot 2026-11-15 192720" src="https://github.com/user-attachments/assets/79ab2bf7-5f73-4679-9923-f218f5b0cef2" />

<img width="1366" height="768" alt="Screenshot 2026-11-15 192731" src="https://github.com/user-attachments/assets/ea69e3be-94f7-4297-834e-32b723e88e5c" />

<img width="1366" height="768" alt="Screenshot 2026-11-15 192742" src="https://github.com/user-attachments/assets/ca7d38bf-75f9-43a2-bcc1-bc87ca40e8d6" />

<img width="1366" height="768" alt="Screenshot 2026-11-15 192751" src="https://github.com/user-attachments/assets/1c7abe29-6523-40f7-88d4-02d3c5754914" />








