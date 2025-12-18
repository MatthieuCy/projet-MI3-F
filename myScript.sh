#!/bin/bash

# 1. Vérification des arguments
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <fichier.csv> <commande> [option/ID]"
    exit 1
fi

FILE=$1
CMD=$2
OPT=$3
EXEC="wildwater"

# 2. Compilation
echo "--- Compilation ---"
make clean
make

if [ ! -f "./$EXEC" ]; then
    echo "Erreur de compilation : l'exécutable $EXEC n'a pas pu être créé."
    exit 1
fi

# 3. Exécution
echo "--- Exécution de la commande $CMD ---"

if [ "$CMD" == "histo" ]; then
    # Format: ./wildwater histo fichier option
    ./$EXEC histo "$FILE" "$OPT"
    
    # Si Gnuplot est présent, on génère l'image
    if [ -f "histo_data.dat" ]; then
        gnuplot histo.plt 2>/dev/null
        echo "Graphique généré dans 'histogramme_usines.png'."
    fi

elif [ "$CMD" == "leaks" ]; then
    # Format: ./wildwater leaks fichier ID
    ./$EXEC leaks "$FILE" "$OPT"
    echo "Résultats écrits dans 'leaks_history.dat'."

else
    echo "Commande inconnue : $CMD (utilisez 'histo' ou 'leaks')"
    exit 1
fi

echo "--- Terminé ---"
