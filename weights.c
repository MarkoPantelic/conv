/*============================================
 *		    measureconv
 *	Conversions between different weights 
 *	and measure units
 *============================================*/


#include <stdlib.h>
#include "weights.h"
#include "global_def.h"
#include "wam_unit.h"
#include "si_system.h"

const char OUNCE[] = "ounce";
const char GRAM[] = "gram";

/* TODO: create unit lists for all weights systems */


/*  AVOIRDUPOIS, now used in imperial and US customary system */


/* 
 * Return value how much metric grams are in one ounce depending on ounce variant argument.
 * If 'variant' is invalid return 0 
 */
float ginounce(char variant)
{
	switch (variant){

		case AVOIRDUPOIS_OZ:  /* avoirdupois ounce */
			return 28.349523125; /* 437.5 grains */
		case TROY_OZ: /* troy ounce, unit_t 't oz' or 'oz t', troy ounce of gold ISO 4217 currency code = 'XAU', silver = 'XAG'*/
			return 31.1034768; /* 480 grains */
		case DUTCH_OZ: /* Dutch ounce (ons)  */
			return 100;
		case THERESIA_OZ: /* Maria Theresia ounce (birr in Ethiopia) */
			return 28.0668;
		case SPANISH_OZ: /* Spanish ounce (onza) */
			return 28.75;
		case FRENCH_OZ: /* French ounce (once) */
			return 30.59;
		case PORTUGUESE_OZ: /* Portuguese ounce (onca) */
			return 28.69;
		case CHINESE_OZ: /* Chinese metric ounce */
			return 50;
		default:
			return 0;
	}
}


/* 
 * Convert ounce float value to metric gram value depending on ounce variant
 * Ounce values expected are weight values not ounce-force or fluid-ounce values. 
 */
float ouncetog(float ounce, char variant)
{
	
	float g_in_ounce = ginounce(variant);

	if (g_in_ounce == 0)
		return -1;

	return g_in_ounce * ounce;
}


/* 
 * Convert gram float value to ounce value depending on ounce variant
 * Ounce values expected are weight values not ounce-force or fluid-ounce values. 
 */
float gtoounce(float gram, char variant)
{
	float g_in_ounce = ginounce(variant);

	if (g_in_ounce == 0)
		return -1;

	return 1.0/g_in_ounce * gram;

}


/* convert ounce value represented as a string into gram value represented as a float */
float souncetog(const char *strounce, char variant)
{
	return ouncetog((float)atof(strounce), variant);
}


/* convert gram value represented as a string into ounce value represented as a float */
float sgtoounce(const char *strgram, char variant)
{
	return gtoounce((float)atof(strgram), variant);
}


/* LIST NOT FINISHED !!! */
/* troy */
int GRAIN_T_ID = 1, POUND_T_ID = 2, TROY_WEIGHTS = 7;

/* create imperial units and return them as linked list */
unit_t *weights_list(unit_t **tail){

	unit_t *head = NULL;


	/* set imperial weight units
	 * ------------------------- */
	/* grain */
	*tail =
	nodeunit(GRAIN_T_ID, Q_WEIGHT, TROY_WEIGHTS, "grain", "gr", POUND_T_ID,
			0, 0, G_SI_ID, SI_SYSTEM, &head);
	/* dram */   
	/* ounce */
	/* pound */
	/* stone */
	/* long quarter */
	/* long hunderdweight */
	/* long ton */
	/* slug (slug SI value is not exact (it's ~)) */

	return head;
}
