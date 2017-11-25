/* File: listsirkuler.c
 * NIM            : 13516103
 * Nama           : Gerardus Samudra S.
 * Tanggal        : 2017-10-25
 * Topik praktikum: ADT Stack dan Queue dengan Representasi List Linier
 * Deskripsi      : Implementasi ADT Queue dengen representasi list berkait
 *                  dengan HEAD dan TAIL eksplisit
 */

#include "Queue.h"
#include <stdlib.h>

/* Prototype manajemen memori */

void Alokasi (qaddress *P, int X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
  /* Algoritma */
  *P = (ElmtQueue *) malloc(sizeof(ElmtQueue));
  if (*P != Nil) {
    qInfo(*P) = X;
    qNext(*P) = Nil;
  }
  /* else *P == Nil */
}

void qDealokasi (qaddress  P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
  /* Algoritma */
  free(P);
}

boolean qIsEmpty (Queue Q)
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
{
  /* Algoritma */
  return qHead(Q) == Nil && qTail(Q) == Nil;
}

boolean qIsOneElmt (Queue Q)
/* Mengirim true jika Q berisi satu elemen */
{
  return qHead(Q) != Nil && qHead(Q) == qTail(Q);
}

int qNbElmt(Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
{
  /* Kamus lokal */
  int count = 0;
  qaddress P;
  /* Algoritma */
  for (P = qHead(Q); P != Nil; P = qNext(P))
    ++count;
  return count;
}

/*** Kreator ***/
void qCreateEmpty(Queue * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
{
  /* Algoritma */
  qHead(*Q) = qTail(*Q) = Nil;
}

/*** Primitif Add/Delete ***/

void qAdd (Queue * Q, int X)
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
{
  /* Kamus lokal */
  qaddress P;
  /* Algoritma */
  Alokasi(&P, X);
  if (P != Nil) {
    if (qIsEmpty(*Q))
      qHead(*Q) = P;
    else
      qNext(qTail(*Q)) = P;
    qTail(*Q) = P;
  }
}

void qDel(Queue * Q, int * X)
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
{
  /* Kamus lokal */
  qaddress P;
  /* Algoritma */
  P = qHead(*Q);
  *X = qInfo(P);
  qHead(*Q) = qNext(P);
  if (qTail(*Q) == P) /* Queue satu elemen */
    qTail(*Q) = Nil;
}
