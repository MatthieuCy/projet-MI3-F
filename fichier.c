#include <stdio.h>
#include <string.h>
#include "fichier.h"

int charger_animaux(const char* nom_fichier, Animal* animaux, int max) {
    FILE* f = fopen(nom_fichier, "r");
    if (!f) return 0;

    int count = 0;
    char ligne[512];
    while (fgets(ligne, sizeof(ligne), f) && count < max) {
        Animal a;
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
        fprintf(f, "%d;%s;%s;%d;%.2f;%s\n",
                animaux[i].id, animaux[i].nom, animaux[i].espece,
                animaux[i].annee_naissance, animaux[i].poids, animaux[i].commentaire);
    }

    fclose(f);
}
