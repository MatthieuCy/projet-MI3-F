# 🐾 Gestion d'un refuge pour animaux

Ce projet est une application en langage C permettant de gérer un refuge pour animaux. Il permet d'ajouter, rechercher, adopter et afficher les animaux présents dans le refuge, tout en sauvegardant les données dans un fichier.

## 📌 Fonctionnalités

- 🔹 Ajouter un nouvel animal (avec vérifications des champs : nom, espèce, poids, âge, etc.)
- 🔍 Rechercher un animal par critère (ex. espèce ou nom)
- ✅ Adopter un animal (suppression par ID)
- 📋 Afficher l'inventaire de tous les animaux
- 💾 Sauvegarde automatique des données dans un fichier texte

## 🛠️ Structure des données

Chaque animal est représenté par une structure `Animal` contenant :


typedef struct {
    int id;
    char nom[50];
    int poids;
    int age;
    char race[30];
    char commentaire[200];
} Animal;



main.c : point d'entrée de l'application

animal.c : contient les fonctions principales (ajout, adoption, recherche, affichage)

aanimal.h : déclarations des fonctions et de la structure animaal

Pour l'éxxécution on utilise github et on faut:
make
./refuge
