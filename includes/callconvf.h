/*======================================
       H file for callconvf module
	 
========================================*/

#ifndef _CALLCONVF_H
#define _CALLCONVF_H

#include "wam_unit.h"

void cprint(int verbose, const char *ct_str, char vtype, void *val);
void callconvf(unit_t *in, unit_t *out, char *val, char *precision, int verbose);
unit_t *in_process(char *opt_val, unit_t **all_units, int au_len);
unit_t *out_process(char *opt_val, unit_t **all_units, int au_len);
int chk_val(char *val, char input);


#endif /* _CALLCONVF_H */



