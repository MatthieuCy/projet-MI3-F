#include "leaks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/
static NoeudArbre *creer_noeud_arbre(const char *identifiant, double pourcentage_fuite)
{
    
    NoeudArbre *noeud = malloc(sizeof(NoeudArbre));
    if (noeud == NULL)
        return NULL;

    noeud->identifiant = strdup(identifiant);
    if (noeud->identifiant == NULL)
    {
        free(noeud);
        return NULL;
    }
    noeud->pourcentage_fuite = pourcentage_fuite;
    noeud->compte_enfants = 0;
    noeud->enfants = NULL;
    return noeud;
}


static void ajouter_enfant(NoeudArbre *parent, NoeudArbre *enfant)
{
    // Utilisation du type renommé
    MaillonEnfant *maillon = malloc(sizeof(MaillonEnfant));
    if (maillon == NULL)
        return;

    maillon->enfant = enfant;
    // Ajout en tête de liste
    maillon->suivant = parent->enfants;
    parent->enfants = maillon;
    parent->compte_enfants++;
}


static void liberer_arbre(NoeudArbre *noeud)
{
    if (noeud == NULL)
        return;

    MaillonEnfant *maillon = noeud->enfants;
    while (maillon)
    {
        MaillonEnfant *suivant = maillon->suivant;
        // Libération récursive de l'enfant
        liberer_arbre(maillon->enfant);
        // Libération du maillon de la liste
        free(maillon);
        maillon = suivant;
    }
    // Libération de l'identifiant et du noeud
    free(noeud->identifiant);
    free(noeud);
}


static double calculer_fuites_recursif(NoeudArbre *noeud, double volume_entrant)
{
    if (noeud == NULL || volume_entrant <= 0)
        return 0.0;

    // Calcul de la fuite au niveau de ce noeud
    double fuite = volume_entrant * (noeud->pourcentage_fuite / 100.0);
    double restant = volume_entrant - fuite;

    // Si c'est une feuille, le volume restant est perdu 
    // Ici, on considère que seuls les fuites sont tracées, le reste est distribué aux enfants
    if (noeud->compte_enfants == 0)
    {
        return fuite;
    }

    // Répartition du volume restant également entre les enfants
    double volume_par_enfant = restant / noeud->compte_enfants;
    double fuite_totale = fuite;

    // Appel récursif pour chaque enfant
    MaillonEnfant *maillon = noeud->enfants;
    while (maillon)
    {
        fuite_totale += calculer_fuites_recursif(maillon->enfant, volume_par_enfant);
        maillon = maillon->suivant;
    }

    return fuite_totale;
}


int fuites_traiter(const char *fichier_entree, const char *fichier_sortie, const char *id_usine)
{
    FILE *fp = fopen(fichier_entree, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier d'entrée %s\n", fichier_entree);
        return 1;
    }

    // AVL pour indexer les NoeudArbre par ID (clé = ID, donnée = pointeur NoeudArbre)
    NoeudAVL *index_noeuds = NULL;
    // Racine de l'arbre de fuites (l'usine principale)
    NoeudArbre *racine_usine = NULL;
    double volume_max_usine = 0.0;
    int usine_trouvee = 0;

    char ligne[1024];
    char **lignes = NULL; // Pour stocker toutes les lignes en mémoire
    int compte_lignes = 0;
    int capacite_lignes = 10000;

    lignes = malloc(sizeof(char *) * capacite_lignes);
    if (lignes == NULL)
    {
        fclose(fp);
        return 1;
    }

    // Phase 1: Lire toutes les lignes du fichier en mémoire 
    while (fgets(ligne, sizeof(ligne), fp))
    {
        if (compte_lignes >= capacite_lignes)
        {
            capacite_lignes *= 2;
            char **nouvelles_lignes = realloc(lignes, sizeof(char *) * capacite_lignes);
            if (nouvelles_lignes == NULL)
            {
                for (int i = 0; i < compte_lignes; i++)
                    free(lignes[i]);
                free(lignes);
                fclose(fp);
                return 1;
            }
            lignes = nouvelles_lignes;
        }
        lignes[compte_lignes] = strdup(ligne);
        compte_lignes++;
    }
    fclose(fp);

    // Phase 2: Trouver le volume max de l'usine racine 
    for (int i = 0; i < compte_lignes; i++)
    {
        char *l = lignes[i];
        l[strcspn(l, "\n\r")] = 0;

        char col1[256] = "-", col2[256] = "-", col3[256] = "-", col4[256] = "-", col5[256] = "-";
        char *copie_l = strdup(l);

        
        char *token = strtok(copie_l, ";");
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

        free(copie_l);

        // Ligne de définition du volume max de l'usine : 
        if (strcmp(col1, "-") == 0 && strcmp(col2, id_usine) == 0 && strcmp(col3, "-") == 0 && strcmp(col4, "-") != 0)
        {
            volume_max_usine = atof(col4);
            usine_trouvee = 1;
        }
    }

    // Si l'usine racine n'est pas trouvée, écrire -1 et quitter
    if (!usine_trouvee)
    {
        for (int i = 0; i < compte_lignes; i++)
            free(lignes[i]);
        free(lignes);

        FILE *out = fopen(fichier_sortie, "a");
        /
        if (out == NULL) { /* handle error */ return 1; }
        fseek(out, 0, SEEK_END);
        long pos = ftell(out);
        if (pos == 0)
        {
            fprintf(out, "identifiant;Volume de fuite (M.m3.an-1)\n");
        }
        fprintf(out, "%s;-1\n", id_usine);
        fclose(out);
        return 0;
    }

    // Initialiser la racine de l'arbre de fuites
    racine_usine = creer_noeud_arbre(id_usine, 0.0);
    if (racine_usine == NULL)
    {
        for (int i = 0; i < compte_lignes; i++)
            free(lignes[i]);
        free(lignes);
        return 1;
    }

    // Indexer la racine dans l'AVL
    NoeudAVL *trouve = NULL;
    index_noeuds = avl_inserer(index_noeuds, id_usine, racine_usine, &trouve);

    /Phase 3: Construction itérative de l'arbre de fuites 
    
    int changements = 1;
    while (changements)
    {
        changements = 0;
        for (int i = 0; i < compte_lignes; i++)
        {
            char *l = lignes[i];
            // ... (Parsing des colonnes col1 à col5, identique à Phase 2)
            char col1[256] = "-", col2[256] = "-", col3[256] = "-", col4[256] = "-", col5[256] = "-";
            char *copie_l = strdup(l);

            char *token = strtok(copie_l, ";");
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

            free(copie_l);
            // Si la colonne 3 (destinataire) est vide, on ignore
            if (strcmp(col3, "-") == 0)
                continue;

            // Une ligne représente un segment PlantSegment (PlantID -> ID_PLANT/Source)
            int est_segment_usine = (strcmp(col1, id_usine) == 0);
            // OU un segment de stockage (Source -> PlantID)
            int est_usine_vers_stockage = (strcmp(col1, "-") == 0 && strcmp(col2, id_usine) == 0);

            if (!est_segment_usine && !est_usine_vers_stockage)
                continue;

            // 1. Chercher le noeud parent (col2) dans l'index AVL
            AVLNode *noeud_parent_avl = avl_rechercher(index_noeuds, col2);
            if (noeud_parent_avl == NULL)
                continue; // Le parent n'est pas encore dans l'arbre

            // 2. Vérifier si le noeud enfant (col3) existe déjà
            AVLNode *noeud_enfant_avl = avl_rechercher(index_noeuds, col3);
            if (noeud_enfant_avl != NULL)
                continue; // L'enfant est déjà connecté

            // 3. Créer et connecter l'enfant
            double pourcentage_fuite = (strcmp(col5, "-") != 0) ? atof(col5) : 0.0;
            NoeudArbre *enfant = creer_noeud_arbre(col3, pourcentage_fuite);
            if (enfant == NULL)
                continue;

            NoeudArbre *parent = (NoeudArbre *)noeud_parent_avl->donnee;
            ajouter_enfant(parent, enfant); // Ajouter au noeud parent réel

            // 4. Indexer l'enfant pour les prochaines itérations
            index_noeuds = avl_inserer(index_noeuds, col3, enfant, NULL);
            changements = 1; // Un noeud a été ajouté, il faut relancer la boucle
        }
    }

    // --- Phase 4: Calcul des fuites ---
    double fuites_totales = 0.0;

    if (racine_usine->compte_enfants > 0)
    {
        // Répartition initiale du volume max sur les premiers enfants
        double volume_par_enfant = volume_max_usine / racine_usine->compte_enfants;
        MaillonEnfant *maillon = racine_usine->enfants;
        while (maillon)
        {
            // La racine n'a pas de fuite propre dans ce modèle, on commence la récursion sur les enfants
            fuites_totales += calculer_fuites_recursif(maillon->enfant, volume_par_enfant);
            maillon = maillon->suivant;
        }
    }

    // Conversion en millions de m³
    double fuites_totales_mm3 = fuites_totales / 1000000.0;

    // --- Phase 5: Écriture du résultat et nettoyage ---

    FILE *out = fopen(fichier_sortie, "a");
    // ... (gestion des erreurs et écriture du résultat)
    if (out == NULL)
    {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier de sortie %s\n", fichier_sortie);
        liberer_arbre(racine_usine);
        // L'AVL n'indexait que des pointeurs, pas besoin de fonction de libération des données (NULL)
        avl_liberer(index_noeuds, NULL);
        for (int i = 0; i < compte_lignes; i++)
            free(lignes[i]);
        free(lignes);
        return 1;
    }

    fseek(out, 0, SEEK_END);
    long pos = ftell(out);
    if (pos == 0)
    {
        fprintf(out, "identifiant;Volume de fuite (M.m3.an-1)\n");
    }
    fprintf(out, "%s;%.6f\n", id_usine, fuites_totales_mm3);
    fclose(out);

    // Nettoyage final
    liberer_arbre(racine_usine);
    avl_liberer(index_noeuds, NULL);
    for (int i = 0; i < compte_lignes; i++)
        free(lignes[i]);
    free(lignes);

    return 0;
}
