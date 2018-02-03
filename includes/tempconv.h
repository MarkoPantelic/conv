/*
 * =====================================
 *         h file for tempconv.c
 *     temperature values conversions		
 * =====================================
 */

#ifndef _TEMPCONV_H
#define _TEMPCONV_H

extern const char KELVIN[];
extern const char CELSIUS[];
extern const char FAHRENHEIT[];

float cel_to_kel(float cel);
float cel_to_fahr(float cel);
float fahr_to_cel(float fahr);
float fahr_to_kel(float fahr);
float kel_to_cel(float kel);
float kel_to_fahr(float kel);

float scel_to_kel(const char *scel);
float scel_to_fahr(const char *scel);
float sfahr_to_cel(const char *sfahr);
float sfahr_to_kel(const char *sfahr);
float skel_to_cel(const char *skel);
float skel_to_fahr(const char *skel);

#endif /* _TEMPCONV_H */
