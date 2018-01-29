/*
 * =====================================
 * 	          tempconv
 * 	Temperature value conversions		
 * =====================================
 */


#include <stdlib.h>



/* 
 * Convert Celsius temperature value to Fahrenheit temperature value 
 */
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

