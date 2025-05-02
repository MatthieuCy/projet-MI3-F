#ifndef FICHIER_H
#define FICHIER_H

#include "animal.h"

int charger_animaux(const char* nom_fichier, Animal* animaux, int max);
void sauvegarder_animaux(const char* nom_fichier, Animal* animaux, int nb);

#endif
