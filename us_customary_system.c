/*
 * 			us_customary_system.c 
 * United States customary units
 *
 *
 */

#include <stdlib.h>
#include "unit.h"
#include "global_def.h"
#include "si_system.h" /* for SI system id constants */
#include "non_si_compat.h" /* for liter and hectare id constants */



/* comparison between descendents of English system */
/* English units */     /* Imperial system mass units */  /* USA customary mass units */ 
			/*
			 * grain (gr) 1/7000              * #same#
			 * dram (dr) 1/256                * #same#
			 * ounce (oz) 1/16                * #same#
			 * pound (lb) 1                   * #same#
			 * stone (st) 14                  * #non existant#
			 * long quarter (qr) 28           * short quarter (qr) 25
			 * long hundredweight (cwt) 112   * short hunderdweight (cwt) 100
			 * long ton (t) 2240              * short ton (t) 2000
			 * slug (slug) ~ 32.17404856 lb   * #same#
			 */


enum {GRAIN_US_ID=1, DRAM_US_ID, OUNCE_US_ID, POUND_US_ID, HWEIGHT_US_ID, 
      QUARTER_US_ID, TON_US_ID, POINT_US_ID, PICA_US_ID, INCH_US_ID, 
      FOOT_US_ID, YARD_US_ID, MILE_US_ID, LINK_US_ID, ROD_US_ID, CHAIN_US_ID, 
      FURLONG_US_ID, LEAGUE_US_ID, FATHOM_US_ID, CABLE_US_ID , NAUTICAL_MI_US_ID, 
      SQUARE_FOOT_US_ID, SQUARE_CHAIN_US_ID, ACRE_US_ID, SECTION_US_ID, 
      TOWNSHIP_US_ID, MINIM_US_ID, FLUID_DRAM_US_ID, TEASPOON_US_ID,
      TABLESPOON_US_ID, FLUID_OZ_US_ID, SHOT_US_ID, GILL_US_ID, CUP_US_ID, 
      PINT_US_ID, QUART_US_ID, GALLON_US_ID, BARREL_US_ID, OIL_BARREL_US_ID,
      HOGSHEAD_US_ID}; 
 


/* create US customary units and return them as linked list */
unit_t *us_units_list(unit_t **tail){

/* Unit values ratio to SI unit_t values set in the following code, are defined
 * by the international yard and pound agreement of 1959 */

	unit_t *head = NULL;


	/* set mass units
	 * -------------- */

	/* grain */
	*tail =
	nodeunit(GRAIN_US_ID, Q_MASS, US_SYS, "grain", "gr", POUND_US_ID,
			1.0/7000, 0.06479891, G_SI_ID, SI_SYSTEM, &head);
	/* dram */   
	nodeunit(DRAM_US_ID, Q_MASS, US_SYS, "dram", "dr", POUND_US_ID,
			1.0/256, 1.7718451953125, G_SI_ID, SI_SYSTEM, &head);
	/* ounce */
	nodeunit(OUNCE_US_ID, Q_MASS, US_SYS, "ounce", "oz",
			POUND_US_ID, 1.0/16, 28.349523125, G_SI_ID, SI_SYSTEM,
			&head);
	/* pound */
	nodeunit(POUND_US_ID, Q_MASS, US_SYS, "pound", "lb",
			POUND_US_ID, 1, 453.59237, G_SI_ID, SI_SYSTEM, &head);
	/* US hunderdweight */
	nodeunit(HWEIGHT_US_ID, Q_MASS, US_SYS, "hundredweight", "cwt",
			POUND_US_ID, 100, 45359.237, G_SI_ID, SI_SYSTEM, 
			&head); 
	/* long hunderdweight */
	nodeunit(HWEIGHT_US_ID, Q_MASS, US_SYS, "hundredweight", "cwt",
			POUND_US_ID, 112, 50802.34544, G_SI_ID, SI_SYSTEM, 
			&head); 
	/* short quarter */
	nodeunit(QUARTER_US_ID, Q_MASS, US_SYS, "quarter", "qr", 
			POUND_US_ID, 28, 12700.58636, G_SI_ID, SI_SYSTEM, &head); 
	/* short ton */
	nodeunit(TON_US_ID, Q_MASS, US_SYS, "ton", "t", POUND_US_ID,
			2000, 907184.74, G_SI_ID, SI_SYSTEM, &head);
	/* long ton */
	/*
	nodeunit(LTON_US_ID, Q_MASS, US_SYS, "ton", "t", POUND_US_ID,
			2240, 1016046.9088, G_SI_ID, SI_SYSTEM, &head);
	*/

	/* set length units
	 * ---------------- */

	/* -- International -- */

	/* point */
	nodeunit(POINT_US_ID, Q_LENGTH, US_SYS, "point", "p", FOOT_US_ID,
			1.0/864, 127/360000, METER_SI_ID, SI_SYSTEM, &head); 
	/* pica */
	nodeunit(PICA_US_ID, Q_LENGTH, US_SYS, "pica", "P/", FOOT_US_ID,
			1.0/72, 127/30000, METER_SI_ID, SI_SYSTEM, &head); 
	/* inch */
	nodeunit(INCH_US_ID, Q_LENGTH, US_SYS, "inch", "in", FOOT_US_ID,
			1.0/12, 0.0254, METER_SI_ID, SI_SYSTEM, &head); 
	/* foot */
	nodeunit(FOOT_US_ID, Q_LENGTH, US_SYS, "foot", "ft", FOOT_US_ID,
			1, 0.3048, METER_SI_ID, SI_SYSTEM, &head); 
	/* yard */
	nodeunit(YARD_US_ID, Q_LENGTH, US_SYS, "yard", "yd", FOOT_US_ID,
			3, 0.9144, METER_SI_ID, SI_SYSTEM, &head); 
	/* mile */
	nodeunit(MILE_US_ID, Q_LENGTH, US_SYS, "mile", "mi", FOOT_US_ID,
			5280, 1609.344, METER_SI_ID, SI_SYSTEM, &head); 

	/* -- US Survey -- */

	/* link */
	nodeunit(LINK_US_ID, Q_LENGTH, US_SYS, "link", "li",
			FOOT_US_ID, 33/50, 792/3937, METER_SI_ID, SI_SYSTEM,
			 &head);
	/* survey foot */
	/*
	nodeunit(FOOT_US_ID, Q_LENGTH, US_SYS, "foot", "ft", FOOT_US_ID,
			1, 1200/3937, METER_SI_ID, SI_SYSTEM, &head); 
	*/
	/* rod (also known as pole or perch) */
	nodeunit(ROD_US_ID, Q_LENGTH, US_SYS, "rod", "rd", FOOT_US_ID,
			16.5, 19800/3937, METER_SI_ID, SI_SYSTEM, &head); 
	/* chain */
	nodeunit(CHAIN_US_ID, Q_LENGTH, US_SYS, "chain", "ch",
			FOOT_US_ID, 66, 79200/3937, METER_SI_ID, SI_SYSTEM, &head); 
	/* furlong */
	nodeunit(FURLONG_US_ID, Q_LENGTH, US_SYS, "furlong", "fur",
			FOOT_US_ID, 660, 792000/3937, METER_SI_ID, SI_SYSTEM, &head); 
	/* survey mile */	
	/*
	nodeunit(MILE_US_ID, Q_LENGTH, US_SYS, "mile", "mi", FOOT_US_ID,
			5280, 6336000/3937, METER_SI_ID, SI_SYSTEM, &head); 
	*/
	/* league */
	nodeunit(LEAGUE_US_ID, Q_LENGTH, US_SYS, "league", "lea",
			FOOT_US_ID, 15840, 19008000/3937, METER_SI_ID, SI_SYSTEM,
			&head); 

	/* -- International Nautical -- */

	/* fathom */
	nodeunit(FATHOM_US_ID, Q_LENGTH, US_SYS, "fathom", "ftm",
			FOOT_US_ID, 6, 1.8288, METER_SI_ID, SI_SYSTEM,
			&head); 
	/* cable */
	nodeunit(CABLE_US_ID, Q_LENGTH, US_SYS, "cable", "cb",
			FOOT_US_ID, 720, 219.456, METER_SI_ID, SI_SYSTEM, &head); 
	/* nautical mile (value here set is valid until 1970, after it's 1852m)*/
	nodeunit(NAUTICAL_MI_US_ID, Q_LENGTH, US_SYS, "nml", 
			"nautical mi", FOOT_US_ID, 6076.08, 1852, METER_SI_ID,
			 SI_SYSTEM, &head);



	/* set area units 
	 * -------------- */

	/* square survey foot */
	nodeunit(SQUARE_FOOT_US_ID, Q_AREA, US_SYS, "square foot", "sq ft", SQUARE_FOOT_US_ID,
			1, 0.09290341, METER_SQUARE_SI_ID, SI_SYSTEM, &head);
	/* square chain */
	nodeunit(SQUARE_CHAIN_US_ID, Q_AREA, US_SYS, "square chain", "sq ch", SQUARE_FOOT_US_ID,
			4356, 404.6873, METER_SQUARE_SI_ID, SI_SYSTEM, &head);
	/* acre */
	nodeunit(ACRE_US_ID, Q_AREA, US_SYS, "acre", "acre", SQUARE_FOOT_US_ID,
			43560, 4046.873, METER_SQUARE_SI_ID, SI_SYSTEM, &head);
	/* section */
	nodeunit(SECTION_US_ID, Q_AREA, US_SYS, "section", "section", SQUARE_FOOT_US_ID,
			27878400, 2589.998, METER_SQUARE_SI_ID, SI_SYSTEM, &head);
	/* survey township */
	nodeunit(TOWNSHIP_US_ID, Q_AREA, US_SYS, "survey township", "twp", SQUARE_FOOT_US_ID,
			1003622400, 93239.93, METER_SQUARE_SI_ID, SI_SYSTEM, &head);



	/* set capacity and volume units
	 * ----------------------------- */

	/* minim */
	nodeunit(MINIM_US_ID, Q_VOLUME, US_SYS, "minim", "min", MINIM_US_ID,
			1, 0.000061611519921875, LITER_ID, NON_SI_COMPAT, &head);
	/* fluid dram */
	nodeunit(FLUID_DRAM_US_ID, Q_VOLUME, US_SYS, "fluid dram", "fl dr", MINIM_US_ID,
			60, 0.0036966911953125, LITER_ID, NON_SI_COMPAT, &head);
	/* teaspoon */
	nodeunit(TEASPOON_US_ID, Q_VOLUME, US_SYS, "teaspoon", "tsp", MINIM_US_ID,
			80, 0.00492892159375, LITER_ID, NON_SI_COMPAT, &head);
	/* tablespoon */
	nodeunit(TABLESPOON_US_ID, Q_VOLUME, US_SYS, "tablespoon", "Tbsp", TEASPOON_US_ID,
			3, 0.01478676478125, LITER_ID, NON_SI_COMPAT, &head);
	/* fluid ounce */
	nodeunit(FLUID_OZ_US_ID, Q_VOLUME, US_SYS, "fluid ounce",
			"fl oz", TABLESPOON_US_ID, 2, 0.0295735295625, LITER_ID, 
			NON_SI_COMPAT, &head);
	/* shot */
	nodeunit(SHOT_US_ID, Q_VOLUME, US_SYS, "shot", "jig", FLUID_OZ_US_ID,
			1.5, 0.04436029434375, LITER_ID, NON_SI_COMPAT, &head);
	/* gill */
	nodeunit(GILL_US_ID, Q_VOLUME, US_SYS, "gill", "gi", FLUID_OZ_US_ID,
			4, 0.11829411825, LITER_ID, NON_SI_COMPAT, &head);
	/* cup */
	nodeunit(CUP_US_ID, Q_VOLUME, US_SYS, "cup", "cp", FLUID_OZ_US_ID,
			8, 0.2365882365, LITER_ID, NON_SI_COMPAT, &head);
	/* pint */
	nodeunit(PINT_US_ID, Q_VOLUME, US_SYS, "pint", "pt", CUP_US_ID,
			2, 0.473176473, LITER_ID, NON_SI_COMPAT, &head);
	/* quart */
	nodeunit(QUART_US_ID, Q_VOLUME, US_SYS, "quart", "qt", 
			PINT_US_ID, 2, 0.946352946, LITER_ID, NON_SI_COMPAT, 
			&head);
	/* gallon */
	nodeunit(GALLON_US_ID, Q_VOLUME, US_SYS, "gallon", "gal",
			QUART_US_ID, 4, 3.785411784, LITER_ID, NON_SI_COMPAT, 
			&head);
	/* barrel */
	nodeunit(BARREL_US_ID, Q_VOLUME, US_SYS, "barrel", "bbl",
			GALLON_US_ID, 31.5, 119.240471196, LITER_ID, NON_SI_COMPAT, 
			&head);
	/* oil barrel */
	nodeunit(OIL_BARREL_US_ID, Q_VOLUME, US_SYS, "oil barrel", "oil bbl",
			GALLON_US_ID, 42, 158.987294928, LITER_ID, NON_SI_COMPAT, 
			&head);
	/* hogshead */
	nodeunit(HOGSHEAD_US_ID, Q_VOLUME, US_SYS, "hogshead", "hogshead",
			GALLON_US_ID, 63, 238.480942392, LITER_ID, NON_SI_COMPAT, 
			&head);



	return head;

}
