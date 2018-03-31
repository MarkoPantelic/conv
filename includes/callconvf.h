/*======================================
       H file for callconvf module
	 
========================================*/

#ifndef _CALLCONVF_H
#define _CALLCONVF_H

#include "unit.h"

void cprint(int verbose, const char *ct_str, char vtype, void *val);
void callconvf(unit_t *in, unit_t *out, char *val, char *precision, int verbose);
unit_t *in_process(char *opt_val, unit_t *head_node);
unit_t *out_process(char *opt_val, unit_t *head_node);
int chk_val(char *val, int unit_system, int unit_id);


#endif /* _CALLCONVF_H */



