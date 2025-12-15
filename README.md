# Projet Distribution d’Eau  
Analyse de données d’un système de distribution d’eau en France  
*(Shell + C)*

---

## 📌 Objectif du projet

Ce projet a pour objectif d’analyser des données issues d’un système de distribution d’eau potable en France.  
Il permet notamment :

- la génération d’**histogrammes** sur les capacités et volumes des usines,
- le **calcul des pertes d’eau (fuites)** en aval d’une usine donnée,
- l’export des résultats sous forme de **fichiers CSV** et de **graphiques PNG**.

Le projet repose sur :
- un **script Shell** (`run.sh`) pour l’orchestration,
- plusieurs **programmes en C** (structures AVL, calculs, agrégation),
- **Gnuplot** pour la visualisation graphique.

---

## 📁 Structure du projet

```text
.
├── run.sh                 # Script principal
├── README.md              # Documentation
├── src/                   # Code source C
│   ├── Makefile
│   ├── avl.c / avl.h      # Arbres AVL
│   ├── histo.c            # Histogrammes
│   ├── leaks.c            # Calcul des fuites
│   └── ...
├── data/                  # Données d’entrée (CSV / DAT)
│   └── c-wildwater_v3.dat
├── output/                # Résultats générés (CSV + PNG)
└── .github/workflows/     # Intégration continue (GitHub Actions)
