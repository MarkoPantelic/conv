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

double cel_to_kel(double cel);
double cel_to_fahr(double cel);
double fahr_to_cel(double fahr);
double fahr_to_kel(double fahr);
double kel_to_cel(double kel);
double kel_to_fahr(double kel);

double scel_to_kel(const char *scel);
double scel_to_fahr(const char *scel);
double sfahr_to_cel(const char *sfahr);
double sfahr_to_kel(const char *sfahr);
double skel_to_cel(const char *skel);
double skel_to_fahr(const char *skel);

unit_t *temperature_list(unit_t **tail);

#endif /* _TEMPCONV_H */
