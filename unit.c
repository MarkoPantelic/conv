
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "unit.h"
#include "global_def.h"


/* TODO: pass alternative names and alternative symbol strings*/
/* allocate space for unit_t struct and assign to all it's members passed values
 * except for inner structs 'prefix' and 'cmp'.
 */
unit_t *mknode(int id, int qnt, int sys, char *name, char *sym, int sbuid, 
	     double rtbu)
{

	unit_t *u = xmalloc( sizeof(unit_t) );
	
	u->id = id;
	u->system = sys;
	u->quantity = qnt;

	u->name = xmalloc( sizeof(char) * (strlen(name)+1) );
	strcpy(u->name, name);

	u->symbol = xmalloc( sizeof(char) * (strlen(sym)+1) );
	strcpy(u->symbol, sym);
	
	u->power = 1;
	u->sbuid = sbuid;
	u->rtbu = rtbu;

	u->prefix_list = NULL;
	u->cmp = NULL; 

	u->next = NULL;

	return u;
}


/* link prefix list to unit node */
void linkprefix(unit_t *u, prefix_t *prefix_list)
{
	u->prefix_list = prefix_list;
}


/* add struct cmp_ratio_t to unit_t */
void addcmprt(unit_t *u, int id, int system, double ratio)
{
	u->cmp = xmalloc( sizeof(cmp_ratio_t) );

	u->cmp->id = id;
	u->cmp->system = system;
	u->cmp->ratio = ratio;
}


/* forward connect (connect to the head) to the linked list */
void linkunit(unit_t **head, unit_t *new)
{
	new->next = (*head);
	(*head) = new;	
}


/* create unit and connect it to linked list */
/* example for creating and connecting one node (used in imperial_system.c) */
unit_t *nodeunit(int id, int qnt, int sys, char *name, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys, unit_t **head)
{
	unit_t *u = mknode(id, qnt, sys, name, sym, sbuid, rtbu);

	addcmprt(u, csuid, csys, rtcsu);
	linkunit(head, u);
	return u;
}


/* 
 * Create prefixed unit.
 * Copy and concatenate from prefix_t and input unit_t to new unit_t 
 */
unit_t *prefixed_unit(unit_t *u, prefix_t *p)
{

	/* copy 'u' members to 'o' */
	unit_t *o = xmalloc(sizeof(unit_t));
	o->quantity = u->quantity;
	o->system = u->system;
	o->sbuid = u->sbuid;
	o->power = u->power;

	/* point to original unit compare ratio struct */
	o->cmp = u->cmp;
	

	o->name = xmalloc( sizeof(char) * (strlen(u->name) + p->name_len-1) );
	strcpy(o->name, p->name);
	strcat(o->name, u->name);

	o->symbol = xmalloc( sizeof(char) * (strlen(u->symbol) + p->symbol_len-1) );
	strcpy(o->symbol, p->symbol);
	strcat(o->symbol, u->symbol);

	/* multiply, in order to get unique value id for prefix-unit combination*/
	o->id = u->id * p->id;
 	
	o->rtbu = pow(10, p->pow_factor);
	//o->rtbu = u->rtbu;

	return o;
}


/* 
 * Search for needle member in unit_t struct.
 * If unit_t struct has prefix struct, copy elements from
 * prefix struct to unit_t struct which will be returned 
 */
unit_t *search_units_by(char what, char *needle, unit_t *u)
{
	prefix_t *prfx = NULL;	
	char *u_str, *p_str;
	int p_len;


	// DEBUG
	//printf("# %s:\n", needle);

	while(u != NULL){
		
		if (what == 'n') {
			u_str = u->name;
		}
		else if (what == 's') {
			u_str = u->symbol;
		}
		else {
			fprintf(stderr, "programer error! in search_units_by() in unit.h");
			exit(EXIT_FAILURE);
		}

		// DEBUG
		//printf("unit = %s, it's power = %d\n", u->name, u->power);
 
		if(strcmp(needle, u_str) == 0)
			return u;

		
		prfx = u->prefix_list;

		while(prfx != NULL){


			if (what == 'n') {
				p_str = prfx->name;
				p_len = prfx->name_len;
			}
			else if (what == 's') {
				p_str = prfx->symbol;
				p_len = prfx->symbol_len;
			}
			else {
				fprintf(stderr, "programer error! in search_units_by() in unit.h");
				exit(EXIT_FAILURE);
			}
			
			// compare just prefix with needle
			if (strncmp(p_str, needle, p_len) == 0) {
				
				// DEBUG
				//printf("prefix (%s) part match found, ", p_str);
				
				// compare just unit string part of needle with unit string
				// DEBUG
				//printf("now comparing ->%s, needle len = %d, prfx->len = %d\n", u_str, strlen(needle), p_len);
				if(strncmp(u_str, needle+p_len, strlen(needle)-p_len) == 0){

					if ( strlen(needle) == (p_len+strlen(u_str)) ) {

						u = prefixed_unit(u, prfx);
						return u;
					}
				}
			}

			prfx = prfx->next;
		}
		

		u = u->next;
	}
	
	return NULL;
}



/* search name member in unit_t struct */
unit_t *search_units_by_name(char *name, unit_t *u)
{
	return search_units_by('n', name, u);

}


/* search symbol member in unit_t struct */
unit_t *search_units_by_symbol(char *symbol, unit_t *u)
{
	return search_units_by('s', symbol, u);
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
long double convert_unit(long double inval, unit_t *inunit, unit_t *outunit) 
{

	long double conv_val;
	/* DEBUG */
	/*	
	printf("convert_unit() passed val = %f\n", inval);
	printf("passed inunit -> %s, outunit -> %s\n", inunit->name, outunit->name); 
	*/

	if (inunit->quantity != outunit->quantity) {
		fprintf(stderr, "Cannot convert, incompatable quantities '%s' and '%s'\n", 
			QUANTITY_STR_LIST[inunit->quantity],
			QUANTITY_STR_LIST[outunit->quantity]);
		exit(EXIT_FAILURE);
	}

	if (inunit->system == outunit->system) {

		if (inunit->sbuid == outunit->sbuid){
			//conv_val = inval * inunit->rtbu / outunit->rtbu;
			conv_val = inval * pow(inunit->rtbu, inunit->power) / pow(outunit->rtbu, outunit->power);

		}
		else{
			fprintf(stderr, "ERROR! convert_unit() -> unequal system base " \
				"unit_t id for inunit and outunit\n");
			exit(EXIT_FAILURE);
		}
	}
	/* if inunit common system is outunit system */
	else if (inunit->cmp != NULL && inunit->cmp->system == outunit->system) {
		//printf("inunit->cmp->system == outunit->system \n");
		//printf("inunit->power = %d, outunit->power = %d\n", inunit->power, outunit->power);
		//if (inunit->csuid != outunit->id)// TODO: insert check inunit->compare sys id to out unit id, and convert outunit to compatable unit
		//	printf("!!! NOTE: unequal id's, inunit->common->id = %d, outunit->id = %d\n", inunit->csuid, outunit->id);

		conv_val = inval * inunit->cmp->ratio / outunit->rtbu;
		//conv_val = inval * inunit->cmp->ratio * pow(inunit->rtbu, inunit->power) / pow(outunit->rtbu, outunit->power);
	}

	/* if inunit system is outunit common system*/
	else if (outunit->cmp != NULL && inunit->system == outunit->cmp->system) {

		//printf("inunit->cmp->system == outunit->system \n");
		//printf("inunit->power = %d, outunit->power = %d\n", inunit->power, outunit->power);
		//printf("inunit->rtbu = %f, outunit->cmp->ratio = %f\n", inunit->rtbu, outunit->cmp->ratio);

		conv_val = inval / outunit->cmp->ratio * inunit->rtbu;
		//conv_val = inval * inunit->rtbu / outunit->cmp->ratio;
		//conv_val = inval * pow(inunit->rtbu, inunit->power)  / pow(outunit->rtbu, outunit->power) / outunit->cmp->ratio;
	}
	/* first convert to common system and then to outunit system. */
	else if (inunit->cmp != NULL && outunit->cmp != NULL && 
		 inunit->cmp->system == outunit->cmp->system) {
		

		if (inunit->cmp->id == outunit->cmp->id) {
			conv_val = inval * inunit->cmp->ratio / outunit->cmp->ratio / outunit->rtbu;
		}
		else{
			fprintf(stderr, "ERROR! convert_unit() -> unequal compare system units\n");
			exit(EXIT_FAILURE);
		}	
	}
	else {
		fprintf(stderr, "ERROR! convert_unit() -> incompatible systems\n");
		exit(EXIT_FAILURE);
	}

	return conv_val;
}


/* pretty print unit list */
void print_unit_list(unit_t *node)
{		
	int i;

	/* print heading */
	printf("\n %-15s %-27s %18s %-s\n", "system", "quantity", "unit", "symbol");
	for(i=0; i<78; i++)
		printf("=");

	printf("\n");

	while(node != NULL) {
		printf(" %-15s %-27s %18s (%s)\n", SYSTEM_STR_LIST[node->system], 
			QUANTITY_STR_LIST[node->quantity], node->name, node->symbol);
		node = node->next;
	}

	printf("\n");
}


/* Create or append prefix linked list */
prefix_t *ca_prefix_list(prefix_t **head, int list_len, int id[], char *name[], 
			 char*symbol[], int factor[] )
{
	int i;
	prefix_t *tail = NULL;
	
	for(i=0; i<list_len; i++){

		prefix_t *node = xmalloc( sizeof(prefix_t) );	

		node->id = id[i];

		node->name_len = strlen(name[i]);
		node->symbol_len = strlen(symbol[i]);

		node->name = xmalloc( sizeof(char) * node->name_len );
		node->symbol = xmalloc( sizeof(char) * node->symbol_len );

		strcpy(node->name, name[i]);
		strcpy(node->symbol, symbol[i]);
		node->pow_factor = factor[i];

		if ((*head) == NULL){
			(*head) = node;
			(*head)->next = NULL;
		}
		else{
			node->next = (*head);
			(*head) = node;
		}

		if (i == 0)
			tail = node;
	}
	
	return tail;	
}
