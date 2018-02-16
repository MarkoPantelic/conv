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


/* create SI compatible units and return them as linked list */
unit_t *si_compat_list(unit_t **tail, prefix_t *si_prfx_lst)
{
	unit_t *head = NULL;


	/* liter */
	*tail =
	si_node(LITER_ID, Q_VOLUME, NON_SI_COMPAT, "liter", "L", LITER_ID,
		1, si_prfx_lst, &head);
	/* hectare */
	nodeunit(HECTARE_ID, Q_AREA, NON_SI_COMPAT, "hectare", "ha", HECTARE_ID,
		1, 100, METER_SQUARE_SI_ID, SI_SYSTEM, &head);

	return head;
}
