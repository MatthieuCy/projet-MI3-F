#include <stdio.h>
#include "main.h"

 do {
        afficher_menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1: rechercher_animaux(animaux, nb_animaux); break;
            case 2: ajouter_animal(animaux, &nb_animaux); break;
            case 3: {
                int id;
                printf("ID de l’animal à adopter : ");
                scanf("%d", &id);
                adopter_animal(animaux, &nb_animaux, id);
                break;
            }
            case 4: inventaire_desc(animaux, nb_animaux); break;
            case 5: inventaire_age(animaux, nb_animaux); break;
            case 6: besoin_croquettes(animaux, nb_animaux); break;
            case 7: charge_nettoyage(animaux, nb_animaux); break;
            case 0: sauvegarder_animaux(animaux, nb_animaux); break;
            default: printf("Choix invalide.\n");
        }
