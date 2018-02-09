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

/* delete this function later
inline double CF(x,y) { return x/y; }
*/

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





/*TODO: move to si_system.c */
enum {G_SI_ID, KG_SI_ID, METER_SI_ID, HECTAR_SI_ID, LITER_SI_ID};


enum {GRAIN_I_ID, DRAM_I_ID, OUNCE_I_ID, POUND_I_ID, STONE_I_ID, QUARTER_I_ID, 
      HWEIGHT_I_ID, TON_I_ID, SLUG_I_ID, THOU_I_ID, INCH_I_ID, FOOT_I_ID, 
      YARD_I_ID, CHAIN_I_ID, FURLONG_I_ID, MILE_I_ID, LEAGUE_I_ID, FATHOM_I_ID, 
      CABLE_I_ID, NAUTICAL_MI_I_ID, LINK_I_ID, ROD_I_ID, PERCH_I_ID, ROOD_I_ID, 
      ACRE_I_ID, FLUID_OZ_I_ID, GILL_I_ID, PINT_I_ID, QUART_I_ID, GALLON_I_ID}; 
 


/* function to initialize all imperial unit's and return **unit[] */
unit **mkimperial(int *iu_len){

/* Unit values ratio to SI unit values set in the following code, are defined
 * by the international yard and pound agreement of 1959 */


	*iu_len = 29;
	unit **iu = xmalloc ( sizeof(unit*) * (*iu_len) );


	/* set imperial weight units
	 * ------------------------- */
	/* grain */
	iu[0] = mkunit(GRAIN_I_ID, C_WEIGHT, IMPERIAL_SYS, "grain", "gr", POUND_I_ID,
			1.0/7000, 0.06479891, G_SI_ID, SI_SYSTEM);
	/* dram */   
	iu[1] = mkunit(DRAM_I_ID, C_WEIGHT, IMPERIAL_SYS, "dram", "dr", POUND_I_ID,
			1.0/256, 1.7718451953125, G_SI_ID, SI_SYSTEM);
	/* ounce */
	iu[2] = mkunit(OUNCE_I_ID, C_WEIGHT, IMPERIAL_SYS, "ounce", "oz",
			POUND_I_ID, 1.0/16, 28.349523125, G_SI_ID, SI_SYSTEM);
	/* pound */
	iu[3] = mkunit(POUND_I_ID, C_WEIGHT, IMPERIAL_SYS, "pound", "lb",
			POUND_I_ID, 1, 0.45359237, KG_SI_ID, SI_SYSTEM);
	/* stone */
	iu[4] = mkunit(STONE_I_ID, C_WEIGHT, IMPERIAL_SYS, "stone", "st",
			POUND_I_ID, 14, 6.35029318, KG_SI_ID, SI_SYSTEM);
	/* long quarter */
	iu[5] = mkunit(QUARTER_I_ID, C_WEIGHT, IMPERIAL_SYS, "quarter", "qr", 
			POUND_I_ID, 28, 12.70058636, KG_SI_ID, SI_SYSTEM); 
	/* long hunderdweight */
	iu[6] = mkunit(HWEIGHT_I_ID, C_WEIGHT, IMPERIAL_SYS,
			"hundredweight", "cwt", POUND_I_ID, 112, 50.80234544, KG_SI_ID,
			SI_SYSTEM); 
	/* long ton */
	iu[7] = mkunit(TON_I_ID, C_WEIGHT, IMPERIAL_SYS, "ton", "t", POUND_I_ID,
			2240, 1016.0469088, KG_SI_ID, SI_SYSTEM);
	/* slug (slug SI value is not exact (it's ~)) */
	iu[8] = mkunit(SLUG_I_ID, C_WEIGHT, IMPERIAL_SYS, "slug", "slug",
			POUND_I_ID, 32.17404856 , 14.59390294, KG_SI_ID, SI_SYSTEM);


	/* set imperial length units
	 * ------------------------- */
	/* thou also known as mil */
	iu[9] = mkunit(THOU_I_ID, C_LENGTH, IMPERIAL_SYS, "thou", "th", FOOT_I_ID,
			1.0/12000, 0.0000254, METER_SI_ID, SI_SYSTEM); 
	/* inch */
	iu[10] = mkunit(INCH_I_ID, C_LENGTH, IMPERIAL_SYS, "inch", "in", FOOT_I_ID,
			1.0/12, 0.0254, METER_SI_ID, SI_SYSTEM); 
	/* foot */
	iu[11] = mkunit(FOOT_I_ID, C_LENGTH, IMPERIAL_SYS, "foot", "ft", FOOT_I_ID,
			1, 0.3048, METER_SI_ID, SI_SYSTEM); 
	/* yard */
	iu[12] = mkunit(YARD_I_ID, C_LENGTH, IMPERIAL_SYS, "yard", "yd", FOOT_I_ID,
			3, 0.9144, METER_SI_ID, SI_SYSTEM); 
	/* chain */
	iu[13] = mkunit(CHAIN_I_ID, C_LENGTH, IMPERIAL_SYS, "chain", "ch",
			FOOT_I_ID, 66, 20.1168, METER_SI_ID, SI_SYSTEM); 
	/* furlong */
	iu[14] = mkunit(FURLONG_I_ID, C_LENGTH, IMPERIAL_SYS, "furlong", "fur",
			FOOT_I_ID, 660, 201.168, METER_SI_ID, SI_SYSTEM); 
	/* mile */
	iu[15] = mkunit(MILE_I_ID, C_LENGTH, IMPERIAL_SYS, "mile", "mi", FOOT_I_ID,
			5280, 1609.344, METER_SI_ID, SI_SYSTEM); 
	/* league */
	iu[16] = mkunit(LEAGUE_I_ID, C_LENGTH, IMPERIAL_SYS, "league", "lea",
			FOOT_I_ID, 15840, 4828.032, METER_SI_ID, SI_SYSTEM); 
	/* fathom */
	iu[17] = mkunit(FATHOM_I_ID, C_LENGTH, IMPERIAL_SYS, "fathom", "ftm",
			FOOT_I_ID, 6.08, 1.853184, METER_SI_ID, SI_SYSTEM); 
	/* cable */
	iu[18] = mkunit(CABLE_I_ID, C_LENGTH, IMPERIAL_SYS, "cable", "cable",
			FOOT_I_ID, 608, 185.3184, METER_SI_ID, SI_SYSTEM); 
	/* nautical mile (SI meter value here set is valid until 1970, after it's 1852m)*/
	iu[19] = mkunit(NAUTICAL_MI_I_ID, C_LENGTH, IMPERIAL_SYS,
			"nautical mile", "nautical mi", FOOT_I_ID, 6080, 1853.184,
			METER_SI_ID, SI_SYSTEM);
	/* link */
	iu[20] = mkunit(LINK_I_ID, C_LENGTH, IMPERIAL_SYS, "link", "link",
			FOOT_I_ID, 66.0/100, 0.201168, METER_SI_ID, SI_SYSTEM);
	/* rod (also known as pole or perch) */
	iu[21] = mkunit(ROD_I_ID, C_LENGTH, IMPERIAL_SYS, "rod", "rod", FOOT_I_ID,
			66.0/4, 5.0292, METER_SI_ID, SI_SYSTEM); 


	/* set imperial area units 
	 * ----------------------- */
	/* perch (also known as square rod, square perch, square pole)*/
	iu[22] = mkunit(PERCH_I_ID, C_AREA, IMPERIAL_SYS, "perch", "perch",
			PERCH_I_ID, 1, 0.002529, HECTAR_SI_ID, SI_SYSTEM); 
	/* rood */
	iu[23] = mkunit(ROOD_I_ID, C_AREA, IMPERIAL_SYS, "rood", "rood", PERCH_I_ID,
			40, 0.1012, HECTAR_SI_ID, SI_SYSTEM);
	/* acre */
	iu[24] = mkunit(ACRE_I_ID, C_AREA, IMPERIAL_SYS, "acre", "acre", PERCH_I_ID,
			160, 0.4047, HECTAR_SI_ID, SI_SYSTEM);


	/* set imperial volume units
	 * ------------------------- */
	/* fluid ounce */
	iu[25]  = mkunit(FLUID_OZ_I_ID, C_VOLUME, IMPERIAL_SYS, "fluid ounce",
			"fl oz", OUNCE_I_ID, 1, 0.0284130625, LITER_SI_ID, SI_SYSTEM);
	/* gill */
	iu[26] = mkunit(GILL_I_ID, C_VOLUME, IMPERIAL_SYS, "gill", "gi", OUNCE_I_ID,
			5, 0.1420653125, LITER_SI_ID, SI_SYSTEM);
	/* pint */
	iu[27] = mkunit(PINT_I_ID, C_VOLUME, IMPERIAL_SYS, "pint", "pt", OUNCE_I_ID,
			20, 0.56826125, LITER_SI_ID, SI_SYSTEM);
	/* quart */
	iu[28] = mkunit(QUART_I_ID, C_VOLUME, IMPERIAL_SYS, "quart", "qt", 
			OUNCE_I_ID, 40, 1.1365225, LITER_SI_ID, SI_SYSTEM);
	/* gallon */
	iu[29] = mkunit(GALLON_I_ID, C_VOLUME, IMPERIAL_SYS, "gallon", "gal",
			OUNCE_I_ID, 160, 4.54609, LITER_SI_ID, SI_SYSTEM);



	return iu;
/* = { grain, dram, ounce, pound, stone, quarter,
		hundredweight, ton, slug, yard, mile };
*/
}
