/*======================================
	    - callconvf module -
	   Call convert functions
========================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> /* for pow() */
#include "nsconv.h"
#include "tempconv.h"
#include "chk_inval.h"
#include "measureconv.h"
#include "wam_unit.h" /* definitions for weight and measure unit_t struct and functions that operate on it */
#include "global_def.h"


#define IN 0
#define OUT 1


/* 
 * Print value pointed by 'val' regardless of it's type.
 * If verbose flag is set, print additional info.
 * 
 */
void cprint(const char *prefix, const char *suffix, char vtype, void *val, char *precision)
{
	char format_str[256];

	sprintf(format_str, "%s%%%c%s\n", prefix, vtype, suffix);

	if (vtype == 's')
		printf(format_str, (char*)val);
	else if (vtype == 'd')
		printf(format_str, *((int *)val) );	
	else if (vtype == 'f'){
		sprintf(format_str, "%s%%0.%s%c %s\n", prefix, precision, vtype, suffix);
		printf(format_str, *((float*)val) );
	}
	else {
		fprintf(stderr, "rprint() -> option '%c' not implemented\n", vtype);
		exit(EXIT_FAILURE);
	}
	

}


void not_implemented()
{
	printf("option not implemented\n");
	exit(EXIT_FAILURE);
}


/* 
 * Call conversion function according to 'in' and 'out' args.  
 * Print result with verbosity in mind.
 */
void callconvf(unit_t *inunit, unit_t *outunit, char *val, char *precision, int verbose)
{

	char type_flag = 's'; /* set for default because string is prevailing return type in 'convert functions' */
	void *ptr_cval;	
	char *prefix = "", *suffix = "";


		/*


		case 'u':
			if (out == 'g'){ // 'a' = avoirdupois system - default for testing
				float gram_value = souncetog(val, TROY_OZ); ptr_cval = &gram_value; type_flag = 'f'; suffix ="g";
			}
			else{
				fprintf(stderr, "invalid 'out' conversion type for 'in' value type\n"); 
				exit(EXIT_FAILURE);
			}
			break;

		case 'g':

			if (out == 'u'){ // 'a' = avoirdupois system - default for testing
				float ounce_value = sgtoounce(val, TROY_OZ); ptr_cval = &ounce_value; type_flag = 'f'; suffix ="oz t";
			}
			else{
				fprintf(stderr, "invalid 'out' conversion type for 'in' value type\n"); 
				exit(EXIT_FAILURE);
			}
			break;

		default:
			fprintf(stderr, "assert switch-case: invalid 'in' argument passed to call_convf()\n");
			exit(EXIT_FAILURE); 
	}
		*/


	char hex_repr = 'U';
	char bin_repr = 'f';
		

	/* call for imperial units */
	
	switch(inunit->system){

		
		case NUMBER_SYS:


			switch(inunit->id){

				case 'b':
					if (outunit->id == 'd'){
						int dec_value = sbin_to_dec(val); ptr_cval = &dec_value; type_flag = 'd'; prefix = "decimal value: ";
					}
					else if (outunit->id == 'o'){
						ptr_cval = sbin_to_soct(val); prefix = "octal value: ";
					}
					else if (outunit->id == 'h'){
						ptr_cval = sbin_to_shex(val, hex_repr); prefix = "hexadecimal value: ";
					}
					else{
						fprintf(stderr, "invalid 'out' conversion type for 'in' value type\n"); 
						exit(EXIT_FAILURE);
					}
					break;

				case 'o':
					if (outunit->id == 'b'){
						ptr_cval = soct_to_sbin(val, bin_repr); prefix = "binary value: ";	
					}
					else if (outunit->id == 'd'){
						int dec_value = soct_to_dec(val); ptr_cval = &dec_value; type_flag = 'd'; prefix = "decimal value:";
					}
					else if (outunit->id == 'h'){
						ptr_cval = soct_to_shex(val, hex_repr); prefix = "hexadecimal value:";	
					}
					else{
						fprintf(stderr, "invalid 'out' conversion type for 'in' value type\n"); 
						exit(EXIT_FAILURE);
					}
					break;

				case 'd':
					if (outunit->id == 'b'){
						ptr_cval = sdec_to_sbin(val, bin_repr); prefix = "binary value:";
					}
					else if (outunit->id == 'o'){
						ptr_cval = sdec_to_soct(val); prefix = "octal value:";
					}
					else if (outunit->id == 'h'){
						ptr_cval = sdec_to_shex(val, hex_repr); prefix = "hexadecimal value: ";
					}
					else{
						fprintf(stderr, "invalid 'out' conversion type for 'in' value type\n"); 
						exit(EXIT_FAILURE);
					}
					break;

				case 'h':
					if (outunit->id == 'b'){
						ptr_cval = shex_to_sbin(val, bin_repr); prefix = "binary value: ";
					}
					else if (outunit->id == 'o'){
						ptr_cval = shex_to_soct(val); prefix = "octal value: ";
					}
					else if (outunit->id == 'd'){
						int dec_value = shex_to_dec(val); ptr_cval = &dec_value; type_flag = 'd'; prefix = "decimal value: ";
					}
					else{
						fprintf(stderr, "invalid 'out' conversion type for 'in' value type\n"); 
						exit(EXIT_FAILURE);
					}
					break;

				default:
					fprintf(stderr, "callconvf() assert switch-case: invalid IMPERIAL_SYS unit_t 'id'\n");
					exit(EXIT_FAILURE); 
			}

			break;
		/* end case NUMBER_SYS */

		case TEMPERATURE:
			
			switch(inunit->id){

				case 'f':
					if (outunit->id == 'c'){
						float cel_value = sfahr_to_cel(val); ptr_cval = &cel_value; type_flag = 'f'; suffix = "C";
					}
					else if (outunit->id == 'k'){
						float kel_value = sfahr_to_kel(val); ptr_cval = &kel_value; type_flag = 'f'; ; suffix = "K";
					}
					else{
						fprintf(stderr, "invalid 'out' conversion type for 'in' value type\n"); 
						exit(EXIT_FAILURE);
					}
					break;

				case 'c':
					if (outunit->id == 'f'){
						float fahr_value = scel_to_fahr(val); ptr_cval = &fahr_value; type_flag = 'f'; suffix = "F";
					}
					else if (outunit->id == 'k'){
						float kel_value = scel_to_kel(val); ptr_cval = &kel_value; type_flag = 'f'; suffix = "K";
					}
					else{
						fprintf(stderr, "invalid 'out' conversion type for 'in' value type\n"); 
						exit(EXIT_FAILURE);
					}
					break;

				case 'k':
					if (outunit->id == 'f'){
						float fahr_value = skel_to_fahr(val); ptr_cval = &fahr_value; type_flag = 'f'; suffix ="F";
					}
					else if (outunit->id == 'c'){
						float cel_value = skel_to_cel(val); ptr_cval = &cel_value; type_flag = 'f'; suffix = "C";
					}
					else{
						fprintf(stderr, "invalid 'out' conversion type for 'in' value type\n"); 
						exit(EXIT_FAILURE);
					}
					break;

				default:
					fprintf(stderr, "callconvf() assert switch-case: invalid TEMPERATURE unit_t 'id'\n");
					exit(EXIT_FAILURE); 
			}

			break;
		/* end case TEMPERATURE */
	
		case IMPERIAL_SYS:

			if(1){
				float cnvval = convert_unit(atof(val), inunit, outunit); ptr_cval = &cnvval; type_flag = 'f'; suffix = outunit->symbol;	
			}
			break;

		default:
			fprintf(stderr, "programer error: call_convf() => inunit->system is unknown!\n");
			exit(EXIT_FAILURE); 
	}

	/* If verbose flag is not set, remove prefix and suffix */
	if (!verbose){
		prefix = ""; suffix = "";	
	}

	cprint(prefix, suffix, type_flag, ptr_cval, precision);
}


/* 
 * Check if values passed to argument 'input' are valid
 * Return first char from string opt_val
 */
unit_t *in_process(char *opt_val, unit_t **all_units, int au_len)
{
	unit_t *in = NULL;
	/*
	const char *lval_list[] = {BIN, DEC, OCT, HEX, KELVIN, FAHRENHEIT, CELSIUS, OUNCE, GRAM};
	const char *rc_list = "bdohkfcug";
	int i, lval_size = 9; 
	int len = strlen(opt_val);
	char fch = opt_val[0]; // opt_val is minimum strlen=1. That is guaranteed by marg	


	for (i=0; i<lval_size; i++){
		
		// compare whole string
		if (len > 1 && strcmp(opt_val, lval_list[i]) == 0){
			return rc_list[i]; 
		} 
		// compare 3 char shortcuts
		if (len == 3 && strncmp(opt_val, lval_list[i], 3) == 0){
			return rc_list[i];
		}
		// compare 1 char
		if ( len == 1 && fch == rc_list[i] ){
			
			switch(fch){

				case 'b': 
					return 'b';
				case 'd':
					return 'd';
				case 'o':
					return 'o';
				case 'h':
					return 'h';
				case 'f':
					return 'f';
				case 'c':
					return 'c';
				case 'k':
					return 'k';
				case 'u':
					return 'u';
				case 'g':
					return 'g';
			}
		}

		
	}
	*/
	in = search_for_unit(opt_val, all_units, au_len);
	
	return in;
	
}


/* Currently same as for in_process() */
unit_t *out_process(char *opt_val, unit_t **all_units, int au_len)
{
	return in_process(opt_val, all_units, au_len);
}


/* 
 * Check input value
 * Call adequate check function from 'chk_inval'
 * depending on input flag
 * Return: chk functions return 1 if valid, -1 if invalid
 */
int chk_val(char *val, char input)
{
	switch(input){
		case 'b':
			return chksbin(val);
		case 'd':
			return chksdec(val);
		case 'o':
			return chksoct(val);
		case 'h':
			return chkshex(val);
		case 'c':
		case 'f':
		case 'k':
		case 'u':
		case 'g':
		case 'q':
			return chksfloat(val);
		default:
			fprintf(stderr, "assert switch-case: case '%c' not found in chk_val()", input);
			exit(EXIT_FAILURE);
	}
}






