#ifndef LEAKS_H
#define LEAKS_H


#include "avl.h"

typedef struct MaillonEnfant
{
    struct NoeudArbre *enfant;      
    struct MaillonEnfant *suivant;  
} MaillonEnfant;


typedef struct NoeudArbre
{
    char *identifiant;      
    double pourcentage_fuite; 
    int compte_enfants;     
    MaillonEnfant *enfants; 
} NoeudArbre;


int fuites_traiter(const char *fichier_entree, const char *fichier_sortie, const char *id_usine);

#endif // LEAKS_H
