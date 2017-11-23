/* File : stack.h */
#ifndef _STACKLIST_H
#define _STACKLIST_H

#include "../boolean.h"
#include <stdlib.h>

typedef struct {
    int unitID;
    int delta;
    int prevDestOwnerID;
} UndoStkEntry;

#define stkInfoType UndoStkEntry

/* stkStack dengan representasi berkait dengan pointer */
typedef struct stkSElement * stkAddress;
typedef struct stkSElement { 
  stkInfoType Info;
  stkAddress Next;
} stkElement; 

/* Type stkStack dengan ciri TOP : */
typedef struct { 
  stkAddress TOP;  /* alamat TOP: elemen puncak */
} stkStack;

/* Selektor */
#define stkTop(S) (S).TOP
#define stkInfoTop(S) (S).TOP->Info 
#define stkNext(P) (P)->Next
#define stkInfo(P) (P)->Info

/* Prototype manajemen memori */
void stkAlokasi (stkAddress *P, stkInfoType X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void stkDealokasi (stkAddress P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */ 

/* ********* PROTOTYPE REPRESENTASI LOJIK stkStack ***************/
boolean stkIsEmpty (stkStack S);
/* Mengirim true jika stkStack kosong: TOP(S) = Nil */
void stkCreateEmpty (stkStack * S);
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stkStack S yang kosong */
void stkPush (stkStack * S, stkInfoType X);
/* Menambahkan X sebagai elemen stkStack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void stkPop (stkStack * S, stkInfoType * X);
/* Menghapus X dari stkStack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
void stkDestroy(stkStack *S);
/* Menghapus semua elemen dari stack */

#endif
