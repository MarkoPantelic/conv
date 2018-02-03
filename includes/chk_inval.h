/*
 * Check functions used for checking input values
 * All functions return 1 if input value is valid
 */

#ifndef _CHK_INVAL_H
#define _CHK_INVAL_H

int hex_prfx_chk(const char *hex_str);
int chksoct(const char *val);
int chkshex(const char *val);
int chksdec(const char *val);
int chksbin(const char *val);
int chksfloat(const char *val);

#endif /* _CHK_INVAL_H */

