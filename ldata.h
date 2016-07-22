typedef struct Symbol *Symbol;
typedef struct Cons *Cons;
typedef struct Sexp *Sexp;
typedef struct Func *Func;
typedef enum Types {Num, Char, Sym, Str, Cns, Fn} Type;

Sexp newsexp(AType t);
Sexp bindnum(int n);
Sexp bindchar(char c);
Sexp bindsym(Symbol s);
Sexp bindcons(Cons c);

void unreference(Sexp s);
void freesexp(Sexp s);

Sexp cons(Sexp car, Sexp cdr);
Sexp car(Sexp s);
Sexp cdr(Sexp s);
unsigned int hashstr(char *s, int hsize);
