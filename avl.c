#include "avl.h"
#include <string.h>
#include <stdio.h>


int avl_hauteur(NoeudAVL *noeud)
{
    if (noeud == NULL)
        return 0;
    return noeud->hauteur; 
}


static int avl_equilibre(NoeudAVL *noeud)
{
    if (noeud == NULL)
        return 0;
    
    return avl_hauteur(noeud->gauche) - avl_hauteur(noeud->droite);
}

static int max(int a, int b)
{
    return (a > b) ? a : b;
}


static void mettre_a_jour_hauteur(NoeudAVL *noeud)
{
   
    noeud->hauteur = 1 + max(avl_hauteur(noeud->gauche), avl_hauteur(noeud->droite));
}


NoeudAVL *avl_creer_noeud(const char *cle, void *donnee)
{
    
    NoeudAVL *noeud = malloc(sizeof(NoeudAVL));
    if (noeud == NULL)
        return NULL;
    noeud->cle = strdup(cle);
    if (noeud->cle == NULL)
    {
        free(noeud);
        return NULL;
    }
    noeud->donnee = donnee;
    noeud->hauteur = 1;
    noeud->gauche = NULL;
    noeud->droite = NULL;
    return noeud;
}

static NoeudAVL *rotation_droite(NoeudAVL *y)
{
    NoeudAVL *x = y->gauche;
    NoeudAVL *T2 = x->droite;
    x->droite = y;
    y->gauche = T2;
    // Use the renamed update function
    mettre_a_jour_hauteur(y);
    mettre_a_jour_hauteur(x);
    return x;
}

static NoeudAVL *rotation_gauche(NoeudAVL *x)
{
    NoeudAVL *y = x->droite;
    NoeudAVL *T2 = y->gauche;
    y->gauche = x;
    x->droite = T2;
    // Use the renamed update function
    mettre_a_jour_hauteur(x);
    mettre_a_jour_hauteur(y);
    return y;
}


NoeudAVL *avl_inserer(NoeudAVL *racine, const char *cle, void *donnee, NoeudAVL **trouve)
{
    if (racine == NULL)
    {
        
        NoeudAVL *noeud = avl_creer_noeud(cle, donnee);
        if (trouve)
            *trouve = noeud;
        return noeud;
    }

    
    int cmp = strcmp(cle, racine->cle);
    if (cmp < 0)
    {
      
        racine->gauche = avl_inserer(racine->gauche, cle, donnee, trouve);
    }
    else if (cmp > 0)
    {
        
        racine->droite = avl_inserer(racine->droite, cle, donnee, trouve);
    }
    else
    {
        if (trouve)
            *trouve = racine;
        return racine;
    }

    
   NoeudAVL * mettre_a_jour_hauteur(racine){
    int balance = avl_equilibre(racine);

   
    if (balance > 1 && strcmp(cle, racine->gauche->cle) < 0)
        return rotation_droite(racine);

   
    if (balance < -1 && strcmp(cle, racine->droite->cle) > 0)
        return rotation_gauche(racine);

    
    if (balance > 1 && strcmp(cle, racine->gauche->cle) > 0)
    {
        
        racine->gauche = rotation_gauche(racine->gauche);
        return rotation_droite(racine);
    }

    
    if (balance < -1 && strcmp(cle, racine->droite->cle) < 0)
    {
        
        racine->droite = rotation_droite(racine->droite);
        return rotation_gauche(racine);
    }

    return racine;
}


NoeudAVL *avl_rechercher(NoeudAVL *racine, const char *cle)
{
    if (racine == NULL)
        return NULL;
    int cmp = strcmp(cle, racine->cle);
    if (cmp < 0)
        
        return avl_rechercher(racine->gauche, cle);
    if (cmp > 0)
        
        return avl_rechercher(racine->droite, cle);
    return racine;
}


void avl_parcourir_inverse(NoeudAVL *racine, void (*rappel)(NoeudAVL *, void *), void *arg)
{
    if (racine == NULL)
        return;
    /
    avl_parcourir_inverse(racine->droite, rappel, arg);
    rappel(racine, arg);
    
    avl_parcourir_inverse(racine->gauche, rappel, arg);
}


void avl_liberer(NoeudAVL *racine, void (*liberer_donnee)(void *))
{
    if (racine == NULL)
        return;
    
    avl_liberer(racine->gauche, liberer_donnee);
    avl_liberer(racine->droite, liberer_donnee);
    free(racine->cle);
    if (liberer_donnee && racine->donnee)
        liberer_donnee(racine->donnee);
    free(racine);
}


int avl_compter(NoeudAVL *racine)
{
    if (racine == NULL)
        return 0;
    // Use the renamed struct member and avl_compter function
    return 1 + avl_compter(racine->gauche) + avl_compter(racine->droite);
}
