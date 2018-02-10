#ifndef _WAM_UNIT_H
#define _WAM_UNIT_H

typedef struct unit_t {
	int id; /* unique id in a system */
	int system; /* e.g. imperial or SI */
	int class;
	char *fullname; /* e.g. "inch" */
	char *symbol; /* unit_t symbol e.g. "in" for inch */
	int sys_base_unit_id; /* e.g. id for feet in imperial system*/
	double rtbu; /* ratio to base unit_t */
	double rtcsu; /* this unit_t ratio to common unit_t */
	int csuid; /* id of common unit_t for ratio in 'rtcsu' */
	int csys; /* common system */
} unit_t;


unit_t *mkunit(int id, int cls, int sys, char *fn, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys);
unit_t *search_for_unit(char *needle, unit_t **haystack, int haystack_len);
double convert_unit(double inval, unit_t *inunit, unit_t *outunit); 
unit_t **unite_unit_lists(unit_t **first, int first_len, unit_t **second, int second_len);
void print_unit_list(unit_t **list, int list_len);

#endif /* _WAM_UNIT_H */

