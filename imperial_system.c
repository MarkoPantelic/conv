/*
 * 			imperial_system.c 
 * Imperial system of units | British imperial
 * Units based on British Weights and Measures Act of 1824
 * Predecesors: Exchequer Standards (1588-1825), Winchester Units (1495-1587)
 *
 */

#include <stdlib.h>
#include "wam_unit.h"
#include "global_def.h"
#include "si_system.h" /* for SI system id constants */



/* imperial compared to other */
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


enum {GRAIN_I_ID, DRAM_I_ID, OUNCE_I_ID, POUND_I_ID, STONE_I_ID, QUARTER_I_ID, 
      HWEIGHT_I_ID, TON_I_ID, SLUG_I_ID, THOU_I_ID, INCH_I_ID, FOOT_I_ID, 
      YARD_I_ID, CHAIN_I_ID, FURLONG_I_ID, MILE_I_ID, LEAGUE_I_ID, FATHOM_I_ID, 
      CABLE_I_ID, NAUTICAL_MI_I_ID, LINK_I_ID, ROD_I_ID, PERCH_I_ID, ROOD_I_ID, 
      ACRE_I_ID, FLUID_OZ_I_ID, GILL_I_ID, PINT_I_ID, QUART_I_ID, GALLON_I_ID}; 
 


/* create imperial units and return them as linked list */
unit_t *imperial_list(unit_t **tail){

/* Unit values ratio to SI unit_t values set in the following code, are defined
 * by the international yard and pound agreement of 1959 */

	unit_t *head = NULL;


	/* set imperial weight units
	 * ------------------------- */
	/* grain */
	*tail =
	nodeunit(GRAIN_I_ID, Q_WEIGHT, IMPERIAL_SYS, "grain", "gr", POUND_I_ID,
			1.0/7000, 0.06479891, G_SI_ID, SI_SYSTEM, &head);
	/* dram */   
	nodeunit(DRAM_I_ID, Q_WEIGHT, IMPERIAL_SYS, "dram", "dr", POUND_I_ID,
			1.0/256, 1.7718451953125, G_SI_ID, SI_SYSTEM, &head);
	/* ounce */
	nodeunit(OUNCE_I_ID, Q_WEIGHT, IMPERIAL_SYS, "ounce", "oz",
			POUND_I_ID, 1.0/16, 28.349523125, G_SI_ID, SI_SYSTEM,
			&head);
	/* pound */
	nodeunit(POUND_I_ID, Q_WEIGHT, IMPERIAL_SYS, "pound", "lb",
			POUND_I_ID, 1, 0.45359237, KG_SI_ID, SI_SYSTEM, &head);
	/* stone */
	nodeunit(STONE_I_ID, Q_WEIGHT, IMPERIAL_SYS, "stone", "st",
			POUND_I_ID, 14, 6.35029318, KG_SI_ID, SI_SYSTEM, &head);
	/* long quarter */
	nodeunit(QUARTER_I_ID, Q_WEIGHT, IMPERIAL_SYS, "quarter", "qr", 
			POUND_I_ID, 28, 12.70058636, KG_SI_ID, SI_SYSTEM, &head); 
	/* long hunderdweight */
	nodeunit(HWEIGHT_I_ID, Q_WEIGHT, IMPERIAL_SYS, "hundredweight", "cwt",
			POUND_I_ID, 112, 50.80234544, KG_SI_ID, SI_SYSTEM, 
			&head); 
	/* long ton */
	nodeunit(TON_I_ID, Q_WEIGHT, IMPERIAL_SYS, "ton", "t", POUND_I_ID,
			2240, 1016.0469088, KG_SI_ID, SI_SYSTEM, &head);
	/* slug (slug SI value is not exact (it's ~)) */
	nodeunit(SLUG_I_ID, Q_WEIGHT, IMPERIAL_SYS, "slug", "slug", POUND_I_ID, 
			32.17404856 , 14.59390294, KG_SI_ID, SI_SYSTEM, &head);


	/* set imperial length units
	 * ------------------------- */
	/* thou also known as mil */
	nodeunit(THOU_I_ID, Q_LENGTH, IMPERIAL_SYS, "thou", "th", FOOT_I_ID,
			1.0/12000, 0.0000254, METER_SI_ID, SI_SYSTEM, &head); 
	/* inch */
	nodeunit(INCH_I_ID, Q_LENGTH, IMPERIAL_SYS, "inch", "in", FOOT_I_ID,
			1.0/12, 0.0254, METER_SI_ID, SI_SYSTEM, &head); 
	/* foot */
	nodeunit(FOOT_I_ID, Q_LENGTH, IMPERIAL_SYS, "foot", "ft", FOOT_I_ID,
			1, 0.3048, METER_SI_ID, SI_SYSTEM, &head); 
	/* yard */
	nodeunit(YARD_I_ID, Q_LENGTH, IMPERIAL_SYS, "yard", "yd", FOOT_I_ID,
			3, 0.9144, METER_SI_ID, SI_SYSTEM, &head); 
	/* chain */
	nodeunit(CHAIN_I_ID, Q_LENGTH, IMPERIAL_SYS, "chain", "ch",
			FOOT_I_ID, 66, 20.1168, METER_SI_ID, SI_SYSTEM, &head); 
	/* furlong */
	nodeunit(FURLONG_I_ID, Q_LENGTH, IMPERIAL_SYS, "furlong", "fur",
			FOOT_I_ID, 660, 201.168, METER_SI_ID, SI_SYSTEM, &head); 
	/* mile */
	nodeunit(MILE_I_ID, Q_LENGTH, IMPERIAL_SYS, "mile", "mi", FOOT_I_ID,
			5280, 1609.344, METER_SI_ID, SI_SYSTEM, &head); 
	/* league */
	nodeunit(LEAGUE_I_ID, Q_LENGTH, IMPERIAL_SYS, "league", "lea",
			FOOT_I_ID, 15840, 4828.032, METER_SI_ID, SI_SYSTEM,
			&head); 
	/* fathom */
	nodeunit(FATHOM_I_ID, Q_LENGTH, IMPERIAL_SYS, "fathom", "ftm",
			FOOT_I_ID, 6.08, 1.853184, METER_SI_ID, SI_SYSTEM,
			&head); 
	/* cable */
	nodeunit(CABLE_I_ID, Q_LENGTH, IMPERIAL_SYS, "cable", "cable",
			FOOT_I_ID, 608, 185.3184, METER_SI_ID, SI_SYSTEM, &head); 
	/* nautical mile (value here set is valid until 1970, after it's 1852m)*/
	nodeunit(NAUTICAL_MI_I_ID, Q_LENGTH, IMPERIAL_SYS, "nautical mile", 
			"nautical mi", FOOT_I_ID, 6080, 1853.184, METER_SI_ID,
			 SI_SYSTEM, &head);
	/* link */
	nodeunit(LINK_I_ID, Q_LENGTH, IMPERIAL_SYS, "link", "link",
			FOOT_I_ID, 66.0/100, 0.201168, METER_SI_ID, SI_SYSTEM,
			 &head);
	/* rod (also known as pole or perch) */
	nodeunit(ROD_I_ID, Q_LENGTH, IMPERIAL_SYS, "rod", "rod", FOOT_I_ID,
			66.0/4, 5.0292, METER_SI_ID, SI_SYSTEM, &head); 


	/* set imperial area units 
	 * ----------------------- */
	/* perch (also known as square rod, square perch, square pole)*/
	nodeunit(PERCH_I_ID, Q_AREA, IMPERIAL_SYS, "perch", "perch",
			PERCH_I_ID, 1, 0.002529, HECTAR_SI_ID, SI_SYSTEM, &head); 
	/* rood */
	nodeunit(ROOD_I_ID, Q_AREA, IMPERIAL_SYS, "rood", "rood", PERCH_I_ID,
			40, 0.1012, HECTAR_SI_ID, SI_SYSTEM, &head);
	/* acre */
	nodeunit(ACRE_I_ID, Q_AREA, IMPERIAL_SYS, "acre", "acre", PERCH_I_ID,
			160, 0.4047, HECTAR_SI_ID, SI_SYSTEM, &head);


	/* set imperial volume units
	 * ------------------------- */
	/* fluid ounce */
	nodeunit(FLUID_OZ_I_ID, Q_VOLUME, IMPERIAL_SYS, "fluid ounce",
			"fl oz", OUNCE_I_ID, 1, 0.0284130625, LITER_OU_ID, 
			OTHER_UNITS, &head);
	/* gill */
	nodeunit(GILL_I_ID, Q_VOLUME, IMPERIAL_SYS, "gill", "gi", OUNCE_I_ID,
			5, 0.1420653125, LITER_OU_ID, OTHER_UNITS, &head);
	/* pint */
	nodeunit(PINT_I_ID, Q_VOLUME, IMPERIAL_SYS, "pint", "pt", OUNCE_I_ID,
			20, 0.56826125, LITER_OU_ID, OTHER_UNITS, &head);
	/* quart */
	nodeunit(QUART_I_ID, Q_VOLUME, IMPERIAL_SYS, "quart", "qt", 
			OUNCE_I_ID, 40, 1.1365225, LITER_OU_ID, OTHER_UNITS, 
			&head);
	/* gallon */
	nodeunit(GALLON_I_ID, Q_VOLUME, IMPERIAL_SYS, "gallon", "gal",
			OUNCE_I_ID, 160, 4.54609, LITER_OU_ID, OTHER_UNITS, 
			&head);


	return head;

}
