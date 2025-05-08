#include <recherche.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define ANNEE_ACTUELLE 2025
#include "recherche.h"

void adopter_animal() {
    FILE* f = fopen("animaux/data.txt", "r");
    if (!f) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    FILE* temp = fopen("animaux/temp.txt", "w");
    if (!temp) {
        fclose(f);
        printf("Erreur création fichier temporaire.\n");
        return;
    }

    int id_cible;
    printf("ID de l’animal à adopter : ");
    scanf("%d", &id_cible);

    char ligne[512];
    int trouve = 0;
    while (fgets(ligne, sizeof(ligne), f)) {
        int id;
        sscanf(ligne, "%d;", &id);
        if (id != id_cible) {
            fputs(ligne, temp);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(temp);
    remove("animaux/data.txt");
    rename("animaux/temp.txt", "animaux/data.txt");

    if (trouve)
        printf("🎉 Adoption réussie !\n");
    else
        printf("❌ Animal non trouvé.\n");
}

void rechercher_animaux() {
    char nom[50] = "", espece[30] = "";
    int type_age = -1;

    printf("Recherche par nom (laisser vide si non) : ");
    getchar(); // pour nettoyer après scanf
    fgets(nom, sizeof(nom), stdin);
    nom[strcspn(nom, "\n")] = 0;

    printf("Recherche par espèce (laisser vide si non) : ");
    fgets(espece, sizeof(espece), stdin);
    espece[strcspn(espece, "\n")] = 0;

    printf("Recherche par âge (0=aucun, 1=jeune, 2=senior) : ");
    scanf("%d", &type_age);

    FILE* f = fopen("animaux/data.txt", "r");
    if (!f) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    char ligne[512];
    while (fgets(ligne, sizeof(ligne), f)) {
        Animal a;
        sscanf(ligne, "%d;%[^;];%[^;];%d;%f;%[^\n]", &a.id, a.nom, a.espece, &a.annee_naissance, &a.poids, a.commentaire);

        int age = ANNEE_ACTUELLE - a.annee_naissance;
        int ok = 1;

        if (strlen(nom) > 0 && strcasecmp(a.nom, nom) != 0) ok = 0;
        if (strlen(espece) > 0 && strcasecmp(a.espece, espece) != 0) ok = 0;
        if (type_age == 1 && age >= 2) ok = 0;
        if (type_age == 2 && age <= 10) ok = 0;

        if (ok) {
            printf("\n🐶 ID: %d\nNom: %s\nEspèce: %s\nAnnée: %d\nPoids: %.2f kg\nCommentaire: %s\n",
                   a.id, a.nom, a.espece, a.annee_naissance, a.poids, a.commentaire);
        }
    }

    fclose(f);
}

void ajouter_animal() {
    FILE* f = fopen("animaux/data.txt", "a+");
    if (!f) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Animal a;
    int count = 0;
    char ligne[512];
    while (fgets(ligne, sizeof(ligne), f)) {
        count++;
    }

    if (count >= MAX_ANIMAUX) {
        printf("⚠️ Le refuge est plein (maximum %d animaux).\n", MAX_ANIMAUX);
        fclose(f);
        return;
    }

    a.id = (int)time(NULL); // ID basé sur l'heure (unique approximativement)

    printf("Nom : ");
    scanf("%s", a.nom);
    printf("Espèce (chien/chat/hamster/autruche) : ");
    scanf("%s", a.espece);
    printf("Année de naissance : ");
    scanf("%d", &a.annee_naissance);
    printf("Poids : ");
    scanf("%f", &a.poids);
    printf("Commentaire (laisser vide si aucun) : ");
    getchar(); // nettoyer le buffer
    fgets(a.commentaire, sizeof(a.commentaire), stdin);
    a.commentaire[strcspn(a.commentaire, "\n")] = 0; // enlever le \n

    fprintf(f, "%d;%s;%s;%d;%.2f;%s\n", a.id, a.nom, a.espece, a.annee_naissance, a.poids, a.commentaire);
    fclose(f);
    printf("✅ Animal ajouté avec succès !\n");
}






