/* Driver dari Time untuk pengecekan yang hanya ada di program utama */

#include <stdio.h>
#include <time.h>
#include "Time.h"

int main() {
	Time time;
	short year;
	char month;
    char day;
    char hh; /* integer [0..23] */
    char mm; /* integer [0..59] */
    char ss; /* integer [0..59] */

	printf("Input time right now ! (Year Month Day hh mm ss) \n");
	scanf("%hd %hhd %hhd %hhd %hhd %hhd", &year, &month, &day, &hh, &mm, &ss);
	while (isTimeValid(year, month, day, hh, mm, ss)) {
		printf("Input time right now ! (Year Month Day hh mm ss) \n");
		scanf("%hd %hhd %hhd %hhd %hhd %hhd", &year, &month, &day, &hh, &mm, &ss);
	}
	time = makeTime(year, month, day, hh, mm, ss);
	writeDate(time); printf("\n");
	writeTime(time); printf("\n");

	Time timeNow = getCurrentTime();
	writeDate(timeNow); printf("\n");
	writeTime(timeNow); printf("\n");

}