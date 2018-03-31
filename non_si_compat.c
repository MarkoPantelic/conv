/*===============================================
 *		    non_si_compat
 *             Non-SI compatable units
 * Units officialy accepted for use with SI system 
 *	
 *===============================================*/

#include "non_si_compat.h"


/* TODO:
 * minute, hour, day, degree of arc, minute of arc, second of arc, hectare, tonne, astronomical unit, neper, bel, decibel
 */

#include "global_def.h"
#include "unit.h"
#include "si_system.h"



/* create unit with prefix and compare structs and connect it to linked list */
unit_t *cmpltnode(int id, int qnt, int sys, char *name, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys, prefix_t *prfx_head,
	     unit_t **head) 
{
	unit_t *u = mknode(id, qnt, sys, name, sym, sbuid, rtbu);
	addcmprt(u, csuid, csys, rtcsu);
	linkprefix(u, prfx_head);

	linkunit(head, u);

	return u;
}


/* create SI compatible units and return them as linked list */
unit_t *si_compat_list(unit_t **tail, prefix_t *si_prfx_lst)
{
	unit_t *head = NULL;


	/* BAD !!!!! */
	/* Add unit power ratio for units with power greater than 1*/

	/* liter */
	*tail =
	cmpltnode(LITER_ID, Q_VOLUME, NON_SI_COMPAT, "liter", "L", LITER_ID,
		1, 0.001, METER_CUBIC_SI_ID, SI_SYSTEM, si_prfx_lst, &head);
	head->power = 3;
	/* hectare */
	nodeunit(HECTARE_ID, Q_AREA, NON_SI_COMPAT, "hectare", "ha", HECTARE_ID,
		1, 100, METER_SQUARE_SI_ID, SI_SYSTEM, &head);
	head->power = 2;

	return head;
}
