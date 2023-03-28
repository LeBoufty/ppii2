from math import radians, sin, cos, acos

def distance(x1, y1, x2, y2):
    if x1 == x2 and y1 == y2:
        return 0 # Pour éviter les potentielles erreurs de calcul faisant que la distance soit non-nulle.
    x1 = radians(x1)
    y1 = radians(y1)
    x2 = radians(x2)
    y2 = radians(y2)
    
    A = sin(y1)*sin(y2) + cos(y1)*cos(y2)*cos(x2-x1)
    # Gestion des erreurs de flottant
    if A > 1: A = 1
    if A < -1: A = -1 
    
    return 6371 * acos(A)

def a_proximite(x, y, xy_trouves, distmin = 5):
    i = 0
    if len(xy_trouves) == 0: return False
    x2, y2 = xy_trouves[0]
    while i < len(xy_trouves) and distance(x, y, x2, y2) > distmin:
        x2, y2 = xy_trouves[i]
        i += 1
    return distance(x, y, x2, y2) <= distmin