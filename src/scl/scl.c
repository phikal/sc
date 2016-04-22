
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
#include "vtree.h"
#include "snode.h"

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

      if (*c == '(') {
	ND *f = (ND *) calloc(1, sizeof(ND));
	VAL *v = (VAL *) calloc(1, sizeof(VAL));
        f->parent = f->group = n;
	v->type = NODE;
	v->val.n = f;
	n->head = v;
	
	n = f;
	depth++;
      } else if (*c == ')') { depth--;
	ND *f = (ND *) calloc(1, sizeof(ND));
	f->parent = n->group;
	f->group = n->group->group;

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

      VAL *v = (VAL *) calloc(1, sizeof(VAL));
      if (mode == VAR) {
	v->type = VARIAB;
	v->val.s = q;
      } else if (mode == SYM) {
	v->type = SYMBOL;
	v->val.s = q;
      } else if (mode == NUM) {
	char *m;
	long double n = strtold(q, &m);
	if (q == m) {
	  fprintf(stderr, "l%d, r%d: \"%s\" inv. number\n", line, col, q);
	  return NULL;
	}
	v->type = SCALAR;
	v->val.v = n;
      }

      n->head = v;
      ND *f = (ND *) calloc(1, sizeof(ND));
      f->parent = n;
      f->group = n->group;
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

  /* printnode(stdout, n, 0); */
  /* fprintf(stdout, "\n"); */
}
