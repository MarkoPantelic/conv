#ifndef _NON_SI_COMPAT_H
#define _NON_SI_COMPAT_H

#include "unit.h"

enum {LITER_ID=1, HECTARE_ID} ;


unit_t *si_compat_list(unit_t **tail, prefix_t *si_prfx_lst);


#endif /* _NON_SI_COMPAT_H */
