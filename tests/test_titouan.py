import matplotlib.pyplot as plt
# Test rapide avec Pyplot pour visualiser les données

with open('tests\stations.csv', 'r') as f:
    lines = f.readlines()

names = []
x_s = []
y_s = []

for line in lines:
    name_u, x_u, y_u = line.strip().split(',')
    names.append(name)
    x_s.append(float(x))
    y_s.append(float(y))

fig, ax = plt.subplots()
ax.scatter(x_s, y_s)

for i, name in enumerate(names):
    ax.annotate(name, (x_s[i], y_s[i]))

plt.show()