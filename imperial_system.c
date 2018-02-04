/*
 * 			imperial_system.c 
 * Imperial system of units | British imperial
 * Units based on British Weights and Measures Act of 1824
 * Predecesors: Exchequer Standards (1588-1825), Winchester Units (1495-1587)
 *
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




/* TODO: move to h file for systems def's 
 * -------------------------------------*/
#define IMPERIAL_SYS 1
#define SI_SYSTEM 2

/* define unit class possibilities */
#define C_WEIGHT 1
#define C_LENGTH 2
#define C_AREA 3
#define C_VOLUME 4
/* ------------------------------------ */

/*TODO: move to si_system.c */
enum {G_SI_ID, KG_SI_ID, METER_SI_ID, HECTAR_SI_ID, LITER_SI_ID};


enum {GRAIN_I_ID, DRAM_I_ID, OUNCE_I_ID, POUND_I_ID, STONE_I_ID, QUARTER_I_ID, 
      HWEIGHT_I_ID, TON_I_ID, SLUG_I_ID, THOU_I_ID, INCH_I_ID, FOOT_I_ID, 
      YARD_I_ID, CHAIN_I_ID, FURLONG_I_ID, MILE_I_ID, LEAGUE_I_ID, FATHOM_I_ID, 
      CABLE_I_ID, NAUTICAL_MI_I_ID, LING_I_ID, ROD_I_ID, PERCH_I_ID, ROOD_I_ID, 
      ACRE_I_ID, FLUID_OZ_I_ID, GILL_I_ID, PINT_I_ID, QUART_I_ID, GALLON_I_ID}; 
 

/* TODO: move this definition to another h file */
typedef struct unit {
	int id; /* unique id in a system */
	int system; /* e.g. imperial or SI */
	char *fullname; /* e.g. "inch" */
	char *symbol; /* unit symbol e.g. "in" for inch */
	int sys_base_unit_id; /* e.g. id for feet in imperial system*/
	double rtbu; /* ratio to base unit */
	double rtcsu; /* this unit ratio to compared unit */
	int csuid; /* id of compare unit for ratio in 'rtcsu' */
	int csys; /* compare system */
} unit;

/* TODO: pass alternative names and alternative symbol strings*/
/* allocate space for unit struct and assign to it's members passed values */
unit *mkunit(int id, int cls, int sys, char *fn, char *sym, int sbuid, 
	     double rtbu, double rtcsu, int csuid, int csys)
{

	unit *a_unit = malloc(sizeof(unit));
	
	a_unit->id = id;
	a_unit->sys = sys;
	a_unit->class = cls;

	a_unit->fullname = malloc(sizeof(char)*(strlen(fn)+1));
	strcpy(a_unit->fullname, fn);

	a_unit->symbol = malloc(sizeof(char)*(strlen(sym)+1));
	strcpy(a_unit->symbol, sym);
	
	a_unit->sys_base_unit_id = sbuid;
	a_unit->rtbu = rtbu;
	a_unit->rtcsu = rtcsu;
	a_unit->csuid = csuid;
	a_unit->csys = csys;

	return a_unit;
}


/* Unit values ratio to SI unit values set in the following code, are defined
 * by the international yard and pound agreement of 1959 */

/* set imperial weight units
 * ------------------------- */
unit *grain = mkunit(GRAIN_I_ID, C_WEIGHT, IMPERIAL_SYS, "grain", "gr", 
		POUND_I_ID, 1.0/7000, 0.06479891, G_SI_ID, SI_SYSTEM);

unit *dram = mkunit(DRAM_I_ID, C_WEIGHT, IMPERIAL_SYS, "dram", "dr", POUND_I_ID,
		1.0/256, 1.7718451953125, G_SI_ID, SI_SYSTEM);

unit *ounce = mkunit(OUNCE_I_ID, C_WEIGHT, IMPERIAL_SYS, "ounce", "oz",
		POUND_I_ID, 1.0/16, 28.349523125, GI_SI_ID, SI_SYSTEM);

unit *pound = mkunit(POUND_I_ID, C_WEIGHT, IMPERIAL_SYS, "pound", "lb",
		POUND_I_ID, 1, 0.45359237, KG_SI_ID, SI_SYSTEM);

unit *stone = mkunit(STONE_I_ID, C_WEIGHT, IMPERIAL_SYS, "stone", "st",
		POUND_I_ID, 14, 6.35029318, KG_SI_ID, SI_SYSTEM);
/* long quarter */
unit *quarter = mkunit(QUARTER_I_ID, C_WEIGHT, IMPERIAL_SYS, "quarter", "qr", 
		POUND_I_ID, 28, 12.70058636, KG_SI_ID, SI_SYSTEM); 
/* long hunderdweight */
unit *hundredweight = mkunit(HWEIGHT_I_ID, C_WEIGHT, IMPERIAL_SYS,
		"hundredweight", "cwt", POUND_I_ID, 112, 50.80234544, KG_SI_ID,
		 SI_SYSTEM); 
/* long ton */
unit *ton = mkunit(TON_I_ID, C_WEIGHT, IMPERIAL_SYS, "ton", "t", POUND_I_ID,
		 2240, 1016.0469088, KG_SI_ID, SI_SYSTEM);
/* slug SI value is not exact (it's ~) */
unit *slug = mkunit(SLUG_I_ID, C_WEIGHT, IMPERIAL_SYS, "slug", "slug",
		POUND_I_ID, 32.17404856 , 14.59390294, KG_SI_ID, SI_SYSTEM);


/* set imperial length units
 * ------------------------- */
/* thou also known as mil */
unit thou = mkunit(THOU_I_ID, C_LENGTH, IMPERIAL_SYS, "thou", "th", FOOT_I_ID,
		 1/12000, 0.0000254, METER_SI_ID, SI_SYSTEM); 

unit *inch = mkunit(INCH_I_ID, C_LENGTH, IMPERIAL_SYS, "inch", "in", FOOT_I_ID,
		 1/12, 0.0254, METER_SI_ID, SI_SYSTEM); 

unit *foot = mkunit(FOOT_I_ID, C_LENGTH, IMPERIAL_SYS, "foot", "ft", FOOT_I_ID,
		 1, 0.3048, METER_SI_ID, SI_SYSTEM); 

unit *yard = mkunit(YARD_I_ID, C_LENGTH, IMPERIAL_SYS, "yard", "yd", FOOT_I_ID,
		 3, 0.9144, METER_SI_ID, SI_SYSTEM); 

unit *chain = mkunit(CHAIN_I_ID, C_LENGTH, IMPERIAL_SYS, "chain", "ch",
		 FOOT_I_ID, 66, 20.1168, METER_SI_ID, SI_SYSTEM); 

unit *furlong = mkunit(FURLONG_I_ID, C_LENGTH, IMPERIAL_SYS, "furlong", "fur",
		 FOOT_I_ID, 660, 201.168, METER_SI_ID, SI_SYSTEM); 

unit *mile = mkunit(MILE_I_ID, C_LENGTH, IMPERIAL_SYS, "mile", "mi", FOOT_I_ID,
		 5280, 1609.344, METER_SI_ID, SI_SYSTEM); 

unit *league = mkunit(LEAGUE_I_ID, C_LENGTH, IMPERIAL_SYS, "league", "lea",
		 FOOT_I_ID, 15840, 4828.032, METER_SI_ID, SI_SYSTEM); 

unit *fathom = mkunit(FATHOM_I_ID, C_LENGTH, IMPERIAL_SYS, "fathom", "ftm",
		 FOOT_I_ID, 6.08, 1.853184, METER_SI_ID, SI_SYSTEM); 

unit *cable = mkunit(CABLE_I_ID, C_LENGTH, IMPERIAL_SYS, "cable", "cable",
		 FOOT_I_ID, 608, 185.3184, METER_SI_ID, SI_SYSTEM); 
/* nautical mile SI meter value here set is valid until 1970, after it's 1852m*/
unit *nautical_mile = mkunit(NAUTICAL_MI_I_ID, C_LENGTH, IMPERIAL_SYS,
		 "nautical mile", "nautical mi", FOOT_I_ID, 6080, 1853.184,
		 METER_SI_ID, SI_SYSTEM);

unit *link = mkunit(LINK_I_ID, C_LENGTH, IMPERIAL_SYS, "link", "link",
		 FOOT_I_ID, 66/100, 0.201168, METER_SI_ID, SI_SYSTEM);
/*also known as pole or perch */
unit *rod = mkunit(ROD_I_ID, C_LENGTH, IMPERIAL_SYS, "rod", "rod", FOOT_I_ID,
		 66/4, 5.0292, METER_SI_ID, SI_SYSTEM); 

 
/* set imperial area units 
 * ----------------------- */
/* square rod, square perch, square pole*/
unit *perch = mkunit(PERCH_I_ID, C_AREA, IMPERIAL_SYS, "perch", "perch",
		 PERCH_I_ID, 1, 0.002529, HECTAR_SI_ID, SI_SYSTEM); 

unit *rood = mkunit(ROOD_I_ID, C_AREA, IMPERIAL_SYS, "rood", "rood", PERCH_I_ID,
		 40, 0.1012, HECTAR_SI_ID, SI_SYSTEM);

unit *acre = mkunit(ACRE_I_ID, C_AREA, IMPERIAL_SYS, "acre", "acre", PERCH_I_ID,
		 160, 0.4047, HECTAR_SI_ID, SI_SYSTEM);


/* set imperial volume units
 * ------------------------- */
unit *fluid_ounce = mkunit(FLUID_OZ_I_ID, C_VOLUME, IMPERIAL_SYS, "fluid ounce",
		 "fl oz", OUNCE_I_ID, 1, 0.0284130625, LITER_SI_ID, SI_SYSTEM);

unit *gill = mkunit(GILL_I_ID, C_VOLUME, IMPERIAL_SYS, "gill", "gi", OUNCE_I_ID,
		 5, 0.1420653125, LITER_SI_ID, SI_SYSTEM);

unit *pint = mkunit(PINT_I_ID, C_VOLUME, IMPERIAL_SYS, "pint", "pt", OUNCE_I_ID,
		 20, 0.56826125, LITER_SI_ID, SI_SYSTEM);

unit *quart = mkunit(QUART_I_ID, C_VOLUME, IMPERIAL_SYS, "quart", "qt", 
		OUNCE_I_ID, 40, 1.1365225, LITER_SI_ID, SI_SYSTEM);

unit *gallon = mkunit(GALLON_I_ID, C_VOLUME, IMPERIAL_SYS, "gallon", "gal",
		 OUNCE_I_ID, 160, 4.54609, LITER_SI_ID, SI_SYSTEM);




/* set array of all imperial units*/
unit *all_imperial[] = {grain, dram, ounce, pound, stone, quarter, hunderdweight, ton slug};




