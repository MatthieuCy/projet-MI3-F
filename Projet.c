#include <stdio.h>
#include <string.h>

typedef struct{
char *nom;
char *espece;
int annee;
char *commentaire;
int num;
int poids;
} Animal;

typedef struct {
    char nom[50];
   int cont;
} AnimalCount;

void affiche_animaux(Animal refuge[50]) {
    int i, c = 0;
    int chien = 0, chat = 0, autruche = 0, hamster = 0;

    // Comptage du nombre d'animaux présents dans le refuge
    for (i = 0; i < 50; i++) {
        if (strlen(refuge[i].nom) != 0) {
            c++;
        }
    }
    printf("Il y a %d animaux dans le refuge.\n", c);

    // Comptage du nombre d'animaux par espèce
    for (i = 0; i < 50; i++) {
        if (strcmp(refuge[i].nom, "chien") == 0) {
            chien++;
        }
        if (strcmp(refuge[i].nom, "chat") == 0) {
            chat++;
        }
        if (strcmp(refuge[i].nom, "autruche") == 0) {
            autruche++;
        }
        if (strcmp(refuge[i].nom, "hamster") == 0) {
            hamster++;
        }
    }

    // Tableau pour stocker les animaux et leur nombre
    AnimalCount animaux[4] = {
        {"chien", chien},
        {"chat", chat},
        {"autruche", autruche},
        {"hamster", hamster}
    };

    // Tri des animaux par nombre décroissant
    for (i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (animaux[i].cont < animaux[j].cont) {
                // Échange des animaux
                AnimalCount temp = animaux[i];
                animaux[i] = animaux[j];
                animaux[j] = temp;
            }
        }
    }

    // Affichage du nombre d'animaux par espèce
    printf("\nNombre d'animaux par espèce :\n");
    for (i = 0; i < 4; i++) {
        if (animaux[i].cont > 0) {
            printf("%s: %d\n", animaux[i].espece, animaux[i].cont);
        }
    }
}



void affiche_nouritture(Animal refuge[50]){
int i;
for(i=0;i<50;i++){
if(refuge[i].espece=="autruche"){
printf("L'animal numéro %d a besoind de 2.5kg de croquettes par jour.", i);
}
if(refuge[i].espece=="hamster"){
printf("L'animal numéro %d a besoin de 200g par jour", i);
}
if(refuge[i].espece=="chien" || refuge[i].espece=="chat"){
if(2025-refuge[i].annee <2){
printf("L'animal numéro %d a besoin de 500 g par jour", i);
else{
printf("L'animal numéro %d a besoin de %d", i, refuge[i].poids*0.1);
}


void affiche_nettoyage(Animal refuge[50]){
int i;
for(i=0; i<50;i++){


int main(){

  Animal * refuge = malloc(sizeof(Animal) * SIZE);
  if(refuge == NULL){
    printf("Erreur d'allocation mémoire");
    exit(1);
  }


    
  return 0;
}
    
    
