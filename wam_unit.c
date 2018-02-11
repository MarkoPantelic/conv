
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "wam_unit.h"
#include "global_def.h"



/* TODO: pass alternative names and alternative symbol strings*/
/* allocate space for unit_t struct and assign to it's members passed values */
unit_t *mkunit(int id, int qnt, int sys, char *fn, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys)
{

	unit_t *u = xmalloc(sizeof(unit_t));
	
	u->id = id;
	u->system = sys;
	u->quantity = qnt;

	u->fullname = xmalloc(sizeof(char)*(strlen(fn)+1));
	strcpy(u->fullname, fn);

	u->symbol = xmalloc(sizeof(char)*(strlen(sym)+1));
	strcpy(u->symbol, sym);
	
	u->sys_base_unit_id = sbuid;
	u->rtbu = rtbu;
	u->rtcsu = rtcsu;
	u->csuid = csuid;
	u->csys = csys;
	u->next = NULL;

	return u;
}

/* forward connect (connect to the head) to the linked list */
void link_unit(unit_t **head, unit_t *new)
{
	new->next = *head;
	*head = new;	
}

/* create unit and connect it to linked list */
unit_t *nodeunit(int id, int qnt, int sys, char *fn, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys, unit_t **head)
{
	unit_t *u = mkunit(id, qnt, sys, fn, sym, sbuid, rtbu, rtcsu, csuid,
			   csys);
	link_unit(head, u);
	return u;
}


/* search name member in unit_t struct */
unit_t *search_units_by_name(char *name, unit_t *node)
{

	while(node != NULL){
		
		if(strcmp(name, node->fullname) == 0)
			return node;

		node = node->next;
	}
	
	return NULL;
}

/* search symbol member in unit_t struct */
unit_t *search_units_by_symbol(char *symbol, unit_t *node)
{

	while(node != NULL){
		
		if(strcmp(symbol, node->symbol) == 0)
			return node;
		
		node = node->next;
	}
	
	return NULL;
}

/* search in unit_t haystack for the needle */
unit_t *search_for_unit(char *needle, unit_t *node)
{

	unit_t *s = search_units_by_symbol(needle, node);
	
	if(s != NULL)
		return s;
	
	s = search_units_by_name(needle, node);
	
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

	if (inunit->quantity != outunit->quantity){
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


/* pretty print unit list */
void print_unit_list(unit_t *node)
{		
	int i;

	/* print heading */
	printf("\n%-18s %-15s %24s %-s\n", "system", "quantity", "unit", "symbol");
	for(i=0; i<70; i++)
		printf("=");

	printf("\n");

	while(node != NULL){
		printf("%-18s %-15s --- %20s (%s)\n", SYSTEM_STR_LIST[node->system], 
			QUANTITY_STR_LIST[node->quantity], node->fullname, node->symbol);
		node = node->next;
	}

	printf("\n");
}
