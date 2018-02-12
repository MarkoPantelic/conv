#include <stdlib.h>
#include <stdio.h>

/* these const char *x[] element members must have equal position within x
 * array paralleling the value of int constants defined in global_def.h */
const char *SYSTEM_STR_LIST[] = {"no system", "imperial", "SI system", "number", "temperature"};
const char *QUANTITY_STR_LIST[] = {"no quantity", "weight", "lenght", "time", "electric current", "amount of substance", "area", "volume", "number", "thermodynamic temperature", "luminous intensity"};

/* Allocate memory. If errors, notify and exit.*/
void *xmalloc(size_t n)
{
	void *m;

	if ( (m = malloc(n)) == NULL ){
		printf("Cannot allocate enough memory! Exiting...\n");
		exit(EXIT_FAILURE);
	}

	return m;
}
