
#include <stdio.h>
#include <string.h>
#include "fonction.h"

typedef struct {
    char nom[50];
   int cont;
} AnimalCount;

void affiche_animaux(Animal *animaux) {
    int i, c = 0;
    int chien = 0, chat = 0, autruche = 0, hamster = 0;

    // Comptage du nombre d'animaux présents dans le refuge
 for (i = 0; i < 50; i++) {
        if (strlen(animaux[i].nom) != 0) {
            c++;

            // Comptage du nombre d'animaux par espèce
            if (strcmp(animaux[i].espece, "chien") == 0) {
                chien++;
            } else if (strcmp(animaux[i].espece, "chat") == 0) {
                chat++;
            } else if (strcmp(animaux[i].espece, "autruche") == 0) {
                autruche++;
            } else if (strcmp(animaux[i].espece, "hamster") == 0) {
                hamster++;
            }
        }
    }

    printf("Il y a %d animaux dans le refuge.\n", c);

    // Tableau pour stocker les animaux et leur nombre
    AnimalCount compteEspeces[4] = {
        {"chien", chien},
        {"chat", chat},
        {"autruche", autruche},
        {"hamster", hamster}
    };

    // Tri des animaux par ordre décroissant
    for (i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (compteEspeces[i].cont < compteEspeces[j].cont) {
                AnimalCount temp = compteEspeces[i];
                compteEspeces[i] = compteEspeces[j];
                compteEspeces[j] = temp;
            }
        }
    }

    // Affichage du nombre d'animaux par espèce
    printf("\nNombre d'animaux par espèce :\n");
    for (i = 0; i < 4; i++) {
        if (compteEspeces[i].cont > 0) {
            printf("%s: %d\n", compteEspeces[i].espece, compteEspeces[i].cont);
        }
    }
}


void affiche_nouritture(Animal *animaux){
int i;
for(i=0;i<50;i++){
if(animaux[i].espece=="autruche"){
printf("L'animal numéro %d a besoind de 2.5kg de croquettes par jour.", i);
}
if(animaux[i].espece=="hamster"){
printf("L'animal numéro %d a besoin de 200g par jour", i);
}
if(animaux[i].espece=="chien" || animaux[i].espece=="chat"){
if(2025-refuge[i].annee <2){
printf("L'animal numéro %d a besoin de 500 g par jour", i);
else{
printf("L'animal numéro %d a besoin de %d", i, refuge[i].poids*0.1);
}


void calculer_nettoyage_hebdo(Animal* animaux, int nb_animaux) {
    
    FILE* f = fopen("animaux/data.txt", "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier animaux/data.txt\n");
        return;
    }

    int total_chien = 0, total_chat = 0, total_hamster = 0, total_autruche = 0;

  char ligne[512];
    while (fgets(ligne, sizeof(ligne), f)) {
        int id;
        char nom[100], espece[30];

        // Lecture de l'identifiant, du nom, et de l'espèce 
        if (sscanf(ligne, "%d;%[^;];%[^;]", &id, nom, espece) == 3) {
            if (strcmp(espece, "chien") == 0) total_chien++;
            else if (strcmp(espece, "chat") == 0) total_chat++;
            else if (strcmp(espece, "hamster") == 0) total_hamster++;
            else if (strcmp(espece, "autruche") == 0) total_autruche++;
        }
    }
    fclose(f);

    int total_quotidien =
        total_hamster * 10 +
        total_chat * 10 +
        total_autruche * 20 +
        total_chien * 5;

    int total_hebdo =
        total_hamster * 20 +
        total_chat * 20 +
        total_autruche * 45 +
        total_chien * 20;

    // Ajoute nettoyage des cages vides : 2 min/jour
    int nb_animaux = total_chien + total_chat + total_hamster + total_autruche;
    int max_cages = 50;
    int cages_vides = max_cages - nb_animaux;
    total_quotidien += cages_vides * 2;

    printf("\n🧽 Charge de nettoyage hebdomadaire :\n");
    printf("- Minutes de nettoyage quotidien total (x7 jours) : %d min\n", total_quotidien * 7);
    printf("- Minutes de nettoyage hebdomadaire : %d min\n", total_hebdo);
    printf("🧼 ➤ Temps total pour la semaine : %d min (soit %.2f heures)\n",
           total_quotidien * 7 + total_hebdo,
           (total_quotidien * 7 + total_hebdo) / 60.0);
}

int calculer_age(int annee_naissance) {
    // Utilise l'année actuelle (2025)
    return 2025 - annee_naissance;
}

void afficher_par_tranche_age( Animal* animaux, int nb_animaux) {
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




    
