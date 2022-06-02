#include <stdio.h>	//untuk library input output
#include <string.h> //untuk library yang berhubungan dengan data string
#include <stdlib.h> //untuk penggunaan pointer
#include "function.c"

// func utama main
int main()
{
	int input, indexAccount;
	FILE *ptr; // penggunaan file handling

	// pembuatan pointer dari struct Account bernama mahasiswa
	Account *mahasiswa = (Account *)calloc(100, sizeof(Account));
	// pembuatan pointer dari struct Account bernama admin
	Account *admin = (Account *)calloc(100, sizeof(Account));
	// pembuatan pointer dari struct Buku bernama data
	Buku *data = (Buku *)calloc(100, sizeof(Buku));

	struct biodata *root = NULL;

	// untuk memberikan informasi jika memory untuk pointer tidak tercukupi
	if (mahasiswa == NULL || admin == NULL || admin == NULL)
	{
		printf("Error! Memory Not Allocated");
		exit(0);
	}

	// memanggil func opening untuk memulai program
	// opening();

// meminta input pilihan masuk
nanyaakun: // program akan kembali kesini ketika memanggil goto nanyaakun
	system("cls");
	printf(" =================================================\n"
		   " |--------- Selamat Datang  Di Aplikasi ---------|\n"
		   " |------------  E-Library Mahasiswa  ------------|\n"
		   " =================================================\n\n"
		   " Masuk Sebagai : \n\n 1. Admin\t\t2. Mahasiswa\n\n Masukkan Pilihan : ");
	scanf("%d", &input);
	system("cls");
	if (input < 1 || input > 2)
	{
		error(); // memanggil func error ketika terjadi error
		system("cls");
		goto nanyaakun; // goto berfungsi untuk melanjutkan ke tempat selanjutnya yang direncanakan
	}

	// memanggil func login page yang akan mereturn index dalam data base dari username yang login
	indexAccount = loginPage(ptr, admin, mahasiswa, input);

	if (input == 1)
	{ // jika user login sebagai admin
		adminAkses(ptr, data, mahasiswa, root);
	}
	else if (input == 2)
	{ // jika user login sebagai mahasiswa
		mahasiswaAkses(ptr, data, mahasiswa, root, indexAccount);
	}

	// Setelah program selesai, program akan melepas memori pointer
	free(mahasiswa);
	free(admin);
	free(data);
	return 0;
}
