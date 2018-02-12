/*===============================================
 *		    si_system
 * Units from International system of units (SI system)  
 *	
 *===============================================*/

/*
 * SI base units:
 * metre, kilogram, second, ampere, kelvin, mole, candela
 */

/*
 * Units derived from SI base units:
 * radian, steraradian, hertz, newton, pascal, joule, watt, coulomb, volt,
 * farad, ohm, siemens, weber, tesla, henry, celsius, lumen, lux, becquerel,
 * gray, sievert, katal
 */

/* Non-SI units accepted for use with SI: */
/* minute, hour, day, degree of arc, minute of arc, second of arc, hectare, liter, tonne, astronomical unit, decibel
 */

#include <stdlib.h>
#include "global_def.h"
#include "wam_unit.h"
#include "si_system.h"


typedef struct prefix_t {
	char *name;
	char *symbol;
	int pow_factor;
} prefix_t;

/* metric prefixes */
/* symbol for 'micro' is replaced by 'u' */
int metric_prfx_half_len = 10;

char *multiples_name[] = {"deca", "hecto", "kilo", "mega", "giga", "tera",
			  "peta", "exa" "zetta", "yotta"};
char *multiples_symbol[] = {"da", "h", "k", "M", "G", "T", "P", "E", "Z", "Y"};
int multiples_factor[] = {1, 2, 3, 6, 9, 12, 15, 18, 21, 24};

char *submultiples_name[] = {"deci", "centi", "mili", "micro", "nano", "pico",
			     "femto", "atto", "zepto", "yocto"};
char *submultiples_symbol[] = {"d", "c", "m", "u", "n", "p", "f", "a", "z", "y"};
int submultiples_factor[] = {-1, -2, -3, -6, -9, -12, -15, -18, -21, -24};
/* non official prefixes */
/* micron = 1 um */
/* angstrom = 0.1 nm */
/* fermi = 1 fm */
/* myriameter = 10 km */


/* create a list of all metric prefixes */
/*prefix_t *metric_prefix_list(int list_len){
	return NULL;	
}
*/


/* create SI units and return them as linked list */
unit_t *si_system_list(unit_t **tail)
{

	unit_t *head = NULL;

	/* set base units */
	/* -------------- */
	/* meter */
	*tail =
	nodeunit(METER_SI_ID, Q_LENGTH, SI_SYSTEM, "meter", "m", METER_SI_ID,
		1, -1, -1, -1, &head);

	/* kilogram */
	nodeunit(KG_SI_ID, Q_WEIGHT, SI_SYSTEM, "kilogram", "kg", KG_SI_ID,
		1, -1, -1, -1, &head);

	/* second */
	nodeunit(SECOND_SI_ID, Q_TIME, SI_SYSTEM, "second", "s", SECOND_SI_ID,
		1, -1, -1, -1, &head);

	/* ampere */
	nodeunit(AMPERE_SI_ID, Q_EL_CURRENT, SI_SYSTEM, "ampere", "A", AMPERE_SI_ID,
		1, -1, -1, -1, &head);

	/* kelvin */
	nodeunit(KELVIN_SI_ID, Q_TEMPERATURE, SI_SYSTEM, "kelvin", "K", KELVIN_SI_ID,
		1, -1, -1, -1, &head);
	
	/* mole */
	nodeunit(MOLE_SI_ID, Q_SUBSTANCE_A, SI_SYSTEM, "mole", "mol", MOLE_SI_ID,
		1, -1, -1, -1, &head);

	/* candela */
	nodeunit(CANDELA_SI_ID, Q_WEIGHT, SI_SYSTEM, "candela", "cd", CANDELA_SI_ID,
		1, -1, -1, -1, &head);

	return head;
}

