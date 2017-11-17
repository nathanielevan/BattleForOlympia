/* File : stacklist.c */
#include "stacklist.h"
#include <stdlib.h>

/* Prototype manajemen memori */

void stkAlokasi (stkAddress *P, int X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka stkInfo(P)=X dan 
        stkNext(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
  /* Algoritma */
  *P = (stkElement *) malloc(sizeof(stkElement));
  if (*P != Nil) {
    stkInfo(*P) = X;
    stkNext(*P) = Nil;
  }
  /* else *P == Nil */
}

void stkDealokasi (stkAddress P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
  /* Algoritma */
  free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK stkStack ***************/

boolean stkIsEmpty (stkStack S)
/* Mengirim true jika stkStack kosong: stkTop(S) = Nil */
{
  /* Algoritma */
  return stkTop(S) == Nil;
}

void stkCreateEmpty (stkStack * S)
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stkStack S yang kosong */
{
  /* Algoritma */
  stkTop(*S) = Nil;
}

void stkPush (stkStack * S, int X)
/* Menambahkan X sebagai elemen stkStack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi stkTop yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
{
  /* Kamus lokal */
  stkAddress P;
  /* Algoritma */
  stkAlokasi(&P, X);
  if (P != Nil) {
    /* Bila S kosong, ini menjadi stkNext(P) = Nil */
    stkNext(P) = stkTop(*S);
    stkTop(*S) = P;
  }
}

void stkPop (stkStack * S, int * X)
/* Menghapus X dari stkStack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen stkTop yang lama, */
/*      elemen stkTop yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
{
  /* Kamus lokal */
  stkAddress P;
  /* Algoritma */
  P = stkTop(*S);
  *X = stkInfo(P);
  stkTop(*S) = stkNext(P);
  stkDealokasi(P);
}
