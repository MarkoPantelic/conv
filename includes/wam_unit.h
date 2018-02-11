#ifndef _WAM_UNIT_H
#define _WAM_UNIT_H

/* unit_t implemented for use in a linked list */
typedef struct unit_t {
	int id; 		/* unique id in a system */
	int system; 		/* e.g. imperial or SI */
	int quantity; 		/* quantity id for e.g. mass or length */
	char *fullname; 	/* e.g. "inch" */
	char *symbol; 		/* unit symbol e.g. "in" for inch */
	int sys_base_unit_id; 	/* e.g. id for feet in imperial system*/
	double rtbu; 		/* ratio of this unit to base unit */
	double rtcsu; 		/* this unit_t ratio to common unit */
	int csuid; 		/* id of common unit for ratio in 'rtcsu' */
	int csys; 		/* common system */
	struct unit_t *next; 		/* next node in linked list */
} unit_t;


unit_t *mkunit(int id, int qnt, int sys, char *fn, char *sym, int sbuid, 
	       double rtbu, double rtcsu, int csuid, int csys);
void link_unit(unit_t **head, unit_t *new);
unit_t *nodeunit(int id, int qnt, int sys, char *fn, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys, unit_t **head);
unit_t *search_for_unit(char *needle, unit_t *head_list);
double convert_unit(double inval, unit_t *inunit, unit_t *outunit); 
void print_unit_list(unit_t *head_list);

#endif /* _WAM_UNIT_H */

