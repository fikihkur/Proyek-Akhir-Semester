#include "function.h"

// func untuk menampilkan opening program
void opening()
{
	int i; // deklarasi variabel integer

	printf("!--- Untuk Interface Maksimal Silakan Full Screen Lalu Tekan ENTER ---!");
	getchar();			// memanggil function getchar
	system("CLS");		// Membersihkan layar
	Sleep(800);			// menjeda program selama 0.8 detik
	system("color F0"); // memberikan warna pada layar

	printf("\n\n\n\n\n\n\n");
	char a[] = {"\t\t\t\t\t\t\t\t\t\t=================================================\n"
				"\t\t\t\t\t\t\t\t\t\t|--------- Selamat Datang  Di Aplikasi ---------|\n"
				"\t\t\t\t\t\t\t\t\t\t|------------  E-Library Mahasiswa  ------------|\n"
				"\t\t\t\t\t\t\t\t\t\t|-----------  Pemrograman Lanjut 01  -----------|\n"
				"\t\t\t\t\t\t\t\t\t\t=================================================\n"
				"\t\t\t\t\t\t\t\t\t\t|               This app made by :              |\n"
				"\t\t\t\t\t\t\t\t\t\t|  1. Albertus Timothy Gunawan  // 2106639472   |\n"
				"\t\t\t\t\t\t\t\t\t\t|  2. Luthfi Misbachul Munir   // 2106631961    |\n"
				"\t\t\t\t\t\t\t\t\t\t|  3. Abdul Fikih Kurnia       // 2106731200    |\n"
				"\t\t\t\t\t\t\t\t\t\t=================================================\n\n"};

	for (i = 0; a[i] != a[828]; i++)
	{
		printf("%c", a[i]);
		Sleep(2);
	}

	printf("\t\t\t\t\t\t\t\t\t\t\t\t   Loading... \n\n");
	printf("\a");
	Sleep(1000); // menjeda program selama 1 detik

	for (i = 1; i <= 211; i++)
	{
		printf("%c", 223); // 233 adalah kode KARAKTER beta di dalam ASCII2
		if (i == 70 || i == 140)
			Sleep(500); // menjeda program selama 0.5 detik
		Sleep(12);
	}
	Sleep(1600);   // menjeda program selama 1.6 detik
	system("CLS"); // Membersihkan layar
}

// func loginPage untuk pengaksesan dan pembuatan akun dalam program yang akan disimpan dalam file
int loginPage(FILE *ptr, Account *admin, Account *mahasiswa, int input)
{
	int choose, indexAccount;

	switch (input)
	{
	case 1:										// ketika user memberikan input 1 atau login maka akan mengcall func loginAccount
		ptr = fopen("Account Admin.txt", "a+"); // membuka file dengan mode append dan read
		if (ptr == NULL)
		{
			printf("File tidak ditemukan.\n");
			exit(0);
		}

	point:
		printf(" ==================================================\n"
			   " |--------- Aplikasi E-Library Mahasiswa ---------|\n"
			   " |-------------- Akses Administrator -------------|\n"
			   " ==================================================\n\n"
			   " Pilihan :\n\n 1. Sign In\t\t 2. Sign Up\n\n Masukkan Pilihan : ");
		scanf("%d", &choose);
		system("cls");
		if (choose < 1 || choose > 2)
		{
			error();	// memanggil func error ketika terjadi error
			goto point; // goto berfungsi untuk melanjutkan ke tempat selanjutnya yang direncanakan
		}

		// function untuk sign up dan sign in (bergantung pada choose)
		return loginAccount(ptr, admin, choose);

		fclose(ptr);
		break;

	case 2: // ketika user memberikan input 2 atau membuat akun maka akan mengcall func newAccount
		ptr = fopen("Account Mahasiswa.txt", "a+");
		if (ptr == NULL)
		{
			printf(" File tidak ditemukan.\n");
			exit(0);
		}

	pointMahasiswa: // titik tuju point mahasiswa
		printf(" ==================================================\n"
			   " |--------- Aplikasi E-Library Mahasiswa ---------|\n"
			   " |---------------- Akses Mahasiswa ---------------|\n"
			   " ==================================================\n\n"
			   " Pilihan : \n\n 1. Sign In\t\t 2. Sign Up\n\n Masukkan Pilihan : ");
		scanf("%d", &choose);
		system("cls");
		if (choose < 1 || choose > 2)
		{
			error();			 // memanggil func error ketika terjadi error
			goto pointMahasiswa; // goto berfungsi untuk melanjutkan ke tempat selanjutnya yang direncanakan
		}

		// function untuk sign up dan sign in (bergantung pada choose)
		return loginAccount(ptr, mahasiswa, choose);

		fclose(ptr);
		break;
	}
}

// func loginAccount untuk dapat mengakses program e-library
int loginAccount(FILE *ptr, Account *database, int inOrUp)
{
	int i, found = 0, pilih, index, temp;
	char inputUsername[100], inputPass[50];

	// memindahkan data dari file ke dalam struct
	for (i = 0; i < 100; i++)
	{
		fscanf(ptr, "%s %[^\n]s", &(database + i)->pass, &(database + i)->username);
	}

	// jika user memilih untuk sign up, program akan langsung memerintahkan ke line untuk memanggil signup
	if (inOrUp == 2)
	{
		goto signup;
		exit(0);
	}

	while (found == 0)
	{
		printf("|-------------------------------|\n"
			   "|~ ~ ~ ~ ~   Sign In   ~ ~ ~ ~ ~|\n"
			   "|-------------------------------|\n\n");
		printf("Masukkan Username Anda : ");
		scanf("%*c%[^\n]", &inputUsername);
		printf("Masukkan Password Anda : ");
		i = 0;
		while (1)
		{
			temp = getch();
			if (temp == 13)
			{ // jika ditekan enter maka akan break
				break;
			}
			else if (temp == 8)
			{
				if (i > 0)
				{
					i--;
					inputPass[i] = '\0';
					printf("\b \b");
				}
			}
			else if (temp == 32 || temp == 9) // jika inputan spasi atau tab maka tidak terdeteksi
				continue;
			else
			{
				inputPass[i] = temp;
				i++;
				printf("*"); // memunculkan bintang untuk mencover huruf
			}
		}
		inputPass[i] = '\0'; // menambahkan spasi di akhir array
		// perulangan untuk pengecekan username dan password
		for (i = 0; i < 100; i++)
		{
			// login sukses
			if (strcmp(inputUsername, (database + i)->username) == 0 && strcmp(inputPass, (database + i)->pass) == 0)
			{
				found = 1;
				index = i;
			}
		}

		// jika login sukses, function akan mereturn index
		if (found == 1)
		{
			system("cls");
			return index;
		}
		else
		{ // login gagal
			error();
		titik: // titik tuju goto titik
			printf("|------------------------------------|\n"
				   "|~ ~ ~ ! Akun Tidak Ditemukan ! ~ ~ ~|\n"
				   "|------------------------------------|\n\n");
			printf(" Buat Akun Baru?\n\n 1. Ya\t 2. Tidak\n\n Masukkan Pilihan: ");
			scanf("%d", &pilih);
			if (pilih > 2 || pilih < 1)
			{ // errorhandling
				error();
				goto titik;
			}
			else if (pilih == 1)
			{ // melakukan sign up
			signup:
				system("cls");
				newAccount(ptr, database); // memanggil fungsi newAccount
			}
			system("cls");
		}
	}
}

// func newAccount untuk pembuatan akun dalam program yang akan disimpan dalam file
void newAccount(FILE *ptr, Account *database)
{
	int signup, i, pilih, temp;
	char inputPass[30], inputUser[50];

balik: // titik tuju goto balik
	i = 0;
	printf("|-------------------------------|\n"
		   "|~ ~ ~ ~ ~   Sign Up   ~ ~ ~ ~ ~|\n"
		   "|-------------------------------|\n\n"
		   " Masukkan Username (Tanpa Spasi): ");
	while (1)
	{
		temp = getch();
		if (temp == 13)
		{ // jika di enter maka akan break
			break;
		}
		else if (temp == 8)
		{ // jika di backspace maka bisa menghapus
			if (i > 0)
			{
				i--;
				inputUser[i] = '\0';
				printf("\b \b");
			}
		}
		else if (temp == 32 || temp == 9) // jika spasi atau tab maka tidak akan masuk ke dalam array
			continue;
		else
		{
			inputUser[i] = temp;
			i++;
			printf("%c", inputUser[i - 1]); // untuk memunculkan huruf yang di input
		}
	}
	inputUser[i] = '\0';						  // menambahkan spasi di akhir array
	strcpy((database + 99)->username, inputUser); // memasukkan array inputUser ke dalam username database

	for (i = 0; i < 99; i++)
	{
		// mengecek apakah username yang diinput pernah dipakai atau tidak
		if (strcmp((database + i)->username, (database + 99)->username) == 0)
		{
			system("cls");
			printf(" ! ~ ~ Username Telah Terpakai ~ ~ !\n");
			goto balik;
		}
	}
	printf("\n Masukkan Password (Tanpa Spasi): ");
	i = 0;
	while (1)
	{
		temp = getch();
		if (temp == 13)
		{ // jika di enter maka akan break
			break;
		}
		else if (temp == 8)
		{ // jika spasi atau tab maka tidak akan masuk ke dalam array
			if (i > 0)
			{
				i--;
				inputPass[i] = '\0';
				printf("\b \b");
			}
		}
		else if (temp == 32 || temp == 9) // jika spasi atau tab maka tidak akan masuk ke dalam array
			continue;
		else
		{
			inputPass[i] = temp;
			i++;
			printf("*"); // mengcover huruf inputan dengan bintang
		}
	}
	inputPass[i] = '\0';
	strcpy((database + 99)->pass, inputPass); // memasukkan array inputPass ke dalam pass database

	// mennyimpan account dalam database
	fprintf(ptr, "%s %s\n", (database + 99)->pass, (database + 99)->username);

	system("cls");
	printf("! - - Silakan Masuk Kembali Ke Dalam Program Setelah Keluar - - !\n");
	exit(0);
}

// func adminAkses untuk masuk kedalam func admin
void adminAkses(FILE *ptr, Buku *data, Account *database)
{
	int pil;
	system("cls");
	while (pil != 6)
	{
		printf("===================================\n"
			   "|~ ~ ~ Aplikasi Perpustakaan ~ ~ ~|\n"
			   "|~ ~ ~ ~ ~  Menu Admin   ~ ~ ~ ~ ~|\n"
			   "|---------------------------------|\n"
			   "|   1. Input Buku                 |\n"
			   "|   2. Daftar Buku                |\n"
			   "|   3. Status Peminjaman Buku     |\n"
			   "|   4. Permintaan Buku            |\n"
			   "|   5. Panduan Aplikasi           |\n"
			   "|   6. EXIT                       |\n"
			   "===================================\n\n"
			   "Masukkan Pilihan [ 1 s.d. 6 ] = ");
		scanf("%d", &pil);

		while (pil < 1 || pil > 6)
		{ // eror handling
			error();
			printf("Mohon Masukkan Pilihan dengan benar!: ");
			scanf("%d", &pil);
			system("cls");
		}
		switch (pil)
		{
		case 1:
			inputBuku(ptr, data, database); // memanggil fungsi untuk menginput buku
			system("CLS");					// membersihkan layar display
			break;
		case 2:
			daftarBuku(ptr, data); // memanggil fungsi untuk melihat daftar buku
			system("pause");	   // menjeda program sampai ada input
			system("CLS");		   // membersihkan layar display
			break;
		case 3:
			laporan(ptr, data, database); // memanggil fungsi untuk melihat laporan mahasiswa yang meminjam
			system("pause");			  // menjeda program sampai ada input
			system("CLS");				  // membersihkan layar display
			break;
		case 4:
			lihatReqBuku(ptr, database); // memanggil fungsi untuk melihat buku yang direquest oleh mahasiswa
			system("pause");			 // menjeda program sampai ada input
			system("CLS");				 // membersihkan layar display
			break;
		case 5:
			panduanAdmin(); // melihat panduan program
			break;
		case 6:
			closing();
			exit(0);
		default:
			error();
		}
	}
}

// func inputBuku untuk menginput buku kedalam database
void inputBuku(FILE *ptr, Buku *data, Account *database)
{
	int i = 0, j, lagi, pilih, sizeReq = 0, indexUsername[100], found = 0;
	char reqJudul[100][100];

pilihan: // titik tuju goto pilihan
	system("CLS");
	printf(" ===============================================\n"
		   " |---------- Pilihan Menu Input Buku ----------|\n"
		   " ===============================================\n\n");
	printf(" Pilihan : \n\n 1. Menerima Request Buku\t 2. Input Buku\n\nMasukkan Pilihan : ");
	scanf("%d", &pilih); // menginput pilihan menu
	system("CLS");
	// pengkondisian pilihan
	switch (pilih)
	{
	case 1:
	cari:
		lihatReqBuku(ptr, database); // memanggil fungsi lihat req buku
		ptr = fopen("Database Req Buku.txt", "r");
		if (ptr == NULL)
		{
			printf("File tidak ditemukan.\n");
			exit(0);
		}

		for (j = 0; j < 100; j++)
		{
			fscanf(ptr, "%d %[^\n]s", &indexUsername[j], &reqJudul[j]);
			if (*reqJudul[j] == '\0')
			{
				break;
			}
			sizeReq++;
		}
		fclose(ptr);
	case 2:
		// Input data buku baru
		do
		{
			printf(" ===============================================\n"
				   " |-------------- Menu Input Buku --------------|\n"
				   " ===============================================\n\n"
				   " |------------ Pengisian Data Buku ------------|\n\n");
			printf(" Masukkan Nomor Buku\t\t\t\t: ");
			scanf("%s", &(data + i)->kode);
			printf(" Masukkan Judul Buku\t\t\t\t: ");
			scanf("%*c%[^\n]", &(data + i)->judul);
			printf(" Masukkan Jumlah Buku\t\t\t\t: ");
			scanf("%d", &(data + i)->stok);

			if (pilih == 1)
			{
				sizeReq--;
				if (strcmp((data + i)->judul, reqJudul[sizeReq]) == 0)
				{
					found = 1;
				}
				freopen("Database Req Buku.txt", "w", ptr);
				if (ptr == NULL)
				{
					printf("File tidak ditemukan.\n");
					exit(0);
				}
				for (j = 0; j < sizeReq; j++)
				{
					if (strcmp((data + i)->judul, reqJudul[j]) == 0)
					{
						found = 1;
						if (j == (sizeReq - 1))
						{
							break;
						}
						j++;
					}
					fprintf(ptr, "%d %s\n", indexUsername[j], reqJudul[j]);
				}
				fclose(ptr);
				if (found == 0)
				{
					printf("==================================================================\n"
						   "| ! ~ ~ ~ Buku yang diinput tidak sesuai dengan database ~ ~ ~ ! |\n"
						   "==================================================================\n\n");
					printf("Buku yang diinput tidak sesuai dengan database\n");
					goto cari;
				}
			}
			ptr = fopen("Data Base Buku.txt", "a");
			if (ptr == NULL)
			{
				printf("File tidak ditemukan.\n");
				exit(0);
			}
			// memindahkan data ke database
			fprintf(ptr, "%s %d %s\n", (data + i)->kode, (data + i)->stok, (data + i)->judul);
			fclose(ptr);

			printf("\n Apakah Anda Ingin Menambahkan Buku Lagi ?\n YA : 1\n NO : 2\n Masukkan Pilihan : ");
			scanf("%d", &lagi);
			if (lagi == 1)
			{ // jika mengulang maka layar akan di kosongkan
				system("CLS");
			}
		} while (lagi == 1);
		break;
	default: // error handling
		error();
		printf("\nPilihan yang anda masukkan salah!\n");
		goto pilihan; // menuju titik tuju pilihan
		break;
	}
}

// func daftarBuku untuk menampilkan seluruh database buku
void daftarBuku(FILE *ptr, Buku *data)
{
	int j, i, size = 0;
	system("CLS"); // Membersihkan layar
	ptr = fopen("Data Base Buku.txt", "a+");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}

	printf("==================================================================================================\n"
		   "| ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Menu Daftar Buku ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |\n"
		   "==================================================================================================\n\n");
	for (i = 1; i <= 92; i++)
	{ // membuat garis horizontal tabel
		printf("%c", 196);
	}
	printf("\n");
	printf("|%-3s|\t%-10s  |\t%-30s|%-2s%-13s|%-4s%-16s|\n", "No.", "Kode Buku", "Judul Buku", " ", "Jumlah Buku", " ", "Status Buku");
	for (i = 1; i <= 92; i++)
	{ // membuat garis horizontal tabel
		printf("%c", 196);
	}
	printf("\n");

	// memindahkan database file ke dalam struct dan menghitung size dari database buku
	for (j = 0; j < 100; j++)
	{
		fscanf(ptr, "%s %d %[^\n]s", &(data + j)->kode, &(data + j)->stok, &(data + j)->judul);
		if (*(data + j)->judul == '\0')
		{
			break;
		}
		size++;
	}
	sort(data, size); // mengurutkan struct berdasarkan judul

	for (j = 0; j < size; j++)
	{
		if ((data + j)->stok > 0)
		{ // output jika stok = 0
			printf("| %-2d|\t%-10s  |\t%-30s|%-7s%-8d|%-6s%-14s|\n", j + 1, (data + j)->kode, (data + j)->judul, " ", (data + j)->stok, " ", "Tersedia");
			for (i = 1; i <= 92; i++)
			{ // membuat garis horizontal tabel
				printf("%c", 196);
			}
			printf("\n");
		}
		else
		{ // output jika stok /= 0
			printf("| %-2d|\t%-10s  |\t%-30s|%-7s%-8d|%-3s%-17s|\n", j + 1, (data + j)->kode, (data + j)->judul, " ", (data + j)->stok, " ", "Tidak Tersedia");
			for (i = 1; i <= 92; i++)
			{ // membuat garis horizontal tabel
				printf("%c", 196);
			}
			printf("\n");
		}
	}
	fclose(ptr);
}

// func laporan untuk melihat laporan peminjaman
void laporan(FILE *ptr, Buku *data, Account *database)
{
	int i, j, size = 0, account[100] = {0}, indexJudul[100] = {0};

	ptr = fopen("Data Peminjam.txt", "r");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// memindahkan database file ke dalam struct dan menghitung size dari data peminjam
	for (i = 0; i < 100; i++)
	{
		fscanf(ptr, "%d %d %d %d %d %s %s %d %[^\n]s", &(data + i)->tglPinjam, &(data + i)->blnPinjam, &(data + i)->tglBalik, &(data + i)->blnBalik, &indexJudul[i], &(data + i)->fakultas, &(data + i)->NPM, &account[i], &(data + i)->namaPeminjam);
		if (*(data + i)->namaPeminjam == '\0')
		{
			break;
		}
		size++;
	}
	fclose(ptr);

	ptr = fopen("Account Mahasiswa.txt", "r");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// memindahkan dari database file ke dalam struct
	for (i = 0; i < 100; i++)
	{
		fscanf(ptr, "%s %[^\n]s", &(database + i)->pass, &(database + i)->username);
	}
	fclose(ptr);

	ptr = fopen("Data Base Buku.txt", "r");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// memindahkan dari database file ke dalam struct
	for (i = 0; i < 100; i++)
	{
		fscanf(ptr, "%s %d %[^\n]s", &(data + i)->kode, &(data + i)->stok, &(data + i)->judul);
	}
	fclose(ptr);

	system("CLS");
	// Mencetak data peminjaman buku
	printf("|==========================================================================================================================================================|\n"
		   "| ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Menu Laporan Peminjaman Buku ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |\n"
		   "|==========================================================================================================================================================|\n\n");
	for (i = 1; i <= 156; i++)
	{ // membuat garis horizontal tabel
		printf("%c", 196);
	}
	printf("\n");
	printf("| %-4s | %-15s | %-25s | %-12s | %-9s | %-15s | %-20s | %-10s |  %-17s |\n",
		   "No.", "Username", "Nama Peminjam", "NPM", "Fakultas", "Tgl Peminjaman", "Judul Buku", "Kode Buku", "Tgl Pengembalian");
	for (i = 1; i <= 156; i++)
	{ // membuat garis horizontal tabel
		printf("%c", 196);
	}
	printf("\n");
	for (i = 0; i < size; i++)
	{
		printf("|  %-3d | %-15s | %-25s | %-12s | %-9s | %7d-%-7d | %-20s | %-10s |  %8d-%-8d |\n", i + 1, (database + account[i])->username, (data + i)->namaPeminjam,
			   (data + i)->NPM, (data + i)->fakultas, (data + i)->tglPinjam, (data + i)->blnPinjam, (data + indexJudul[i])->judul,
			   (data + indexJudul[i])->kode, (data + i)->tglBalik, (data + i)->blnBalik);
		for (j = 1; j <= 156; j++)
		{ // membuat garis horizontal tabel
			printf("%c", 196);
		}
		printf("\n");
	}
	printf("\n");
}

// func lihatReqBuku untuk melihat buku yang di request oleh mahasiswa
void lihatReqBuku(FILE *ptr, Account *database)
{
	int i, j, size = 0, indexUsername[100];
	char judul[100][100];
	for (i = 0; i < 100; i++)
	{
		indexUsername[i] = -1;
	}
	ptr = fopen("Database Req Buku.txt", "r");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// memindahkan database file ke dalam struct dan menghitung size dari data base req buku
	for (i = 0; i < 100; i++)
	{
		fscanf(ptr, "%d %[^\n]s", &indexUsername[i], &judul[i]);
		if (indexUsername[i] == -1)
		{
			break;
		}
		size++;
	}
	fclose(ptr);

	ptr = fopen("Account Mahasiswa.txt", "r");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// memindahkan database file ke dalam struct
	for (i = 0; i < 100; i++)
	{
		fscanf(ptr, "%s %[^\n]s", &(database + i)->pass, &(database + i)->username);
		if (*(database + i)->username == '\0')
		{
			break;
		}
	}
	fclose(ptr);

	system("CLS");
	printf("|==========================================================|\n"
		   "| ~ ~ ~ ~ ~ ~ Daftar Permintaan Pengadaan Buku ~ ~ ~ ~ ~ ~ |\n"
		   "|==========================================================|\n\n");
	for (i = 1; i <= 63; i++)
	{ // membuat garis horizontal tabel
		printf("%c", 196);
	}
	printf("\n");
	printf("| %-4s |   %-15s |   %-30s |\n", "No.", "Username", "Judul Buku");
	for (i = 1; i <= 63; i++)
	{ // membuat garis horizontal tabel
		printf("%c", 196);
	}
	printf("\n");
	for (i = 0; i < size; i++)
	{
		printf("|  %-3d |   %-15s |   %-30s |\n", i + 1, (database + indexUsername[i])->username, judul[i]);
		for (j = 1; j <= 63; j++)
		{ // membuat garis horizontal tabel
			printf("%c", 196);
		}
		printf("\n");
	}
	printf("\n");
}

// func mahasiswaAkses untuk masuk ke dalam func mahasiswa
void mahasiswaAkses(FILE *ptr, Buku *data, Account *database, struct biodata *root, int account)
{
	int pil;
	system("cls");
	while (pil != 7)
	{
		printf("=====================================\n"
			   "|~ ~ ~ Aplikasi Perpustakaan ~ ~ ~ ~|\n"
			   "|~ ~ ~ ~ ~ Menu Mahasiswa ~ ~ ~ ~ ~ |\n"
			   "|-----------------------------------|\n"
			   "|   1. Input Biodata                |\n"
			   "|   2. Daftar Buku                  |\n"
			   "|   3. Peminjaman Buku              | \n"
			   "|   4. Pengembalian Buku            | \n"
			   "|   5. Request Buku                 |\n"
			   "|   6. Panduan Aplikasi             | \n"
			   "|   7. EXIT                         | \n"
			   "=====================================\n\n"
			   "Masukkan Pilihan [ 1 s.d. 7 ] : ");
		scanf("%d", &pil);

		while (pil < 1 || pil > 7)
		{ // error handling
			error();
			printf(" Mohon Masukkan Pilihan dengan benar !: ");
			scanf("%d", &pil);
			system("cls");
		}
		// pengkondisian pilihan menu utama
		switch (pil)
		{
		case 1:
			inputBiodata(ptr, root, account);
			system("pause"); // menjeda program sampai ada input
			system("CLS");	 // membersihkan layar display
			break;
		case 2:					   // jika pilihan 1
			daftarBuku(ptr, data); // memanggil fungsi daftarBuku
			system("pause");	   // menjeda program sampai ada input
			system("CLS");		   // membersihkan layar display
			break;
		case 3: // jika pilihan 2
			system("cls");
			pinjamBuku(ptr, data, database, account); // memanggil fungsi pinjamBuku
			system("CLS");
			break;
		case 4:										 // jika pilihan 3
			balikBuku(ptr, data, database, account); // memanggil fungsi balikBuku
			system("pause");						 // menjeda program sampai ada input
			system("CLS");							 // membersihkan layar display
			break;
		case 5:					   // jika pilihan 4
			reqBuku(ptr, account); // memanggil fungsi request buku
			system("CLS");
			break;
		case 6:					// jika pilihan 5
			panduanMahasiswa(); // memanggil fungsi panduan aplikasi mahasiswa
			break;
		case 7: // jika pilihan 6
			closing();
			exit(0);
		default: // error handling
			error();
		}
	}
}

// func pijamBuku untuk mahasiswa agar dapat meminjam buku
void pinjamBuku(FILE *ptr, Buku *data, Account *database, int account)
{
	int i, indexJudul, sizeLib = 0, pilih, pil;
	char judulBuku[50];

	ptr = fopen("Data Base Buku.txt", "r");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// menghitung ukuran dari library dan memindahkan data ke dalam struct
	for (i = 0; i < 100; i++)
	{
		fscanf(ptr, "%s %d %[^\n]s", &(data + i)->kode, &(data + i)->stok, &(data + i)->judul);
		if (*(data + i)->judul == '\0')
		{ // jika judul habis maka akan break
			break;
		}
		sizeLib++;
	}
	fclose(ptr);

	ptr = fopen("Account Mahasiswa.txt", "r");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// memindahkan data dari file ke dalam struct
	for (i = 0; i < 100; i++)
	{
		fscanf(ptr, "%s %[^\n]s", &(database + i)->pass, &(database + i)->username);
	}
	fclose(ptr);

bek: // titik tuju goto bek
	system("CLS");
	// melakukan input data peminjaman buku
	printf(" ==============================================\n"
		   " |----------- Menu Peminjaman Buku -----------|\n"
		   " ==============================================\n\n");
	printf("Nama Peminjam\t\t\t\t: ");
	scanf("%*c%[^\n]", &(data + 0)->namaPeminjam);
	printf("Nomor Pokok Mahasiswa\t\t\t: ");
	scanf("%s", &(data + 0)->NPM);
	printf("Fakultas (FT = Fakultas Teknik, dst)\t: ");
	scanf("%s", &(data + 0)->fakultas);
cari: // titik tuju goto cari
	do
	{
		printf("Judul Buku yang Dipinjam\t\t: ");
		scanf("%*c%[^\n]", &judulBuku);
		indexJudul = searchBuku(data, judulBuku, sizeLib); // index untuk mengakses judul, stock
		// pengkondisian jika buku tidak ditemukan
		if (indexJudul == -1)
		{
			error();
			printf(" Buku Tidak Ditemukan!\n\n Request Buku?\n\n 1. Ya\t 2. Tidak\n\n Masukkan Pilihan : ");
			scanf("%d", &pilih);
			while (pilih < 1 || pilih > 2)
			{ // pengkondisian jika pilihan tidak tepat
				error();
				printf(" Pilihan tidak Tersedia\n\nRequest Buku? \n\n 1. Ya\t2. Tidak \n\n Masukkan Pilihan : ");
				scanf("%d", &pilih);
			}
			// pengkondisian pilihan
			if (pilih == 1)
			{
				reqBuku(ptr, account); // memanggil fungsi request buku
				goto akhir;
			} // untuk kembali ke menu
			if (pilih == 2)
			{
				goto cari;
			} // menuju ke titik tuju cari
		}
		else if ((data + indexJudul)->stok <= 0)
		{ // pengkondisian jika stok buku <= 0
			printf("Stok Buku Habis, Silakan Pilih Buku Yang Lain\n");
		}
		else
		{ // jika nilai return tidak dikenali
			break;
		}
	} while ((data + indexJudul)->stok <= 0); // sentinel perulangan jika stok <= 0

	// mengurangi stock buku setelah dipinjam
	(data + indexJudul)->stok--;

// input bulan peminjaman
bulan:
	printf("Bulan Peminjaman\t\t\t: ");
	scanf("%d", &(data + 0)->blnPinjam);
	if ((data + 0)->blnPinjam < 1 || (data + 0)->blnPinjam > 12)
	{
		error();
		printf("Bulan Tidak Ada!\n");
		goto bulan;
	}
// input tanggal peminjaman
tanggal:
	printf("Tanggal Peminjaman\t\t\t: ");
	scanf("%d", &(data + 0)->tglPinjam);
	if ((data + 0)->blnPinjam <= 7)
	{
		if ((data + 0)->blnPinjam % 2 != 0)
		{
			if ((data + 0)->tglPinjam < 0 || (data + 0)->tglPinjam > 31)
			{
				error();
				printf("Tanggal Tidak Ada!\n");
				goto tanggal;
			}
		}
		else if ((data + 0)->blnPinjam == 2)
		{
			if ((data + 0)->tglPinjam < 0 || (data + 0)->tglPinjam > 28)
			{
				error();
				printf("Tanggal Tidak Ada!\n");
				goto tanggal;
			}
		}
		if ((data + 0)->blnPinjam % 2 == 0)
		{
			if ((data + 0)->tglPinjam < 0 || (data + 0)->tglPinjam > 30)
			{
				error();
				printf("Tanggal Tidak Ada!\n");
				goto tanggal;
			}
		}
	}
	hitungTanggal(data);

	system("CLS");
	// menampilkan kartu peminjaman dan memverifikasi apakah peminjaman sudah benar
	kartuPinjam(data, database, indexJudul, account);
	printf("\n\n Apakah data peminjaman sudah benar? \n\n 1. Benar \n 2. Salah \n\n Masukkan Pilihan :  ");
	scanf("%d", &pil);
	if (pil == 2)
	{
		goto bek;
	}

	ptr = fopen("Data Peminjam.txt", "a");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// menambahkan data-data peminjaman ke file data peminjam
	fprintf(ptr, "%d %d %d %d %d %s %s %d %s\n", (data + 0)->tglPinjam, (data + 0)->blnPinjam, (data + 0)->tglBalik, (data + 0)->blnBalik, indexJudul, (data + 0)->fakultas, (data + 0)->NPM, account, (data + 0)->namaPeminjam);
	fclose(ptr);

	freopen("Data Base Buku.txt", "w", ptr);
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// update data base buku
	for (i = 0; i < sizeLib; i++)
	{
		fprintf(ptr, "%s %d %s\n", (data + i)->kode, (data + i)->stok, (data + i)->judul);
	}
akhir:
	fclose(ptr);
}

// func searchBuku untuk melakukan pencarian buku
int searchBuku(Buku *data, char input[], int size)
{
	int i, j, k, index = -1, counter;

	for (i = 0; i <= size; i++)
	{ // mengecek tiap judul dalam database
		counter = 0;
		for (j = 0, k = 0; j < strlen((data + i)->judul); j++)
		{ // mengecek setiap karakter pada judul
			while ((data + i)->judul[j + k] == input[k])
			{ // jika ada karakter judul yang sama dengan karakter setelahnya juga akan di cek
				counter++;
				k++;
				if (strlen(input) == counter)
				{ // jika semua karakter input sama dengan dengan judul
					index = i;
					return index;
				}
				if (k == strlen(input))
				{
					break;
				}
			}
		}
		if (i == size - 1)
		{ // jika searching tidak menemukan hasil
			return -1;
		}
	}
}

// func hitungTanggal untuk menghitung kapan tanggal pengembalian buku
void hitungTanggal(Buku *data)
{
	if ((data + 0)->blnPinjam == 12)
	{
		(data + 0)->blnBalik = 1;
		(data + 0)->tglBalik = (data + 0)->tglPinjam;
	}
	else if ((data + 0)->blnPinjam == 1 && (data + 0)->tglPinjam > 28)
	{
		(data + 0)->blnBalik = 3;
		(data + 0)->tglBalik = (data + 0)->tglPinjam - 28;
	}
	else if ((data + 0)->tglPinjam == 31)
	{
		(data + 0)->blnBalik = (data + 0)->blnPinjam + 2;
		(data + 0)->tglBalik = 1;
	}
	else
	{
		(data + 0)->blnBalik = (data + 0)->blnPinjam + 1;
		(data + 0)->tglBalik = (data + 0)->tglPinjam;
	}
}

// func kartuPinjam untuk melihak kartu peminjaman buku
void kartuPinjam(Buku *data, Account *database, int indexJudul, int account)
{
	int user, size = 0, index = 0, i;
	// menampilkan output kartu peminjaman
	printf(" ===================================================\n"
		   " |----------- E-Receipt Peminjaman Buku -----------|\n"
		   " |-------------  E-Library Mahasiswa  -------------|\n"
		   " ===================================================\n");
	printf(" | %-20s : %-24s |\n", "Username", (database + account)->username);
	printf(" | %-20s : %-24s |\n", "Nama Peminjam", (data + 0)->namaPeminjam);
	printf(" | %-20s : %-24s |\n", "NPM", (data + 0)->NPM);
	printf(" | %-20s : %-24s |\n", "Fakultas", (data + 0)->fakultas);
	printf(" | %-20s : %-24s |\n", "Judul Buku", (data + indexJudul)->judul);
	printf(" | %-20s : %-6s %-3d %-8s %-4d |\n", "Tanggal Peminjaman", "Bulan ", (data + 0)->blnPinjam, "Tanggal ", (data + 0)->tglPinjam);
	printf(" | %-20s : %-6s %-3d %-8s %-4d |\n", "Tanggal Pengembalian", "Bulan ", (data + 0)->blnBalik, "Tanggal ", (data + 0)->tglBalik);
	printf(" | %-20s   %-24s |\n", " ", " ");
	printf(" | %-13s%-7c   %-24s |\n", "Terima Kasih", 1, " ");
	printf(" | %-20s   %-24s |\n", " ", " ");
	printf(" ===================================================\n");
}

// func reqBuku bagi mahasiswa yang ingin merequest buku kepada admin
void reqBuku(FILE *ptr, int account)
{
	char reqJudul[100][100]; // mendeklarasikan array 2 dimensi
	int jumlah = 0, i;

	system("CLS");
	ptr = fopen("Database Req Buku.txt", "a"); // membuka file request buku dengan mode penambahan
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// menginput buku yang di request
	printf("===============================================================================\n"
		   "| ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Menu Request Buku ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |\n"
		   "===============================================================================\n\n");
	do
	{
		printf("Jumlah Buku yang ingin di request: ");
		scanf("%d", &jumlah);
	} while (jumlah < 1); // perulangan jika jumlah buku < 1
	// perulangan inputan buku sesuai dengan jumlah buku dan langsung ditambahkan ke dalam file
	for (i = 0; i < jumlah; i++)
	{
		printf("Judul Buku yang Ingin Di Request: ");
		scanf("%*c%[^\n]", &reqJudul[i]);
		fprintf(ptr, "%d %s\n", account, reqJudul[i]);
	}
	fclose(ptr);
}

// func balikBuku untuk menu mengembalikan buku
void balikBuku(FILE *ptr, Buku *data, Account *database, int account)
{
	int i, j, sizePinjaman = 0, indexJudul[100], indexAccount[100], sizePeminjam = 0, sizeLib = 0, indexPeminjam[10], indexBalik;
	char balikJudul[100];

	ptr = fopen("Data Base Buku.txt", "r");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// memindahkan data dari file data base buku ke dalam struct beserta menghitung size dari data base buku
	for (i = 0; i < 100; i++)
	{
		fscanf(ptr, "%s %d %[^\n]s", &(data + i)->kode, &(data + i)->stok, &(data + i)->judul);
		if (*(data + i)->judul == '\0')
		{
			break;
		}
		sizeLib++;
	}
	fclose(ptr);

	ptr = fopen("Data Peminjam.txt", "r");
	if (ptr == NULL)
	{
		printf("File tidak ditemukan.\n");
		exit(0);
	}
	// memindahkan data dari data peminjam ke dalam struct beserta menghitung jumlah peminjaman secara keseluruhan
	for (i = 0; i < 100; i++)
	{
		fscanf(ptr, "%d %d %d %d %d %s %s %d %[^\n]s", &(data + i)->tglPinjam, &(data + i)->blnPinjam, &(data + i)->tglBalik, &(data + i)->blnBalik, &indexJudul[i], &(data + i)->fakultas, &(data + i)->NPM, &indexAccount[i], &(data + i)->namaPeminjam);
		if (*(data + i)->namaPeminjam == '\0')
		{
			break;
		}
		sizePinjaman++;
	}
	fclose(ptr);

	system("CLS");
	// perulangan untuk menghitung jumlah peminjaman yang dilakukan oleh user tersebut
	for (i = 0, sizePeminjam = 0; i < sizePinjaman; i++)
	{
		if (indexAccount[i] == account)
		{									 // jika nilai indexAccount dan account cocok
			indexPeminjam[sizePeminjam] = i; // menyimpan di index mana saja user meminjam buku
			sizePeminjam++;					 // penambahan size
		}
	}
	if (sizePeminjam == 0)
	{ // pengkondisian jika user belum meminjam buku
		printf("\n |========================================================|\n"
			   " | ! ~ ~ ~ Anda tidak memiliki riwayat peminjaman ~ ~ ~ ! |\n"
			   " | ! ~ ~ Silakan Lakukan Peminjaman Terlebih Dahulu ~ ~ ! |\n"
			   " |========================================================|\n\n");
		system("pause");
		system("CLS");
	}
	else
	{ // pengkondisian jika user telah meminjam buku
		// menampilkan daftar peminjaman buku
		printf("|=========================================================================================================================================================|\n"
			   "| ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Menu Pengembalian Buku ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~|\n"
			   "| ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Daftar Peminjaman ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |\n"
			   "|=========================================================================================================================================================|\n\n");
		for (i = 1; i <= 156; i++)
		{ // membuat garis horizontal tabel
			printf("%c", 196);
		}
		printf("\n");
		printf("| %-4s | %-15s | %-25s | %-12s | %-9s | %-15s | %-20s | %-10s |  %-17s |\n",
			   "No.", "Username", "Nama Peminjam", "NPM", "Fakultas", "Tgl Peminjaman", "Judul Buku", "Kode Buku", "Tgl Pengembalian");
		for (i = 1; i <= 156; i++)
		{ // membuat garis horizontal tabel
			printf("%c", 196);
		}
		printf("\n");
		for (i = 0; i < sizePeminjam; i++)
		{
			printf("|  %-3d | %-15s | %-25s | %-12s | %-9s | %7d-%-7d | %-20s | %-10s |  %8d-%-8d |\n", i + 1, (database + account)->username, (data + indexPeminjam[i])->namaPeminjam,
				   (data + indexPeminjam[i])->NPM, (data + indexPeminjam[i])->fakultas, (data + indexPeminjam[i])->tglPinjam, (data + indexPeminjam[i])->blnPinjam, (data + indexJudul[indexPeminjam[i]])->judul,
				   (data + indexJudul[indexPeminjam[i]])->kode, (data + indexPeminjam[i])->tglBalik, (data + indexPeminjam[i])->blnBalik);
			for (j = 1; j <= 156; j++)
			{ // membuat garis horizontal tabel
				printf("%c", 196);
			}
			printf("\n");
		}
	// input pengembalian buku
	cari:
		printf("\nMasukkan judul buku yang ingin dikembalikan: ");
		scanf("%*c%[^\n]", &balikJudul);
		sizePinjaman--;

		indexBalik = searchBuku(data, balikJudul, sizeLib); // memanggil fungsi serachBuku dan menginisialisasi nilainya ke indexBalik

		if (indexBalik == -1)
		{ // jika buku yang ingin dikembalikan tidak cocok dengan buku yang dipinjam
			error();
			printf("Buku Tidak Ditemukan!\n");
			Sleep(500);
			goto cari;
		}

		// update file Data Peminjam
		freopen("Data Peminjam.txt", "w", ptr);
		if (ptr == NULL)
		{
			printf("File tidak ditemukan.\n");
			exit(0);
		}
		for (i = 0; i < sizePinjaman; i++)
		{
			if (indexJudul[i] == indexBalik && indexAccount[i] == account)
			{
				i++;
			}
			fprintf(ptr, "%d %d %d %d %d %s %s %d %s\n", (data + i)->tglPinjam, (data + i)->blnPinjam, (data + i)->tglBalik, (data + i)->blnBalik, indexJudul[i], (data + i)->fakultas, (data + i)->NPM, indexAccount[i], (data + i)->namaPeminjam);
		}
		fclose(ptr);

		// menambahkan stock buku setelah buku telah dikembalikan
		(data + indexBalik)->stok++;

		// update file database buku
		freopen("Data Base Buku.txt", "w", ptr);
		if (ptr == NULL)
		{
			printf("File tidak ditemukan.\n");
			exit(0);
		}
		for (i = 0; i < sizeLib; i++)
		{
			fprintf(ptr, "%s %d %s\n", (data + i)->kode, (data + i)->stok, (data + i)->judul);
		}
		fclose(ptr);
	}
}

void inputBiodata(FILE *ptr, struct biodata *root, int account)
{
	int i, pil, descision;
	char nama[50], NPM[15], jurusan[25], tempatLahir[25], tanggalLahir[15], akun[50], pass[50], akunFile[50];

	ptr = fopen("Account Mahasiswa.txt", "r");
	for (i = 0; i <= account; i++)
	{
		fscanf(ptr, "%s %[^\n]s", &pass, &akun);
	}
	fclose(ptr);

	ptr = fopen("biodata_mahasiswa.txt", "r");
	if (ptr != NULL)
	{
		while (fscanf(ptr, " %50[^\n]s", akunFile) == 1 && fscanf(ptr, " %50[^\n]s", nama) == 1 && fscanf(ptr, " %15[^\n]s", NPM) == 1 && fscanf(ptr, " %25[^\n]s", jurusan) == 1 && fscanf(ptr, " %25[^\n]s", tempatLahir) == 1 && fscanf(ptr, " %15[^\n]s", tanggalLahir) == 1)
		{
			insertChild(&root, nama, NPM, jurusan, tempatLahir, tanggalLahir, akunFile);
		}
	}

	if (searchAccountBST(root, akun) == -1)
	{
	prev:
		system("cls");
		printf("Input Biodata Mahasiswa\n");
		printf("Nama: ");
		scanf("%*c%[^\n]", nama);
		printf("NPM: ");
		scanf("%*c%[^\n]", NPM);
		printf("Jurusan: ");
		scanf("%*c%[^\n]", jurusan);
		printf("Tempat Lahir: ");
		scanf("%*c%[^\n]", tempatLahir);
		printf("Tanggal Lahir: ");
		scanf("%*c%[^\n]", tanggalLahir);

		printf("Apakah Data Diri Anda Sudah Sesuai?\n1. Ya\t2. Tidak\nMasukkan Pilihan: ");
		scanf("%d", &pil);
		if (pil == 1)
		{
			insertChild(&root, nama, NPM, jurusan, tempatLahir, tanggalLahir, akun);
			kartuAnggota(root, akun);
			ptr = fopen("biodata_mahasiswa.txt", "w");
			saveBiodata(ptr, root);
			fclose(ptr);
		}
		else
		{
			goto prev;
		}
	}
	else if (searchAccountBST(root, akun) == 1)
	{
		do
		{
			system("cls");
			printf("Apakah Anda ingin Mengubah Biodata Anda Sebelumnya?\n1. Ya\t2. Tidak\nMasukkan Pilihan: ");
			scanf("%d", &descision);
		} while (descision < 1 || descision > 2);

		if (descision == 1)
		{
		back:
			system("cls");
			printf("Input Biodata Mahasiswa\n");
			printf("Nama: ");
			scanf("%*c%[^\n]", nama);
			printf("NPM: ");
			scanf("%*c%[^\n]", NPM);
			printf("Jurusan: ");
			scanf("%*c%[^\n]", jurusan);
			printf("Tempat Lahir: ");
			scanf("%*c%[^\n]", tempatLahir);
			printf("Tanggal Lahir: ");
			scanf("%*c%[^\n]", tanggalLahir);
			root = delete (root, akun);
			insertChild(&root, nama, NPM, jurusan, tempatLahir, tanggalLahir, akun);
			kartuAnggota(root, akun);
			freopen("biodata_mahasiswa.txt", "w", ptr);
			saveBiodata(ptr, root);
			fclose(ptr);

			printf("Apakah Data Diri Anda Sudah Sesuai?\n1. Ya\t2. Tidak\nMasukkan Pilihan: ");
			scanf("%d", &pil);
			if (pil == 2)
			{
				goto back;
			}
		}
	}
}

void saveBiodata(FILE *ptr, struct biodata *root)
{

	if (root != NULL)
	{
		saveBiodata(ptr, root->leftPtr);

		fprintf(ptr, "%s\n%s\n%s\n%s\n%s\n%s\n", root->account, root->nama, root->NPM, root->jurusan, root->tempatLahir, root->tanggalLahir);
		saveBiodata(ptr, root->rightPtr);
	}
}

void insertChild(struct biodata **root, char nama[], char NPM[], char jurusan[], char tempatLahir[], char tanggalLahir[], char akun[])
{
	struct biodata *ptr = malloc(sizeof(struct biodata));
	struct biodata *curPtr = *root;

	strcpy(ptr->nama, nama);
	strcpy(ptr->NPM, NPM);
	strcpy(ptr->jurusan, jurusan);
	strcpy(ptr->tempatLahir, tempatLahir);
	strcpy(ptr->tanggalLahir, tanggalLahir);
	strcpy(ptr->account, akun);
	ptr->leftPtr = NULL;
	ptr->rightPtr = NULL;

	if (*root == NULL)
	{
		*root = ptr;
	}
	else
	{
		if (strcmp((*root)->account, ptr->account) >= 0)
		{
			insertChild(&((*root)->leftPtr), nama, NPM, jurusan, tempatLahir, tanggalLahir, akun);
		}
		else
		{
			insertChild(&((*root)->rightPtr), nama, NPM, jurusan, tempatLahir, tanggalLahir, akun);
		}
	}
}

int searchAccountBST(struct biodata *root, char akun[])
{
	if (root == NULL)
	{
		return -1;
	}
	if (strcmp(root->account, akun) == 0)
	{
		return 1;
	}
	else if (strcmp(root->account, akun) > 0)
	{
		searchAccountBST(root->leftPtr, akun);
	}
	else
	{
		searchAccountBST(root->rightPtr, akun);
	}
}

struct biodata *minValueNode(struct biodata *node)
{
	struct biodata *current = node;

	/* loop down to find the leftmost leaf */
	while (current && current->leftPtr != NULL)
		current = current->leftPtr;

	return current;
}

struct biodata *delete (struct biodata *root, char akun[])
{
	// base case
	if (root == NULL)
		return root;

	// If the key to be deleted
	// is smaller than the root's
	// key, then it lies in left subtree
	if (strcmp(akun, root->account) < 0)
		root->leftPtr = delete (root->leftPtr, akun);

	// If the key to be deleted
	// is greater than the root's
	// key, then it lies in right subtree
	else if (strcmp(akun, root->account) > 0)
		root->rightPtr = delete (root->rightPtr, akun);

	// if key is same as root's key,
	// then This is the node
	// to be deleted
	else
	{
		if (root->leftPtr == NULL && root->rightPtr == NULL)
		{
			free(root);
			return NULL;
		}
		// node with only one child or no child
		else if (root->leftPtr == NULL)
		{
			struct biodata *temp = root->rightPtr;
			free(root);
			return temp;
		}
		else if (root->rightPtr == NULL)
		{
			struct biodata *temp = root->leftPtr;
			free(root);
			return temp;
		}
		else
		{
			// node with two children:
			// Get the inorder successor
			// (smallest in the right subtree)
			struct biodata *temp = minValueNode(root->rightPtr);

			// Copy the inorder
			// successor's content to this node
			strcpy(root->account, temp->account);
			strcpy(root->nama, temp->nama);
			strcpy(root->NPM, temp->NPM);
			strcpy(root->jurusan, temp->jurusan);
			strcpy(root->tempatLahir, temp->tempatLahir);
			strcpy(root->tanggalLahir, temp->tanggalLahir);

			// Delete the inorder successor
			root->rightPtr = delete (root->rightPtr, temp->account);
		}
	}
	return root;
}

void kartuAnggota(struct biodata *root, char akun[])
{
	if (strcmp(root->account, akun) == 0)
	{
		// menampilkan output kartu peminjaman
		printf(" ======================================================\n"
			   " |-------------- Kartu Keanggotaan Aktif -------------|\n"
			   " |---------------- E-Library Mahasiswa ---------------|\n"
			   " ======================================================\n");
		printf(" | %-20s : %-27s |\n", "Username", root->account);
		printf(" | %-20s : %-27s |\n", "Nama Lengkap", root->nama);
		printf(" | %-20s : %-27s |\n", "NPM", root->NPM);
		printf(" | %-20s : %-27s |\n", "Jurusan", root->jurusan);
		printf(" | %-20s : %-27s |\n", "Tempat Lahir", root->tempatLahir);
		printf(" | %-20s : %-27s |\n", "Tanggal Lahir", root->tanggalLahir);
		printf(" | %-20s   %-27s |\n", " ", " ");
		printf(" |  %-20s  %-27s |\n", "Salam Hangat", " ");
		printf(" | %-15s%-5c   %-27s |\n", "Administrator", 1, " ");
		printf(" | %-20s   %-27s |\n", " ", " ");
		printf(" ======================================================\n");
	}
	else if (strcmp(root->account, akun) > 0)
	{
		kartuAnggota(root->leftPtr, akun);
	}
	else
	{
		kartuAnggota(root->rightPtr, akun);
	}
}

// func error untuk menampilkan output ketika program error
void error()
{
	system("color 40");
	printf("\n\a !---- Pilihan yang Anda masukkan salah, Silakan masukkan pilihan yang benar ---!\n\n");
	Sleep(1500); // memberikan delay selama 1 detik
	system("color F0");
	system("cls");
}

// func untuk mengurutkan sesuai abjad
void sort(Buku *data, int size)
{
	int i, j, tempint;
	char temp[100];

	if (size == 1)
	{
		return;
	}

	// bubble sorting
	for (i = 0; i < (size - 1); i++)
	{
		if (strcmp((data + i)->judul, (data + (i + 1))->judul) > 0)
		{ // mengurutkan berdasarkan alfabet judul buku
			// menukar judul buku
			strcpy(temp, (data + i)->judul);
			strcpy((data + i)->judul, (data + (i + 1))->judul);
			strcpy((data + (i + 1))->judul, temp);

			// menukar kode buku
			strcpy(temp, (data + i)->kode);
			strcpy((data + i)->kode, (data + (i + 1))->kode);
			strcpy((data + (i + 1))->kode, temp);

			// menukar stok buku
			tempint = (data + i)->stok;
			(data + i)->stok = (data + (i + 1))->stok;
			(data + (i + 1))->stok = tempint;
		}
	}
	size = size - 1;
	sort(data, size); // dipanggil secara rekursif
}

// func untuk menampilkan helpdesk dalam menu mahasiswa
void panduanMahasiswa()
{
	int pedoman = 0, pilTrans = 0, choice = 0; // deklarasi variabel integer
	system("CLS");							   // Membersihkan layar
	printf("===================================================\n"
		   "|        Pedoman Dalam Menggunakan Aplikasi       |\n"
		   "|                 Untuk Mahasiswa                 |\n"
		   "===================================================\n"
		   "| 1. Pedoman Menampilkan Daftar Buku              |\n"
		   "| 2. Pedoman Melakukan Peminjaman Buku            |\n"
		   "| 3. Pedoman Melakukan Pengembalian Buku          |\n"
		   "| 4. Pedoman Melakukan Request Buku               |\n"
		   "| 5. Pedoman Exit Dari Aplikasi                   |\n"
		   "===================================================\n\n");
	do
	{
		printf(" Masukkan Nomor Pilihan: ");
		scanf("%d", &pedoman);
		system("CLS"); // Membersihkan layar
		switch (pedoman)
		{
		case 1: // jika pedoman = 1
			printf("========================================================================\n"
				   "|                   Pedoman Menampilkan Daftar Buku                    |\n"
				   "========================================================================\n"
				   "| 1. User memilih login sebagai mahasiswa                              |\n"
				   "| 2. User dapat login jika telah memiliki akun                         |\n"
				   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
				   "| 4. Dalam menu mahasiswa, user dapat memilih menu 1                   |\n"
				   "| 5. Lalu User akan diminta untuk memilih, apakah ingin menerima        |\n"
				   "|    request buku atau menginput buku secara langsung                  |\n"
				   "| 6. Jika ingin menerima request maka pilih 1, jika ingin input buku   |\n"
				   "|    tanpa menerima request pilih 2                                    |\n"
				   "========================================================================\n\n");
			system("pause"); // menjeda program sampai ada input
			break;
		case 2: // jika pedoman = 2
			printf("========================================================================\n"
				   "|                   Pedoman Melakukan Peminjaman Buku                  |\n"
				   "========================================================================\n"
				   "| 1. User memilih login sebagai mahasiswa                              |\n"
				   "| 2. User dapat login jika telah memiliki akun                         |\n"
				   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
				   "| 4. Dalam menu mahasiswa, user dapat memilih menu 2 untuk input       |\n"
				   "|    peminjaman buku                                                   |\n"
				   "| 5. User dapat menginput nama peminjam, npm mahasiswa, fakultas,      |\n"
				   "|    judul buku, bulan peminjaman, tanggal peminjaman                  |\n"
				   "| 6. Program akan memberikan data tanggal batas pengembalian buku      |\n"
				   "| 7. Program akan menampilkan kartu peminjaman untuk memverifikasi     |\n"
				   "|    apakah data yang diinput oleh user sudah benar, jika belum maka   |\n"
				   "|    program akan meminta input data ulang							   |\n"
				   "| 8. Jika data yang diinput sudah benar, maka data akan tersimpan 	   |\n"
				   "|    otomatis dalam database                                           |\n"
				   "========================================================================\n\n");
			system("pause"); // menjeda program sampai ada input
			break;			 // keluar dari pengkondisian
		case 3:				 // jika pedoman = 3
			printf("========================================================================\n"
				   "|                 Pedoman Melakukan Pengembalian Buku                  |\n"
				   "========================================================================\n"
				   "| 1. User memilih login sebagai mahasiswa                              |\n"
				   "| 2. User dapat login jika telah memiliki akun                         |\n"
				   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
				   "| 4. Dalam menu mahasiswa, user dapat memilih menu 3 untuk melakukan   |\n"
				   "|    pengembalian buku                                                 |\n"
				   "| 5. User dapat melihat daftar peminjaman buku yang ada, sehingga      |\n"
				   "|    user dapat mengetahui buku apa yang ia pinjam                     |\n"
				   "| 6. Kemudian user diminta untuk menginput judul buku yang ia pinjam   |\n"
				   "| 7. Lalu user diminta untuk menekan enter agar perubahan data bisa    |\n"
				   "|    tersimpan                                                         |\n"
				   "========================================================================\n\n");
			system("pause"); // menjeda program sampai ada input
			break;			 // keluar dari pengkondisian
		case 4:				 // jika pedoman = 4
			printf("========================================================================\n"
				   "|                   Pedoman Melakukan Request Buku                     |\n"
				   "========================================================================\n"
				   "| 1. User memilih login sebagai mahasiswa                              |\n"
				   "| 2. User dapat login jika telah memiliki akun                         |\n"
				   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
				   "| 4. Dalam menu mahasiswa, user dapat memilih menu 4 untuk melakukan   |\n"
				   "|    Request Buku                                                      |\n"
				   "| 5. User diminta untuk menginput jumlah buku yang ingin di request    |\n"
				   "|    (1 buku = 1 judul)                                                |\n"
				   "| 6. Kemudian user diminta untuk menginput judul buku yang ingin       |\n"
				   "|    di request sebanyak jumlah buku                                   |\n"
				   "| 7. Lalu user diminta untuk menekan enter agar request buku bisa      |\n"
				   "|    tersimpan                                                         |\n"
				   "========================================================================\n\n");
			system("pause"); // menjeda program sampai ada input
			break;			 // keluar dari pengkondisian
		case 5:				 // jika pedoman = 5
			printf("========================================================================\n"
				   "|                  Pedoman Untuk Keluar Dari Aplikasi                  |\n"
				   "========================================================================\n"
				   "| 1. User memilih login sebagai mahasiswa                              |\n"
				   "| 2. User dapat login jika telah memiliki akun                         |\n"
				   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
				   "| 4. Dalam menu mahasiswa, user dapat memilih menu 6 untuk keluar dari |\n"
				   "|    program                                                           |\n"
				   "| 5. Program akan menutup secara otomatis dan menampilkan func closing |\n"
				   "========================================================================\n\n");
			system("pause"); // menjeda program sampai ada input
			break;			 // keluar dari pengkondisian
		default:			 // error handling
			error();
		}
	} while (pedoman < 1 || pedoman > 5); // perulangan jika input tidak 1 <= input <= 5
}

// func untuk menampilkan helpdesk dalam menu admin
void panduanAdmin()
{
	int pedoman = 0, pilTrans = 0, choice = 0; // deklarasi variabel integer
	system("CLS");							   // Membersihkan layar
	printf("===================================================\n"
		   "|       Pedoman Dalam Menggunakan Aplikasi        |\n"
		   "|               Untuk Administrator               |\n"
		   "===================================================\n"
		   "| 1. Pedoman Melakukan Input Buku                 |\n"
		   "| 2. Pedoman Menampilkan Daftar Buku              |\n"
		   "| 3. Pedoman Menampilkan Status Peminjaman Buku   |\n"
		   "| 4. Pedoman Menampilkan Daftar Request Buku      |\n"
		   "| 5. Pedoman Exit Dari Aplikasi                   |\n"
		   "===================================================\n\n");
	do
	{
		printf(" Masukkan Nomor Pilihan: ");
		scanf("%d", &pedoman);
		system("CLS"); // Membersihkan layar
		switch (pedoman)
		{
		case 1: // jika pedoman = 1
		prev:	// titik tuju goto prev
			printf("=============================================\n"
				   "|            Pedoman Input Buku             |\n"
				   "=============================================\n"
				   "| 1. Menerima Request Buku                  |\n"
				   "| 2. Input Buku Tanpa Menerima Request      |\n"
				   "=============================================\n\n"
				   " Masukkan Nomor Pilihan : ");
			scanf("%d", &choice);
			switch (choice)
			{		// pengkondisian inputan
			case 1: // jika choice = 1
				system("CLS");
				printf("========================================================================\n"
					   "|                   Pedoman Menampilkan Daftar Buku                    |\n"
					   "========================================================================\n"
					   "| 1. User memilih login sebagai mahasiswa                              |\n"
					   "| 2. User dapat login jika telah memiliki akun                         |\n"
					   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
					   "| 4. Dalam menu mahasiswa, user dapat memilih menu 1                   |\n"
					   "| 5. Lalu User akan diminta untuk memilih, apakah ingin menerima       |\n"
					   "|    request buku atau menginput buku secara langsung                  |\n"
					   "| 6. User akan memilih 1 untuk menerima request buku, maka tabel       |\n"
					   "|    request akan di tampilkan                                         |\n"
					   "| 7. User akan menginput buku sesuai dengan yang ada di tabel request  |\n"
					   "| 8. User akan diminta untuk menginput beberapa informasi buku,        |\n"
					   "|    seperti kode buku, judul buku, dan jumlah buku                    |\n"
					   "| 9. Lalu user menekan tombol enter untuk menyimpan perubahan          |\n"
					   "========================================================================\n\n");
				system("pause");
				system("CLS");
				break;
			case 2: // jika choice = 2
				system("CLS");
				printf("========================================================================\n"
					   "|                   Pedoman Menampilkan Daftar Buku                    |\n"
					   "========================================================================\n"
					   "| 1. User memilih login sebagai admin                                  |\n"
					   "| 2. User dapat login jika telah memiliki akun                         |\n"
					   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
					   "| 4. Dalam menu admin, user dapat memilih menu 1 untuk input buku      |\n"
					   "| 5. Lalu User akan diminta untuk memilih, apakah ingin menerima       |\n"
					   "|    request buku atau menginput buku secara langsung                  |\n"
					   "| 6. User akan memilih 2 untuk melakukan input buku tanpa menerima     |\n"
					   "|    request                                                           |\n"
					   "| 7. User akan diminta untuk menginput beberapa informasi buku,        |\n"
					   "|    seperti kode buku, judul buku, dan jumlah buku                    |\n"
					   "| 8. Lalu user menekan tombol enter untuk menyimpan perubahan          |\n"
					   "========================================================================\n\n");
				system("pause");
				system("CLS");
				break;
			default: // error handling
				error();
				goto prev; // menuju titik prev
				break;
			}
			break; // keluar dari pengkondisian
		case 2:	   // jika pedoman = 2
			printf("========================================================================\n"
				   "|                   Pedoman Menampilkan Daftar Buku                    |\n"
				   "========================================================================\n"
				   "| 1. User memilih login sebagai admin                                  |\n"
				   "| 2. User dapat login jika telah memiliki akun                         |\n"
				   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
				   "| 4. Dalam menu admin, user dapat memilih menu 2 untuk menampilkan     |\n"
				   "|    daftar buku                                                       |\n"
				   "| 5. Daftar buku yang terdapat dalam database akan tertampilkan semua  |\n"
				   "========================================================================\n\n");
			system("pause"); // menjeda program sampai ada input
			system("CLS");	 // membersihkan tampilan program
			break;			 // keluar dari pengkondisian
		case 3:				 // jika pedoman = 3
			printf("========================================================================\n"
				   "|                Pedoman Menampilkan Status Peminjaman                 |\n"
				   "========================================================================\n"
				   "| 1. User memilih login sebagai admin                                  |\n"
				   "| 2. User dapat login jika telah memiliki akun                         |\n"
				   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
				   "| 4. Dalam menu admin, user dapat memilih menu 3 untuk menampilkan     |\n"
				   "|    status peminjaman buku                                            |\n"
				   "| 5. Status peminjaman buku akan tertampilkan semua beserta informasi  |\n"
				   "|    yang ada                                                          |\n"
				   "========================================================================\n\n");
			system("pause"); // menjeda program sampai ada input
			system("CLS");
			break; // keluar dari pengkondisian
		case 4:	   // jika pedoman = 4
			printf("========================================================================\n"
				   "|               Pedoman Menampilkan Daftar Request Buku                |\n"
				   "========================================================================\n"
				   "| 1. User memilih login sebagai admin                                  |\n"
				   "| 2. User dapat login jika telah memiliki akun                         |\n"
				   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
				   "| 4. Dalam menu admin, user dapat memilih menu 4 untuk menampilkan     |\n"
				   "|    Daftar Request Buku                                               |\n"
				   "| 5. Daftar request buku akan tertampilkan semua beserta informasi     |\n"
				   "|    yang ada                                                          |\n"
				   "========================================================================\n\n");
			system("pause"); // menjeda program sampai ada input
			system("CLS");
			break; // keluar dari pengkondisian
		case 5:	   // jika pedoman = 5
			printf("========================================================================\n"
				   "|                 Pedoman Untuk Keluar Dari Aplikasi                   |\n"
				   "========================================================================\n"
				   "| 1. User memilih login sebagai admin                                  |\n"
				   "| 2. User dapat login jika telah memiliki akun                         |\n"
				   "| 3. Jika belum, user dipersilahkan untuk membuat akun terlebih dahulu |\n"
				   "| 4. Dalam menu admin, user dapat memilih menu 6 untuk keluar dari     |\n"
				   "|    program                                                           |\n"
				   "| 5. Program akan menutup secara otomatis dan menampilkan func closing |\n"
				   "========================================================================\n\n");
			system("pause"); // menjeda program sampai ada input
			system("CLS");	 // membersihkan tampilan program
			break;			 // keluar dari pengkondisian
		default:			 // error handling
			error();
			break;
		}
	} while (pedoman < 1 || pedoman > 5); // perulangan jika inputa tidak 1 <= input <= 5
}

// func untuk tampilan saat menutup program
void closing()
{
	int i;
	system("CLS"); // Membersihkan layar
	Sleep(800);	   // menjeda program selama 0.8 detik
	system("color F0");

	printf("\n\n\n\n\n\n\n");
	char a[] = {"\t\t\t\t\t\t\t\t============================================================\n"
				"\t\t\t\t\t\t\t\t============================================================\n"
				"\t\t\t\t\t\t\t\t|--------- Terima kasih telah menggunakan program ---------|\n"
				"\t\t\t\t\t\t\t\t|-----------------  E-Library Mahasiswa  ------------------|\n"
				"\t\t\t\t\t\t\t\t============================================================\n"
				"\t\t\t\t\t\t\t\t============================================================\n\n"};
	// menampilkan output array secara berurut
	for (i = 0; a[i] != a[866]; i++)
	{
		printf("%c", a[i]);
		Sleep(2);
	}
}
