/*===============================================
 *		    si_system
 * Units from International system of units (SI system)  
 *	
 *===============================================*/


/* metric prefixes */
char *multiples_name[] = {"deca", "hecto", "kilo", "mega", "giga", "tera", "peta", "exa" "zetta", "yotta"};
char *multiples_symbol[] = {"da", "h", "k", "M", "G", "T", "P", "E", "Z", "Y"};
int *multiples_factor = {1, 2, 3, 6, 9, 12, 15, 18, 21, 24};

char *submultiples_name[] = {"deci", "centi", "mili", "micro", "nano", "pico", "femto", "atto", "zepto", "yocto"};
char *submultiples_symbol[] = {"d", "c", "m", "u", "n", "p", "f", "a", "z", "y"}; /* symbol for 'micro' is replaced by 'u' */
int *submultiples_factor = {-1, -2, -3, -6, -9, -12, -15, -18, -21, -24};

/* non official prefixes */
/* micron = 1 um */
/* angstrom = 0.1 nm */
/* fermi = 1 fm */
/* myriameter = 10 km */


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

/* Non-SI units accepted for use with SI */
/* minute, hour, day, degree of arc, minute of arc, second of arc, hectare, liter, tonne, astronomical unit, decibel
 *
 *
 */

/* create SI units and return them as linked list */
unit_t *si_sistem_list(init_t **tail){

	unit_t *head = NULL;


	/* set imperial weight units
	 * ------------------------- */
	/* meter */
	*tail =
	nodeunit(METER_SI_ID, Q_LENGTH, SI_SYSTEM, "meter", "m", METER_SI_ID,
		1, -1, -1, -1, &head);

	return head;
}

