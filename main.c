#include <stdio.h>
#include "animal.h"

int main() {
    Animal animaux[TAILLE_MAX];
    int nb_animaux = charger_animaux(FICHIER_DATA, animaux, TAILLE_MAX);

    int choix;
    do {
        printf("\n--- Menu du refuge ---\n");
        printf("1. Ajouter un animal\n");
        printf("2. Afficher les animaux\n");
        printf("3. Rechercher un animal\n");
        printf("4. Enregistrer et quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_animal(animaux, &nb_animaux);
                break;
            case 2:
                afficher_animaux(animaux, nb_animaux);
                break;
            case 3:
                rechercher_animaux(animaux, nb_animaux);
                break;
            case 4:
                enregistrer_animaux(FICHIER_DATA, animaux, nb_animaux);
                printf("Données enregistrées. Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 4);

    return 0;
}

