/*
 * =====================================
 * 	          tempconv
 * 	Temperature value conversions		
 * =====================================
 */


#include <stdlib.h>
#include "global_def.h"
#include "wam_unit.h"

const char KELVIN[] = "kelvin";
const char CELSIUS[] = "celsius";
const char FAHRENHEIT[] = "fahrenheit";


/*  Convert Celsius temperature value to Fahrenheit temperature value */
float cel_to_fahr(float cel)
{
	return (9 * cel)/5 + 32; 
}


float cel_to_kel(float cel)
{
	return cel + 273.15;
}


/* Convert Fahrenheit temperature value to Celsius temperature value */
float fahr_to_cel(float fahr)
{
	return (5.0/9) * (fahr-32); 
}


float fahr_to_kel(float fahr)
{
	return (fahr + 459.67) * (5.0/9);
}


float kel_to_cel(float kel)
{
	return kel - 273.15;
}


float kel_to_fahr(float kel)
{
	return kel * (9.0/5) - 459.67;
}


float scel_to_fahr(const char *scel)
{
	float cel = (float)atof(scel);

	return cel_to_fahr(cel);	
}


float scel_to_kel(const char *scel)
{
	float cel = (float)atof(scel);

	return cel_to_kel(cel);	
}


float sfahr_to_cel(const char *sfahr)
{
	float fahr = (float)atof(sfahr);

	return fahr_to_cel(fahr);	
}


float sfahr_to_kel(const char *sfahr)
{
	float fahr = (float)atof(sfahr);

	return fahr_to_kel(fahr);	
}


float skel_to_cel(const char *skel)
{
	float kel = (float)atof(skel);

	return kel_to_cel(kel);	
}


float skel_to_fahr(const char *skel)
{
	float kel = (float)atof(skel);

	return kel_to_fahr(kel);	
}



int KELVIN_ID = 'k';
int FAHRENHEIT_ID = 'f';
int CELSIUS_ID = 'c';


/* create list and allocate space for temperature units */
unit_t *temperature_list(unit_t **tail)
{

	unit_t *head = NULL;

	/* set temperature system units
	 * ----------------------- */
	/* kelvin */
	*tail =
	nodeunit(KELVIN_ID, Q_TEMPERATURE, TEMPERATURE, "kelvin", "k", CELSIUS_ID, -1,
			 -1, -1, -1, &head);
	/* fahrenheit */
	nodeunit(FAHRENHEIT_ID, Q_TEMPERATURE, TEMPERATURE, "fahrenheit", "f", 
			CELSIUS_ID, -1, -1, -1, -1, &head);
	/* celsius */
	nodeunit(CELSIUS_ID, Q_TEMPERATURE, TEMPERATURE, "celsius", "c", CELSIUS_ID,
		 	-1, -1, -1, -1, &head);

	return head;
}
