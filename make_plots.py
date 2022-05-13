import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# plot beta
beta = open('beta_iter.txt', 'r')
lines = []
betas = []
iters = []

for linia in beta:
    lines.append(linia.strip())
    
beta.close()

for line in lines:
    L = line.split()
    iters.append(float(L[0]))
    betas.append(float(L[1]))

fig, ax = plt.subplots(figsize=(10,10))
ax.plot(iters, betas)
ax.set_xlabel("Beta")
ax.set_ylabel("Iterations")
fig.savefig("beta.jpg")

# plot energy
energy = open('energy_iter.txt', 'r')
lines = []
energies = []
iters = []

for linia in energy:
    lines.append(linia.strip())
    
energy.close()

for line in lines:
    L = line.split()
    iters.append(float(L[0]))
    energies.append(float(L[1]))

fig, ax = plt.subplots(figsize=(10,10))
ax.plot(iters, energies)
ax.set_xlabel("Energy [eV]")
ax.set_ylabel("Iterations")
fig.savefig("energy.jpg")


# draw fulleren 
xyz = open('atoms_coordinates.txt', 'r')
lines = []
X = []
Y = []
Z = []

for linia in xyz:
    lines.append(linia.strip())
    
xyz.close()

for line in lines:
    L = line.split()
    X.append(float(L[0]))
    Y.append(float(L[1]))
    Z.append(float(L[2]))

fig = plt.figure(figsize=(10,10))
ax = fig.add_subplot(111, projection='3d')
ax.scatter(xs=X,ys=Y,zs=Z,marker="*")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
fig.savefig("fulleren.jpg")


