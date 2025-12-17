#include "avl.h"
#include <string.h>
#include <stdio.h>

// Renamed avl_height to avl_hauteur
int avl_hauteur(NoeudAVL *noeud)
{
    if (noeud == NULL)
        return 0;
    return noeud->hauteur; // Use the renamed struct member
}

// Renamed avl_balance to avl_equilibre
static int avl_equilibre(NoeudAVL *noeud)
{
    if (noeud == NULL)
        return 0;
    // Use the renamed avl_hauteur function and struct members
    return avl_hauteur(noeud->gauche) - avl_hauteur(noeud->droite);
}

static int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Renamed update_height to mettre_a_jour_hauteur
static void mettre_a_jour_hauteur(NoeudAVL *noeud)
{
    // Use the renamed avl_hauteur function and struct members
    noeud->hauteur = 1 + max(avl_hauteur(noeud->gauche), avl_hauteur(noeud->droite));
}

// Renamed avl_create_node to avl_creer_noeud
NoeudAVL *avl_creer_noeud(const char *cle, void *donnee)
{
    // Use the renamed struct type
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

// Renamed rotate_right to rotation_droite
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

// Renamed rotate_left to rotation_gauche
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

// Renamed avl_insert to avl_inserer
NoeudAVL *avl_inserer(NoeudAVL *racine, const char *cle, void *donnee, NoeudAVL **trouve)
{
    if (racine == NULL)
    {
        // Use the renamed avl_creer_noeud function and struct type
        NoeudAVL *noeud = avl_creer_noeud(cle, donnee);
        if (trouve)
            *trouve = noeud;
        return noeud;
    }

    // Use the renamed struct member
    int cmp = strcmp(cle, racine->cle);
    if (cmp < 0)
    {
        // Use the renamed struct member and avl_inserer function
        racine->gauche = avl_inserer(racine->gauche, cle, donnee, trouve);
    }
    else if (cmp > 0)
    {
        // Use the renamed struct member and avl_inserer function
        racine->droite = avl_inserer(racine->droite, cle, donnee, trouve);
    }
    else
    {
        if (trouve)
            *trouve = racine;
        return racine;
    }

    // Use the renamed update and balance functions
    mettre_a_jour_hauteur(racine);
    int balance = avl_equilibre(racine);

    // LL Case
    if (balance > 1 && strcmp(cle, racine->gauche->cle) < 0)
        return rotation_droite(racine);

    // RR Case
    if (balance < -1 && strcmp(cle, racine->droite->cle) > 0)
        return rotation_gauche(racine);

    // LR Case
    if (balance > 1 && strcmp(cle, racine->gauche->cle) > 0)
    {
        // Use the renamed struct member and rotation functions
        racine->gauche = rotation_gauche(racine->gauche);
        return rotation_droite(racine);
    }

    // RL Case
    if (balance < -1 && strcmp(cle, racine->droite->cle) < 0)
    {
        // Use the renamed struct member and rotation functions
        racine->droite = rotation_droite(racine->droite);
        return rotation_gauche(racine);
    }

    return racine;
}

// Renamed avl_search to avl_rechercher
NoeudAVL *avl_rechercher(NoeudAVL *racine, const char *cle)
{
    if (racine == NULL)
        return NULL;
    int cmp = strcmp(cle, racine->cle);
    if (cmp < 0)
        // Use the renamed struct member and avl_rechercher function
        return avl_rechercher(racine->gauche, cle);
    if (cmp > 0)
        // Use the renamed struct member and avl_rechercher function
        return avl_rechercher(racine->droite, cle);
    return racine;
}

// Renamed avl_traverse_reverse to avl_parcourir_inverse
void avl_parcourir_inverse(NoeudAVL *racine, void (*rappel)(NoeudAVL *, void *), void *arg)
{
    if (racine == NULL)
        return;
    // Use the renamed struct member and avl_parcourir_inverse function
    avl_parcourir_inverse(racine->droite, rappel, arg);
    rappel(racine, arg);
    // Use the renamed struct member and avl_parcourir_inverse function
    avl_parcourir_inverse(racine->gauche, rappel, arg);
}

// Renamed avl_free to avl_liberer
void avl_liberer(NoeudAVL *racine, void (*liberer_donnee)(void *))
{
    if (racine == NULL)
        return;
    // Use the renamed struct member and avl_liberer function
    avl_liberer(racine->gauche, liberer_donnee);
    avl_liberer(racine->droite, liberer_donnee);
    free(racine->cle);
    if (liberer_donnee && racine->donnee)
        liberer_donnee(racine->donnee);
    free(racine);
}

// Renamed avl_count to avl_compter
int avl_compter(NoeudAVL *racine)
{
    if (racine == NULL)
        return 0;
    // Use the renamed struct member and avl_compter function
    return 1 + avl_compter(racine->gauche) + avl_compter(racine->droite);
}
