/* File: jam.c
 * NIM            : 13516103
 * Nama           : Gerardus Samudra S.
 * Tanggal        : 2017-08-31
 * Deskripsi      : Realisasi/implementasi ADT Time
 */

#include <stdio.h>
#include <time.h>
#include "Time.h"

/* ***************************************************************** */
/* IMPLEMENTASI PRIMITIF                                             */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */

boolean isTimeValid (int Y, int M, int D, int HH, int MM, int SS)
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Time */
{
    /* Kamus lokal */
    boolean isDiv4, isDiv100, isDiv400;
    /* Algoritma */
    if (!(Y >= 2017 && Y < 65536))
        return false;
    if (D < 1)
        return false;
    switch (M) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (D > 31)
            return false;
        break;
    case 4: case 6: case 9: case 11:
        if (D > 30)
            return false;
        break;
    case 2:
        isDiv400 = ((Y % 400) == 0);
        isDiv100 = isDiv400 || ((Y % 100) == 0);
        isDiv4 = isDiv100 || ((Y % 4) == 0);
        if (isDiv400 || (!isDiv100 && isDiv4)) {
            if (D > 29)
                return false;
        } else {
            if (D > 28)
                return false;
        }
        break;
    default:
        return false;
    }
    return (HH >= 0 && HH <= 23 && MM >= 0 && MM <= 59 && SS >= 0 && SS <= 59);
}

/* *** Konstruktor: Membentuk sebuah Time dari komponen-komponennya *** */
Time makeTime (int year, int month, int day, int hh, int mm, int ss)
/* Membentuk sebuah Time dari komponen-komponennya yang valid */
/* Prekondisi : hh, mm, ss valid untuk membentuk Time */
{
    /* Kamus lokal dengan inisialisasi */
    Time j = { year, month, day, hh, mm, ss };
    /* Algoritma */
    return j;
}

Time getCurrentTime ()
/* Gets the current local time */
{
    /* Kamus lokal */
    time_t t;
    struct tm *tm;
    /* Algoritma */
    t = time(NULL);
    tm = localtime(&t);
    return makeTime(tm->tm_year, tm->tm_mon, tm->tm_mday,
                    tm->tm_hour, tm->tm_min, tm->tm_sec);
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */

void writeDate (Time J)
/* Writes the date part of J as YYYY-MM-DD */
{
    /* Algoritma */
    printf("%04d-%02d-%02d", Year(J), Month(J), Day(J));
}

void writeTime (Time J)
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format hh:mm:ss */
/* Proses : menulis nilai setiap komponen J ke layar dalam format hh:mm:ss
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
{
    /* Algoritma */
    printf("%02d:%02d:%02d", Hour(J), Minute(J), Second(J));
}
