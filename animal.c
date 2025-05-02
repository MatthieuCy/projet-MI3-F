#include <stdio.h>
#include <string.h>
#include "animal.h"

Animal creer_animal(int id, const char* nom, const char* espece, int annee, float poids, const char* commentaire) {
    Animal a;
    a.id = id;
    strncpy(a.nom, nom, sizeof(a.nom));
    strncpy(a.espece, espece, sizeof(a.espece));
    a.annee_naissance = annee;
    a.poids = poids;
    strncpy(a.commentaire, commentaire, sizeof(a.commentaire));
    return a;
}

void afficher_animal(Animal a) {
    printf("ID: %d\nNom: %s\nEspèce: %s\nAnnée: %d\nPoids: %.2f kg\nCommentaire: %s\n",
           a.id, a.nom, a.espece, a.annee_naissance, a.poids, a.commentaire);
}
