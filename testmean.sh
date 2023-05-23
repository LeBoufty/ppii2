#!/bin/bash

OUTPUT_FILE="execution_times_mean.csv"

for ((N=226; N<=1052; N=N+50))
do
    echo "Running simulation for N=$N"

    total_time=0

    # Lance la simu 10 fois et récupère le temps de début et de fin
    for ((i=0; i<15; i++))
    do
        START_TIME=$(date +%s%N)
        ./exe/simulation.exe "$N"
        END_TIME=$(date +%s%N)

        # Calcul le temps d'exécution en secondes
        ELAPSED_TIME=$(echo "scale=6; ($END_TIME - $START_TIME) / 1000000000" | bc)

        total_time=$(echo "$total_time + $ELAPSED_TIME" | bc)
    done

    # Calcul le temps moyen d'exécution en secondes
    AVERAGE_TIME=$(echo "scale=6; $total_time / 15" | bc)

    # Ajoute les résultats au fichier de sortie
    echo "$N,$AVERAGE_TIME" >> "$OUTPUT_FILE"
done
