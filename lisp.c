#include <stdio.h>
#include "ldata.h"

typedef Sexp (*Reader)(FILE *);
typedef struct RMacro *RMacro;

typedef struct RMacro {
	char d;
	Reader f;
	RMacro next;
} *RMacro;

int
main() {
	for(int c = 0; c != EOF; c = fgetc(stdin)){
		putc(c, stdout);
	}
	return 0;
}
