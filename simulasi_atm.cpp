/*
 * Simulasi ATM
 * Copyright (c) 2024, Muhammad Fattahillah. Mz
 * Kode: Muhammad Fattahillah. Mz
 * Pengkoreksi & Visual: Naila Nelsa Salsabilla, Osevina Oktavianous, Raldizian Hazimul Fikri
 */

// Library
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <limits>
#include <sstream>

// Menghapus std
using namespace std;

// Function
// Function	Menambahkan titik ke Saldo. Contoh: Rp. xxx.xxx,xx
string formatCurrency(int amount) {
	// Buat Variabel untuk Menyimpan Amount Saldo Menjadi String
    string strAmount = to_string(amount);
	// Buat Variabel Formatted Amount untuk Memasukkan "." Ke Dalam Integer
    string formattedAmount;
    // Iterasi Awal
    int count = 0;
	
    for (int i = strAmount.length() - 1; i >= 0; --i) { // Perulangan untuk Menambahkan "." Setelah 3 Angka Terakhir
        formattedAmount = strAmount[i] + formattedAmount;
        // Iterasi Count Bertambah
        ++count;
	
        if (count == 3 && i > 0) { // Jika Count Telah Mencapai 3 Setelah Bertambah, Tambahkan "." nya
            // "." Telah Ditambahkan
			formattedAmount = "." + formattedAmount;
            // Reset Count Menjadi 0 Agar Kembali Cek Apakah Ada Bilangan yang Mencapai 3 Lagi Setelahnya, Misal 1000.000, Bilangan Sebelumnya Masih Berjumlah 4, Maka Kondisi Ini Akan Berjalan dan Menambahkan "." Lagi Menjadi 1.000.000
			count = 0;
        }
    }
	
    return formattedAmount;
}

// Function Transfer Bank
long long Transfer(int biayaAdmin, long long saldoUser) {
	// Menghapus Semua Command Line Diatas
	system("cls");
	
	// Variabel Nominal Transfer
	long long nominalTransfer;

	// Input Nominal Transfer
    cout << "Transfer Ke Bank Lain Akan Terkena Biaya Admin Sebesar Rp 6.500." << endl;
    cout << "Masukkan Nominal Transfer: ";
    cin >> nominalTransfer;

    // Validasi input
    if (cin.fail() || nominalTransfer <= 0) { // Jika Input Berupa String(NaN) atau Value Nominal Transfer Ber-isikan Angka Negatif
        cout << "Nominal Transfer Harus Berupa Angka! Press Any Key to Menu!" << endl;
        // Mereset/Membersihkan Cin
        cin.clear();
        // Mereset/Membersihkan buffer input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
        getch();
        // Menghapus Semua Command Line Diatas
        system("cls");
        // Mengembalikan nilai saldoUser tanpa mengurangi
        return saldoUser;
    }
    
    if( saldoUser - (nominalTransfer + biayaAdmin) >= 0 ) { // Jika Saldo User - (Nominal Transfer + Biaya Admin) Hasilnya Bukan Angka Positif, Berarti Saldo Tidak Cukup
    	// Mengurangkan saldo dengan nominal transfer dan biaya admin
    	saldoUser -= (nominalTransfer + biayaAdmin);
	    // Jika Transfer Berhasil dengan Sukses!
	    // Menghapus Semua Command Line Diatas
		system("cls");
		cout << "Tunggu Sebentar...";
		// Waktu Delay 3 Detik
		this_thread::sleep_for(chrono::seconds(3));
		// Memberikan Baris Kosong
		cout << endl;
		cout << endl;
		// Tampilkan Pesan Bahwa Transfer Berhasil
		cout << "Transfer Berhasil! Press Any Key to Menu!";
		// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
		getch();
		// Mengembalikan Nilai
	    return saldoUser;
	}else { // Jika Saldo Tidak Cukup Tampilkan Kesalahan
		system("cls");
		cout << "Saldo Tidak Mencukupi! Press Any Key to Menu!";
		// Menekan Tombol Apapun untuk Melanjutkan Program
		getch();
		// Mengembalikan Nilai
		return saldoUser;
	}
}

long long TransferWithNominalDef(long long saldoUser, int pilihanNom, string output) { // Function Transfer dengan Mencegah Saldo Diperbarui Ketika Saldo yang Ingin Ditarik Tidak Mencukupi dengan Jumlah Penarikan
	// Variabel Check Hasil Saldo User - Pilihan Nominal
	long long checkHasil = saldoUser - pilihanNom;
	if( checkHasil >= 0 ) { // Jika Hasilnya Angka positif (Diatas 0), Lanjutkan Penarikan
		// Menghapus Semua Command Line Diatas
		system("cls");
		// Jika Penarikan Sukses
		cout << "Tunggu Sebentar...";
		// Waktu Delay 3 Detik
		this_thread::sleep_for(chrono::seconds(3));
		// Memberikan Baris Kosong
		cout << endl;
		cout << endl << output;
		// Jumlah Saldo Dikurangi Sesuai pada Menu
		saldoUser -= pilihanNom;
		// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
		getch();
		// Menghapus Semua Command Line Diatas
		system("cls");
		// Mengembalikan Nilai
		return saldoUser;
	}else { // Jika Hasilnya Angka Negatif (Dibawah 0), Hentikan dan Tetapkan Jumlah Saldo User Awal, Lalu Tampilkan Pesan Kesalahan
		cout << "Saldo Tidak Mencukupi! Press Any Key to Menu!";
		// Menekan Tombol Apapun untuk Melanjutkan Program
		getch();
		// Mengembalikan Nilai
		return saldoUser;
	}
}

// Function Membatalkan Input String
bool CancelString(string cancel) { // Jika Input Ber-valueBernilai "Cancel" atau "cancel" Kembalikan Nilai True	
	if( cancel == "Cancel" || cancel == "cancel" ) { // Jika User Memasukkan Input an "Cancel" atau "cancel", Kembalikan Ke Menu Awal
		return true; // Kembalikan Nilai True
	}else { // Jika User Memasukkan Input Selain "Cancel" atau "cancel" Lanjutkan Program
		return false; // Kembalikan Nilai False
	}
}

// Function Menampilkan Output Cancel
void OutputCancel() {
	// Menghapus Semua Command Line Diatas
	system("cls");
	// Output
	cout << "Waiting for Cancel...";
	// Waktu Delay 3 Detik
	this_thread::sleep_for(chrono::seconds(3));
	// Menghapus Semua Command Line Diatas
	system("cls");
}

// Function Confirm yang Mengembalikan Nilai dengan Tipe Data String
string Confirm(string confirmUser) { // Konfirmasi Penarikan dengan Nominal yang Telah Ada
	if( confirmUser == "Y" || confirmUser == "y" ) { // Jika User Memasukkan "Y" atau "y" pada Input, Kembalikan Value True
		return "true"; // Kembalikan Nilai True
	}else if( confirmUser == "N" || confirmUser == "n" ) { // Jika User Memasukkan "N" atau "n" pada Input, Kembalikan Value False
		return "false"; // Kembalikan Nilai False
	}else { // Jika User Memasukkan Selain "Y", "y", "N", "n", pada Input, Kembalikan Value other
		return "other"; // Kembalikan Value other
	}
}

// Function Confirm yang Mengembalikan Nilai dengan Tipe Data Number/Integer
bool ConfirmInt(int confirmUser) {
	if( confirmUser == 0 ) {
		return true;
	}
}

// Program
int main() {
	
    // Variabel
    string inputPIN, namaUser, confirm, cnfrmStts;
    	   namaUser = "Azwar Anas, S. Kom.";
    
    // Variabel PIN User dan Saldo User
	long long pinUser, saldoUser;
	
	// Variabel Biaya Administrasi Bank
	const int biayaAdmin = 6500;
	
	// Saldo User
	saldoUser = 100000000;
	
	// Nama Aplikasi
	cout << "|=============================|" << endl;
	cout << "|        Nama Aplikasi        |" << endl;
	cout << "|=============================|" << endl;
	cout << "|        Simulasi ATM         |" << endl;
	cout << "|=============================|" << endl;
	// Menambahkan Baris Kosong
	cout << endl;
	// Nama Nama Kelompok
	cout << "|=============================|" << endl;
	cout << "|        Dibuat Oleh:         |" << endl;
	cout << "|=============================|" << endl;
	cout << "|                             |" << endl;
	cout << "| 1. Muhammad Fattahillah. Mz |" << endl;
	cout << "| 2. Osevina Oktavianous      |" << endl;
	cout << "| 3. Naila Nelsa Salsabila    |" << endl;
	cout << "| 4. Raldizian Hazimul Fikri  |" << endl;
	cout << "|=============================|" << endl;
	cout << endl;
	cout << "Tekan Tombol Apapun Untuk Memulai Program!";
	//Menekan Tombol Apapun untuk Melanjutkan Program
	getch();
	
	// Sebelum Menampilkan Input-an PIN, Bersihkan Command Line-nya Terlebih Dahulu!
	system("cls");
	
	// Meminta User untuk Memasukkan Kartu
	cout << "====================== Masukkan Kartu Anda! ========================" << endl;
	cout << "==== Jika Sudah, Tekan Tombol Apapun untuk Melanjutkan Program! ====";
	
	// Menekan Tombol Apapun untuk Melanjutkan Program
	getch();
	
	// Menghapus Semua Command Line Diatas
	system("cls");
	
	// Program Perulangan Dimulai	
	while (true) {
		// Awalan Program
		cout << "|=============================|" << endl;
		cout << "|       Selamat Datang!       |" << endl;
		cout << "|=============================|" << endl;
		cout << endl;
		
		// User Diminta Untuk Memasukkan PIN
        cout << "Masukkan PIN Anda (6 Digit): ";
		// Sebuah PIN disimpan ke Dalam Variabel dengan Type Data String        
        getline(cin, inputPIN);

		// Menggunakan Try untuk Menangkap Success atau Error
        try {
        	// PIN User Dikonversi menjadi Integer
            pinUser = stoi(inputPIN);
            
            // Menghitung Jumlah Digit PIN yang Dimasukkan Oleh User
            int jumDigitPin = static_cast<int>(log10(abs(pinUser)) + 1);
            
            // Validasi Sebuah Digit PIN
            bool checkPIN = ( jumDigitPin == 6 );
            
            // Kondisional Validasi Digit PIN ( Jika Bernilai TRUE, Maka Perulangan While Akan Dihentikan, Jika tidak, Maka Perulangan Akan terus Berlanjut )
            if( checkPIN && pinUser >= 100000 && pinUser <= 999999 ) { // Jika Benar PIN 6 Digit, Lanjutkan Ke Menu
            	// Menghapus Semua Command Line Diatas
				system("cls");
            	cout << "PIN Benar! Mohon Tunggu Beberapa Detik untuk System Menampilkan Menunya.";
				// Menghentikan Looping/Masuk Ke Menu
				break;
			}else { // Jika PIN 0 dan Dibawah 0 (Angka/Bilangan Negatif) atau PIN Tidak Berjumlah 6 Digit
				// Menghapus Semua Command Line Diatas
				system("cls");
				cout << "PIN Salah! PIN Harus Berjumlah 6 Digit dan Tidak Kosong!";
				//cout << endl;
				getch();
				// Menghapus Semua Command Line Diatas
				system("cls");
				// Mengembalikan Ke Input an PIN
				continue;
			}
        } catch (const invalid_argument&) { // Menangkap Sebuah Error, Jika Input an Bukanlah Angka (Character) atau Input an Bernilai Kosong
        	// Menghapus Semua Command Line Diatas
        	system("cls");
            cout << "Input Bukan Angka!";
            getch();
            // Menghapus Semua Command Line Diatas
            system("cls");
        } catch (const out_of_range) { // Menangkap Sebuah Error, Jika Input an Memiliki Jumlah Digit yang Terlalu Banyak
        	// Menghapus Semua Command Line Diatas
        	system("cls");
        	cout << "Jumlah Digit Pada Input Terlalu Banyak!";
        	getch();
        	// Menghapus Semua Command Line Diatas
        	system("cls");
		}
    }
    
	// Waktu Delay 3 detik.    
    this_thread::sleep_for(chrono::seconds(3));
    
    // Sebelum Menampilkan Menu, Bersihkan Command Line-nya Terlebih Dahulu!
    system("cls");

	while( true ) {
		// Menghitung Jumlah Digit Saldo
		int jumDigitSaldo = static_cast<int>(log10(abs(saldoUser)) + 1);
	    
	    // Menu Menu Bank
	    cout << "|=================================|" << endl;
	    cout << "|        Selamat Datang Di        |" << endl;
	    cout << "|            Bank MORN            |" << endl;
	    cout << "|=================================|" << endl;
	    cout << "| Pemilik : " << namaUser << "   |" << endl;
		string formattedSaldo = formatCurrency(saldoUser); // Memformat Saldo User/Menambahkan Titik Setelah 3 Bilangan dari Belakang, Contoh: 1.000.000
		switch (jumDigitSaldo) { // Mengatur Tata Letak Tabel Sesuai Dengan Jumlah Digit Angka
			case 1: // Rp 1,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00              |" << endl;
				break;
			case 2: // Rp 10,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00             |" << endl;
				break;
			case 3: // Rp 100,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00            |" << endl;
				break;
			case 4: // Rp 1.000,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00          |" << endl;
				break;
			case 5: // Rp 10.000,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00         |" << endl;
				break;
			case 6: // Rp 100.000,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00        |" << endl;
				break;
			case 7: // Rp 1.000.000,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00      |" << endl;
				break;
			case 8: // Rp 10.000.000,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00     |" << endl;
				break;
			case 9: // Rp 100.000.000,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00    |" << endl;
				break;
			case 10: // Rp 1.000.000.000,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00  |" << endl;
				break;
			case 11: // Rp 10.000.000.000,00
				cout << "| Saldo   : Rp. " << formattedSaldo << ",00      |" << endl;
				break;
			default: // Ketika Tidak Ada Lagi Saldo User-nya, Tampilkan Angka 0 yang Mengindisikan Saldo Habis
				cout << "| Saldo   : Rp. 0" << "                 |" << endl;
		}
		cout << "|=================================|" << endl;
		cout << "| Menu:                           |" << endl;
		cout << "|                                 |" << endl;
		cout << "| 1. 100.000        6. 700.000    |" << endl;
		cout << "| 2. 200.000        7. 1.000.000  |" << endl;
		cout << "| 3. 500.000        8. 1.500.000  |" << endl;
		cout << "| 4. Tarik Tunai    9. Transfer   |" << endl;
		cout << "| 5. Report         10. Exit      |" << endl;
		cout << "|                                 |" << endl;
		cout << "|=================================|" << endl;
		// Memberikan Baris Kosong
		cout << endl;
		// Variabel Pilihan Menu
		int pilihanMenu;
		
		// Array Nominal Pilihan 1-3, dan 6-8
		int pilihanNom[] = {100000, 200000, 500000, 700000, 1000000, 1500000};
		
		// Variabel Pilihan Menu
		cout << "Silahkan Pilih Menu (1-10): ";
		cin >> pilihanMenu;
		
		// Jika Menyimpan Value Tarik Tunai Manual Gagal (Sebuah Huruf)
		if (cin.fail()) {
			// Menghapus Semua Command Line Diatas
			system("cls");
        	cout << "Pilihan Menu Tidak Ada! Press Any Key to Menu!";
        	// Mereset/Membersihkan Cin
        	cin.clear();
        	// Mereset/Membersihkan buffer input
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
    		getch();
    		// Menghapus Semua Command Line Diatas
    		system("cls");
    		// Melanjutkan Ke Menu
			continue;
		}
		
		// Menghapus/Mengabaikan Value CIN (pilihanMenu) yang Telah Ditangkap Sebelumnya
		cin.ignore();
		
		if( pilihanMenu == 1 ) { // Pilihan Pertama Yaitu: Menarik Uang dengan Jumlah Rp 100.000 (Tidak Manual)
			// Menghapus Semua Command Line Diatas
			system("cls");
			while(true) {
				// Confirm Penarikan
				cout << "Apakah Anda Yakin Ingin Melanjutkan Penarikan Uang Senilai Rp " << pilihanNom[0] << "? (Y/N): ";
				cin >> confirm;
				
				// Menjalankan Function Confirm Status
				cnfrmStts = Confirm(confirm);
				
				if( cnfrmStts == "true" ) {
					// Jumlah Saldo Dikurangi Rp 100.000 (Sesuai Dimenu)
					saldoUser = TransferWithNominalDef(saldoUser, pilihanNom[0], "Sukses! Silahkan Diambil Uangnya.");
					break;
				}else if( cnfrmStts == "false" ) {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Penarikan Dibatalkan! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Awal
					break;
				}else {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Tidak Ada Opsi! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Confirm
					continue;
				}
			
			}
			
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Melanjutkan Ke Menu Awal
			continue;
		}else if( pilihanMenu == 2 ) { // Pilihan Kedua
			// Menghapus Semua Command Line Diatas
			system("cls");
			while(true) {
				// Confirm Penarikan
				cout << "Apakah Anda Yakin Ingin Melanjutkan Penarikan Uang Senilai Rp " << pilihanNom[1] << "? (Y/N): ";
				cin >> confirm;
				
				// Menjalankan Function Confirm Status
				cnfrmStts = Confirm(confirm);
				
				if( cnfrmStts == "true" ) {
					// Jumlah Saldo Dikurangi Rp 100.000 (Sesuai Dimenu)
					saldoUser = TransferWithNominalDef(saldoUser, pilihanNom[1], "Sukses! Silahkan Diambil Uangnya.");
					break;
				}else if( cnfrmStts == "false" ) {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Penarikan Dibatalkan! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Awal
					break;
				}else {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Tidak Ada Opsi! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Confirm
					continue;
				}
			
			}
			
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Melanjutkan Ke Menu
			continue;
		}else if( pilihanMenu == 3 ) { // Pilihan 3
			// Menghapus Semua Command Line Diatas
			system("cls");
			while(true) {
				// Confirm Penarikan
				cout << "Apakah Anda Yakin Ingin Melanjutkan Penarikan Uang Senilai Rp " << pilihanNom[2] << "? (Y/N): ";
				cin >> confirm;
				
				// Menjalankan Function Confirm Status
				cnfrmStts = Confirm(confirm);
				
				if( cnfrmStts == "true" ) {
					// Jumlah Saldo Dikurangi Rp 100.000 (Sesuai Dimenu)
					saldoUser = TransferWithNominalDef(saldoUser, pilihanNom[2], "Sukses! Silahkan Diambil Uangnya.");
					break;
				}else if( cnfrmStts == "false" ) {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Penarikan Dibatalkan! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Awal
					break;
				}else {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Tidak Ada Opsi! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Confirm
					continue;
				}
			
			}
			
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Melanjutkan Ke Menu
			continue;
		}else if( pilihanMenu == 4 ) { // Pilihan 4
			// Variabel Tarik Tunai Manual User
			long tarikTunaiManual;
			// Menghapus Semua Command Line Diatas
			system("cls");
			
			// Input Tarik Tunai
			cout << "Masukkan Nominal Penarikan: Rp ";
			cin >> tarikTunaiManual;
			
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Jika Menyimpan Value Tarik Tunai Manual Gagal (Sebuah Huruf)
			if (cin.fail()) {
        		cout << endl << "Input Harus Berupa Angka! Press Any Key to Menu!";
        		// Mereset/Membersihkan Cin
        		cin.clear();
        		// Mereset/Membersihkan buffer input
        		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        		// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
    			getch();
    			// Menghapus Semua Command Line Diatas
    			system("cls");
    			// Melanjutkan Ke Menu
				continue;
			}
			
			// Jika Jumlah Tarik Tunai bernilai 0, Berikan Perintah untuk Memasukkan Nominal yang Benar
			if( tarikTunaiManual == 0 ) { // Jika Input an Tarik Manual yang Dimasukkan senilai 0, Tampilkan Pesan Kesalahan
				cout << endl << "Masukkan Nominal yang Benar! Press Any Key to Menu!";
				// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
				getch();
				// Menghapus Semua Command Line Diatas
				system("cls");
				// Melanjutkan Ke Menu
				continue;
			}
			
			// Saldo Dikurangi dengan Jumlah Tarik Manual yang Telah Dimasukkan User
			saldoUser = TransferWithNominalDef(saldoUser, tarikTunaiManual, "Sukses! Silahkan Diambil Uangnya.");
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Melanjutkan Ke Menu
			continue;
		}else if( pilihanMenu == 5 ) { // Pilihan 5
			// Variabel Report User yang Ber-tipe Data: String
			string reportUser;
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Memberitahukan Kepada User untuk Mengetik "Cancel" agar Membatalkan Opsi
			cout << "Ketik \"Cancel\" untuk Membatalkan!" << endl;
			cout << "Masukkan Masalah yang Anda Keluhkan: ";
			getline(cin, reportUser);
			
			if( CancelString(reportUser) ) { // Jika Report User Bervalue "Cancel" atau "cancel" Maka True akan Dikembalikan
				// Output Cancel
				OutputCancel();
				// Melanjutkan Ke Menu Awal
				continue;
			}else {
				if( reportUser.empty() ) { // Jika Input an Kosong Tampilkan Pesan Kesalahan
					cout << endl << "String Tidak Boleh Kosong! Press Any Key to Menu!";
					// Menekan Tombol Apapun untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu
					continue;
				}
				
				// Menghapus Semua Command Line Diatas
				system("cls");
				// Jika Report User Berhasil Terkirim
				cout << "Tunggu Sebentar...";
				// Waktu Delay 3 Detik
				this_thread::sleep_for(chrono::seconds(3));
				// Menambahkan Baris Kosong
				cout << endl;
				cout << endl << "Report Berhasil Terkirim! Press Any Key to Menu!";
				// Menekan Tombol Apapun untuk Melanjutkan Program
				getch();
				// Menghapus Semua Command Line Diatas
				system("cls");
				// Melanjutkan Ke Menu
				continue;
			}
			
		}else if( pilihanMenu == 6 ) { // Pilihan 6
			// Menghapus Semua Command Line Diatas
			system("cls");
			while(true) {
				// Confirm Penarikan
				cout << "Apakah Anda Yakin Ingin Melanjutkan Penarikan Uang Senilai Rp " << pilihanNom[3] << "? (Y/N): ";
				cin >> confirm;
				
				// Menjalankan Function Confirm Status
				cnfrmStts = Confirm(confirm);
				
				if( cnfrmStts == "true" ) {
					// Jumlah Saldo Dikurangi Rp 100.000 (Sesuai Dimenu)
					saldoUser = TransferWithNominalDef(saldoUser, pilihanNom[3], "Sukses! Silahkan Diambil Uangnya.");
					break;
				}else if( cnfrmStts == "false" ) {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Penarikan Dibatalkan! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Awal
					break;
				}else {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Tidak Ada Opsi! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Confirm
					continue;
				}
			
			}
			
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Melanjutkan Ke Menu
			continue;
		}else if( pilihanMenu == 7 ) { // Pilihan 7
			// Menghapus Semua Command Line Diatas
			system("cls");
			while(true) {
				// Confirm Penarikan
				cout << "Apakah Anda Yakin Ingin Melanjutkan Penarikan Uang Senilai Rp " << pilihanNom[4] << "? (Y/N): ";
				cin >> confirm;
				
				// Menjalankan Function Confirm Status
				cnfrmStts = Confirm(confirm);
				
				if( cnfrmStts == "true" ) {
					// Jumlah Saldo Dikurangi Rp 100.000 (Sesuai Dimenu)
					saldoUser = TransferWithNominalDef(saldoUser, pilihanNom[4], "Sukses! Silahkan Diambil Uangnya.");
					break;
				}else if( cnfrmStts == "false" ) {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Penarikan Dibatalkan! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Awal
					break;
				}else {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Tidak Ada Opsi! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Confirm
					continue;
				}
			
			}
			
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Melanjutkan Ke Menu
			continue;
		}else if( pilihanMenu == 8 ) { // Pilihan 8
			// Menghapus Semua Command Line Diatas
			system("cls");
			while(true) {
				// Confirm Penarikan
				cout << "Apakah Anda Yakin Ingin Melanjutkan Penarikan Uang Senilai Rp " << pilihanNom[5] << "? (Y/N): ";
				cin >> confirm;
				
				// Menjalankan Function Confirm Status
				cnfrmStts = Confirm(confirm);
				
				if( cnfrmStts == "true" ) {
					// Jumlah Saldo Dikurangi Rp 100.000 (Sesuai Dimenu)
					saldoUser = TransferWithNominalDef(saldoUser, pilihanNom[5], "Sukses! Silahkan Diambil Uangnya.");
					break;
				}else if( cnfrmStts == "false" ) {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Penarikan Dibatalkan! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Awal
					break;
				}else {
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Output Error
					cout << "Tidak Ada Opsi! Press Any Key to Menu!";
					// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
					getch();
					// Menghapus Semua Command Line Diatas
					system("cls");
					// Melanjutkan Ke Menu Confirm
					continue;
				}
			
			}
			
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Melanjutkan Ke Menu
			continue;
		}else if( pilihanMenu == 9 ) { // Pilihan 9
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Variabel Nama Nama Bank
			int transferBankMenu;
			// Menu Menu Bank Menggunakan Perulangan
			while(true) {
				cout << "|=============================|" << endl;
				cout << "|         Daftar Bank         |" << endl;
				cout << "|=============================|" << endl;
				cout << "|                             |" << endl;
				cout << "| 1. Bank 9 Jambi             |" << endl;
				cout << "| 2. Bank BNI                 |" << endl;
				cout << "| 3. Bank BRI                 |" << endl;
				cout << "| 4. Kembali                  |" << endl;
				cout << "|                             |" << endl;
				cout << "|=============================|" << endl;
				
				// Memberikan Baris Kosong
				cout << endl;
				 
				// Input Pilihan Bank
				cout << "Pilih Bank: ";
				cin >> transferBankMenu;
				
				// Menghapus/Mengabaikan Value CIN (pilihanMenu) yang Telah Ditangkap Sebelumnya
				cin.ignore();
				
				// Jika Input an Bukan Sebuah Angka Tampilkan Kesalahan
				if( cin.fail() ) {
					// Menghapus Semua Command Line Diatas
					system("cls");
					cout << "Input Harus Berupa Angka! Press Any Key to Menu!";
	        		// Mereset/Membersihkan Cin
	        		cin.clear();
	        		// Mereset/Membersihkan buffer input
	        		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	        		// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
	    			getch();
	    			// Menghapus Semua Command Line Diatas
	    			system("cls");
	    			// Melanjutkan Ke Menu
					continue;
				}
				
				switch( transferBankMenu ) {
					case 1: // Transfer Ke Bank 9
						long long nominalTransfer;
						// Menghapus Semua Command Line Diatas
						system("cls");
						// Input an Nominal Transfer
						cout << "Masukkan Nominal Transfer: Rp ";
						cin >> nominalTransfer;
						// Menghapus Semua Command Line Diatas
						system("cls");
						// Saldo Dikurangi Sesuai dengan Jumlah yang Dimasukkan User
						saldoUser = TransferWithNominalDef(saldoUser, nominalTransfer, "Transfer Berhasil! Press Any Key to Menu!");
						// Menghapus Semua Command Line Diatas
						system("cls");
						// Menghentikan Looping/Kembali Ke Menu Pilihan Bank
						break;
					case 2: // Transfer Ke Bank BNI
						// Menjalankan Sebuah Function Transfer() yang Telah Dibuat
						saldoUser = Transfer(biayaAdmin, saldoUser);
						// Menghentikan Looping/Kembali Ke Menu Pilihan Bank
						break;
					case 3: // Transfer Ke Bank BRI
						// Menjalankan Sebuah Function Transfer yang Telah Dibuat
						saldoUser = Transfer(biayaAdmin, saldoUser);
						// Menghentikan Looping/Kembali Ke Menu Pilihan Bank
						break;
					case 4: // Kembali Ke Menu Awal
						// Menghapus Semua Command Line Diatas
						system("cls");
						cout << "Tunggu Sebentar...";
						// Waktu Delay 3 Detik
						this_thread::sleep_for(chrono::seconds(3));
						// Menghentikan Looping/Kembali Ke Menu Pilihan Bank
						break;
					default:
						// Menghapus Semua Command Line Diatas
						system("cls");
						cout << "Tidak Ada Menu! Wait...";
						// Waktu Delay 3 Detik
						this_thread::sleep_for(chrono::seconds(3));
						//Menghapus Semua Command Line Diatas
						system("cls");
						// Menghentikan Looping/Kembali Ke Menu Pilihan Bank
						continue;
				}
				
				// Menghapus Semua Command Line Diatas
				system("cls");
				// Menghentikan Looping/Kembali Ke Menu Awal
				break;
			}
		}else if( pilihanMenu == 10 ) { // Pilihan 10
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Jika Tidak Ada Error pada Pilihan Menu 10
			cout << "Tunggu Sebentar...";
			// Waktu Delay 3 Detik
			this_thread::sleep_for(chrono::seconds(3));
			// Memberikan Baris Kosong
			cout << endl;
			cout << endl << "Selesai! Silahkan Ambil Kartunya!";
			// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
			getch();
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Menghentikan Looping/Mengeluarkan User dari Menu
			break;
		}else {
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Jika Tidak Ada Error pada Pilihan Menu 10
			cout << "Menu Tidak Ada! Press Any Key to Menu!";
			// Menekan Tombol Apapun pada Keyboard untuk Melanjutkan Program
			getch();
			// Menghapus Semua Command Line Diatas
			system("cls");
			// Menghentikan Looping/Mengeluarkan User dari Menu
			continue;
		}
		
	}
	
	// Program Terakhir
	// Memberikan Baris Kosong
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	
	cout << "=================================================================================" << endl;
	cout << "=============================== Namun Perlu Diingat =============================" << endl;
	cout << "=================================================================================" << endl;
	cout << "========================= Ini Hanyalah Sebuah Simulasi ==========================" << endl;
	cout << "=================================================================================" << endl;
	cout << "================== Tidak Ada yang Nyata Didalam Program Ini =====================" << endl;
	cout << "=================================================================================" << endl;
	cout << "============== Program Ini Mendapatkan Referensi dari BANK 9 JAMBI ==============" << endl;
	cout << "=================================================================================" << endl;
	cout << "======== Maaf Jika Ada Kesalahan atau Kurang Kepuasan Dalam Program Kami ========" << endl;
	cout << "=================================================================================" << endl;
	cout << "============================ Program Telah Berakhir =============================" << endl;
	cout << "=================================================================================" << endl;
	cout << "================================= Terima Kasih ==================================" << endl;
	cout << "=================================================================================";
	
	// Memberikan Baris Kosong
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	
	return 0;
}