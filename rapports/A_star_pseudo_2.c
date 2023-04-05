file_prochain = [] // De la plus petite a plus grande distance
chemin_depart = [id_depart] // Du départ a l'arrivee
vu = [id_depart] // Du plus petit au plus grand ID
lambda = 2 // lambda permet de choisir le style de chemin prefere pour une recherche plus rapide

pour i, voisin de id_depart :
    distance_total_appro_i = distance(id_depart, i) + lambda*distance(i, id_arrive)
    insert_croissant(file_prochain, [distance_total_appro_i, i, chemin_depart])
    

tant que file_prochain != [] ou point_plus_proche(file_prochain) == id_arrive :
    [meilleur_distance, id_meilleur_point, meilleur_chemin] = retire_plus_petit(file_prochain)
    vu += [id_meilleur_point]
    meilleur_chemin += [id_meilleur_point]

    pour i, voisin de id_meilleur_point :
        distance_total_appro_i = distance(id_meilleur_point, i) + lambda*distance(i, id_arrive)
        insert_croissant(file_prochain, [distance_total_appro_i, i, meilleur_chemin])


si file_prochain != [] :
    Pas de chemin

sinon :
    retourne meilleur_chemin + [id_arrive]
