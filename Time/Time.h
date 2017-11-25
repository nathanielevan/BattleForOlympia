/* File: jam.h */
/* Tanggal: 28 Agustus 2016 */
/* Definisi ADT Time */

#ifndef Time_H
#define Time_H

#include "boolean.h"

/* *** Definisi TYPE Time <hh:mm:ss> *** */
typedef struct {
    short year;
    char month;
    char day;
    char hh; /* integer [0..23] */
    char mm; /* integer [0..59] */
    char ss; /* integer [0..59] */
} Time;

/* *** Notasi Akses: selektor Time *** */
#define Hour(J) (J).hh
#define Minute(J) (J).mm
#define Second(J) (J).ss
#define Day(J) (J).day
#define Month(J) (J).month
#define Year(J) (J).year

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean isTimeValid (int Y, int M, int D, int HH, int MM, int SS);
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Time */

/* *** Konstruktor: Membentuk sebuah Time dari komponen-komponennya *** */
Time makeTime (int year, int month, int day, int hh, int mm, int ss);
/* Membentuk sebuah Time dari komponen-komponennya yang valid */
/* Prekondisi : hh, mm, ss valid untuk membentuk Time */

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */

void writeDate (Time J);
/* Writes the date part of J as YYYY-MM-DD */

void writeTime (Time J);
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format hh:mm:ss */
/* Proses : menulis nilai setiap komponen J ke layar dalam format hh:mm:ss
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 

#endif
