
typedef struct senode ND;
typedef struct vtree VT;
typedef struct value VAL;
typedef VAL *(FUNC)(ND *n);
typedef struct lambda LBD;


// VALUE TREE
struct vtree {
  char *name;
  VAL *val;
  VT *r_val, *l_val;
};

// S-EXPRESSION VALUE
struct value {
  enum {
    SCALAR,
    NODE,
    SYMBOL,
    CFUNC,
    LFUNC,
    VARIAB
  } type;
  union {
    long double v;
    ND *n;
    char *s;
    LBD *l;
    FUNC *f;
  } val;
};

// S-EXPRESSION NODE
struct senode {
  VT *varib;
  VAL *head;
  ND *parent, *tail, *group;
};

// LAMBDA FUNCTION
struct lambda {
  char **params;
  int pcount;
  ND *body;
};
