/*=========================================
	h file for nsconv.c module
	Numeral system conversions
===========================================*/

#ifndef _NS_CONV_H
#define _NS_CONV_H

#include "unit.h"

extern const char BIN[];
extern const char OCT[];
extern const char DEC[];
extern const char HEX[];

//extern const int BIN_ID, OCT_ID, DEC_ID, HEX_ID;
enum { BIN_ID, DEC_ID, OCT_ID, HEX_ID };

unit_t *ns_list(unit_t **tail);

char *sbin_to_shex(const char *num_str, char repr);
char *sbin_to_soct(const char *num_str);
int sbin_to_dec(const char *num_str);

short *dec_to_binarr(int num, int *bit_width, int *hb1_pos);
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

char *shex_to_srgb(char *str_hex);
char *srgb_to_shex(char *str_rgb);

#endif /* define _NS_CONV_H */
