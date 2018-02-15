/*===============================================
 *		    si_system
 * Units from International system of units (SI system)  
 *	
 *===============================================*/


/*
 * Units derived from SI base units:
 * radian, steraradian, hertz, newton, pascal, joule, watt, coulomb, volt,
 * farad, ohm, siemens, weber, tesla, henry, celsius, lumen, lux, becquerel,
 * gray, sievert, katal
 */

/* Non-SI units accepted for use with SI (definitions are in non_si_compat.c: */
/* minute, hour, day, degree of arc, minute of arc, second of arc, hectare, liter, tonne, astronomical unit, neper, bel, decibel
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global_def.h"
#include "wam_unit.h"
#include "si_system.h"


/* metric prefixes */
/* symbol for 'micro' is replaced by 'u' */
int mphlen = 10;

char *multiples_name[] = {"deca", "hecto", "kilo", "mega", "giga", "tera",
			  "peta", "exa", "zetta", "yotta"};
char *multiples_symbol[] = {"da", "h", "k", "M", "G", "T", "P", "E", "Z", "Y"};
int multiples_factor[] = {1, 2, 3, 6, 9, 12, 15, 18, 21, 24};
int multiples_id[] = {50, 51, 52, 53, 54, 55, 56, 57, 58, 59};

char *submultiples_name[] = {"deci", "centi", "mili", "micro", "nano", "pico",
			     "femto", "atto", "zepto", "yocto"};
char *submultiples_symbol[] = {"d", "c", "m", "u", "n", "p", "f", "a", "z", "y"};
int submultiples_factor[] = {-1, -2, -3, -6, -9, -12, -15, -18, -21, -24};
int submultiples_id[] = {60, 61, 62, 63, 64, 65, 66, 67, 68, 69};
/* non official prefixes */
/* micron = 1 um */
/* angstrom = 0.1 nm */
/* fermi = 1 fm */
/* myriameter = 10 km */


/* create or append prefix linked list */
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


unit_t *si_node(int id, int qnt, int sys, char *fn, char *sym, int sbuid, 
	     double rtbu, prefix_t *prfx_head, unit_t **head)
{
	unit_t *u = mkunit(id, qnt, sys, fn, sym, sbuid, rtbu, prfx_head, -1,
			   -1, -1);
	link_unit(head, u);
	return u;
}


/* create SI units and return them as linked list */
unit_t *si_system_list(unit_t **tail)
{
	prefix_t *prfx_lst = NULL;
	unit_t *head = NULL;

	ca_prefix_list(&prfx_lst, mphlen, multiples_id, multiples_name, 
		       multiples_symbol, multiples_factor);
	ca_prefix_list(&prfx_lst, mphlen, submultiples_id, submultiples_name,
		       submultiples_symbol, submultiples_factor);


	/* set base units */
	/* -------------- */
	/* meter */
	*tail =
	si_node(METER_SI_ID, Q_LENGTH, SI_SYSTEM, "meter", "m", METER_SI_ID,
		1, prfx_lst, &head);

	/* gram !!!!! kilogram is a base SI unit, but here set - gram */
	si_node(G_SI_ID, Q_MASS, SI_SYSTEM, "gram", "g", G_SI_ID,
		1, prfx_lst, &head);

	/* second */
	si_node(SECOND_SI_ID, Q_TIME, SI_SYSTEM, "second", "s", SECOND_SI_ID,
		1, prfx_lst, &head);

	/* ampere */
	si_node(AMPERE_SI_ID, Q_EL_CURRENT, SI_SYSTEM, "ampere", "A", AMPERE_SI_ID,
		1, prfx_lst, &head);

	/* kelvin */
	si_node(KELVIN_SI_ID, Q_TEMPERATURE, SI_SYSTEM, "kelvin", "K", KELVIN_SI_ID,
		1, prfx_lst, &head);
	
	/* mole */
	si_node(MOLE_SI_ID, Q_SUBSTANCE_A, SI_SYSTEM, "mole", "mol", MOLE_SI_ID,
		1, prfx_lst, &head);

	/* candela */
	si_node(CANDELA_SI_ID, Q_LUMINOUS_I, SI_SYSTEM, "candela", "cd", CANDELA_SI_ID,
		1, prfx_lst, &head);

	return head;
}

