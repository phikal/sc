VAL *get(ND *n, char *key);

VT *put(VT *tr, VAL *val, char *key);
void put_sc(ND *n, double val, char *key);
void put_nd(ND *n, ND *val, char *key);
void put_sym(ND *n, char *val, char *key);
void put_cf(ND *n, FUNC *val, char *key);
void put_lf(ND *n, ND *val, char *key);
void put_var(ND *n, char *val, char *key);
