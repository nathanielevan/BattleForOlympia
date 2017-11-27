#include "Point.h"

int main() {
	Point p;
	int x, y;

	printf("Input X and Y\n");
	scanf("%d %d", &x, &y);
	p = MakePoint(x, y);

	Point p2 = p;

	if (EQ(p, p2)) 
		

	return 0;
}