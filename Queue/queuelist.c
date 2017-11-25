/* File: listsirkuler.c
 * NIM            : 13516103
 * Nama           : Gerardus Samudra S.
 * Tanggal        : 2017-10-25
 * Topik praktikum: ADT Stack dan Queue dengan Representasi List Linier
 * Deskripsi      : Implementasi ADT Queue dengen representasi list berkait
 *                  dengan HEAD dan TAIL eksplisit
 */

#include "queuelist.h"
#include <stdlib.h>

/* Prototype manajemen memori */

void Alokasi (address *P, infotype X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
  /* Algoritma */
  *P = (ElmtQueue *) malloc(sizeof(ElmtQueue));
  if (*P != Nil) {
    Info(*P) = X;
    Next(*P) = Nil;
  }
  /* else *P == Nil */
}

void Dealokasi (address  P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
  /* Algoritma */
  free(P);
}

boolean IsEmpty (Queue Q)
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
{
  /* Algoritma */
  return Head(Q) == Nil && Tail(Q) == Nil;
}

int NbElmt(Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
{
  /* Kamus lokal */
  int count = 0;
  address P;
  /* Algoritma */
  for (P = Head(Q); P != Nil; P = Next(P))
    ++count;
  return count;
}

/*** Kreator ***/
void CreateEmpty(Queue * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
{
  /* Algoritma */
  Head(*Q) = Tail(*Q) = Nil;
}

/*** Primitif Add/Delete ***/

void Add (Queue * Q, infotype X)
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  Alokasi(&P, X);
  if (P != Nil) {
    if (IsEmpty(*Q))
      Head(*Q) = P;
    else
      Next(Tail(*Q)) = P;
    Tail(*Q) = P;
  }
}

void Del(Queue * Q, infotype * X)
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  P = Head(*Q);
  *X = Info(P);
  Head(*Q) = Next(P);
  if (Tail(*Q) == P) /* Queue satu elemen */
    Tail(*Q) = Nil;
}
