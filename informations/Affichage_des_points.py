import matplotlib.pyplot as plt
# Test rapide avec Pyplot pour visualiser les données

with open('informations\stations.csv', 'r') as f:
    lines = f.readlines()[1:-1]

names = []
x_s = []
y_s = []

for line in lines:
    name, x, y, nbre_pdc = line.strip().split(',')
    x = float(x)
    y = float(y)
    if y >= 40:
        names.append(name)
        x_s.append(x)
        y_s.append(y)

fig, ax = plt.subplots()
ax.scatter(x_s, y_s)

#for i, name in enumerate(names):
#    ax.annotate(name, (x_s[i], y_s[i]))

plt.show()
