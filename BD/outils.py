from math import radians, sin, cos, acos

def distance(x1, y1, x2, y2):
    if x1 == x2 and y1 == y2:
        return 0 # Pour éviter les potentielles erreurs de calcul faisant que la distance soit non-nulle.
    x1 = radians(x1)
    y1 = radians(y1)
    x2 = radians(x2)
    y2 = radians(y2)
    
    A = sin(y1)*sin(y2) + cos(y1)*cos(y2)*cos(x2-x1)
    return 6371 * acos(A)