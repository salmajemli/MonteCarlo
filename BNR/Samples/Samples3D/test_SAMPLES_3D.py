import numpy as np
import scipy
from scipy.stats import kstest
import matplotlib.pyplot as plt
import subprocess
import os

# Étape 1 : Compilation et exécution du fichier C++ (test_SAMPLES_2D.cpp)
cpp_file = "test_SAMPLES_3D.cpp"
executable_file = "test_SAMPLES_3D"

# Compilation du fichier C++
print("Compilation du fichier C++...")
compilation = subprocess.run(["g++", cpp_file, "-o", executable_file], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

if compilation.returncode != 0:
    print("Erreur lors de la compilation du fichier C++ :")
    print(compilation.stderr)
    exit(1)
else:
    print("Compilation réussie.")

# Exécution du fichier C++ pour générer les données
print("Exécution de l'exécutable...")
execution = subprocess.run([f"./{executable_file}"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

if execution.returncode != 0:
    print("Erreur lors de l'exécution de l'exécutable :")
    print(execution.stderr)
    exit(1)
else:
    print("Exécution réussie.")
    print("Sortie de l'exécutable :")
    print(execution.stdout)

# Convertir des coordonnées cartésiennes (x, y) en polaires (r, phi)
def cartesian_to_polar(x, y, z):
    x = np.array(x)
    y = np.array(y)
    z = np.array(z)

    r = np.sqrt(x**2 + y**2 + z**2)
    theta = np.arccos(z / r)
    phi = np.arctan2(y, x)
    phi = np.mod(phi, 2 * np.pi)

    
    return r, theta, phi

# Fonction pour charger les données 2D depuis un fichier
def load_data_2d(file_path):
    data = np.loadtxt(file_path)  
    return data[:, 0], data[:, 1], data[:, 2]  # Charger uniquement x et y

# Fichier contenant les points 2D
data_file = 'Test_Echantillon.txt'
data_x, data_y, data_z = load_data_2d(data_file)

# Conversion des coordonnées
r, theta, phi = cartesian_to_polar(data_x, data_y, data_z)

# Test KS pour phi (doit suivre une loi uniforme sur [0, 2*pi])
statistic_phi, p_value_phi = kstest(phi, 'uniform', args=(0, 2*np.pi))

if p_value_phi < 0.05:
    print("La distribution de phi n'est pas uniforme. p-value =", p_value_phi)
else:
    print("La distribution de phi est uniforme. p-value =", p_value_phi)


# Fonction de répartition cumulative pour f(theta) = sin(theta)
def cdf_theta(theta):
    return (1 - np.cos(theta)) / 2


# Test KS pour theta (doit suivre une loi uniforme sur [0, pi])
statistic_theta, p_value_theta = kstest(theta, cdf_theta)

if p_value_theta < 0.05:
    print("La distribution de theta n'est pas uniforme. p-value =", p_value_theta)
else:
    print("La distribution de theta est uniforme. p-value =", p_value_theta)


# Visualisation de phi
plt.hist(phi, bins=50, density=True, alpha=0.7, color='blue', edgecolor='black')
plt.xlabel("Phi (radians)")
plt.ylabel("Densité")
plt.title("Histogramme de Phi (3D)")
plt.show()

# Visualisation de theta
plt.hist(theta, bins=50, density=True, alpha=0.7, color='orange', edgecolor='black')
plt.xlabel("Theta (radians)")
plt.ylabel("Densité")
plt.title("Histogramme de Theta (3D)")
plt.show()