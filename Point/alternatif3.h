/* alternatif 3 */

#define nil NULL

typedef struct tElmtMK *addressMK;
typedef struct tElmtMK_DOS *addressMK_DOS;
typedef struct tElmtDosen *addressDosen;

typedef struct tElmtMK {
	char* nameMK;
	addressMK_DOS addrMK_DOS;
	addressMK next;
} ElmtMK;

typedef struct tElmtMK_DOS {
	
} ElmtMK_DOS;

typedef struct tElmtDosen {
	char* nameDosen;
	addressMK_DOS addrMK_DOS;
	addressDosen next;
} ElmtDosen;