/****************************************************
*			MARG                        *
*	Linux style argument options parsing	    *
*						    *
*  Made to be used as a module by other C programs  *
*						    *
*		Author: Marko Pantelic              *
*****************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "marg.h"


#define OPTION_MAX_STRING_LENGTH 50
#define SHORT_OPTION 0
#define LONG_OPTION 1


char *err_strings[200] = {
			"Valid short option",
			"Valid long option",
			"Invalid short option, missing -",
			"Invalid long option, only one dash(-) supplied",
			"Too many dashes",
			"Short option with two dashes",
			"Option string too long",
			"invalid option argument value",
			"invalid option",
			"unknown option"};



short int opt_syntax_check(char *option)
{
	/* 
		Check if argument option syntax is valid. Returns valid code or error code.
		Checks Linux style argument option. e.g. -a (short) --argument (long)
	*/

	/*
		valid/error codes
		# 0 - valid short option syntax
		# 1 - valid long option syntax
		# 2 - short option missing pre-option dash ('-')
		# 3 - long option missing two pre-option dashes ('--')
		# 4 - too many pre-option dashes
		# 5 - short option with two dashes
		# 6 - option string too long
		# 7 - invalid option argument range (e.g. =100392)
		# 8 - invalid option

	*/

	int option_len = strlen(option);

	if (option_len > OPTION_MAX_STRING_LENGTH)
		return 6;

	// ndash stores number of '-' chars found at the beginning of an option string 
	short int ndash = 0;

	short int i = 0;

	// check if number of dashes ('-') is valid
	for(i=0; i<option_len; i++)
	{

		if (option[i] == '-') 
			ndash++;

		if (ndash == 3)
			return 4; 

		if (i > 4)
			break;  
	} 

	// val of i in if clause is for 1 larger than one think it should, because of /0 char
 
	if (i == 2 && ndash == 1) return (short int)SHORT_OPTION;     

	else if(i > 3 && ndash == 2) return (short int)LONG_OPTION;             

	// operand with one char supplied || operand with more chars supplied
	else if ((i == 1 && ndash == 0) || (i > 1 && ndash == 0)) return 2;

	// long option missing two pre-option dashes
	else if (i > 1 && ndash == 1) return 3;

	// short option with two dashes 
	else if (i == 3 && ndash == 2) return 5;         

	// didn't catch any value/error code. Unknown reason for invalid option 
	else return 8;		

}


char *remove_dash_from_str(char *str, short int val_code)
{
	// remove one or two dashes from string

	short int dash_num = val_code + 1;

	char *nodashstr = malloc(sizeof(char)*OPTION_MAX_STRING_LENGTH);
	
	if (nodashstr == NULL){
		printf("memory allocation error: memory not allocated\n");
		exit(1);
	}

	int i;
	
	// store string without dash/es
	for(i=dash_num; i<strlen(str); i++){
	
		nodashstr[i-dash_num] = str[i];
	}		

	return nodashstr;

}


id opt_exist(char *optstr, p_opt_struct *all_opt, size_t n_all_opt, short int short_or_long_opt)
{
	/*
		Compare string optstr with all option strings from all_opt array of structs
		Return id number of option that exist or return -1 if it doesn't
		Set 'called' member to 1 if option exist

		NOTE: badly done -> free(optstr) call in func on multiple places
	*/

	int i;

	for (i=0; i<n_all_opt; i++){

		char c = '-'; // default value (chosen because optstr cannot contain dash('-') character)

		//convert recognized 'short option as string' to char
		if (short_or_long_opt == SHORT_OPTION){

			c = (char)*optstr;

			if (c==all_opt[i]->short_option){
				all_opt[i]->called = 1;
				free(optstr);
				return all_opt[i]->id;
			}
		}
		else if (short_or_long_opt == LONG_OPTION){

			char *str = all_opt[i]->long_option;

			if (strcmp(str, optstr) == 0){
				all_opt[i]->called = 1;
				free(optstr);
				return all_opt[i]->id;
			}
		}
	}

	free(optstr);

	return -1;
}



short int check_and_store_operand(char *operand, id arg_id, p_opt_struct *all_options, size_t n_all_opt){

	short int res = -1;

	int i;

	for (i=0; i<n_all_opt; i++){

		if (all_options[i]->id == arg_id){

			if (all_options[i]->has_operand == 1){
				all_options[i]->operand = malloc(sizeof(operand));
				strcpy(all_options[i]->operand, operand);
				res = 1;
			}
			else{
				res = -1;
			}
			break;
		}
	}

	
	return res;
}


void check_all_options(char *prog_name, int argc, char **argv, p_opt_struct *all_options, size_t n_all_options)
{
	/* 
		Compare all arguments which were passed by argv with struct all_options 
		which is struct of all program short and long options.
		Return array all_valid_options which contains all valid options option_struct->id 
	*/

	int i;
	id last_arg_id;
	short int prev_it_op = 0; // previous iteration operand. Check this var to disallow two consecutive operand strings 


	for (i=1; i<argc; i++){ //in Linux argc[0] program name
	
		short int osc_code = opt_syntax_check(argv[i]);

		// DEBUG
		//printf("check all options loop num: %d, argv: %s, osc_code = %d\n", i, argv[i], osc_code);

		if (osc_code > 2){
			printf("%s: bad option %s -> %s\n", prog_name, argv[i], err_strings[osc_code]);
			printf("exiting...\n");
			exit(1);
		}

		// argument operand supplied
		if (osc_code == 2){

			if (prev_it_op == 1){
				printf("%s: Two consecutive operand strings not allowed. Use 'operand_str1 operand_str2...'\n", prog_name);
				printf("exiting...\n");
				exit(1);		
			}

			if (i==1){
				printf("%s: Invalid option without dash/es. If operand, it must be supplied after an argument\n", prog_name);
				printf("exiting...\n");
				exit(1);	
			}

			prev_it_op = 1;

			short int res = check_and_store_operand(argv[i], last_arg_id, all_options, n_all_options);
			if (res == -1){
				printf("%s: argument %s does not accept an operand. '%s' supplied\n", prog_name, argv[i-1], argv[i]);
				printf("exiting...\n");
				exit(1);	
			}
			
		}
		else{
			prev_it_op = 0; // restart var

			char *purestr = remove_dash_from_str(argv[i], osc_code);
	
			id res = opt_exist(purestr, all_options, n_all_options, osc_code);
	
			if (res == -1){
				printf("%s: option '%s' -> %s\n", prog_name, argv[i], err_strings[9]);
				printf("exiting...\n");
				exit(1);
			}

			last_arg_id = res;
		}
		
	}

}



p_opt_struct *create_opt_structs(size_t n_opt, char shopt[], char *longopt[], short int has_operand[]){
	/*
		Create array of pointers to option_structs
		Allocate memory for option_struct struct
		Allocate memory for option_struct members
		Return array of pointers to option_stucts
	*/
	
	// Create pointer and allocate memmory for pointers to opttion_structs
	p_opt_struct *all_opt = calloc(sizeof(p_opt_struct), n_opt);

	if (all_opt == NULL){
		printf("memory allocation error: memory not allocated\n");
		exit(1);
	}

	int i;
	for (i=0; i<n_opt; i++){
		
		// Allocate memory for one option_struct struct
		all_opt[i] = malloc(sizeof(option_struct));
		if (all_opt[i] == NULL){
			printf("memory allocation error: memory not allocated\n");
			exit(1);
		}


		all_opt[i]->id = i;
		all_opt[i]->short_option = shopt[i];
		all_opt[i]->has_operand = has_operand[i];

		all_opt[i]->long_option = malloc(sizeof(longopt[i]));

		if (all_opt[i]->long_option == NULL){
			printf("memory allocation error: memory not allocated\n");
			exit(1);
		}

		strcpy(all_opt[i]->long_option, longopt[i]);

		// set default value
		all_opt[i]->called = 0;
		all_opt[i]->operand = NULL;

	}


	return all_opt;
}



p_opt_struct *margcreate(char *prog_name, int argc, char *argv[], size_t n_opt, char shopt[], char *longopt[], short int has_operand[]){
	/*
		Create all options structs
		Check passed arguments
		Set all struct members
		prog_name -> caller program name
	*/

	p_opt_struct *all_options = create_opt_structs(n_opt, shopt, longopt, has_operand);
	check_all_options(prog_name, argc, argv, all_options, n_opt);

	return all_options;
}



int margfree(p_opt_struct *all_opt, size_t n_opt){
	/*
		free marg allocated memory
	*/ 
	
	int i;
	for (i=0; i<n_opt; i++){
		free(all_opt[i]->long_option);
		free(all_opt[i]->operand);
		free(all_opt[i]);
	}

	free(all_opt);

	return 1;
}











