#ifndef _WAM_UNIT_H
#define _WAM_UNIT_H

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


/* unit_t implemented for use in a linked list */
typedef struct unit_t {
	int id; 		/* unique id for unit in a system */
	int system; 		/* system id e.g. imperial or SI */
	int quantity; 		/* quantity id for e.g. mass or length */
	char *name; 	/* e.g. "inch" */
	char *symbol; 		/* unit symbol e.g. "in" for inch */
	int sbuid; 		/* sytem base unit id e.g 3 for "foot" */
	double rtbu; 		/* ratio of this unit to it's system base unit */
	prefix_t *prefix_list;	/* pointer to prefix linked list */
	int csuid; 		/* id of common unit for ratio in 'rtcsu' */
	int csys; 		/* common system */
	double rtcsu; 		/* this unit ratio to common unit */
	struct unit_t *next; 	/* next node in linked list */
} unit_t;


unit_t *mkunit(int id, int qnt, int sys, char *fn, char *sym, int sbuid, 
	       double rtbu, prefix_t *prfx_list, double rtcsu, int csuid,
	       int csys);
void link_unit(unit_t **head, unit_t *new);
unit_t *nodeunit(int id, int qnt, int sys, char *fn, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys, unit_t **head);
unit_t *search_for_unit(char *needle, unit_t *head_list);
double convert_unit(double inval, unit_t *inunit, unit_t *outunit); 
void print_unit_list(unit_t *head_list);

#endif /* _WAM_UNIT_H */

