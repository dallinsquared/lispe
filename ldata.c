#include <stdlib.h>
#include "ldata.h"

typedef struct Symbol {
	char *s;
	Symbol next;
	Sexp data;
} *Symbol;

typedef struct Cons {
	Sexp car, cdr;
	int ref;
} *Cons;

typedef struct Func {
	int arity;
	int var;
	Sexp params;
	Sexp body;
}

typedef struct Sexp {
	Type t;
	int ref;
	union {
		int n;
		char c;
		Symbol sy;
		char *st;
		Cons c;
		Func f;
	} v;
} *Sexp;

Sexp
bindcons(Cons c) {
	Sexp s = malloc(sizeof (struct Sexp));
	s->t = Cns;
	s->v.c = c;
	return s;
}

Sexp
newsexp(Type t) {
	Sexp s = malloc(sizeof (struct Sexp));
	s->t = t;
	return s;
}

Sexp
bindnum(int n) {
	Sexp s = newsexp(Num);
	s->v.n = n;
	return s;
}

Sexp
bindchar(char c) {
	Sexp s = newsexp(Char);
	s->v.c = c;
	return s;
}

Sexp
bindstr(char *st) {
	Sexp s = newsexp(Str);
	char *ns = malloc(sizeof(char)*strlen(st));
	s->v.st = ns;
	return s;
}

Sexp
bindsym(Symbol sy) {
	Sexp s = newsexp(Sym);
	s->v.sy = sy;
	return s;
}

Sexp
bindfn(Func f) {
	Sexp s = newsexp(Fn);
	s->v.f = f;
	return s;
}

void
unreference(Sexp s) {
	--(s->ref) < 1 ? freesexp(s);
}

void
refer(Sexp s) {
	(s->ref)++;
}

void
freesexp(Sexp s) {
	switch (s->t) {
	case Str:
		free(s->v.st);
	case Cns:
		unreference(s->v.c->car); //--(s->v.c->car->ref) < 1 ? freesexp(s->v.c->car) : 0;
		unreference(s->v.c->cdr); //--(s->v.c->cdr->ref) < 1 ? freesexp(s->v.c->cdr) : 0;
		free(s->v.c);
	}
	free(s);
}

Sexp
cons(Sexp car, Sexp cdr) {
	Cons c = malloc(sizeof (struct Cons));
	refer(car);
	refer(cdr);
	c->car = car;
	c->cdr = cdr;
	return bindcons(c);
}

Sexp
car(Sexp s) {
	Sexp c = s->v.c->car;
	unreference s;
	return c;
}

Sexp
cdr(Sexp s) {
	Sexp c = s->v.c->cdr;
	unreference s;
	return c;
}

unsigned int
hashstr(char *s, int hsize) {
	unsigned int num = 1;
	char *temp = s;
	for(char *temp = s; *temp != '\0'; temp++) {
		num *= (int)(*temp);
	}
	num %= 1500007;
	unsigned int mask = -1;
	mask <<= hsize;
	mask = ~mask;
	return num & mask;
}

