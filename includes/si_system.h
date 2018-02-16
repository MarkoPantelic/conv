#ifndef _SI_SYSTEM_H
#define _SI_SYSTEM_H

#include "unit.h"

/* id's of base units */
enum {G_SI_ID=1, KG_SI_ID, METER_SI_ID, SECOND_SI_ID, AMPERE_SI_ID, KELVIN_SI_ID, MOLE_SI_ID, CANDELA_SI_ID, METER_SQUARE_SI_ID} ;


unit_t *si_system_list(unit_t **tail, prefix_t *prfx_lst);

prefix_t *si_prefix_list(void);

unit_t *si_node(int id, int qnt, int sys, char *fn, char *sym, int sbuid, 
	     double rtbu, prefix_t *prfx_head, unit_t **head);


#endif /* _SI_SYSTEM_H */
