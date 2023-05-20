#!/bin/bash

OUTPUT_FILE="execution_times.csv"

for ((N=0; N<=100; N++))
do
    echo "Running simulation for N=$N"

    # lance la simu et récupère le temps de début et de fin
    START_TIME=$(date +%s%N)
    ./exe/simulation.exe "$N"
    END_TIME=$(date +%s%N)

    # Calcul le temps d'exécution en secondes   
    ELAPSED_TIME=$(echo "scale=6; ($END_TIME - $START_TIME) / 1000000000" | bc)

    TIME_PER_N=$(echo "scale=6; $ELAPSED_TIME / $N" | bc)

    # Ajoute les résultats au fichier de sortie
    echo "$N,$ELAPSED_TIME,$TIME_PER_N" >> "$OUTPUT_FILE"
done
