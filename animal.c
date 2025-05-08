#include <stdio.h>
#include <string.h>
#include "animal.h"

Animal creer_animal(int id, const char* nom, const char* espece, int annee, float poids, const char* commentaire) {
    Animal a;
    a.id = id;
    strncpy(a.nom, nom, sizeof(a.nom)-1);
    strncpy(a.espece, espece, sizeof(a.espece)-1);
    a.annee_naissance = annee;
    a.poids = poids;
    strncpy(a.commentaire, commentaire, sizeof(a.commentaire)-1);
    return a;
}

void afficher_animal(Animal a) {
    printf("ID: %d\nNom: %s\nEspèce: %s\nAnnée: %d\nPoids: %.2f kg\nCommentaire: %s\n",
           a.id, a.nom, a.espece, a.annee_naissance, a.poids, a.commentaire);
}


int charger_animaux(const char* nom_fichier, Animal* animaux, int max) {
    FILE* f = fopen(nom_fichier, "r");
    if (!f) return 0;

    int count = 0;
    char ligne[512];
    while (fgets(ligne, sizeof(ligne), f) && count < max) {
        Animal a;
        //remplir un animal
        if (sscanf(ligne, "%d;%[^;];%[^;];%d;%f;%[^\n]",
                   &a.id, a.nom, a.espece, &a.annee_naissance, &a.poids, a.commentaire) == 6) {
            animaux[count++] = a;
        }
    }

    fclose(f);
    return count;
}

void sauvegarder_animaux(const char* nom_fichier, Animal* animaux, int nb) {
    FILE* f = fopen(nom_fichier, "w");
    if (!f) return;

    for (int i = 0; i < nb; i++) {
     //affichage dans le termianl de tous les données des animaux
        fprintf(f, "%d;%s;%s;%d;%.2f;%s\n",
                animaux[i].id, animaux[i].nom, animaux[i].espece,
                animaux[i].annee_naissance, animaux[i].poids, animaux[i].commentaire);
    }

    fclose(f);
}
