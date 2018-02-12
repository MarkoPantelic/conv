#ifndef _SI_SYSTEM_H
#define _SI_SYSTEM_H

#include "wam_unit.h"

/* id's of base units */
enum {KG_SI_ID, METER_SI_ID, SECOND_SI_ID, AMPERE_SI_ID, KELVIN_SI_ID, MOLE_SI_ID, CANDELA_SI_ID, HECTAR_SI_ID, G_SI_ID} ;

unit_t *si_system_list(unit_t **tail);

#endif /* _SI_SYSTEM_H */
