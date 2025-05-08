#include "main.h"
 #include <stdio.h>
#include <stdlib.h>



void afficher_menu_principal() {
    int choix;

    do {
        printf("\n");
        printf("=====================================\n");
        printf("🐾  Bienvenue au ChenYl-Tech Refuge  🐾\n");
        printf("=====================================\n");
        printf("Veuillez choisir une action :\n");
        printf("1. 🔍 Rechercher un ou plusieurs animaux\n");
        printf("2. ➕ Ajouter un nouvel animal\n");
        printf("3. ❤️ Adoption d'un animal\n");
     
        printf("0. 🚪 Quitter l'application\n");
        printf("Votre choix : ");
        
        if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide. Veuillez saisir un chiffre.\n");
            while (getchar() != '\n'); // vider le buffer
            continue;
        }

        switch (choix) {
            case 1:
                rechercher_animaux();
                break;
            case 2:
                ajouter_animal();
                break;
            case 3:
                adopter_animal();
                break;
            case 0:
                printf("Fermeture de l'application... À bientôt !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choix != 0);
}
