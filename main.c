#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUK 50

// Deklarasi Array Paralel sebagai struktur data utama
char nama_produk[MAX_PRODUK][50] = {
    "Air Mineral",
    "Nasi Goreng",
    "Es Teh Manis",
    "Roti Bakar",
    "Mie Instan"
};
int harga[MAX_PRODUK] = {3000, 12000, 4000, 8000, 6000};
int stok[MAX_PRODUK] = {20, 15, 25, 10, 30};
int terjual[MAX_PRODUK] = {0, 0, 0, 0, 0};
int jumlah_produk = 5;

// Fungsi untuk membersihkan buffer input agar tidak terjadi lompatan input
void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 1. Fitur Lihat Daftar Produk
void lihatProduk() {
    printf("\n============================================================\n");
    printf("                     DAFTAR PRODUK KANTIN                   \n");
    printf("============================================================\n");
    if (jumlah_produk == 0) {
        printf("Belum ada produk yang terdaftar.\n");
        return;
    }
    printf("%-4s | %-20s | %-10s | %-6s | %-8s\n", "No", "Nama Produk", "Harga (Rp)", "Stok", "Terjual");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < jumlah_produk; i++) {
        printf("%-4d | %-20s | %-10d | %-6d | %-8d\n",
               i + 1, nama_produk[i], harga[i], stok[i], terjual[i]);
    }
    printf("============================================================\n");
}

// 2. Fitur Tambah Produk Baru
void tambahProduk() {
    if (jumlah_produk >= MAX_PRODUK) {
        printf("\n[KESALAHAN] Kapasitas maksimal penyimpanan produk telah tercapai (%d produk)[cite: 3]!\n", MAX_PRODUK);
        return;
    }

    printf("\n--- TAMBAH PRODUK BARU ---\n");
    bersihkanBuffer();
    printf("Masukkan nama produk : ");
    fgets(nama_produk[jumlah_produk], sizeof(nama_produk[jumlah_produk]), stdin);
    // Hapus newline di akhir string jika ada
    nama_produk[jumlah_produk][strcspn(nama_produk[jumlah_produk], "\n")] = 0;

    printf("Masukkan harga produk: ");
    if (scanf("%d", &harga[jumlah_produk]) != 1 || harga[jumlah_produk] < 0) {
        printf("[KESALAHAN] Harga tidak boleh negatif[cite: 3]!\n");
        bersihkanBuffer();
        return;
    }

    printf("Masukkan stok awal   : ");
    if (scanf("%d", &stok[jumlah_produk]) != 1 || stok[jumlah_produk] < 0) {
        printf("[KESALAHAN] Stok tidak boleh negatif[cite: 3]!\n");
        bersihkanBuffer();
        return;
    }

    terjual[jumlah_produk] = 0;
    jumlah_produk++;
    printf("\n[SUKSES] Produk baru berhasil ditambahkan!\n");
}

// 3. Fitur Ubah Produk (Harga & Stok)
void ubahProduk() {
    lihatProduk();
    if (jumlah_produk == 0) return;

    int pilihan;
    printf("\nMasukkan nomor produk yang ingin diubah: ");
    if (scanf("%d", &pilihan) != 1 || pilihan < 1 || pilihan > jumlah_produk) {
        printf("[KESALAHAN] Nomor produk tidak ditemukan[cite: 2, 3]!\n");
        bersihkanBuffer();
        return;
    }

    int idx = pilihan - 1;
    printf("Mengubah produk: %s\n", nama_produk[idx]);

    printf("Masukkan harga baru (saat ini: %d): ", harga[idx]);
    if (scanf("%d", &harga[idx]) != 1 || harga[idx] < 0) {
        printf("[KESALAHAN] Harga tidak valid atau negatif[cite: 3]!\n");
        bersihkanBuffer();
        return;
    }

    printf("Masukkan stok baru (saat ini: %d): ", stok[idx]);
    if (scanf("%d", &stok[idx]) != 1 || stok[idx] < 0) {
        printf("[KESALAHAN] Stok tidak valid atau negatif[cite: 3]!\n");
        bersihkanBuffer();
        return;
    }

    printf("\n[SUKSES] Data produk berhasil diperbarui!\n");
}

// 4. Fitur Transaksi Penjualan (Multi-produk dalam 1 transaksi)
void transaksiPenjualan() {
    if (jumlah_produk == 0) {
        printf("\nBelum ada produk untuk ditransaksikan.\n");
        return;
    }

    char lanjut = 'y';
    int total_transaksi = 0;

    // Struktur sementara untuk menyimpan item keranjang belanja pada transaksi ini
    int keranjang_idx[MAX_PRODUK];
    int keranjang_qty[MAX_PRODUK];
    int jumlah_item_beli = 0;

    // Inisialisasi keranjang
    for(int i=0; i<MAX_PRODUK; i++) {
        keranjang_idx[i] = -1;
        keranjang_qty[i] = 0;
    }

    printf("\n============================================\n");
    printf("            TRANSAKSI PENJUALAN             \n");
    printf("============================================\n");

    while (tolower(lanjut) == 'y') {
        lihatProduk();
        int no_prod, qty;

        printf("\nMasukkan nomor produk yang dibeli: ");
        if (scanf("%d", &no_prod) != 1 || no_prod < 1 || no_prod > jumlah_produk) {
            printf("[KESALAHAN] Nomor produk tidak tersedia[cite: 2, 3]!\n");
            bersihkanBuffer();
            printf("Ingin coba lagi? (y/t): ");
            scanf(" %c", &lanjut);
            continue;
        }

        int idx = no_prod - 1;

        printf("Masukkan jumlah pembelian: ");
        if (scanf("%d", &qty) != 1 || qty <= 0) {
            printf("[KESALAHAN] Jumlah pembelian bernilai nol atau negatif[cite: 3]!\n");
            bersihkanBuffer();
            printf("Ingin coba lagi? (y/t): ");
            scanf(" %c", &lanjut);
            continue;
        }

        // Validasi stok mencukupi
        if (qty > stok[idx]) {
            printf("[KESALAHAN] Transaksi ditolak! Jumlah pembelian (%d) melebihi stok yang tersedia (%d)[cite: 3].\n", qty, stok[idx]);
        } else {
            // Cek apakah produk sudah ada di keranjang transaksi saat ini
            int found = -1;
            for(int i = 0; i < jumlah_item_beli; i++) {
                if(keranjang_idx[i] == idx) {
                    found = i;
                    break;
                }
            }

            // Cek total akumulasi jika produk diinput lebih dari sekali dalam 1 transaksi
            int total_qty_diminta = qty;
            if(found != -1) {
                total_qty_diminta += keranjang_qty[found];
            }

            if(total_qty_diminta > stok[idx]) {
                printf("[KESALAHAN] Akumulasi pembelian melebihi sisa stok yang ada!\n");
            } else {
                if(found != -1) {
                    keranjang_qty[found] = total_qty_diminta;
                } else {
                    keranjang_idx[jumlah_item_beli] = idx;
                    keranjang_qty[jumlah_item_beli] = qty;
                    jumlah_item_beli++;
                }
                printf("[INFO] Produk berhasil ditambahkan ke keranjang transaksi.\n");
            }
        }

        printf("Tambah produk lain dalam transaksi ini? (y/t): ");
        scanf(" %c", &lanjut);
    }

    // Jika ada item yang valid dibeli, proses pengurangan stok dan pencatatan
    if (jumlah_item_beli > 0) {
        printf("\n--------------------------------------------\n");
        printf("              STRUK BELANJA                 \n");
        printf("--------------------------------------------\n");
        for(int i = 0; i < jumlah_item_beli; i++) {
            int idx = keranjang_idx[i];
            int qty = keranjang_qty[i];
            int subtotal = harga[idx] * qty;
            total_transaksi += subtotal;

            // Kurangi stok dan tambah jumlah terjual
            stok[idx] -= qty;
            terjual[idx] += qty;

            printf("%-20s x%-3d = Rp %d\n", nama_produk[idx], qty, subtotal);
        }
        printf("--------------------------------------------\n");
        printf("TOTAL PEMBAYARAN        : Rp %d\n", total_transaksi);
        printf("================================------------\n");
        printf("[SUKSES] Transaksi berhasil diproses!\n");
    } else {
        printf("\n[INFO] Tidak ada transaksi yang diproses.\n");
    }
}

// 5. Fitur Tambah Stok & Cek Stok Menipis (< 5)
void cekStokMenipis() {
    printf("\n============================================\n");
    printf("         PRODUK DENGAN STOK MENIPIS (<5)    \n");
    printf("============================================\n");
    int ada = 0;
    for (int i = 0; i < jumlah_produk; i++) {
        if (stok[i] < 5) {
            printf("- %s (Stok tersisa: %d)\n", nama_produk[i], stok[i]);
            ada = 1;
        }
    }
    if (!ada) {
        printf("Tidak ada produk dengan stok di bawah 5.\n");
    }
    printf("============================================\n");
}

void tambahStok() {
    lihatProduk();
    if (jumlah_produk == 0) return;

    int pilihan, tambahan;
    printf("\nMasukkan nomor produk yang ingin ditambah stoknya: ");
    if (scanf("%d", &pilihan) != 1 || pilihan < 1 || pilihan > jumlah_produk) {
        printf("[KESALAHAN] Nomor produk tidak ditemukan[cite: 2, 3]!\n");
        bersihkanBuffer();
        return;
    }

    int idx = pilihan - 1;
    printf("Masukkan jumlah stok yang ingin ditambahkan: ");
    if (scanf("%d", &tambahan) != 1 || tambahan <= 0) {
        printf("[KESALAHAN] Jumlah penambahan stok harus bernilai positif[cite: 3]!\n");
        bersihkanBuffer();
        return;
    }

    stok[idx] += tambahan;
    printf("\n[SUKSES] Stok berhasil ditambahkan. Stok baru %s adalah %d\n", nama_produk[idx], stok[idx]);
}

// 6. Fitur Cari Produk Berdasarkan Nama
void cariProduk() {
    bersihkanBuffer();
    char keyword[50];
    printf("\nMasukkan nama produk yang ingin dicari: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    printf("\n============================================\n");
    printf("               HASIL PENCARIAN              \n");
    printf("============================================\n");
    int ditemukan = 0;
    for (int i = 0; i < jumlah_produk; i++) {
        // Menggunakan strcasestr atau perbandingan manual sederhana (case-insensitive simulation)
        // Kita bandingkan string (bisa pakaistrstr setelah diubah ke lowercase)
        char temp_prod[50], temp_key[50];
        strcpy(temp_prod, nama_produk[i]);
        strcpy(temp_key, keyword);

        // Ubah ke lowercase untuk pencarian fleksibel
        for(int j=0; temp_prod[j]; j++) temp_prod[j] = tolower(temp_prod[j]);
        for(int j=0; temp_key[j]; j++) temp_key[j] = tolower(temp_key[j]);

        if (strstr(temp_prod, temp_key) != NULL) {
            printf("No. %d\n", i + 1);
            printf("Nama Produk : %s\n", nama_produk[i]);
            printf("Harga       : Rp %d\n", harga[i]);
            printf("Stok        : %d\n", stok[i]);
            printf("Terjual     : %d unit\n", terjual[i]);
            printf("----------------------------------------\n");
            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Produk dengan kata kunci \"%s\" tidak ditemukan[cite: 2, 3].\n", keyword);
    }
    printf("============================================\n");
}

// 7. Fitur Urutkan Produk (Harga termurah & Penjualan terbanyak)
void urutkanProduk() {
    int pilihan;
    printf("\n--- MENU PENGURUTAN PRODUK ---\n");
    printf("1. Urutkan berdasarkan Harga (Termurah ke Termahal)\n");
    printf("2. Urutkan berdasarkan Jumlah Terjual (Terbanyak ke Tersedikit)\n");
    printf("Pilih metode pengurutan (1/2): ");
    if (scanf("%d", &pilihan) != 1) {
        printf("[KESALAHAN] Pilihan tidak valid!\n");
        bersihkanBuffer();
        return;
    }

    // Buat salinan array sementara agar data asli tidak rusak posisinya (opsional, tapi bagus)
    char temp_nama[MAX_PRODUK][50];
    int temp_harga[MAX_PRODUK];
    int temp_stok[MAX_PRODUK];
    int temp_terjual[MAX_PRODUK];

    for (int i = 0; i < jumlah_produk; i++) {
        strcpy(temp_nama[i], nama_produk[i]);
        temp_harga[i] = harga[i];
        temp_stok[i] = stok[i];
        temp_terjual[i] = terjual[i];
    }

    // Bubble Sort
    for (int i = 0; i < jumlah_produk - 1; i++) {
        for (int j = 0; j < jumlah_produk - i - 1; j++) {
            int kondisi = 0;
            if (pilihan == 1) {
                // Harga termurah ke termahal (ascending)
                if (temp_harga[j] > temp_harga[j + 1]) {
                    kondisi = 1;
                }
            } else if (pilihan == 2) {
                // Terjual terbanyak ke tersedikit (descending)
                if (temp_terjual[j] < temp_terjual[j + 1]) {
                    kondisi = 1;
                }
            }

            if (kondisi) {
                // Tukar data
                char t_nama[50];
                strcpy(t_nama, temp_nama[j]);
                strcpy(temp_nama[j], temp_nama[j + 1]);
                strcpy(temp_nama[j + 1], t_nama);

                int t_hrg = temp_harga[j];
                temp_harga[j] = temp_harga[j + 1];
                temp_harga[j + 1] = t_hrg;

                int t_stk = temp_stok[j];
                temp_stok[j] = temp_stok[j + 1];
                temp_stok[j + 1] = t_stk;

                int t_terjual = temp_terjual[j];
                temp_terjual[j] = temp_terjual[j + 1];
                temp_terjual[j + 1] = t_terjual;
            }
        }
    }

    // Tampilkan hasil pengurutan
    printf("\n============================================================\n");
    if (pilihan == 1) {
        printf("         HASIL URUTAN PRODUK (BERDASARKAN HARGA)            \n");
    } else if (pilihan == 2) {
        printf("       HASIL URUTAN PRODUK (BERDASARKAN JUMLAH TERJUAL)     \n");
    } else {
        printf("[KESALAHAN] Pilihan menu pengurutan tidak tersedia[cite: 2, 3].\n");
        return;
    }
    printf("============================================================\n");
    printf("%-4s | %-20s | %-10s | %-6s | %-8s\n", "No", "Nama Produk", "Harga (Rp)", "Stok", "Terjual");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < jumlah_produk; i++) {
        printf("%-4d | %-20s | %-10d | %-6d | %-8d\n",
               i + 1, temp_nama[i], temp_harga[i], temp_stok[i], temp_terjual[i]);
    }
    printf("============================================================\n");
}

// 8. Fitur Laporan Penjualan & Produk Terlaris
void laporanPenjualan() {
    int total_unit_terjual = 0;
    int total_pendapatan = 0;
    int max_terjual = -1;
    int idx_terlaris = -1;

    printf("\n============================================================\n");
    printf("                     LAPORAN PENJUALAN                      \n");
    printf("============================================================\n");
    printf("%-4s | %-20s | %-8s | %-12s\n", "No", "Nama Produk", "Terjual", "Pendapatan");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < jumlah_produk; i++) {
        int pendapatan_prod = terjual[i] * harga[i];
        total_unit_terjual += terjual[i];
        total_pendapatan += pendapatan_prod;

        if (terjual[i] > max_terjual) {
            max_terjual = terjual[i];
            idx_terlaris = i;
        }

        printf("%-4d | %-20s | %-8d | Rp %-9d\n",
               i + 1, nama_produk[i], terjual[i], pendapatan_prod);
    }

    printf("------------------------------------------------------------\n");
    printf("Total Unit Terjual keseluruhan : %d unit\n", total_unit_terjual);
    printf("Total Pendapatan Keseluruhan   : Rp %d\n", total_pendapatan);

    if (max_terjual > 0 && idx_terlaris != -1) {
        printf("Produk Terlaris                : %s (%d unit terjual)\n",
               nama_produk[idx_terlaris], max_terjual);
    } else {
        printf("Produk Terlaris                : Belum ada produk yang terjual\n");
    }
    printf("============================================================\n");
}

// Fungsi Utama / Menu Utama
int main() {
    int pilihan;

    do {
        printf("\n============================================\n");
        printf("   SISTEM MONITORING STOK & PENJUALAN KANTIN\n");
        printf("============================================\n");
        printf("1. Lihat Daftar Produk  | 6. Cari Produk\n");
        printf("2. Tambah Produk        | 7. Urutkan Produk\n");
        printf("3. Ubah Produk          | 8. Laporan Penjualan\n");
        printf("4. Transaksi Penjualan  | 9. Cek Stok Menipis\n");
        printf("5. Tambah Stok          | 0. Keluar\n");
        printf("============================================\n");
        printf("Pilihan menu (0-9): ");

        if (scanf("%d", &pilihan) != 1) {
            printf("\n[KESALAHAN] Masukkan angka pilihan menu yang valid[cite: 2, 3]!\n");
            bersihkanBuffer();
            continue;
        }

        switch (pilihan) {
            case 1:
                lihatProduk();
                break;
            case 2:
                tambahProduk();
                break;
            case 3:
                ubahProduk();
                break;
            case 4:
                transaksiPenjualan();
                break;
            case 5:
                tambahStok();
                break;
            case 6:
                cariProduk();
                break;
            case 7:
                urutkanProduk();
                break;
            case 8:
                laporanPenjualan();
                break;
            case 9:
                cekStokMenipis();
                break;
            case 0:
                printf("\nTerima kasih telah menggunakan program ini. Program keluar.\n");
                break;
            default:
                printf("\n[KESALAHAN] Pilihan menu tidak tersedia[cite: 2, 3]! Silakan pilih antara 0 - 9.\n");
        }
    } while (pilihan != 0);

    return 0;
}
