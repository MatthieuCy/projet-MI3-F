#ifndef AVL_H
#define AVL_H

#include <stdlib.h>

typedef struct NoeudAVL
{
    char *cle; 
    void *donnee; 
    int hauteur; 
    struct NoeudAVL *gauche; 
    struct NoeudAVL *droite; 
} NoeudAVL; 

NoeudAVL *avl_creer_noeud(const char *cle, void *donnee);
NoeudAVL *avl_inserer(NoeudAVL *racine, const char *cle, void *donnee, NoeudAVL **trouve);
NoeudAVL *avl_rechercher(NoeudAVL *racine, const char *cle);
void avl_parcourir_inverse(NoeudAVL *racine, void (*rappel)(NoeudAVL *, void *), void *arg);
void avl_liberer(NoeudAVL *racine, void (*liberer_donnee)(void *));
int avl_hauteur(NoeudAVL *noeud);
int avl_compter(NoeudAVL *racine);

#endif // AVL_H
