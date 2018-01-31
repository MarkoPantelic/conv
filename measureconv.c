/*============================================
 *		    measureconv
 *	Conversions between measure units
 *============================================*/


#include <stdlib.h>

/* 
 * Return value how much metric grams are in one ounce depending on ounce variant argument.
 * If 'variant' is invalid return 0 
 */
float ginounce(char variant)
{
	switch (variant){

		case 'a': /* avoirdupois ounce */
			return 28.349523125; 
		case 't': /* troy ounce */
			return 31.1034768; 
		case 'd': /* Dutch ounce (ons)  */
			return 100;
		case 'm': /* Maria Theresa ounce (birr in Ethiopia) */
			return 28.0668;
		case 's': /* Spanish ounce (onza) */
			return 28.75;
		case 'f': /* French ounce (once) */
			return 30.59;
		case 'p': /* Portuguese ounce (onca) */
			return 28.69;
		case 'c': /* Chinese metric ounce */
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
