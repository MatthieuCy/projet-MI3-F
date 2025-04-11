# projet-MI3-F
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FICHIER_ANIMAUX "animaux/animaux.txt"
#define MAX_TAILLE 256

typedef struct {
    int id;
    char nom[MAX_TAILLE];
    char espece[MAX_TAILLE];
    int annee_naissance;
    float poids;
    char commentaire[MAX_TAILLE];
} Animal;

void creerDossierSiBesoin() {
    system("mkdir -p animaux");
}

int genererIdUnique() {
    // L'ID est l'heure actuelle en secondes pour simplicité
    return (int)time(NULL);
}

void ajouterAnimal() {
    Animal a;
    FILE *fichier = fopen(FICHIER_ANIMAUX, "a");
    if (!fichier) {
        perror("Erreur ouverture fichier");
        return;
    }

    a.id = genererIdUnique();

    printf("Nom : ");
    scanf(" %[^\n]", a.nom);

    do {
        printf("Espece (chien/chat/hamster/autruche) : ");
        scanf(" %[^\n]", a.espece);
    } while (strcmp(a.espece, "chien") != 0 && strcmp(a.espece, "chat") != 0 &&
             strcmp(a.espece, "hamster") != 0 && strcmp(a.espece, "autruche") != 0);

    printf("Annee de naissance : ");
    scanf("%d", &a.annee_naissance);

    printf("Poids (en kg) : ");
    scanf("%f", &a.poids);

    printf("Commentaire (laisser vide si aucun) : ");
    getchar(); // mange le \n
    fgets(a.commentaire, MAX_TAILLE, stdin);
    a.commentaire[strcspn(a.commentaire, "\n")] = '\0'; // retirer \n

    fprintf(fichier, "%d;%s;%s;%d;%.2f;%s\n", a.id, a.nom, a.espece, a.annee_naissance, a.poids, a.commentaire);
    fclose(fichier);

    printf("Animal ajouté avec succès !\n");
}

void rechercherAnimal() {
    FILE *fichier = fopen(FICHIER_ANIMAUX, "r");
    if (!fichier) {
        perror("Erreur ouverture fichier");
        return;
    }

    char rechercheNom[MAX_TAILLE] = "";
    char rechercheEspece[MAX_TAILLE] = "";
    int ageType = 0; // 0: aucun, 1: jeune, 2: senior
    int anneeActuelle = 2024;

    printf("Recherche par nom (laisser vide pour ignorer) : ");
    getchar();
    fgets(rechercheNom, MAX_TAILLE, stdin);
    rechercheNom[strcspn(rechercheNom, "\n")] = '\0';

    printf("Recherche par espece (laisser vide pour ignorer) : ");
    fgets(rechercheEspece, MAX_TAILLE, stdin);
    rechercheEspece[strcspn(rechercheEspece, "\n")] = '\0';

    printf("Type d'age ? (0 = ignorer, 1 = jeune <2 ans, 2 = senior >10 ans) : ");
    scanf("%d", &ageType);

    printf("\nRésultats de recherche :\n");

    Animal a;
    char ligne[512];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        sscanf(ligne, "%d;%[^;];%[^;];%d;%f;%[^\n]",
               &a.id, a.nom, a.espece, &a.annee_naissance, &a.poids, a.commentaire);

        int age = anneeActuelle - a.annee_naissance;
        int ok = 1;

        if (strlen(rechercheNom) > 0 && strstr(a.nom, rechercheNom) == NULL)
            ok = 0;
        if (strlen(rechercheEspece) > 0 && strcmp(a.espece, rechercheEspece) != 0)
            ok = 0;
        if (ageType == 1 && age >= 2)
            ok = 0;
        if (ageType == 2 && age <= 10)
            ok = 0;

        if (ok) {
            printf("ID: %d | Nom: %s | Espece: %s | Age: %d | Poids: %.2fkg | Commentaire: %s\n",
                   a.id, a.nom, a.espece, age, a.poids, a.commentaire[0] ? a.commentaire : "Aucun");
        }
    }

    fclose(fichier);
}

int main() {
    creerDossierSiBesoin();

    int choix;
    do {
        printf("\n--- Menu du chenil ---\n");
        printf("1. Ajouter un animal\n");
        printf("2. Rechercher un animal\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterAnimal();
                break;
            case 2:
                rechercherAnimal();
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}
