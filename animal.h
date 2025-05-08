#ifndef ANIMAL_H
#define ANIMAL_H
#define MAX_NOM 50
#define MAX_ESPECE 30
#define MAX_COMMENTAIRE 200

typedef struct {
    int id;
    char nom[MAX_NOM];
    char espece[MAX_ESPECE];   // Chien, Chat, etc.
    int annee_naissance;
    float poids;
    char commentaire[MAX_COMMENTAIRE];
} Animal;

// Fonctions
Animal creer_animal(int id, const char* nom, const char* espece, int annee, float poids, const char* commentaire);
void afficher_animal(Animal a);

int charger_animaux(const char* nom_fichier, Animal* animaux, int max);
  
void sauvegarder_animaux(const char* nom_fichier, Animal* animaux, int nb);
#endif
