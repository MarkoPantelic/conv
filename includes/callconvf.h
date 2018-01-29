/*======================================
       H file for callconvf module
	 
========================================*/

#ifndef _CALLCONVF_H
#define _CALLCONVF_H

void cprint(int verbose, const char *ct_str, char vtype, void *val);
void callconvf(char in, char out, char *val, char *precision, int verbose);
int in_process(char *opt_val);
int out_process(char *opt_val);
int chk_val(char *val, char input);


#endif /* _CALLCONVF_H */



