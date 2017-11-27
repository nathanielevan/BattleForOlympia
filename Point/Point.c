//
// Created by gery on 06/11/17.
//

#include <stdio.h>
#include <math.h>
#include "Point/Point.h"

/* *** Konstruktor membentuk Point *** */
Point MakePoint (int X, int Y)
/* Membentuk sebuah Point dari komponen-komponennya */
{
    /* Kamus lokal dengan inisialisasi */
    Point p = { X, Y };
    /* Algoritma */
    return p;
}

/* *** Kelompok operasi relasional terhadap Point *** */

boolean EQ (Point P1, Point P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
    /* Algoritma */
    return (unsigned char) ((absis(P1) == absis(P2)) && (ordinat(P1) == ordinat(P2)));
}

boolean NEQ (Point P1, Point P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
    /* Algoritma */
    return (unsigned char) !EQ(P1, P2);
}

/* *** Kelompok menentukan di mana P berada *** */

boolean IsOrigin (Point P)
/* Menghasilkan true jika P adalah titik origin */
{
    /* Algoritma */
    return (unsigned char) ((absis(P) == 0) && (ordinat(P) == 0));
}

boolean IsOnSbX (Point P)
/* Menghasilkan true jika P terletak Pada sumbu X */
{
    /* Algoritma */
    return (unsigned char) (ordinat(P) == 0);
}

boolean IsOnSbY (Point P)
/* Menghasilkan true jika P terletak pada sumbu Y */
{
    /* Algoritma */
    return (unsigned char) (absis(P) == 0);
}

int Kuadran (Point P)
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */
{
    /* Algoritma */
    if (ordinat(P) > 0) {
        if (absis(P) > 0)
            return 1;
        else
            return 2;
    } else {
        if (absis(P) < 0)
            return 3;
        else
            return 4;
    }
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */

Point NextX (Point P)
/* Mengirim salinan P dengan absis ditambah satu */
{
    /* Algoritma */
    return MakePoint(absis(P) + 1.0, ordinat(P));
}

Point NextY (Point P)
/* Mengirim salinan P dengan ordinat ditambah satu */
{
    /* Algoritma */
    return MakePoint(absis(P), ordinat(P) + 1.0);
}

Point PlusDelta (Point P, int deltaX, int deltaY)
/* Mengirim salinan P yang absisnya adalah absis(P) + deltaX dan ordinatnya adalah ordinat(P) + deltaY */
{
    /* Algoritma */
    return MakePoint(absis(P) + deltaX, ordinat(P) + deltaY);
}

void Geser (Point *P, int deltaX, int deltaY)
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
{
    /* Algoritma */
    *P = PlusDelta(*P, deltaX, deltaY);
}

void GeserKeSbX (Point *P)
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
{
    /* Algoritma */
    ordinat(*P) = 0;
}

void GeserKeSbY (Point *P)
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
{
    /* Algoritma */
    absis(*P) = 0;
}

