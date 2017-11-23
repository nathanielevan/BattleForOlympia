#include "WordMachine.h"
#include <ctype.h>

/* State Mesin Kata */
boolean wmEnd;
wmWord wmCWord;

void wmIgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
{
    /* Algoritma */
    while (isspace(cmCC) && !cmEOT)
        cmAdv();
}

void wmStart(FILE *tape)
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    /* Algoritma */
    cmStart(tape);
    /* Abaikan blank di awal pita */
    wmIgnoreBlank();
    if (!cmEOT)
        wmConsumeWord(); /* akan berhenti satu karakter setelah akhir kata */
    else
        wmEnd = true;
}

void wmAdv()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
    /* Algoritma */
    wmIgnoreBlank();
    if (!cmEOT) {
        wmConsumeWord();
        wmIgnoreBlank(); /* maju ke kata berikutnya */
    } else {
        wmEnd = true;
    }
}

void wmConsumeWord()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    /* Kamus lokal */
    int i;
    /* Algoritma */
    for (i = 0; i < WM_NMax && !isspace(cmCC) && !cmEOT; i++) {
        wmCWord.buf[i] = cmCC;
        cmAdv();
    }
    wmCWord.len = i;
}
