#ifndef FUNCTION_H_
#define FUNCTION_H_

// menggunakan struct yang bernama Account yang berisi username dan password
typedef struct
{
	char username[100];
	char pass[50];
} Account;

// menggunakan struct yang bernama Buku yang berisi data buku beserta peminjam
typedef struct
{
	char judul[25];
	char kode[20];
	int stok, user;
	char namaPeminjam[40];
	char NPM[15];
	char fakultas[10];
	int tglPinjam, blnPinjam;
	int tglBalik, blnBalik;
} Buku;

// menggunakan struct yang bernama biodata yang berisi biodata dari akun mahasiswa
typedef struct biodata
{
	char nama[50];
	char NPM[15];
	char jurusan[25];
	char tempatLahir[25];
	char tanggalLahir[15];
	char account[50];
	struct biodata *leftPtr;
	struct biodata *rightPtr;
};

// prototype func opening saat pertama menggunakan program
void opening();

// prototype func loginPage untuk pengaksesan dan pembuatan akun dalam program yang akan disimpan dalam file
int loginPage(FILE *ptr, Account *admin, Account *mahasiswa, int input);

// prototype func loginAccount untuk pengaksesan akun dalam program yang akan disimpan dalam file
int loginAccount(FILE *ptr, Account *database, int inOrUp);

// prototype func newAccount untuk pembuatan akun dalam program yang akan disimpan dalam file
void newAccount(FILE *ptr, Account *database);

// prototype func adminAkses agar dapat mengakses fitur admin
void adminAkses(FILE *ptr, Buku *data, Account *database, struct biodata *root);

// prototype func inputBuku untuk menginput buku yang nantinya akan disimpan ke dalam file
void inputBuku(FILE *ptr, Buku *data, Account *database);

// prototype func daftarBuku untuk menampilkan seluruh database buku
void daftarBuku(FILE *ptr, Buku *data);

// prototype func laporan untuk melihat laporan peminjaman
void laporan(FILE *ptr, Buku *data, Account *database);

// prototype func lihatReqBuku untuk melihat buku yang di request oleh mahasiswa
void lihatReqBuku(FILE *ptr, Account *database);

// prototype func mahasiswaAkses agar dapat meggunakan fitur mahasiswa
void mahasiswaAkses(FILE *ptr, Buku *data, Account *database, struct biodata *root, int account);

// prototype func pijamBuku untuk mahasiswa agar dapat meminjam buku
void pinjamBuku(FILE *ptr, Buku *data, Account *database, int account);

// prototype func searchBuku untuk melakukan pencarian judul buku
int searchBuku(Buku *data, char input[], int size);

// Prototype func hitungTanggal untuk menghitung tanggal buku dikembalikan
void hitungTanggal(Buku *data);

// Prototype func kartuPinjam untuk melihat kartu peminjaman buku
void kartuPinjam(Buku data, Account *database, char *judul, int account);

// Prototype func reqBuku bagi mahasiswa yang ingin merequest buku kepada admin
void reqBuku(FILE *ptr, int account);

// Prototype func balikBuku untuk menu mengembalikan buku
void balikBuku(FILE *ptr, Buku *data, Account *database, int account);

// func bridgeBio sebagai jembatan antara file pointer dengan data dalam program
void bridgeBio(FILE *ptr, struct biodata *root);

// func lihatBioMhs untuk mengeprint pilihan nama pada biodata
void lihatBioMhs(FILE *ptr, struct biodata *root, int i);

// func inputBiodata untuk mengisi biodata tiap akun yang sedang login
void inputBiodata(FILE *ptr, struct biodata *root, int account);

// func saveBiodata digunakan untuk menyinpam data pada binary search tree yang akan
// di sesuaikan data tersebut ke kanan atau kiri head utama
void saveBiodata(FILE *ptr, struct biodata *root);

// func insertChild digunakan untuk menyimpan suatu biodata ke dalam accoun yang sedang login
void insertChild(struct biodata **root, char nama[], char NPM[], char jurusan[], char tempatLahir[], char tanggalLahir[], char akun[]);

// func searchAccounBST digunakan untuk menentukan serta mencari akun yang sedang login dengan biodata dalam Binary Search Tree
int searchAccountBST(struct biodata *root, char akun[]);

struct biodata *minValueNode(struct biodata *node);

// func biodata delete ini digunakan untuk menghapus biodata pada binary search tree
struct biodata *delete (struct biodata *root, char akun[]);

// func kartuAnggota digunakan untuk mengeprint seluruh isi biodata mahasiswa
void kartuAnggota(struct biodata *root, char *akun);

// func lihatKartu digunakan untuk menentukan apakah pada akun tersebut telah terisi biodata atau belum
void lihatKartu(FILE *ptr, struct biodata *root, int account);

// prototye func error untuk menampilkan output ketika program error
void error();

// prototype func untuk mengurutkan judul bukusesuai abjad
void sort(Buku *data, int size);

// prototype func untuk menampilkan helpdesk pada menu mahasiswa
void panduanMahasiswa();

// prototype func untuk menampilkan helpdesk pada menu admin
void panduanAdmin();

// prototype func untuk menutup program
void closing();

#endif
