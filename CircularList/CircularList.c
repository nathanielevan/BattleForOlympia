/* File: listsirkuler.c
 * NIM            : 13516103
 * Nama           : Gerardus Samudra S.
 * Tanggal        : 2017-10-25
 * Topik praktikum: ADT List
 * Deskripsi      : Implementasi ADT List sirkuler dengan
 *                  representasi berkait dan address pointer
 */

#include "listsirkuler.h"
#include <stdlib.h>
#include <stdio.h>

/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
  /* Algoritma */
  return First(L) == Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. L sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
  /* Algoritma */
  First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  P = (ElmtList *) malloc(sizeof(ElmtList));
  if (P != Nil) {
    Info(P) = X;
    Next(P) = Nil;
  }
  return P;
}

void Dealokasi (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
  /* Algoritma */
  free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
  /* Kamus lokal */
  address P, Pfirst = First(L);
  /* Algoritma */
  P = Pfirst;
  if (P == Nil) {
    return Nil;
  } else {
    while (Next(P) != Pfirst && Info(P) != X)
      P = Next(P);
    /* Next(P) == Pfirst || Info(P) == X */
    if (Info(P) == X)
      return P;
    else
      return Nil;
  }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/

/*** PENAMBAHAN ELEMEN ***/

void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  P = Alokasi(X);
  if (P != Nil)
    InsertFirst(L, P);
}

void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  P = Alokasi(X);
  if (P != Nil)
    InsertLast(L, P);
}

/*** PENGHAPUSAN ELEMEN ***/

void DelVFirst (List *L, infotype * X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  DelFirst(L, &P);
  *X = Info(P);
  Dealokasi(P);
}

void DelVLast (List *L, infotype * X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  DelLast(L, &P);
  *X = Info(P);
  Dealokasi(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/

/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/

void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
  /* Kamus lokal */
  address first, last;
  /* Algoritma */
  if (IsEmpty(*L)) {
    Next(P) = P;
  } else {
    first = First(*L);
    for (last = first; Next(last) != first; last = Next(last))
      ;
    /* Next(last) == first */
    Next(P) = first;
    Next(last) = P;
  }
  First(*L) = P;
}

void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
  /* Kamus lokal */
  address first, last;
  /* Algoritma */
  if (IsEmpty(*L)) {
    Next(P) = P;
    First(*L) = P;
  } else {
    first = First(*L);
    for (last = first; Next(last) != first; last = Next(last))
      ;
    /* Next(last) == first */
    InsertAfter(L, P, last);
  }
}

void InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
  /* Algoritma */
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
  /* Kamus lokal */
  address first, last;
  /* Algoritma */
  *P = first = First(*L);
  for (last = first; Next(last) != first; last = Next(last))
    ;
  if (first == last) {
    First(*L) = Nil;
  } else {
    First(*L) = Next(first);
    Next(last) = Next(first);
  }
  Next(*P) = Nil;
}

void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
  /* Kamus lokal */
  address first, last, plast;
  /* Algoritma */
  first = First(*L);
  plast = Nil;
  for (last = first; Next(last) != first; last = Next(last))
    plast = last;
  if (plast != Nil)
    Next(plast) = first;
  else /* menghapus elemen satu-satunya */
    First(*L) = Nil;
  *P = last;
  /* Commenting this out fixes TC 16-17. Why :/ */
  /* Next(*P) = Nil; */
}

void DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
  /* Algoritma */
  *Pdel = Next(Prec);
  Next(Prec) = Next(*Pdel);
  if (*Pdel == First(*L))
    First(*L) = Next(Prec);
  Next(*Pdel) = Nil;
}

void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
  /* Kamus lokal */
  address first, pred, P;
  /* Algoritma */
  first = First(*L);
  if (first != Nil) {
    for (pred = first; Next(pred) != first && Info(Next(pred)) != X;
	 pred = Next(pred))
      ;
    if (Info(Next(pred)) == X) {
      DelAfter(L, &P, pred);
      Dealokasi(P);
    }
  }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
  /* Kamus lokal */
  address P, Pfirst = First(L);
  boolean first = true;
  /* Algoritma */
  putchar('[');
  P = Pfirst;
  while (P != Nil && (first || P != Pfirst)) {
    if (!first)
      putchar(',');
    else
      first = false;
    printf("%d", Info(P));
    P = Next(P);
  }
  putchar(']');
}
