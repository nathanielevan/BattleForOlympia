/* File: listlinier.c
 * NIM            : 13516103
 * Nama           : Gerardus Samudra S.
 * Tanggal        : 2017-10-27
 * Topik praktikum: ADT llList Linier
 * Deskripsi      : Implementasi ADT list berkait dengan representasi
 *                  fisik pointer
 */

#include "listlinier.h"
#include <stdlib.h>
#include <stdio.h>

/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (llList L)
/* Mengirim true jika list kosong */
{
  /* Algoritma */
  return First(L) == Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (llList *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
  /* Algoritma */
  First(*L) = Nil;
}

/****************** Manajemen Memori ******************/

address Alokasi (int X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  P = (llElmtList *) malloc(sizeof(llElmtList));
  if (P != Nil) {
    Info(P) = X;
    Next(P) = Nil;
  }
  return P;
}

void Dealokasi (address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
  /* Algoritma */
  free(*P);
  *P = Nil;
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/

address Search (llList L, int X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  for (P = First(L); P != Nil && Info(P) != X; P = Next(P))
    ;
  /* P == Nil || Info(P) == X */
  return P;
}

boolean FSearch (llList L, address P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
  /* Kamus lokal */
  address Q;
  /* Algoritma */
  for (Q = First(L); Q != Nil && Q != P; Q = Next(Q))
    ;
  /* Q == Nil || Q == P */
  return Q == P;
}

address SearchPrec (llList L, int X)
/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
{
  /* Kamus lokal */
  address P, pred;
  /* Algoritma */
  pred = Nil;
  for (P = First(L); P != Nil && Info(P) != X; P = Next(P))
    pred = P;
  /* P == Nil || Info(P) == X */
  if (P != Nil)
    return pred;
  else
    return Nil;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/

/*** PENAMBAHAN ELEMEN ***/

void InsVFirst (llList *L, int X)
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

void InsVLast (llList *L, int X)
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

void DelVFirst (llList *L, int *X)
/* I.S. llList L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  DelFirst(L, &P);
  *X = Info(P);
  Dealokasi(&P);
}

void DelVLast (llList *L, int *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  DelLast(L, &P);
  *X = Info(P);
  Dealokasi(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/

/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/

void InsertFirst (llList *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
  /* Algoritma */
  Next(P) = First(*L);
  First(*L) = P;
}

void InsertAfter (llList *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
  /* Algoritma */
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

void InsertLast (llList *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
  /* Kamus lokal */
  address pred;
  /* Algoritma */
  pred = First(*L);
  if (pred == Nil) {
    InsertFirst(L, P);
  } else {
    while (Next(pred) != Nil)
      pred = Next(pred);
    Next(pred) = P;
  }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/

void DelFirst (llList *L, address *P)
/* I.S. llList tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
  /* Algoritma */
  *P = First(*L);
  First(*L) = Next(*P);
  Next(*P) = Nil;
}

void DelP (llList *L, int X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* llList mungkin menjadi kosong karena penghapusan */
{
  /* Kamus lokal */
  address pred, P;
  /* Algoritma */
  pred = Nil;
  for (P = First(*L); P != Nil && Info(P) != X; P = Next(P))
    pred = P;
  /* P == Nil | Info(P) == X */
  if (P != Nil) { /* => Info(P) == X */
    if (pred == Nil) /* P elemen pertama */
      First(*L) = Next(P);
    else /* pred dan P berbeda */
      Next(pred) = Next(P);
    Dealokasi(&P);
  }
}

void DelLast (llList *L, address *P)
/* I.S. llList tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
  /* Kamus lokal */
  address pred, last;
  /* Algoritma */
  pred = Nil;
  for (last = First(*L); Next(last) != Nil; last = Next(last))
    pred = last;
  /* Next(last) == Nil */
  if (pred == Nil) { /* Menghapus elemen pertama */
    DelFirst(L, P);
  } else  { /* Ada elemen pred */
    Next(pred) = Nil;
    Next(last) = Nil;
    *P = last;
  }
}

void DelAfter (llList *L, address *Pdel, address Prec)
/* I.S. llList tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
  /* Algoritma */
  *Pdel = Next(Prec);
  /* WHAT IF *Pdel == Nil? */
  Next(Prec) = Next(*Pdel);
  Next(*Pdel) = Nil;
}

/****************** PROSES SEMUA ELEMEN LIST ******************/

void PrintInfo (llList L)
/* I.S. llList mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
  /* Kamus lokal */
  address P;
  boolean first = true;
  /* Algoritma */
  putchar('[');
  for (P = First(L); P != Nil; P = Next(P)) {
    if (!first)
      putchar(',');
    else
      first = false;
    printf("%d", Info(P));
  }
  putchar(']');
}

int NbElmt (llList L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
  /* Kamus lokal */
  int n = 0;
  address P;
  /* Algoritma */
  for (P = First(L); P != Nil; P = Next(P))
    n++;
  return n;
}

/*** Prekondisi untuk Max/Min/rata-rata : llList tidak kosong ***/

int Max (llList L)
/* Mengirimkan nilai Info(P) yang maksimum */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  P = AdrMax(L);
  return Info(P);
}

address AdrMax (llList L)
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
{
  /* Kamus lokal */
  int max;
  address P, maxP;
  /* Algoritma */
  P = First(L);
  max = Info(P);
  maxP = P;
  for (P = Next(P); P != Nil; P = Next(P)) {
    if (Info(P) > max) {
      max = Info(P);
      maxP = P;
    }
  }
  return maxP;
}

int Min (llList L)
/* Mengirimkan nilai info(P) yang minimum */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  P = AdrMin(L);
  return Info(P);
}

address AdrMin (llList L)
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
{
  /* Kamus lokal */
  int min;
  address P, minP;
  /* Algoritma */
  P = First(L);
  min = Info(P);
  minP = P;
  for (P = Next(P); P != Nil; P = Next(P)) {
    if (Info(P) < min) {
      min = Info(P);
      minP = P;
    }
  }
  return minP;
}

float Average (llList L)
/* Mengirimkan nilai rata-rata info(P) */
{
  /* Kamus lokal */
  float sum = 0.0f;
  unsigned n = 0;
  address P;
  /* Algoritma */
  for (P = First(L); P != Nil; P = Next(P), ++n)
    sum += Info(P);
  return sum / n;
}

/****************** PROSES TERHADAP LIST ******************/

void DelAll (llList *L)
/* Delete semua elemen list dan alamat elemen di-dealokasi */
{
  /* Kamus lokal */
  address P;
  /* Algoritma */
  while (First(*L) != Nil) {
    DelFirst(L, &P);
    Dealokasi(&P);
  }
}

void InversList (llList *L)
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
{
  /* Kamus lokal */
  address P, pred, succ;
  /* Algoritma */
  pred = Nil;
  succ = First(*L);
  while (succ != Nil) {
    P = succ;
    succ = Next(P);
    Next(P) = pred;
    pred = P;
  }
  First(*L) = pred;
}

llList FInversList (llList L)
/* Mengirimkan list baru, hasil invers dari L */
/* dengan menyalin semua elemn list. Alokasi mungkin gagal. */
/* Jika alokasi gagal, hasilnya list kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus didealokasi */
{
  /* Kamus lokal */
  llList L2;
  address P, Q;
  int X;
  boolean fail = false;
  /* Algoritma */
  CreateEmpty(&L2);
  for (P = First(L); P != Nil && !fail; P = Next(P)) {
    X = Info(P);
    Q = Alokasi(X);
    if (Q != Nil)
      InsertFirst(&L2, Q);
    else
      fail = true;
  }
  /* P == Nil || fail */
  if (fail)
    DelAll(&L2);
  return L2;
}

void CopyList (llList *L1, llList *L2)
/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/dealokasi elemen */
{
  /* Asumsi: L2 akan dibuat menunjuk ke list yang sama dengan L1 */
  /* I.S. L2 diasumsikan mengarah ke llList kosong atau tidak terinisialisasi */
  /* Algoritma */
  First(*L2) = First(*L1);
}

llList FCopyList (llList L)
/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya list kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus didealokasi */
{
  /* Kamus lokal */
  llList L2;
  address P, Q, last;
  int X;
  boolean fail = false;
  /* Algoritma */
  CreateEmpty(&L2);
  last = Nil;
  for (P = First(L); P != Nil && !fail; P = Next(P)) {
    X = Info(P);
    Q = Alokasi(X);
    fail = (Q == Nil);
    if (!fail) {
      /* Lebih hemat dari InsertLast */
      if (last != Nil)
	Next(last) = Q;
      else
	First(L2) = Q;
      last = Q;
    }
  }
  /* P == Nil || fail */
  if (fail)
    DelAll(&L2);
  return L2;
}

void CpAlokList (llList Lin, llList *Lout)
/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* dengan melakukan alokasi elemen. */
/* Jika ada alokasi yang gagal, maka Lout=Nil dan semua elemen yang terlanjur dialokasi, didealokasi */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal */
{
  /* Asumsi: I.S. Lout mengarah ke llList kosong atau tidak terinisialisasi */
  /* Kamus lokal */
  llList L;
  /* Algoritma */
  L = FCopyList(Lin);
  CopyList(&L, Lout);
  /* Assignment Lout <- Nil tidak akan berpengaruh pada hasil */
}

void Konkat (llList L1, llList L2, llList * L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
/* Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi*/
/* Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi */
/* harus di-dealokasi dan L3=Nil*/
/* Konkatenasi dua buah list : L1 & L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang “baru”. */
/* Jika ada alokasi yang gagal, maka L3 harus bernilai Nil*/
/* dan semua elemen yang pernah dialokasi didealokasi */
{
  /* Kamus lokal */
  address P, Q, last;
  int X;
  boolean fail = false;
  /* Algoritma */
  CreateEmpty(L3);
  last = Nil;
  /* Copy elemen L1 */
  for (P = First(L1); P != Nil && !fail; P = Next(P)) {
    X = Info(P);
    Q = Alokasi(X);
    fail = (Q == Nil);
    if (!fail) {
      if (last != Nil)
	Next(last) = Q;
      else
	First(*L3) = Q;
      last = Q;
    }
  }
  /* P == Nil || fail */
  /* Copy elemen L2 */
  for (P = First(L2); P != Nil && !fail; P = Next(P)) {
    X = Info(P);
    Q = Alokasi(X);
    fail = (Q == Nil);
    if (!fail) {
      if (last != Nil)
	Next(last) = Q;
      else
	First(*L3) = Q;
      last = Q;
    }
  }
  /* P == Nil || fail */
  if (fail) {
    DelAll(L3);
    /* Assignment L3 <- Nil tidak akan berpengaruh pada hasil */
  }
}

void Konkat1 (llList *L1, llList *L2, llList *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
  /* Kamus lokal */
  address last;
  /* Algoritma */
  First(*L3) = First(*L1);
  First(*L1) = Nil;
  if (First(*L3) == Nil) {
    First(*L3) = First(*L2);
  } else {
    for (last = First(*L3); Next(last) != Nil; last = Next(last))
      ;
    Next(last) = First(*L2);
  }
  First(*L2) = Nil;
}

void PecahList (llList *L1, llList *L2, llList L)
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2 */
{
  /* Asumsi: Bila alokasi gagal, L1 dan L2 dikosongkan dan semua elemennya
     di-dealokasi */
  /* Kamus lokal */
  address P, Q, last;
  int X;
  unsigned n, i;
  boolean fail = false;
  /* Algoritma */
  CreateEmpty(L1);
  CreateEmpty(L2);
  n = NbElmt(L);
  P = First(L);
  last = Nil;
  for (i = 0; i < n/2 && !fail; i++) {
    X = Info(P);
    Q = Alokasi(X);
    fail = (Q == Nil);
    if (!fail) {
      if (last != Nil)
	Next(last) = Q;
      else
	First(*L1) = Q;
      last = Q;
    }
    P = Next(P);
  }
  /* i == n/2 || fail */
  last = Nil;
  for (; i < n && !fail; i++) {
    X = Info(P);
    Q = Alokasi(X);
    fail = (Q == Nil);
    if (!fail) {
      if (last != Nil)
	Next(last) = Q;
      else
	First(*L2) = Q;
      last = Q;
    }
    P = Next(P);
  }
  /* i == n || fail */
  if (fail) {
    DelAll(L1);
    DelAll(L2);
  }
}
