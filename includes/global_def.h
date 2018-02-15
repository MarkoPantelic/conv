
#ifndef _GLOBAL_DEF_H
#define _GLOBAL_DEF_H

/* define system id's */
#define IMPERIAL_SYS 1
#define SI_SYSTEM 2
#define NUMBER_SYS 3
#define TEMPERATURE 4
#define OTHER_UNITS 5

/* define quantity id's */
#define Q_MASS 1
#define Q_LENGTH 2
#define Q_TIME 3
#define Q_EL_CURRENT 4
#define Q_SUBSTANCE_A 5
#define Q_AREA 6
#define Q_VOLUME 7
#define Q_NUMBER 8
#define Q_TEMPERATURE 9
#define Q_LUMINOUS_I 10

/* to be moved to other_units.h or non_si_compat.h */ 
#define LITER_OU_ID 1


extern const char *SYSTEM_STR_LIST[];
extern const char *QUANTITY_STR_LIST[];

void *xmalloc(size_t n);

#endif /* _GLOBAL_DEF_H */
