#ifndef ANIMAL_H
#define ANIMAL_H

typedef struct {
    int id;
    char nom[50];
    char espece[30];   // Chien, Chat, etc.
    int annee_naissance;
    float poids;
    char commentaire[200];
} Animal;

// Fonctions
Animal creer_animal(int id,  char* nom,  char* espece, int annee, float poids, char* commentaire);
void afficher_animal(Animal a);

#endif
