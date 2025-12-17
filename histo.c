#include "histo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void liberer_donnees_usine(void *donnee)
{
    if (donnee)
    {
        /
        DonneesUsine *du = (DonneesUsine *)donnee;
        free(du->identifiant);
        free(du);
    }
}


static int est_source(const char *identifiant)
{
    return (strstr(identifiant, "Source") != NULL ||
            strstr(identifiant, "Well") != NULL ||
            strstr(identifiant, "Spring") != NULL ||
            strstr(identifiant, "Fountain") != NULL ||
            strstr(identifiant, "Resurgence") != NULL ||
            strstr(identifiant, "field") != NULL);
}


static int est_usine(const char *identifiant)
{
    return (strstr(identifiant, "Plant") != NULL ||
            strstr(identifiant, "Unit") != NULL ||
            strstr(identifiant, "Module") != NULL ||
            strstr(identifiant, "Facility") != NULL);
}


typedef struct
{
    FILE *descripteur_fichier; // fp
    const char *mode;
} ContexteEcriture;

static void ecrire_usine(NoeudAVL *noeud, void *arg)
{
    /
    ContexteEcriture *ctx = (ContexteEcriture *)arg;
    DonneesUsine *du = (DonneesUsine *)noeud->donnee;
    double valeur = 0.0;

    if (strcmp(ctx->mode, "max") == 0)
    {
        valeur = du->volume_max / 1000.0;
    }
    else if (strcmp(ctx->mode, "src") == 0)
    {
        valeur = du->volume_source / 1000.0;
    }
    else if (strcmp(ctx->mode, "real") == 0)
    {
        valeur = du->volume_reel / 1000.0;
    }

    
    fprintf(ctx->descripteur_fichier, "%s;%.6f\n", du->identifiant, valeur);
}


int histo_traiter(const char *fichier_entree, const char *fichier_sortie, const char *mode)
{
    FILE *fp = fopen(fichier_entree, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier d'entrée %s\n", fichier_entree);
        return 1;
    }

    
    NoeudAVL *usines = NULL; 
    char ligne[1024];        

    // Boucle de lecture du fichier d'entrée
    while (fgets(ligne, sizeof(ligne), fp))
    {
        // Nettoyage de la fin de ligne
        ligne[strcspn(ligne, "\n\r")] = 0;

        // Variables pour stocker les colonnes lues (inchangées pour la simplicité du parsing)
        char col1[256] = "-", col2[256] = "-", col3[256] = "-", col4[256] = "-", col5[256] = "-";

        // Parsing de la ligne
        char *token = strtok(ligne, ";");
        if (token)
            strncpy(col1, token, sizeof(col1) - 1);
        token = strtok(NULL, ";");
        if (token)
            strncpy(col2, token, sizeof(col2) - 1);
        token = strtok(NULL, ";");
        if (token)
            strncpy(col3, token, sizeof(col3) - 1);
        token = strtok(NULL, ";");
        if (token)
            strncpy(col4, token, sizeof(col4) - 1);
        token = strtok(NULL, ";");
        if (token)
            strncpy(col5, token, sizeof(col5) - 1);

        // --- Cas 1: Ligne de volume maximum pour une usine (Plant) 
        // Exemple de format: -;PlantName;-;VolumeMax;-
        if (strcmp(col1, "-") == 0 && est_usine(col2) && strcmp(col3, "-") == 0 && strcmp(col4, "-") != 0)
        {
            NoeudAVL *trouve = NULL;
            // Utilisation de la fonction avl_inserer
            usines = avl_inserer(usines, col2, NULL, &trouve);
            
            // Si le noeud est nouveau ou si c'est le noeud existant
            if (trouve)
            {
                if (trouve->donnee == NULL)
                {
                    // Création de la structure de données pour la nouvelle usine
                    DonneesUsine *du = malloc(sizeof(DonneesUsine));
                    if (du == NULL)
                    {
                        fclose(fp);
                        // Utilisation de la fonction avl_liberer et liberer_donnees_usine
                        avl_liberer(usines, liberer_donnees_usine);
                        return 1;
                    }
                    du->identifiant = strdup(col2);
                    du->volume_max = atof(col4);
                    du->volume_source = 0.0;
                    du->volume_reel = 0.0;
                    trouve->donnee = du;
                }
                else
                {
                    // Mise à jour du volume max si l'usine existe déjà
                    DonneesUsine *du = (DonneesUsine *)trouve->donnee;
                    du->volume_max = atof(col4);
                }
            }
        }

        // --- Cas 2: Ligne d'approvisionnement (Source vers Plant)
       
        if (strcmp(col1, "-") == 0 && est_source(col2) && est_usine(col3) && strcmp(col4, "-") != 0)
        {
            double volume = atof(col4);
            // Si la colonne 5 est présente, utiliser le pourcentage de fuite
            double pourcentage_fuite = (strcmp(col5, "-") != 0) ? atof(col5) : 0.0;
            // Calcul du volume réel (avec fuite)
            double reel = volume * (1.0 - pourcentage_fuite / 100.0);

            NoeudAVL *trouve = NULL;
            // Insérer ou trouver l'usine destinataire
            usines = avl_inserer(usines, col3, NULL, &trouve);

            if (trouve)
            {
                if (trouve->donnee == NULL)
                {
                    // Création de la structure de données pour la nouvelle usine
                    DonneesUsine *du = malloc(sizeof(DonneesUsine));
                    if (du == NULL)
                    {
                        fclose(fp);
                        avl_liberer(usines, liberer_donnees_usine);
                        return 1;
                    }
                    du->identifiant = strdup(col3);
                    du->volume_max = 0.0;
                    du->volume_source = volume;
                    du->volume_reel = reel;
                    trouve->donnee = du;
                }
                else
                {
                    // Mise à jour : ajout du nouveau volume à la source et au volume réel existant
                    DonneesUsine *du = (DonneesUsine *)trouve->donnee;
                    du->volume_source += volume;
                    du->volume_reel += reel;
                }
            }
        }
    }
    
    fclose(fp);

    // Ouverture du fichier de sortie
    FILE *out = fopen(fichier_sortie, "w");
    if (out == NULL)
    {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier de sortie %s\n", fichier_sortie);
        // Libérer la mémoire en cas d'erreur
        avl_liberer(usines, liberer_donnees_usine);
        return 1;
    }

    // Écrire l'en-tête en fonction du mode demandé
    if (strcmp(mode, "max") == 0)
    {
        fprintf(out, "identifiant;volume maximum (k.m3.an-1)\n");
    }
    else if (strcmp(mode, "src") == 0)
    {
        fprintf(out, "identifiant;volume source (k.m3.an-1)\n");
    }
    else if (strcmp(mode, "real") == 0)
    {
        fprintf(out, "identifiant;volume reel (k.m3.an-1)\n");
    }

   
    ContexteEcriture ctx = {out, mode};

    
    avl_parcourir_inverse(usines, ecrire_usine, &ctx);

    // Fermer le fichier de sortie et libérer l'arbre
    fclose(out);
    avl_liberer(usines, liberer_donnees_usine);
    return 0;
}
