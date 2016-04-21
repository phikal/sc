
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "scl.h"
#include "cfunc.h"

// VALUE PRINTING
void printval(FILE *f, VAL *n, int ind);

void printnode(FILE *f, ND *n, int ind) {
  if (n == NULL)
    return printval(f, NULL, ind);
  
  if (n->head == NULL && n->tail == NULL)
    fprintf(f, "x - ");
  else if (n->head != NULL && n->head->type == NODE)
    fprintf(f, "O - ");
  else
    fprintf(f, "o - ");
  
  printval(f, n->head, ind+1);
  fprintf(f, "\t(%p)\n", n->head);
  for (int i = 0; i < ind; i++) fprintf(f, "  ");
  fprintf(f, "L ");
  if (n->tail != NULL)
    printnode(f, n->tail, ind+1);
  else
    printval(f, NULL, ind);
}

void printval(FILE *f, VAL *v, int ind) {
  if (v == NULL)
    fprintf(f, "NULL");
  else if (v->type == SCALAR)
    fprintf(f, "%Lf", v->val.v);
  else if (v->type == NODE)
    printnode(f, v->val.n, ind+1);
  else if (v->type == CFUNC)
    fprintf(f, "[build in function]");
  else if (v->type == LFUNC) {
    fprintf(f, "[lisp function]:");
    printnode(f, v->val.n, ind+1);
  } else if (v->type == SYMBOL)
    fprintf(f, "'%s", v->val.s);
  else if (v->type == VARIAB)
    fprintf(f, "v: %s ", v->val.s);
  else fprintf(f, "INVALID");
}

// VALUE TREE
VAL *get_vt(VT *tr, char *key) {
  if (tr != NULL) {
    if (strcmp(key, tr->name) == 0)
      return tr->val;
    else if (strcmp(key, tr->name) <  0)
      return get_vt(tr->l_val, key);
    else if (strcmp(key, tr->name) >  0)
      return get_vt(tr->r_val, key);
  } return NULL;
}

VAL *get(ND *n, char *key) {
  VAL *v = get_vt(n->varib, key);
  if (v == NULL)
    return get(n->parent, key);
  return v;
}

VT *put(VT *tr, VAL *val, char *key) {
  if (tr == NULL) {
    tr = (VT *) calloc(1,  sizeof(VT));
    tr->name = key;
  }

  if (strcmp(tr->name, key) == 0)
    tr->val = val;
  else if (strcmp(tr->name, key) < 0)
    tr->l_val = put(tr->l_val, val, key);
  else if (strcmp(tr->name, key) > 0)
    tr->r_val = put(tr->r_val, val, key);
  return tr;
}

void put_sc(ND *n, double val, char *key) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = SCALAR;
  v->val.v = val;
  n->varib = put(n->varib, v, key);
}

void put_nd(ND *n, ND *val, char *key) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = NODE;
  v->val.n = val;
  n->varib = put(n->varib, v, key);
}

void put_sym(ND *n, char *val, char *key) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = SYMBOL;
  v->val.s = val;
  n->varib = put(n->varib, v, key);
}

void put_cf(ND *n, FUNC *val, char *key) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = CFUNC;
  v->val.f = val;
  n->varib = put(n->varib, v, key);
}

void put_lf(ND *n, ND *val, char *key) {
  VAL *v = (VAL *) calloc(1, sizeof(VAL));
  v->type = LFUNC;
  v->val.n = val;
  n->varib = put(n->varib, v, key);
}

void put_var(ND *n, char *val, char *key) {
  VAL *v = calloc(1, sizeof(VAL));
  v->type = VARIAB;
  v->val.s = val;
  n->varib = put(n->varib, v, key);
}

// EVAL
/* FILE *findscript(char *name) { */
/*   char *dup = strdup(getenv("SCPATH")); */
/*   char *s = dup; */
/*   char *p = NULL; */
/*   do { */
/*     p = strchr(s, ':'); */
/*     if (p != NULL) { */
/*       p[0] = 0; */
/*     } */
/*     printf("Path in $PATH: %s %d\n", s, strcmp(s, name)); */
/*     s = p + 1; */
/*   } while (p != NULL); */
/*   free(dup); */
/*   return NULL; */
/* } */

ND *eval(char *prog, long len) {
  ND *r = (ND *) calloc(1, sizeof(ND)), // root,
    *n = r->parent = r->group = r;  // current node

  // default keywords and values
  put_cf(r, *evalf, "eval");
  put_cf(r, *loadf, "load");

  put_cf(r, *car, "car");
  put_cf(r, *cdr, "cdr");
  put_cf(r, *def, "def");
  put_cf(r, *lambda, "lambda");
  put_cf(r, *lambda, "\\");
  
  put_cf(r, *sum, "+");
  put_cf(r, *sub, "-");
  put_cf(r, *fac, "*");
  put_cf(r, *quo, "/");
  
  put_cf(r, *eqp, "=");
  put_cf(r, *eqp, "<");
  put_cf(r, *eqp, ">");
  
  put_cf(r, *ife, "if");
  put_cf(r, *and, "and");
  put_cf(r, *or, "or");
  put_cf(r, *not, "not");

  enum {        // Possible parsing modes:
    GEN,    // General
    NUM,    // In number
    SYM,    // In symbol
    VAR     // In variable (anything else)
  } mode = GEN; // current mode

  unsigned int
    line = 1,   // line in file
    col = 1,    // collumn in file
    depth = 0;
  char *c = prog;
  while (c++ < prog+len) {
    if (*c == '\n') { // update position
      line++; col = 1;
    } else col++;

    if (*c == ';') { // start comment
      while (*(++c) != '\n');
      mode = GEN;
      continue;
    }
    
    if (mode == GEN) {
      if (isspace(*c)) continue; // ignore whitespace
      // printf("==> `%c` (%p)\n", *c, c);

      if (*c == '(') {
	ND *f = (ND *) calloc(1, sizeof(ND));
	VAL *v = (VAL *) calloc(1, sizeof(VAL));
        f->parent = f->group = n;
	v->type = NODE;
	v->val.n = f;
	n->head = v;
	
	for (int i = 0; i < (int) depth; i++) printf("  ");
	printf("+ %p\tadded head to %p,\tin  %p\n", f, n->group, n);
	
	n = f;
	depth++;
      } else if (*c == ')') { depth--;
	ND *f = (ND *) calloc(1, sizeof(ND));
	f->parent = n->group;
	f->group = n->group->group;
	
	for (int i = 0; i < (int) depth; i++) printf("  ");
	printf("- %p\tkilled with tail to %p,\tend %p\n", f, n->group, n);

	n->parent->tail = NULL;
	n = n->group->tail = f;
      } else if (*c == '\'') {
	mode = SYM;
      } else if (isdigit(*c) || (*c == '-' && isdigit(*(c+1)))) {
	mode = NUM;
	c--;
      } else {
	mode = VAR;
	c--;
      }
    } else {
      char *s = c; // segment
      do
      	if (s >= prog+len) {
      	  fprintf(stderr, "l%d, r%d: expression not ended\n", line, col);
	  return NULL;
	} else s++;
      while (*s != ')' && *s != '(' && !isspace(*s));
      
      char *q = calloc(s-c, sizeof(char));
      strncpy(q, c, s-c);

      for (int i = 0; i < (int) depth; i++) printf("  ");
      VAL *v = (VAL *) calloc(1, sizeof(VAL));
      if (mode == VAR) {
	v->type = VARIAB;
	v->val.s = q;
	printf("v");
      } else if (mode == SYM) {
	v->type = SYMBOL;
	v->val.s = q;
	printf("s");
      } else if (mode == NUM) {
	char *m;
	long double n = strtold(q, &m);
	if (q == m) {
	  fprintf(stderr, "l%d, r%d: \"%s\" inv. number\n", line, col, q);
	  return NULL;
	}
	v->type = SCALAR;
	printf("n");
	v->val.v = n;
      }

      n->head = v;
      ND *f = (ND *) calloc(1, sizeof(ND));
      f->parent = n;
      f->group = n->group;

      printf(" %p\t`%s` as tail to %p,\tval %p\n", f, q, n, v);
      n = n->tail = f;

      c = s-1;
      mode = GEN;;
    }
  }

  n->parent->tail = NULL;
  return r;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "no file specified\n");
    return 1;
  }

  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "%s: `%s` not found\n", argv[0], argv[1]);
    return 3;
  }
  fseek (f, 0, SEEK_END);
  long len = ftell(f);
  fseek (f, 0, SEEK_SET);

  char *prog, *p;
  if ((p = prog = malloc(len)))
    while (p++ < prog+len) *p = fgetc(f);
  else {
    fprintf(stderr, "%s: alloc error\n", argv[0]);
    return 4;
  }
  fclose (f);
  
  ND *n = eval(prog, len);
  free(prog);
  printf("\n");
  printnode(stdout, n, 0);
  fprintf(stdout, "\n");
}
