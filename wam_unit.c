
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "wam_unit.h"
#include "global_def.h"



/* TODO: pass alternative names and alternative symbol strings*/
/* allocate space for wam unit_t struct and assign to it's members passed values */
unit_t *mkunit(int id, int cls, int sys, char *fn, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys)
{

	unit_t *u = xmalloc(sizeof(unit_t));
	
	u->id = id;
	u->system = sys;
	u->class = cls;

	u->fullname = xmalloc(sizeof(char)*(strlen(fn)+1));
	strcpy(u->fullname, fn);

	u->symbol = xmalloc(sizeof(char)*(strlen(sym)+1));
	strcpy(u->symbol, sym);
	
	u->sys_base_unit_id = sbuid;
	u->rtbu = rtbu;
	u->rtcsu = rtcsu;
	u->csuid = csuid;
	u->csys = csys;

	return u;
}


/* search name member in wam unit_t */
unit_t *search_units_by_name(char *name, unit_t **unit_list, int list_len)
{
	int i;

	for(i=0; i<list_len; i++){
		
		if(strcmp(name, unit_list[i]->fullname) == 0)
			return unit_list[i];
	}
	
	return NULL;
}

/* search symbol member in wam unit_t */
unit_t *search_units_by_symbol(char *symbol, unit_t **unit_list, int list_len)
{
	int i;

	for(i=0; i<list_len; i++){
		
		if(strcmp(symbol, unit_list[i]->symbol) == 0)
			return unit_list[i];
	}
	
	return NULL;
}

/* search in unit_t haystack for the needle */
unit_t *search_for_unit(char *needle, unit_t **haystack, int haystack_len)
{

	unit_t *s = search_units_by_symbol(needle, haystack, haystack_len);
	
	if(s != NULL)
		return s;
	
	s = search_units_by_name(needle, haystack, haystack_len);
	
	return s;
}


/* convert inval from inunit to outunit value */
double convert_unit(double inval, unit_t *inunit, unit_t *outunit) {

	double conv_val;

	/* DEBUG */
	/*	
	printf("convert_unit() passed val = %f\n", inval);
	printf("passed inunit -> %s, outunit -> %s\n", inunit->fullname, outunit->fullname); 
	*/

	if (inunit->class != outunit->class){
		return -1.0;
	}

	if (inunit->system == outunit->system){

		if (inunit->sys_base_unit_id == outunit->sys_base_unit_id)
			conv_val = inval * inunit->rtbu / outunit->rtbu;
		else{
			printf("ERROR! convert_unit() -> unequal system base unit_t id for inunit and outunit\n");
			exit(EXIT_FAILURE);
		}
	}
	/* first convert to common system and then to outunit system */
	else if (inunit->csys == outunit->csys){

		if (inunit->csuid == outunit->csuid){
			conv_val = inval * inunit->rtcsu / outunit->rtcsu;
		}
		else{
			printf("ERROR! convert_unit() -> unequal compare system units\n");
			exit(EXIT_FAILURE);
		}	
	}
	else {
		printf("ERROR! convert_unit() -> incompatible systems\n");
		exit(EXIT_FAILURE);
	}

	return conv_val;
}


/* unite all unit_t lists into one list */
/* TEMPORARY SOLUTION !!! */
unit_t **unite_unit_lists(unit_t **first, int first_len, unit_t **second, int second_len){
 	
	int i, j, total_len = first_len + second_len;

	//unit_t **total_list = realloc(first, sizeof(unit_t*)*total_len);

	
	unit_t **total_list = xmalloc(sizeof(unit_t*)*total_len);

	for(i=0; i<first_len; i++){
		total_list[i] = first[i];	
	}

	for(j=0; j<second_len; j++){
		total_list[i++] = second[j];
	}
	

	/*
	for(i=total_len-first_len, j=0; i<total_len; i++){
		printf("copying in %d, from %d\n", i, j);
		total_list[i] = second[j++];	
	}

	printf("finished uniting list\n");
	printf("first member => %s\n", total_list[0]->fullname);
	printf("last member => %s\n", total_list[total_len-1]->fullname);
	*/

	return total_list;
}


void print_unit_list(unit_t **list, int list_len)
{		
	int i;

	for(i=0; i<list_len; i++){
		printf("%d - %s (%s)\n", list[i]->id, list[i]->fullname, list[i]->symbol);
	}
}
