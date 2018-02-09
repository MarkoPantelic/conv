#include <stdlib.h>
#include <stdio.h>


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
