/* test marg */

#include <stdio.h>
#include <stdlib.h>
#include "marg.h"



int main(int argc, char *argv[]){

	printf("starting marg test...\n");

	int i;


	/*
	//print all input arguments	
	//=========================

	printf("All argv args:\n");
	int i;
	for (i=0; i<argc; i++)
	{ 
		printf("arg num:%d  arg:%s, \n", i, argv[i]);
	}*/




	// create option arrays
	char shopt[] = {'e', 'm', 'n'};
	char *longopt[] = {"elend", "matrix", "nuendo"};
	short int has_operand[] = {0, 1, 1};
	size_t n_opt = 3;
	
	margstructs all_options = marg("marg_test", argc, argv, n_opt, shopt, longopt, has_operand);


	/*
	//print all options
	//=================

	for (i=0; i<n_opt; i++)
	{ 
		printf("option id %d, \n", all_options[i]->id);
		printf("long option %s, \n", all_options[i]->long_option);
		printf("option %c, \n", all_options[i]->short_option);
		printf("option has arg %d, \n\n", all_options[i]->has_arg);
	}
	*/


	// loop through options
	int j;
	for (i=0; i<n_opt; i++)
	{ 
		printf("option called bit = %d, \n", all_options[i]->called);
		if (all_options[i]->called == 1){
			printf("calling option %s with operand %s, \n", all_options[i]->long_option, all_options[i]->operand);
		}
	}

	
	
	margfree(all_options, n_opt);


	return 1;  

}
































































