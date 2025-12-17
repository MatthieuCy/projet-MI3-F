#ifndef HISTO_H
#define HISTO_H


#include "avl.h"


typedef struct
{
    char *identifiant; 
    double volume_max; 
    double volume_source; 
    double volume_reel; 
} DonneesUsine;


int histo_traiter(const char *fichier_entree, const char *fichier_sortie, const char *mode);

#endif
