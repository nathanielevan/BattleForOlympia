/*
  Driver hanya melakukan fungsi yang dijalankan pada permainan
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Point.h"

int main() {
  Point p;
  int x, y;

  printf("Masukan besaran x dan y! \n");
  scanf("%d %d", &x, &y);
  p = MakePoint(x,y);
  printf("Anda berada pada (%d,%d) \n", absis(p), ordinat(p));
  Point p2 = PlusDelta(p, 1, 2);
  printf("Sekarang anda berada pada (%d,%d) \n", absis(p2), ordinat(p2));
  return 0;
}