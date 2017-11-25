/* File : queuelist.h */
/* Representasi queue dengan list berkait dengan first (HEAD) dan last (TAIL) */
#ifndef _QUEUELIST_H
#define _QUEUELIST_H
#include "boolean.h"
#include <stdlib.h>

/* Queue dengan representasi berkait dengan pointer */
typedef struct tElmtQueue * qaddress;
typedef struct tElmtQueue { 
	int Info;
	qaddress Next; 
} ElmtQueue; 

/* Type queue dengan ciri HEAD dan TAIL : */
typedef struct { 
	qaddress HEAD;  /* alamat penghapusan */
	qaddress TAIL;  /* alamat penambahan */
} Queue;

/* Selektor */
#define qHead(Q) (Q).HEAD
#define qTail(Q) (Q).TAIL
#define qInfoHead(Q) (Q).HEAD->Info
#define qInfoTail(Q) (Q).TAIL->Info
#define qNext(P) (P)->Next
#define qInfo(P) (P)->Info

/* Prototype manajemen memori */
void qAlokasi (qaddress *P, int X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void qDealokasi (qaddress  P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
boolean qIsEmpty (Queue Q);
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
boolean qIsOneElmt (Queue Q)
/* Mengirim true jika Q berisi satu elemen */
int qNbElmt(Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
/*** Kreator ***/
void qCreateEmpty(Queue * Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
void qAdd (Queue * Q, int X);
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void qDel(Queue * Q, int * X);
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */

#endif
