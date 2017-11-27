/* File : lcListsirkuler.h */
/* ADT lcList Sirkuler dengan elemen terakhir menunjuk pada elemen pertama */
/* Representasi berkait dengan lcaddress adalah pointer */
/* infotype adalah integer */

#ifndef circularlcList_H
#define circularlcList_H


#include "boolean.h"

#define Nil NULL

typedef int lcType;
typedef struct lctElmtlcList *lcaddress;
typedef struct lctElmtlcList { 
    lcType info;
    lcaddress next;
} lcElmtList;
typedef struct {
    lcaddress First;
} lcList;

/* Definisi lcList : */
/* lcList kosong : First(L) = Nil */
/* Setiap elemen dengan lcaddress P dapat diacu Info(P), Next(P) */
/* Elemen terakhir lcList: jika lcaddressnya Last, maka Next(Last)=First(L) */

/* Notasi Akses */
#define lcInfo(P) (P)->info
#define lcNext(P) (P)->next
#define lcFirst(L) ((L).First)

/* PROTOTYPE */
/****************** TEST lcList KOSONG ******************/
boolean lcIsEmpty (lcList L);
/* Mengirim true jika lcList kosong. Lihat definisi di atas. */

/****************** PEMBUATAN lcList KOSONG ******************/
void lcCreateEmpty (lcList *L);
/* I.S. L sembarang             */
/* F.S. Terbentuk lcList kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/
lcaddress lcAlokasi (lcType X);
/* Mengirimkan lcaddress hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka lcaddress tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void lcDealokasi (lcaddress P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian lcaddress P */

/****************** PENCARIAN SEBUAH ELEMEN lcList ******************/
lcaddress lcSearch (lcList L, lcType X);
/* Mencari apakah ada elemen lcList dengan Info(P)= X */
/* Jika ada, mengirimkan lcaddress elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void lcInsVFirst (lcList *L, lcType X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void lcInsVLast (lcList *L, lcType X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen lcList di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void lcDelVFirst (lcList *L, lcType * X);
/* I.S. lcList L tidak kosong  */
/* F.S. Elemen pertama lcList dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void lcDelVLast (lcList *L, lcType * X);
/* I.S. lcList tidak kosong */
/* F.S. Elemen terakhir lcList dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void lcInsertFirst (lcList *L, lcaddress P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-lcaddress P sebagai elemen pertama */
void lcInsertLast (lcList *L, lcaddress P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void lcInsertAfter (lcList *L, lcaddress P, lcaddress Prec);
/* I.S. Prec pastilah elemen lcList dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void lcDelFirst (lcList *L, lcaddress *P);
/* I.S. lcList tidak kosong */
/* F.S. P adalah alamat elemen pertama lcList sebelum penghapusan */
/*      Elemen lcList berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void lcDelLast (lcList *L, lcaddress *P);
/* I.S. lcList tidak kosong */
/* F.S. P adalah alamat elemen terakhir lcList sebelum penghapusan  */
/*      Elemen lcList berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
void lcDelAfter (lcList *L, lcaddress *Pdel, lcaddress Prec);
/* I.S. lcList tidak kosong. Prec adalah anggota lcList  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen lcList yang dihapus  */
void lcDelP (lcList *L, lcType X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen lcList berlcaddress P, dengan Info(P)=X  */
/* Maka P dihapus dari lcList dan di-dealokasi */
/* Jika tidak ada elemen lcList dengan Info(P)=X, maka lcList tetap */
/* lcList mungkin menjadi kosong karena penghapusan */

/****************** PROSES SEMUA ELEMEN lcList ******************/
void lcPrintInfo (lcList L);
/* I.S. lcList mungkin kosong */
/* F.S. Jika lcList tidak kosong, iai lcList dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika lcList kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

#endif
