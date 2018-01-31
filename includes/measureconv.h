/*============================================
 *          h file for measureconv.c
 *	Conversions between measure units
 *============================================*/

const char OUNCE[] = "ounce";
const char GRAM[] = "gram";


float ouncetog(float ounce, char variant);
float gtoounce(float gram, char variant);

float souncetog(const char *strounce, char variant);
float sgtoounce(const char *strgram, char variant);
