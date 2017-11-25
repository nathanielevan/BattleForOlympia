/* File: jam.h */
/* Tanggal: 28 Agustus 2016 */
/* Definisi ADT Time */

#ifndef Time_H
#define Time_H

#include "boolean.h"

/* *** Definisi TYPE Time <hh:mm:ss> *** */
typedef struct { 
	char hh; /* integer [0..23] */
	char mm; /* integer [0..59] */
	char ss; /* integer [0..59] */
   char Day;
   char Month;
   char Year
} Time;

/* *** Notasi Akses: selektor Time *** */
#define Hour(J) (J).hh
#define Minute(J) (J).mm
#define Second(J) (J).ss
#define Day(J) (J).Day
#define Month(J) (J).Month
#define Year(J) (J).Year

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTimeValid (int H, int M, int S);
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Time */

/* *** Konstruktor: Membentuk sebuah Time dari komponen-komponennya *** */
Time MakeTime (int hh, int mm, int ss, int day, int month, int year);
/* Membentuk sebuah Time dari komponen-komponennya yang valid */
/* Prekondisi : hh, mm, ss valid untuk membentuk Time */

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTime (Time * J);
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen hh, mm, ss sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen hh, mm, ss
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika Time tidak valid maka diberikan pesan: "Time tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh: 
   60 3 4
   Time tidak valid
   1 3 4
   --> akan terbentuk Time <1,3,4> */
   
void TulisTime (Time J);
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format hh:mm:ss */
/* Proses : menulis nilai setiap komponen J ke layar dalam format hh:mm:ss
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JamToDetik (Time J);
/* Diberikan sebuah Time, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*hh + 60*mm + ss */
/* Nilai maksimum = 3600*23+59*60+59 */

Time DetikToJam (long N); 
/* Mengirim  konversi detik ke Time */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: 
   N1 = N mod 86400, baru N1 dikonversi menjadi Time */

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (Time J1, Time J2);
/* Mengirimkan true jika J1=J2, false jika tidak */
boolean JNEQ (Time J1, Time J2);
/* Mengirimkan true jika J1 tidak sama dengan J2 */
boolean JLT (Time J1, Time J2);
/* Mengirimkan true jika J1<J2, false jika tidak */
boolean JGT (Time J1, Time J2);
/* Mengirimkan true jika J1>J2, false jika tidak */
/* *** Operator aritmatika Time *** */
Time NextDetik (Time J);
/* Mengirim 1 detik setelah J dalam bentuk Time */
Time NextNDetik (Time J, int N);
/* Mengirim N detik setelah J dalam bentuk Time */
Time PrevDetik (Time J);
/* Mengirim 1 detik sebelum J dalam bentuk Time */
Time PrevNDetik (Time J, int N);
/* Mengirim N detik sebelum J dalam bentuk Time */
/* *** Kelompok Operator Aritmetika *** */
long Durasi (Time JAw, Time JAkh);
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */

#endif