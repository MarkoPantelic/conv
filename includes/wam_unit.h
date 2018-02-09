#ifndef _WAM_UNIT_H
#define _WAM_UNIT_H

typedef struct unit {
	int id; /* unique id in a system */
	int system; /* e.g. imperial or SI */
	int class;
	char *fullname; /* e.g. "inch" */
	char *symbol; /* unit symbol e.g. "in" for inch */
	int sys_base_unit_id; /* e.g. id for feet in imperial system*/
	double rtbu; /* ratio to base unit */
	double rtcsu; /* this unit ratio to common unit */
	int csuid; /* id of common unit for ratio in 'rtcsu' */
	int csys; /* common system */
} unit;


unit *mkunit(int id, int cls, int sys, char *fn, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys);
unit *search_for_unit(char *needle, unit **haystack, int haystack_len);
double convert_unit(double inval, unit *inunit, unit *outunit); 
unit **unite_unit_lists(unit **first, int first_len, unit **second, int second_len);

#endif /* _WAM_UNIT_H */

