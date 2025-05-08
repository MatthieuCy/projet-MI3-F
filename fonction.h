#ifndef FONCTION_H
#define FONCTION_H

#include "animal.h"

void calculer_nettoyage_hebdo( Animal* animaux, int nb_animaux);
void affiche_animaux(Animal *animaux);
void affiche_nourriture(Animal *animaux);
void afficher_par_tranche_age( Animal* animaux, int nb_animaux);
void menu();
void ajouter_animal();
void rechercher_animaux();
void adopter_animal();
void afficher_animal(Animal a);
int type_age(int age);

#endif
