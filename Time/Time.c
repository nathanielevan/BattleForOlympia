/* File: jam.c
 * NIM            : 13516103
 * Nama           : Gerardus Samudra S.
 * Tanggal        : 2017-08-31
 * Deskripsi      : Realisasi/implementasi ADT Time
 */

#include <stdio.h>
#include "Time.h"

/* ***************************************************************** */
/* IMPLEMENTASI PRIMITIF                                             */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */

boolean IsTimeValid (int H, int M, int S)
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Time */
{
  /* Algoritma */
  return H >= 0 && H <= 23 && M >= 0 && M <= 59 && S >= 0 && S <= 59;
}

/* *** Konstruktor: Membentuk sebuah Time dari komponen-komponennya *** */
Time MakeTime (int hh, int mm, int ss, int day, int month, int year)
/* Membentuk sebuah Time dari komponen-komponennya yang valid */
/* Prekondisi : hh, mm, ss valid untuk membentuk Time */
{
  /* Kamus lokal dengan inisialisasi */
  Time j = { hh, mm, ss, day, month, year };
  /* Algoritma */
  return j;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */

void BacaTime (Time * J)
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
{
  /* Kamus lokal */
  int h, m, s, day, month, year;
  boolean valid = false;
  /* Algoritma */
  while (!valid) {
    scanf("%d %d %d %d %d %d", &h, &m, &s, &day, &month, &year);
    valid = IsTimeValid(h, m, s);
    if (!valid)
      puts("Time tidak valid");
  }
  *J = MakeTime(h, m, s);
}

void TulisTime (Time J)
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format hh:mm:ss */
/* Proses : menulis nilai setiap komponen J ke layar dalam format hh:mm:ss
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
{
  /* Algoritma */
  printf("%02d:%02d:%02d", Hour(J), Minute(J), Second(J));
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */

long JamToDetik (Time J)
/* Diberikan sebuah Time, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*hh + 60*mm + ss */
/* Nilai maksimum = 3600*23+59*60+59 */
{
  /* Algoritma */
  return 3600 * Hour(J) + 60 * Minute(J) + Second(J);
}

Time DetikToJam (long N)
/* Mengirim  konversi detik ke Time */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus:
   N1 = N mod 86400, baru N1 dikonversi menjadi Time */
{
  /* Kamus lokal */
  int h, m, s;
  /* Algoritma */
  N = N % 86400;
  /* Dapatkan modulo bila sisa bagi bertanda negatif */
  N = N < 0 ? N + 86400 : N;
  h = (N / 3600);
  m = (N / 60) % 60;
  s = N % 60;
  return MakeTime(h, m, s);
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */

/* *** Kelompok Operator Relational *** */

boolean JEQ (Time J1, Time J2)
/* Mengirimkan true jika J1=J2, false jika tidak */
{
  /* Algoritma */
  return Hour(J1) == Hour(J2) && Minute(J1) == Minute(J2) &&
    Second(J1) == Second(J2);
}

boolean JNEQ (Time J1, Time J2)
/* Mengirimkan true jika J1 tidak sama dengan J2 */
{
  /* Algoritma */
  return !JEQ(J1, J2);
}

boolean JLT (Time J1, Time J2)
/* Mengirimkan true jika J1<J2, false jika tidak */
{
  /* Algoritma */
  return TimeToDetik(J1) < TimeToDetik(J2);
}

boolean JGT (Time J1, Time J2)
/* Mengirimkan true jika J1>J2, false jika tidak */
{
  /* Algoritma */
  return TimeToDetik(J1) > TimeToDetik(J2);
}

/* *** Operator aritmatika Time *** */

Time NextDetik (Time J)
/* Mengirim 1 detik setelah J dalam bentuk Time */
{
  /* Algoritma */
  return NextNDetik(J, 1);
}

Time NextNDetik (Time J, int N)
/* Mengirim N detik setelah J dalam bentuk Time */
{
  /* Algoritma */
  return DetikToTime(TimeToDetik(J) + N);
}

Time PrevDetik (Time J)
/* Mengirim 1 detik sebelum J dalam bentuk Time */
{
  /* Algoritma */
  return PrevNDetik(J, 1);
}

Time PrevNDetik (Time J, int N)
/* Mengirim N detik sebelum J dalam bentuk Time */
{
  /* Algoritma */
  return NextNDetik(J, -N);
}

/* *** Kelompok Operator Aritmetika *** */

long Durasi (Time JAw, Time JAkh)
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
{
  /* Kamus lokal dengan inisialisasi */
  long dAw = TimeToDetik(JAw);
  long dAk = TimeToDetik(JAkh);
  /* Algoritma */
  if (dAw > dAk)
    dAk += 86400; /* tambah satu hari jika perlu */
  return dAk - dAw;
}
