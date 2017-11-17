#ifndef BATTLEFOROLYMPIA_POINT_H
#define BATTLEFOROLYMPIA_POINT_H

#include "../boolean.h"

typedef struct {
    int X; /* absis   */
    int Y; /* ordinat */
} Point;

/* *** Notasi Akses: Selektor Point *** */
#define absis(P) (P).X
#define ordinat(P) (P).Y

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
Point MakePoint (int X, int Y);
/* Membentuk sebuah Point dari komponen-komponennya */

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQ (Point P1, Point P2);
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
boolean NEQ (Point P1, Point P2);
/* Mengirimkan true jika P1 tidak sama dengan P2 */

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (Point P);
/* Menghasilkan true jika P adalah titik origin */
boolean IsOnSbX (Point P);
/* Menghasilkan true jika P terletak Pada sumbu X */
boolean IsOnSbY (Point P);
/* Menghasilkan true jika P terletak pada sumbu Y */
int Kuadran (Point P);
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
Point NextX (Point P);
/* Mengirim salinan P dengan absis ditambah satu */
Point NextY (Point P);
/* Mengirim salinan P dengan ordinat ditambah satu */

Point PlusDelta (Point P, int deltaX, int deltaY);
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
void Geser (Point *P, int deltaX, int deltaY);
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
void GeserKeSbX (Point *P);
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
void GeserKeSbY (Point *P);
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */

#endif //BATTLEFOROLYMPIA_Point_H
