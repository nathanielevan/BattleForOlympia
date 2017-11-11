//
// Created by gery on 06/11/17.
//

#include <stdio.h>
#include <math.h>
#include "Point.h"

/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (float X, float Y)
/* Membentuk sebuah POINT dari komponen-komponennya */
{
    /* Kamus lokal dengan inisialisasi */
    POINT p = { X, Y };
    /* Algoritma */
    return p;
}

void BacaPOINT (POINT * P)
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
{
    /* Algoritma */
    scanf("%f %f", &Absis(*P), &Ordinat(*P));
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */

void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
{
    /* Algoritma */
    printf("(%.2f,%.2f)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap POINT *** */

boolean EQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
    /* Algoritma */
    return (unsigned char) ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)));
}

boolean NEQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
    /* Algoritma */
    return (unsigned char) !EQ(P1, P2);
}

/* *** Kelompok menentukan di mana P berada *** */

boolean IsOrigin (POINT P)
/* Menghasilkan true jika P adalah titik origin */
{
    /* Algoritma */
    return (unsigned char) ((Absis(P) == 0) && (Ordinat(P) == 0));
}

boolean IsOnSbX (POINT P)
/* Menghasilkan true jika P terletak Pada sumbu X */
{
    /* Algoritma */
    return (unsigned char) (Ordinat(P) == 0);
}

boolean IsOnSbY (POINT P)
/* Menghasilkan true jika P terletak pada sumbu Y */
{
    /* Algoritma */
    return (unsigned char) (Absis(P) == 0);
}

int Kuadran (POINT P)
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */
{
    /* Algoritma */
    if (Ordinat(P) > 0) {
        if (Absis(P) > 0)
            return 1;
        else
            return 2;
    } else {
        if (Absis(P) < 0)
            return 3;
        else
            return 4;
    }
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */

POINT NextX (POINT P)
/* Mengirim salinan P dengan absis ditambah satu */
{
    /* Algoritma */
    return MakePOINT(Absis(P) + 1.0, Ordinat(P));
}

POINT NextY (POINT P)
/* Mengirim salinan P dengan ordinat ditambah satu */
{
    /* Algoritma */
    return MakePOINT(Absis(P), Ordinat(P) + 1.0);
}

POINT PlusDelta (POINT P, float deltaX, float deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
    /* Algoritma */
    return MakePOINT(Absis(P) + deltaX, Ordinat(P) + deltaY);
}

POINT MirrorOf (POINT P, boolean SbX)
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
{
    /* Kamus lokal */
    float x, y;
    /* Algoritma */
    if (SbX)
        x =  Absis(P), y = -Ordinat(P);
    else
        x = -Absis(P), y =  Ordinat(P);
    return MakePOINT(x, y);
}

float Jarak0 (POINT P)
/* Menghitung jarak P ke (0,0) */
{
    /* Kamus lokal */
    const POINT origin = { 0, 0 };  /* konstanta titik origin */
    /* Algoritma */
    return Panjang(origin, P);
}

float Panjang (POINT P1, POINT P2)
/* Menghitung jarak Euclid antara P1 dan P2 */
{
    /* Kamus lokal */
    double dX, dY;  /* Beda absis dan ordinat */
    /* Algoritma */
    /* Perhitungan dalam double untuk presisi */
    dX = Absis(P1) - Absis(P2);
    dY = Ordinat(P1) - Ordinat(P2);
    return (float) sqrt(dX * dX + dY * dY);
}

void Geser (POINT *P, float deltaX, float deltaY)
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
{
    /* Algoritma */
    *P = PlusDelta(*P, deltaX, deltaY);
}

void GeserKeSbX (POINT *P)
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
{
    /* Algoritma */
    Ordinat(*P) = 0;
}

void GeserKeSbY (POINT *P)
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
{
    /* Algoritma */
    Absis(*P) = 0;
}

void Mirror (POINT *P, boolean SbX)
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
{
    /* Algoritma */
    *P = MirrorOf(*P, SbX);
}

void Putar (POINT *P, float Sudut)
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) */
{
    /* Kamus lokal */
    double radian, x, y, x2, y2;
    /* Algoritma */
    radian = Sudut * M_PI / 180.0;  /* Sudut dalam radian */
    x = Absis(*P);                  /* Absis original */
    y = Ordinat(*P);                /* Ordinat original */
    /* Perhitungan dilakukan dalam double; hasil dikonversi secara implisit
       menjadi float pada saat pemanggian MakePOINT */
    x2 = x * cos(radian) - y * sin(radian);
    y2 = x * sin(radian) + y * cos(radian);
    *P = MakePOINT(x2, y2);
}