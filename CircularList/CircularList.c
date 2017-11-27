/* File: lcListsirkuler.c
 * NIM            : 13516103
 * Nama           : Gerardus Samudra S.
 * Tanggal        : 2017-10-25
 * Topik praktikum: ADT lcList
 * Deskripsi      : Implementasi ADT lcList sirkuler dengan
 *                  representasi berkait dan lcaddress pointer
 */

#include "CircularList/CircularList.h"
#include <stdlib.h>
#include <stdio.h>

/****************** TEST lcList KOSONG ******************/
boolean lcIsEmpty (lcList L)
/* Mengirim true jika lcList kosong. Lihat definisi di atas. */
{
    /* Algoritma */
    return lcFirst(L) == Nil;
}

/****************** PEMBUATAN lcList KOSONG ******************/
void lcCreateEmpty (lcList *L)
/* I.S. L sembarang             */
/* F.S. Terbentuk lcList kosong. Lihat definisi di atas. */
{
    /* Algoritma */
    lcFirst(*L) = Nil;
}

/****************** Manajemen Memori ******************/
lcaddress lcAlokasi (lcType X)
/* Mengirimkan lcaddress hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka lcaddress tidak nil, dan misalnya */
/* menghasilkan P, maka lcInfo(P)=X, lcNext(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    /* Kamus lokal */
    lcaddress P;
    /* Algoritma */
    P = (lcElmtList *) malloc(sizeof(lcElmtList));
    if (P != Nil) {
        lcInfo(P) = X;
        lcNext(P) = Nil;
    }
    return P;
}

void lcDealokasi (lcaddress P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian lcaddress P */
{
    /* Algoritma */
    free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN lcList ******************/
lcaddress lcSearch (lcList L, lcType X)
/* Mencari apakah ada elemen lcList dengan lcInfo(P)= X */
/* Jika ada, mengirimkan lcaddress elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    /* Kamus lokal */
    lcaddress P, PFirst = lcFirst(L);
    /* Algoritma */
    P = PFirst;
    if (P == Nil) {
        return Nil;
    } else {
        while (lcNext(P) != PFirst && lcInfo(P) != X)
            P = lcNext(P);
        /* lcNext(P) == PFirst || lcInfo(P) == X */
        if (lcInfo(P) == X)
            return P;
        else
            return Nil;
    }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/

/*** PENAMBAHAN ELEMEN ***/

void lcInsVFirst (lcList *L, lcType X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    /* Kamus lokal */
    lcaddress P;
    /* Algoritma */
    P = lcAlokasi(X);
    if (P != Nil)
        lcInsertFirst(L, P);
}

void lcInsVLast (lcList *L, lcType X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen lcList di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    /* Kamus lokal */
    lcaddress P;
    /* Algoritma */
    P = lcAlokasi(X);
    if (P != Nil)
        lcInsertLast(L, P);
}

/*** PENGHAPUSAN ELEMEN ***/

void lcDelVFirst (lcList *L, lcType * X)
/* I.S. lcList L tidak kosong  */
/* F.S. Elemen pertama lcList dihapus: nilai lcInfo disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    /* Kamus lokal */
    lcaddress P;
    /* Algoritma */
    lcDelFirst(L, &P);
    *X = lcInfo(P);
    lcDealokasi(P);
}

void lcDelVLast (lcList *L, lcType * X)
/* I.S. lcList tidak kosong */
/* F.S. Elemen terakhir lcList dihapus: nilai lcInfo disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    /* Kamus lokal */
    lcaddress P;
    /* Algoritma */
    lcDelLast(L, &P);
    *X = lcInfo(P);
    lcDealokasi(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/

/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/

void lcInsertFirst (lcList *L, lcaddress P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-lcaddress P sebagai elemen pertama */
{
    /* Kamus lokal */
    lcaddress lcFirst, last;
    /* Algoritma */
    if (lcIsEmpty(*L)) {
        lcNext(P) = P;
    } else {
        lcFirst = lcFirst(*L);
        for (last = lcFirst; lcNext(last) != lcFirst; last = lcNext(last))
            ;
        /* lcNext(last) == lcFirst */
        lcNext(P) = lcFirst;
        lcNext(last) = P;
    }
    lcFirst(*L) = P;
}

void lcInsertLast (lcList *L, lcaddress P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    /* Kamus lokal */
    lcaddress lcFirst, last;
    /* Algoritma */
    if (lcIsEmpty(*L)) {
        lcNext(P) = P;
        lcFirst(*L) = P;
    } else {
        lcFirst = lcFirst(*L);
        for (last = lcFirst; lcNext(last) != lcFirst; last = lcNext(last))
            ;
        /* lcNext(last) == lcFirst */
        lcInsertAfter(L, P, last);
    }
}

void lcInsertAfter (lcList *L, lcaddress P, lcaddress Prec)
/* I.S. Prec pastilah elemen lcList dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    /* Algoritma */
    lcNext(P) = lcNext(Prec);
    lcNext(Prec) = P;
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void lcDelFirst (lcList *L, lcaddress *P)
/* I.S. lcList tidak kosong */
/* F.S. P adalah alamat elemen pertama lcList sebelum penghapusan */
/*      Elemen lcList berkurang satu (mungkin menjadi kosong) */
/* lcFirst element yg baru adalah suksesor elemen pertama yang lama */
{
    /* Kamus lokal */
    lcaddress lcFirst, last;
    /* Algoritma */
    *P = lcFirst = lcFirst(*L);
    for (last = lcFirst; lcNext(last) != lcFirst; last = lcNext(last))
        ;
    if (lcFirst == last) {
        lcFirst(*L) = Nil;
    } else {
        lcFirst(*L) = lcNext(lcFirst);
        lcNext(last) = lcNext(lcFirst);
    }
    lcNext(*P) = Nil;
}

void lcDelLast (lcList *L, lcaddress *P)
/* I.S. lcList tidak kosong */
/* F.S. P adalah alamat elemen terakhir lcList sebelum penghapusan  */
/*      Elemen lcList berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
    /* Kamus lokal */
    lcaddress lcFirst, last, plast;
    /* Algoritma */
    lcFirst = lcFirst(*L);
    plast = Nil;
    for (last = lcFirst; lcNext(last) != lcFirst; last = lcNext(last))
        plast = last;
    if (plast != Nil)
        lcNext(plast) = lcFirst;
    else /* menghapus elemen satu-satunya */
        lcFirst(*L) = Nil;
    *P = last;
    /* Commenting this out fixes TC 16-17. Why :/ */
    /* lcNext(*P) = Nil; */
}

void lcDelAfter (lcList *L, lcaddress *Pdel, lcaddress Prec)
/* I.S. lcList tidak kosong. Prec adalah anggota lcList  */
/* F.S. Menghapus lcNext(Prec): */
/*      Pdel adalah alamat elemen lcList yang dihapus  */
{
    /* Algoritma */
    *Pdel = lcNext(Prec);
    lcNext(Prec) = lcNext(*Pdel);
    if (*Pdel == lcFirst(*L)) {
        lcFirst(*L) = lcNext(Prec);
    }
    lcNext(*Pdel) = Nil;
}

void lcDelP (lcList *L, lcType X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen lcList berlcaddress P, dengan lcInfo(P)=X  */
/* Maka P dihapus dari lcList dan di-dealokasi */
/* Jika tidak ada elemen lcList dengan lcInfo(P)=X, maka lcList tetap */
/* lcList mungkin menjadi kosong karena penghapusan */
{
    /* Kamus lokal */
    lcaddress lcFirst, pred, P;
    /* Algoritma */
    lcFirst = lcFirst(*L);
    if (lcFirst != Nil) {
        for (pred = lcFirst; lcNext(pred) != lcFirst && lcInfo(lcNext(pred)) != X; pred = lcNext(pred))
            ;
        if (lcInfo(lcNext(pred)) == X) {
            if (pred == lcNext(pred)) {
                P = pred;
                lcFirst(*L) = Nil;
            } else {
                lcDelAfter(L, &P, pred);
            }
            lcDealokasi(P);
        }
    }
}

/****************** PROSES SEMUA ELEMEN lcList ******************/
void lcPrintInfo (lcList L)
/* I.S. lcList mungkin kosong */
/* F.S. Jika lcList tidak kosong, iai lcList dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika lcList kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    /* Kamus lokal */
    lcaddress P, PFirst = lcFirst(L);
    boolean First = true;
    /* Algoritma */
    putchar('[');
    P = PFirst;
    while (P != Nil && (First || P != PFirst)) {
        if (!First)
            putchar(',');
        else
            First = false;
        printf("%d", lcInfo(P));
        P = lcNext(P);
    }
    putchar(']');
}
