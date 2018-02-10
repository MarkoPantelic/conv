/*=========================================
	h file for nsconv.c module 
	Numeral system conversions	
===========================================*/

#ifndef _NS_CONV_H
#define _NS_CONV_H

#include "wam_unit.h"

extern const char BIN[];
extern const char OCT[];
extern const char DEC[];
extern const char HEX[];

extern int BIN_ID;
extern int OCT_ID;
extern int DEC_ID;
extern int HEX_ID;

unit_t **mknsunits(int *ns_len);

char *sbin_to_shex(const char *num_str, char repr);
char *sbin_to_soct(const char *num_str);
int sbin_to_dec(const char *num_str);

short *dec_to_binarr(const char *num_str, int *width, int *hb1_pos);
char *dec_to_shex(int dec, char repr);
char *dec_to_soct(int dec);
char *dec_to_sbin(int dec, int *width, char repr);

char *sdec_to_shex(const char *num_str, char repr);
char *sdec_to_soct(const char *num_str);
char *sdec_to_sbin(const char *num_str, char repr);

int shex_to_dec(const char *str_hex);
char *shex_to_sbin(const char *str_hex, char repr);
char *shex_to_soct(const char *str_hex);

int soct_to_dec(const char *str_oct);
char *soct_to_sbin(const char *str_oct, char repr);
char *soct_to_shex(const char *str_oct, char repr);

#endif /* define _NS_CONV_H */


