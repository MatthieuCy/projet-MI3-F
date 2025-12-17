#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "histo.h"
#include "leaks.h"

int main(int compte_arguments, char *arguments[]) // argc -> compte_arguments, argv -> arguments
{
    // Vérification du nombre minimum d'arguments
    if (compte_arguments < 4)
    {
        fprintf(stderr, "Utilisation : %s <fichier_entree> <fichier_sortie> <mode> [id_usine]\n", arguments[0]);
        fprintf(stderr, "Modes : max, src, real, leaks\n");
        return 1;
    }

    const char *fichier_entree = arguments[1];
    const char *fichier_sortie = arguments[2];
    const char *mode = arguments[3];

    // Traitement des modes du module 'histo'
    if (strcmp(mode, "max") == 0 || strcmp(mode, "src") == 0 || strcmp(mode, "real") == 0)
    {
        
        return histo_traiter(fichier_entree, fichier_sortie, mode);
    }
    // Traitement du mode du module 'leaks'
    else if (strcmp(mode, "leaks") == 0)
    {
        // Le mode 'leaks' nécessite un argument supplémentaire (l'identifiant de l'usine)
        if (compte_arguments < 5)
        {
            fprintf(stderr, "Erreur : le mode 'leaks' nécessite un identifiant d'usine\n");
            return 1;
        }
        
        const char *id_usine = arguments[4];
        
       
        return fuites_traiter(fichier_entree, fichier_sortie, id_usine);
    }
    // Mode inconnu
    else
    {
        fprintf(stderr, "Erreur : mode inconnu '%s'\n", mode);
        return 1;
    }

    // Ceci est théoriquement unreachable mais inclus pour la conformité
    return 0;
}
