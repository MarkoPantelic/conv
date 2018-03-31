#ifndef _UNIT_H
#define _UNIT_H

/* prefix_t implemented for use in a linked list */
typedef struct prefix_t {

	int id;
	char *name;
	int name_len;
	char *symbol;
	int symbol_len;
	int pow_factor;
	struct prefix_t *next;

} prefix_t;

/* compare ratio struct, to be used as member of unit_t */
typedef struct cmp_ratio_t {

	int id; 		/* id of compare unit */
	int system; 		/* system of compare unit */
	double ratio; 		/* conversion factor */

} cmp_ratio_t;

/* unit_t implemented for use in a linked list */
typedef struct unit_t {

	int id; 		/* unique id for unit in a system */
	int system; 		/* system id e.g. imperial or SI */
	int quantity; 		/* quantity id for e.g. mass or length */
	char *name; 		/* e.g. "inch" */
	char *symbol; 		/* unit symbol e.g. "in" for inch */
	int power;		/* for units e.g. m2 or m3 */
	int sbuid; 		/* system base unit id e.g 3 for "foot" */
	double rtbu; 		/* ratio of this unit to it's system base unit */
	prefix_t *prefix_list;	/* pointer to prefix linked list */
	cmp_ratio_t *cmp;	/* compare ratio struct */
	struct unit_t *next; 	/* next node in linked list */

} unit_t;


unit_t *mknode(int id, int qnt, int sys, char *name, char *sym, int sbuid,
	       double rtbu);

void linkprefix(unit_t *u, prefix_t *prefix_list);
void addcmprt(unit_t *u, int id, int system, double ratio);
void linkunit(unit_t **u_head, unit_t *new);

unit_t *nodeunit(int id, int qnt, int sys, char *name, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys, unit_t **head);

unit_t *search_for_unit(char *needle, unit_t *head_list);

long double convert_unit(long double inval, unit_t *inunit, unit_t *outunit); 

void print_unit_list(unit_t *head_list);

prefix_t *ca_prefix_list(prefix_t **head, int list_len, int id[], char *name[], 
			 char*symbol[], int factor[] );

#endif /* _UNIT_H */

