#include "Stack.h"
#include <stdlib.h>

/* Prototype manajemen memori */

void stkAlokasi (stkAddress *P, stkInfoType X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka stkInfo(P)=X dan 
        stkNext(P)=NULL */
/*      P=NULL jika alokasi gagal */
{
  /* Algoritma */
  *P = (stkElement *) malloc(sizeof(stkElement));
  if (*P != NULL) {
    stkInfo(*P) = X;
    stkNext(*P) = NULL;
  }
  /* else *P == NULL */
}

void stkDealokasi (stkAddress P)
/* I.S. P adalah hasil alokasi, P != NULL */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
  /* Algoritma */
  free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK stkStack ***************/

boolean stkIsEmpty (stkStack S)
/* Mengirim true jika stkStack kosong: stkTop(S) = NULL */
{
  /* Algoritma */
  return stkTop(S) == NULL;
}

void stkCreateEmpty (stkStack * S)
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stkStack S yang kosong */
{
  /* Algoritma */
  stkTop(*S) = NULL;
}

void stkPush (stkStack * S, stkInfoType X)
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
  if (P != NULL) {
    /* Bila S kosong, ini menjadi stkNext(P) = NULL */
    stkNext(P) = stkTop(*S);
    stkTop(*S) = P;
  }
}

void stkPop (stkStack * S, stkInfoType * X)
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

void stkDestroy(stkStack *S) {
  stkAddress P;
  while (!stkIsEmpty(*S)) {
    P = stkTop(*S);
    stkTop(*S) = stkNext(P);
    stkDealokasi(P);
  }
}
