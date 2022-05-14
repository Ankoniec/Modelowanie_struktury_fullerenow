import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# plot beta
beta = open('beta_iter_4.txt', 'r')
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
fig.savefig("beta_4.jpg")

# plot energy
energy = open('energy_iter_4.txt', 'r')
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
fig.savefig("energy_4.jpg")


# draw fulleren 
xyz = open('atoms_coordinates_4.txt', 'r')
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
fig.savefig("fulleren_4.jpg")


# plot histogram
histogram = open("histogram_4.txt","r")
M = []
pcf_hist = []
i = 1
for linia in histogram:
    pcf_hist.append((float)(linia.strip()))
    M.append(i)
    i += 1

print(type(pcf_hist[0]))
fig, ax = plt.subplots(figsize=(10,10))
ax.bar(M, pcf_hist)
ax.set_xlabel("M")
ax.set_ylabel("PCF")
fig.savefig("pcf_histogram_4.jpg")