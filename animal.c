#include <stdio.h>
#include <string.h>
#include "animal.h"

void afficher_animal(Animal a) {
    printf("Nom : %s\n", a.nom);
    printf("Âge : %d\n", a.age);
    printf("Race : %s\n", a.race);
    printf("Genre : %c\n", a.genre);
    printf("Commentaire : %s\n", a.commentaire);
}

void ajouter_animal(Animal* animaux, int* nb_animaux) {
    if (*nb_animaux >= TAILLE_MAX) {
        printf("Le refuge est plein.\n");
        return;
    }

    Animal a;

    printf("Nom : ");
    scanf("%s", a.nom);
    printf("Âge : ");
    scanf("%d", &a.age);
    getchar();  // nettoie le buffer
    printf("Race : ");
    fgets(a.race, NOM_TAILLE, stdin);
    a.race[strcspn(a.race, "\n")] = 0;

    printf("Genre (M/F) : ");
    scanf(" %c", &a.genre);
    getchar();
    printf("Commentaire : ");
    fgets(a.commentaire, COMMENTAIRE_TAILLE, stdin);
    a.commentaire[strcspn(a.commentaire, "\n")] = 0;

    animaux[*nb_animaux] = a;
    (*nb_animaux)++;

    printf("Animal ajouté avec succès.\n");
}

int charger_animaux(const char* nom_fichier, Animal* animaux, int max) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Aucun fichier existant. Création en cours.\n");
        return 0;
    }

    int nb = 0;
    while (nb < max &&
           fscanf(fichier, "%s %d %s %c %[^\n]", animaux[nb].nom, &animaux[nb].age,
                  animaux[nb].race, &animaux[nb].genre, animaux[nb].commentaire) == 5) {
        nb++;
    }

    fclose(fichier);
    return nb;
}

void enregistrer_animaux(const char* nom_fichier, Animal* animaux, int nb_animaux) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        printf("Erreur d'écriture du fichier.\n");
        return;
    }

    for (int i = 0; i < nb_animaux; i++) {
        fprintf(fichier, "%s %d %s %c %s\n", animaux[i].nom, animaux[i].age,
                animaux[i].race, animaux[i].genre, animaux[i].commentaire);
    }

    fclose(fichier);
}

void afficher_animaux(Animal* animaux, int nb_animaux) {
    for (int i = 0; i < nb_animaux; i++) {
        printf("\nAnimal %d:\n", i + 1);
        afficher_animal(animaux[i]);
    }
}

void rechercher_animaux(Animal* animaux, int nb_animaux) {
    char nom_recherche[NOM_TAILLE];
    printf("Nom à rechercher : ");
    scanf("%s", nom_recherche);

    int trouve = 0;
    for (int i = 0; i < nb_animaux; i++) {
        if (strcmp(animaux[i].nom, nom_recherche) == 0) {
            afficher_animal(animaux[i]);
            trouve = 1;
        }
    }

    if (!trouve)
        printf("Aucun animal trouvé avec ce nom.\n");
}

int adopter_animal_par_id(Animal* animaux, int* nb_animaux, int id_a_supprimer) {
    int trouve = 0;

    for (int i = 0; i < *nb_animaux; i++) {
        if (animaux[i].id == id_a_supprimer) {
            trouve = 1;
            // Décaler les animaux suivants
            for (int j = i; j < *nb_animaux - 1; j++) {
                animaux[j] = animaux[j + 1];
            }
            (*nb_animaux)--;
            break;
        }
    }

    if (trouve) {
        printf("🎉 L'animal avec l'ID %d a été adopté avec succès !\n", id_a_supprimer);
    } else {
        printf("❌ Aucun animal trouvé avec l'ID %d.\n", id_a_supprimer);
    }

    return trouve;
}


void afficher_nombre_total_animaux(int nb_animaux) {
    printf("Le nombre total d'animaux dans le refuge est : %d\n", nb_animaux);
}

int comparer_race(const void* a, const void* b) {
    return strcmp(((Animal*)b)->race, ((Animal*)a)->race);  // Tri décroissant
}

void afficher_nombre_par_espece(Animal* animaux, int nb_animaux) {
    char races[TAILLE_MAX][NOM_TAILLE];
    int nombre_par_race[TAILLE_MAX] = {0};
    int race_count = 0;

    for (int i = 0; i < nb_animaux; i++) {
        int existe = 0;
        for (int j = 0; j < race_count; j++) {
            if (strcmp(animaux[i].race, races[j]) == 0) {
                existe = 1;
                break;
            }
        }

        if (!existe) {
            strcpy(races[race_count], animaux[i].race);
            nombre_par_race[race_count] = 1;
            race_count++;
        } else {
            for (int j = 0; j < race_count; j++) {
                if (strcmp(animaux[i].race, races[j]) == 0) {
                    nombre_par_race[j]++;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < race_count - 1; i++) {
        for (int j = i + 1; j < race_count; j++) {
            if (nombre_par_race[i] < nombre_par_race[j]) {
                char temp[NOM_TAILLE];
                strcpy(temp, races[i]);
                strcpy(races[i], races[j]);
                strcpy(races[j], temp);

                int temp_count = nombre_par_race[i];
                nombre_par_race[i] = nombre_par_race[j];
                nombre_par_race[j] = temp_count;
            }
        }
    }

    printf("\nNombre d'animaux par espèce (race) :\n");
    for (int i = 0; i < race_count; i++) {
        printf("%s : %d\n", races[i], nombre_par_race[i]);
    }
}

void calculer_croquettes(Animal* animaux, int nb_animaux) {
    double total_croquettes = 0.0;

    for (int i = 0; i < nb_animaux; i++) {
        if (strcmp(animaux[i].race, "hamster") == 0) {
            total_croquettes += 20;  // 20g pour un hamster
        } else if (strcmp(animaux[i].race, "autruche") == 0) {
            total_croquettes += 2500;  // 2.5kg pour une autruche, soit 2500g
        } else if (strcmp(animaux[i].race, "chat") == 0 || strcmp(animaux[i].race, "chien") == 0) {
            if (animaux[i].age < 2) {
                total_croquettes += 500;  // Moins de 2 ans : 500g pour un chat/chien
            } else {
                total_croquettes += 0.1 * animaux[i].age;  // Plus de 2 ans : 10% de son poids en croquettes
            }
        }
    }

    printf("Quantité totale de croquettes nécessaires : %.2f g\n", total_croquettes);
}
