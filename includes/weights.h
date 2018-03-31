/*============================================
 *          h file for measureconv.c
 *	Conversions between measure units
 *============================================*/

#ifndef _MEASURECONV_H
#define _MEASURECONV_H

/* constants for different versions of ounce */
#define AVOIRDUPOIS_OZ 1
#define TROY_OZ 2
#define DUTCH_OZ 3
#define THERESIA_OZ 4
#define SPANISH_OZ 5
#define FRENCH_OZ 6
#define PORTUGUESE_OZ 7
#define CHINESE_OZ 8

extern const char OUNCE[];
extern const char GRAM[];


float ouncetog(float ounce, char variant);
float gtoounce(float gram, char variant);

float souncetog(const char *strounce, char variant);
float sgtoounce(const char *strgram, char variant);

#endif /* _MEASURE_CONV_H */
