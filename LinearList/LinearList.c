/* File: listlinier.c
 * NIM            : 13516103
 * Nama           : Gerardus Samudra S.
 * Tanggal        : 2017-10-27
 * Topik praktikum: ADT llList Linier
 * Deskripsi      : Implementasi ADT list berkait dengan representasi
 *                  fisik pointer
 */

#include "LinearList/LinearList.h"
#include <stdlib.h>
#include <stdio.h>

/****************** TEST LIST KOSONG ******************/
boolean llIsEmpty (llList L)
/* Mengirim true jika list kosong */
{
    /* Algoritma */
    return llFirst(L) == Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void llCreateEmpty (llList *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    /* Algoritma */
    llFirst(*L) = Nil;
}

/****************** Manajemen Memori ******************/

lladdress llAlokasi (llInfoType X)
/* Mengirimkan lladdress hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka lladdress tidak nil, dan misalnya */
/* menghasilkan P, maka llInfo(P)=X, llNext(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    /* Kamus lokal */
    lladdress P;
    /* Algoritma */
    P = (llElmtList *) malloc(sizeof(llElmtList));
    if (P != Nil) {
        llInfo(P) = X;
        llNext(P) = Nil;
    }
    return P;
}

void llDealokasi (lladdress *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian lladdress P */
{
    /* Algoritma */
    free(*P);
    *P = Nil;
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/

lladdress llSearch (llList L, llInfoType X)
/* Mencari apakah ada elemen list dengan llInfo(P)= X */
/* Jika ada, mengirimkan lladdress elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    /* Kamus lokal */
    lladdress P;
    /* Algoritma */
    for (P = llFirst(L); P != Nil && llInfo(P) != X; P = llNext(P))
        ;
    /* P == Nil || llInfo(P) == X */
    return P;
}

boolean llFSearch (llList L, lladdress P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
    /* Kamus lokal */
    lladdress Q;
    /* Algoritma */
    for (Q = llFirst(L); Q != Nil && Q != P; Q = llNext(Q))
        ;
    /* Q == Nil || Q == P */
    return Q == P;
}

lladdress llSearchPrec (llList L, llInfoType X)
/* Mengirimkan lladdress elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan llInfo(P)=X */
/* Jika ada, mengirimkan lladdress Prec, dengan llNext(Prec)=P dan llInfo(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
{
    /* Kamus lokal */
    lladdress P, pred;
    /* Algoritma */
    pred = Nil;
    for (P = llFirst(L); P != Nil && llInfo(P) != X; P = llNext(P))
        pred = P;
    /* P == Nil || llInfo(P) == X */
    if (P != Nil)
        return pred;
    else
        return Nil;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/

/*** PENAMBAHAN ELEMEN ***/

void llInsVFirst (llList *L, llInfoType X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    /* Kamus lokal */
    lladdress P;
    /* Algoritma */
    P = llAlokasi(X);
    if (P != Nil)
        llInsertFirst(L, P);
}

void llInsVLast (llList *L, llInfoType X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    /* Kamus lokal */
    lladdress P;
    /* Algoritma */
    P = llAlokasi(X);
    if (P != Nil)
        llInsertLast(L, P);
}

/*** PENGHAPUSAN ELEMEN ***/

void llDelVFirst (llList *L, llInfoType *X)
/* I.S. llList L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai llInfo disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    /* Kamus lokal */
    lladdress P;
    /* Algoritma */
    llDelFirst(L, &P);
    *X = llInfo(P);
    llDealokasi(&P);
}

void llDelVLast (llList *L, llInfoType *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai llInfo disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    /* Kamus lokal */
    lladdress P;
    /* Algoritma */
    llDelLast(L, &P);
    *X = llInfo(P);
    llDealokasi(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/

/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/

void llInsertFirst (llList *L, lladdress P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-lladdress P sebagai elemen pertama */
{
    /* Algoritma */
    llNext(P) = llFirst(*L);
    llFirst(*L) = P;
}

void llInsertAfter (llList *L, lladdress P, lladdress Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    /* Algoritma */
    llNext(P) = llNext(Prec);
    llNext(Prec) = P;
}

void llInsertLast (llList *L, lladdress P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    /* Kamus lokal */
    lladdress pred;
    /* Algoritma */
    pred = llFirst(*L);
    if (pred == Nil) {
        llInsertFirst(L, P);
    } else {
        while (llNext(pred) != Nil)
            pred = llNext(pred);
        llNext(pred) = P;
    }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/

void llDelFirst (llList *L, lladdress *P)
/* I.S. llList tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* llFirst element yg baru adalah suksesor elemen pertama yang lama */
{
    /* Algoritma */
    *P = llFirst(*L);
    llFirst(*L) = llNext(*P);
    llNext(*P) = Nil;
}

void llDelP (llList *L, llInfoType X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list berlladdress P, dengan llInfo(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan llInfo(P)=X, maka list tetap */
/* llList mungkin menjadi kosong karena penghapusan */
{
    /* Kamus lokal */
    lladdress pred, P;
    /* Algoritma */
    pred = Nil;
    for (P = llFirst(*L); P != Nil && llInfo(P) != X; P = llNext(P))
        pred = P;
    /* P == Nil | llInfo(P) == X */
    if (P != Nil) { /* => llInfo(P) == X */
        if (pred == Nil) /* P elemen pertama */
            llFirst(*L) = llNext(P);
        else /* pred dan P berbeda */
            llNext(pred) = llNext(P);
        llDealokasi(&P);
    }
}

void llDelLast (llList *L, lladdress *P)
/* I.S. llList tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
    /* Kamus lokal */
    lladdress pred, last;
    /* Algoritma */
    pred = Nil;
    for (last = llFirst(*L); llNext(last) != Nil; last = llNext(last))
        pred = last;
    /* llNext(last) == Nil */
    if (pred == Nil) { /* Menghapus elemen pertama */
        llDelFirst(L, P);
    } else  { /* Ada elemen pred */
        llNext(pred) = Nil;
        llNext(last) = Nil;
        *P = last;
    }
}

void llDelAfter (llList *L, lladdress *Pdel, lladdress Prec)
/* I.S. llList tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus llNext(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
    /* Algoritma */
    *Pdel = llNext(Prec);
    /* WHAT IF *Pdel == Nil? */
    llNext(Prec) = llNext(*Pdel);
    llNext(*Pdel) = Nil;
}

/****************** PROSES SEMUA ELEMEN LIST ******************/

void llPrintInfo (llList L)
/* I.S. llList mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    /* Kamus lokal */
    lladdress P;
    boolean llFirst = true;
    /* Algoritma */
    putchar('[');
    for (P = llFirst(L); P != Nil; P = llNext(P)) {
        if (!llFirst)
            putchar(',');
        else
            llFirst = false;
        printf("%ld", llInfo(P));
    }
    putchar(']');
}

int llNbElmt (llList L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    /* Kamus lokal */
    int n = 0;
    lladdress P;
    /* Algoritma */
    for (P = llFirst(L); P != Nil; P = llNext(P))
        n++;
    return n;
}

/*** Prekondisi untuk Max/Min/rata-rata : llList tidak kosong ***/

llInfoType llMax (llList L)
/* Mengirimkan nilai llInfo(P) yang maksimum */
{
    /* Kamus lokal */
    lladdress P;
    /* Algoritma */
    P = llAdrMax(L);
    return llInfo(P);
}

lladdress llAdrMax (llList L)
/* Mengirimkan lladdress P, dengan llInfo(P) yang bernilai maksimum */
{
    /* Kamus lokal */
    llInfoType max;
    lladdress P, maxP;
    /* Algoritma */
    P = llFirst(L);
    max = llInfo(P);
    maxP = P;
    for (P = llNext(P); P != Nil; P = llNext(P)) {
        if (llInfo(P) > max) {
            max = llInfo(P);
            maxP = P;
        }
    }
    return maxP;
}

llInfoType llMin (llList L)
/* Mengirimkan nilai llInfo(P) yang minimum */
{
    /* Kamus lokal */
    lladdress P;
    /* Algoritma */
    P = llAdrMin(L);
    return llInfo(P);
}

lladdress llAdrMin (llList L)
/* Mengirimkan lladdress P, dengan llInfo(P) yang bernilai minimum */
{
    /* Kamus lokal */
    llInfoType min;
    lladdress P, minP;
    /* Algoritma */
    P = llFirst(L);
    min = llInfo(P);
    minP = P;
    for (P = llNext(P); P != Nil; P = llNext(P)) {
        if (llInfo(P) < min) {
            min = llInfo(P);
            minP = P;
        }
    }
    return minP;
}

float llAverage (llList L)
/* Mengirimkan nilai rata-rata llInfo(P) */
{
    /* Kamus lokal */
    float sum = 0.0f;
    unsigned n = 0;
    lladdress P;
    /* Algoritma */
    for (P = llFirst(L); P != Nil; P = llNext(P), ++n)
        sum += llInfo(P);
    return sum / n;
}

/****************** PROSES TERHADAP LIST ******************/

void llDelAll (llList *L)
/* Delete semua elemen list dan alamat elemen di-dealokasi */
{
    /* Kamus lokal */
    lladdress P;
    /* Algoritma */
    while (llFirst(*L) != Nil) {
        llDelFirst(L, &P);
        llDealokasi(&P);
    }
}

void llInversList (llList *L)
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
{
    /* Kamus lokal */
    lladdress P, pred, succ;
    /* Algoritma */
    pred = Nil;
    succ = llFirst(*L);
    while (succ != Nil) {
        P = succ;
        succ = llNext(P);
        llNext(P) = pred;
        pred = P;
    }
    llFirst(*L) = pred;
}

llList llFInversList (llList L)
/* Mengirimkan list baru, hasil invers dari L */
/* dengan menyalin semua elemn list. Alokasi mungkin gagal. */
/* Jika alokasi gagal, hasilnya list kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus didealokasi */
{
    /* Kamus lokal */
    llList L2;
    lladdress P, Q;
    llInfoType X;
    boolean fail = false;
    /* Algoritma */
    llCreateEmpty(&L2);
    for (P = llFirst(L); P != Nil && !fail; P = llNext(P)) {
        X = llInfo(P);
        Q = llAlokasi(X);
        if (Q != Nil)
            llInsertFirst(&L2, Q);
        else
            fail = true;
    }
    /* P == Nil || fail */
    if (fail)
        llDelAll(&L2);
    return L2;
}

void llCopyList (llList *L1, llList *L2)
/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/dealokasi elemen */
{
    /* Asumsi: L2 akan dibuat menunjuk ke list yang sama dengan L1 */
    /* I.S. L2 diasumsikan mengarah ke llList kosong atau tidak terinisialisasi */
    /* Algoritma */
    llFirst(*L2) = llFirst(*L1);
}

llList llFCopyList (llList L)
/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya list kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus didealokasi */
{
    /* Kamus lokal */
    llList L2;
    lladdress P, Q, last;
    llInfoType X;
    boolean fail = false;
    /* Algoritma */
    llCreateEmpty(&L2);
    last = Nil;
    for (P = llFirst(L); P != Nil && !fail; P = llNext(P)) {
        X = llInfo(P);
        Q = llAlokasi(X);
        fail = (Q == Nil);
        if (!fail) {
            /* Lebih hemat dari InsertLast */
            if (last != Nil)
                    llNext(last) = Q;
            else
                llFirst(L2) = Q;
            last = Q;
        }
    }
    /* P == Nil || fail */
    if (fail)
        llDelAll(&L2);
    return L2;
}

void llCpAlokList (llList Lin, llList *Lout)
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
    L = llFCopyList(Lin);
    llCopyList(&L, Lout);
    /* Assignment Lout <- Nil tidak akan berpengaruh pada hasil */
}

void llKonkat (llList L1, llList L2, llList * L3)
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
    lladdress P, Q, last;
    llInfoType X;
    boolean fail = false;
    /* Algoritma */
    llCreateEmpty(L3);
    last = Nil;
    /* Copy elemen L1 */
    for (P = llFirst(L1); P != Nil && !fail; P = llNext(P)) {
        X = llInfo(P);
        Q = llAlokasi(X);
        fail = (Q == Nil);
        if (!fail) {
            if (last != Nil)
                llNext(last) = Q;
            else
                llFirst(*L3) = Q;
            last = Q;
        }
    }
    /* P == Nil || fail */
    /* Copy elemen L2 */
    for (P = llFirst(L2); P != Nil && !fail; P = llNext(P)) {
        X = llInfo(P);
        Q = llAlokasi(X);
        fail = (Q == Nil);
        if (!fail) {
            if (last != Nil)
                llNext(last) = Q;
            else
                llFirst(*L3) = Q;
            last = Q;
        }
    }
    /* P == Nil || fail */
    if (fail) {
        llDelAll(L3);
        /* Assignment L3 <- Nil tidak akan berpengaruh pada hasil */
    }
}

void llKonkat1 (llList *L1, llList *L2, llList *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    /* Kamus lokal */
    lladdress last;
    /* Algoritma */
    llFirst(*L3) = llFirst(*L1);
    llFirst(*L1) = Nil;
    if (llFirst(*L3) == Nil) {
        llFirst(*L3) = llFirst(*L2);
    } else {
        for (last = llFirst(*L3); llNext(last) != Nil; last = llNext(last))
            ;
        llNext(last) = llFirst(*L2);
    }
    llFirst(*L2) = Nil;
}

void llPecahList (llList *L1, llList *L2, llList L)
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2 */
{
    /* Asumsi: Bila alokasi gagal, L1 dan L2 dikosongkan dan semua elemennya
         di-dealokasi */
    /* Kamus lokal */
    lladdress P, Q, last;
    llInfoType X;
    unsigned n, i;
    boolean fail = false;
    /* Algoritma */
    llCreateEmpty(L1);
    llCreateEmpty(L2);
    n = llNbElmt(L);
    P = llFirst(L);
    last = Nil;
    for (i = 0; i < n/2 && !fail; i++) {
        X = llInfo(P);
        Q = llAlokasi(X);
        fail = (Q == Nil);
        if (!fail) {
            if (last != Nil)
                llNext(last) = Q;
            else
                llFirst(*L1) = Q;
            last = Q;
        }
        P = llNext(P);
    }
    /* i == n/2 || fail */
    last = Nil;
    for (; i < n && !fail; i++) {
        X = llInfo(P);
        Q = llAlokasi(X);
        fail = (Q == Nil);
        if (!fail) {
            if (last != Nil)
                llNext(last) = Q;
            else
                llFirst(*L2) = Q;
            last = Q;
        }
        P = llNext(P);
    }
    /* i == n || fail */
    if (fail) {
        llDelAll(L1);
        llDelAll(L2);
    }
}
