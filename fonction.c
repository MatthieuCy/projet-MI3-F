#include "fonction.h"
#include <stdio.h>
#include <string.h>

#define QUARTILE_AGE_1 5
#define QUARTILE_AGE_2 10
#define QUARTILE_AGE_3 15

// Fonction pour calculer l'âge de l'animal en fonction de son année de naissance
int calculer_age(int annee_naissance) {
    return 2025 - annee_naissance;
}



// Affiche la nourriture en fonction des animaux
void affiche_nourriture(Animal* animaux, int nb_animaux) {
    for (int i = 0; i < nb_animaux; i++) {
        // Exemple de condition pour donner des nourritures spécifiques
        if (strcmp(animaux[i].espece, "autruche") == 0) {
            printf("%s mange du foin.\n", animaux[i].nom);
        } else if (strcmp(animaux[i].espece, "hamster") == 0) {
            printf("%s mange des graines.\n", animaux[i].nom);
        } else if (strcmp(animaux[i].espece, "chien") == 0 || strcmp(animaux[i].espece, "chat") == 0) {
            printf("%s mange des croquettes.\n", animaux[i].nom);
        }
    }
}

// Calcule le nettoyage hebdomadaire
void calculer_nettoyage_hebdo(Animal* animaux, int nb_animaux) {
    int total_chien = 0, total_chat = 0, total_hamster = 0, total_autruche = 0;

    // Compte les animaux par espèce
    for (int i = 0; i < nb_animaux; i++) {
        if (strcmp(animaux[i].espece, "chien") == 0) total_chien++;
        else if (strcmp(animaux[i].espece, "chat") == 0) total_chat++;
        else if (strcmp(animaux[i].espece, "hamster") == 0) total_hamster++;
        else if (strcmp(animaux[i].espece, "autruche") == 0) total_autruche++;
    }

    int total_quotidien = total_hamster * 10 + total_chat * 10 + total_autruche * 20 + total_chien * 5;
    int total_hebdo = total_hamster * 20 + total_chat * 20 + total_autruche * 45 + total_chien * 20;

    // Ajoute nettoyage des cages vides : 2 min/jour
    int max_cages = 50;
    int nb_animaux_total = total_chien + total_chat + total_hamster + total_autruche;
    int cages_vides = max_cages - nb_animaux_total;
    total_quotidien += cages_vides * 2;

    printf("\n🧽 Charge de nettoyage hebdomadaire :\n");
    printf("- Minutes de nettoyage quotidien total (x7 jours) : %d min\n", total_quotidien * 7);
    printf("- Minutes de nettoyage hebdomadaire : %d min\n", total_hebdo);
    printf("🧼 ➤ Temps total pour la semaine : %d min (soit %.2f heures)\n",
           total_quotidien * 7 + total_hebdo,
           (total_quotidien * 7 + total_hebdo) / 60.0);
}

// Affiche la répartition des animaux par tranche d'âge
void afficher_par_tranche_age(Animal* animaux, int nb_animaux) {
    int tranche1 = 0, tranche2 = 0, tranche3 = 0, tranche4 = 0;

    for (int i = 0; i < nb_animaux; i++) {
        int age = calculer_age(animaux[i].annee_naissance);
        if (age < QUARTILE_AGE_1) {
            tranche1++;
        } else if (age < QUARTILE_AGE_2) {
            tranche2++;
        } else if (age < QUARTILE_AGE_3) {
            tranche3++;
        } else {
            tranche4++;
        }
    }

    printf("\n📊 Répartition par tranche d'âge (INV_AGE_ASC) :\n");
    printf("Total d'animaux : %d\n", nb_animaux);
    printf("- Moins de %d ans : %d animaux\n", QUARTILE_AGE_1, tranche1);
    printf("- Moins de %d ans : %d animaux\n", QUARTILE_AGE_2, tranche2);
    printf("- Moins de %d ans : %d animaux\n", QUARTILE_AGE_3, tranche3);
    printf("- Plus de %d ans : %d animaux\n", QUARTILE_AGE_3, tranche4);
}
