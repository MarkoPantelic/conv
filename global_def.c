#include <stdlib.h>
#include <stdio.h>

const char *SYSTEM_STR_LIST[] = {"no system", "imperial", "SI system", "number", "temperature"};
const char *QUANTITY_STR_LIST[] = {"no quantity", "weight", "lenght", "area", "volume", "number", "temperature"};

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
