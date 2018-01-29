/*======================================
	         - conv -
	General purpose converter

	Author: Marko Pantelic
========================================*/


#include <stdio.h>
#include <stdlib.h>
#include "marg.h"
#include "callconvf.h"



void print_usage()
{
	
	printf("Usage: conv [OPTION]... [VALUE]...\n" \
	       "convert VALUE(s) according to OPTION(s) set,\n" \
	       "and print them to standard output.\n" \
	       "\t-h, --help\t\n" \
	       "\t-i, --input\t\n" \
	       "\t-o, --output\t\n" \
	       "\t-p, --precision\t\n" \
	       "\t-v, --verbose\t\n" \
	       "\t-n, --value\t\n" ); 
}



int main(int argc, char* argv[])
{

	int i, verbose;
	char short_opt, in, out, valtmp[1], *val, *operand, *precision; 

	in = out = valtmp[0] = '\0';
	val = valtmp;
	verbose = 0; /* default set not to be verbose */
	precision = "2"; /* default precision */


	if (argc < 2){
		print_usage();
		exit(EXIT_SUCCESS);
	}

	/* marg setup */
	char shopt[] = {'h', 'v', 'i', 'o', 'p', 'n'};
	char *longopt[] = {"help", "verbose", "input", "output", "precision", "value"};
	short int has_operand[] = {0, 0, 1, 1, 1, 1};
	size_t n_opt = 6;
	
	margstructs options = margcreate("conv", argc, argv, n_opt, shopt, longopt, has_operand);


	/* loop through options */
	for (i=0; i<n_opt; i++){ 

		if (options[i]->called == 1){

			short_opt = options[i]->short_option;
			operand = options[i]->operand;

			/* Situation when `has_operand` member is set to 1 but no operand is given */
			if (options[i]->has_operand == 1 && options[i]->operand == NULL){
				printf("operand required for '%c'\n", options[i]->short_option);
				exit(EXIT_FAILURE);				
			}
			
	
			if (short_opt == 'i'){
				in = in_process(operand);
			}
			else if (short_opt == 'o'){
				out = out_process(operand);
			}
			else if (short_opt == 'n'){
				val = operand;
			}
			else if (short_opt == 'p'){
				precision = operand;
			}
			else if (short_opt == 'v'){
				verbose = 1;
			}
			else if (short_opt == 'h'){
			/* silently ignore this option if it's not the only one given */
				if (argc == 2){
					print_usage();
					exit(EXIT_SUCCESS);
				}
			}
			else{
				printf("option '%c' not obtainable\n", short_opt);
				exit(EXIT_FAILURE);
			}
			
		}
	}


	if (in == '\0' || out == '\0'){
		fprintf(stderr, "'input' and 'output' argument values required\n");
		exit(EXIT_FAILURE);
	}
	if (val[0] == '\0'){
		fprintf(stderr, "'value' argument value required\n");
		exit(EXIT_FAILURE);
	}

	if (chk_val(val, in) == -1){
		fprintf(stderr, "invalid input value \"%s\"\n", val);
		exit(EXIT_FAILURE);

	}

	callconvf(in, out, val, precision, verbose);
	
	margfree(options, n_opt);
	
	return 0;
}




