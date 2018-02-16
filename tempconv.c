/*
 * =====================================
 * 	          tempconv
 * 	Temperature value conversions		
 * =====================================
 */

/* TODO:
 * temperature scales:
 * Rankine, Roemer, Newton, Delisle, Reaumur
 */


#include <stdlib.h>
#include <stdio.h>
#include "global_def.h"
#include "unit.h"

const char KELVIN[] = "kelvin";
const char CELSIUS[] = "celsius";
const char FAHRENHEIT[] = "fahrenheit";


/*  Convert Celsius temperature value to Fahrenheit temperature value */
double cel_to_fahr(double cel)
{
	return (9 * cel)/5 + 32; 
}


double cel_to_kel(double cel)
{
	return cel + 273.15;
}


/* Convert Fahrenheit temperature value to Celsius temperature value */
double fahr_to_cel(double fahr)
{
	double res = 5.0/9 * (fahr-32);
	return res; 
}


double fahr_to_kel(double fahr)
{
	return (fahr + 459.67) * (5.0/9);
}


double kel_to_cel(double kel)
{
	return kel - 273.15;
}


double kel_to_fahr(double kel)
{
	return kel * (9.0/5) - 459.67;
}

/* NOTE next 'float'-s should be set to 'double' 
 * and adequate function found instead of atof()
 * */

double scel_to_fahr(const char *scel)
{
	double cel = atof(scel);

	return cel_to_fahr(cel);	
}


double scel_to_kel(const char *scel)
{
	double cel = atof(scel);

	return cel_to_kel(cel);	
}


double sfahr_to_cel(const char *sfahr)
{
	double fahr = atof(sfahr);

	return fahr_to_cel(fahr);	
}


double sfahr_to_kel(const char *sfahr)
{
	double fahr = atof(sfahr);

	return fahr_to_kel(fahr);	
}


double skel_to_cel(const char *skel)
{
	double kel = atof(skel);

	return kel_to_cel(kel);	
}


double skel_to_fahr(const char *skel)
{
	double kel = atof(skel);

	return kel_to_fahr(kel);	
}



int KELVIN_ID = 'k';
int FAHRENHEIT_ID = 'f';
int CELSIUS_ID = 'c';


/* create temperature unit and connect it to linked list */
unit_t *tempunit(int id, int qnt, int sys, char *name, char *sym, unit_t **head)
{
	/* -1, -1 => no 'base unit' and no 'ratio to base unit' */
	unit_t *u = mknode(id, qnt, sys, name, sym, -1, -1);
	linkunit(head, u);

	return u;
}


/* create list and allocate space for temperature units */
unit_t *temperature_list(unit_t **tail)
{

	unit_t *head = NULL;

	/* set temperature system units
	 * ----------------------- */
	/* kelvin */
	*tail =
	tempunit(KELVIN_ID, Q_TEMPERATURE, TEMPERATURE, "kelvin", "K", &head);
 
	/* fahrenheit */
	tempunit(FAHRENHEIT_ID, Q_TEMPERATURE, TEMPERATURE, "fahrenheit", "F", 
		 &head);

	/* celsius */
	tempunit(CELSIUS_ID, Q_TEMPERATURE, TEMPERATURE, "celsius", "C",
		 &head);

	return head;
}
