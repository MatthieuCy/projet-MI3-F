#ifndef FICHIER_H
#define FICHIER_H

#include "animal.h"

int charger_animaux( char* nom_fichier, Animal* animaux, int max);
void sauvegarder_animaux( char* nom_fichier, Animal* animaux, int nb);

#endif
