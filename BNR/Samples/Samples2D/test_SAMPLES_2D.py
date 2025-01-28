import numpy as np
import scipy
from scipy.stats import kstest
import matplotlib.pyplot as plt
import subprocess
import os

# Étape 1 : Compilation et exécution du fichier C++ (test_SAMPLES_2D.cpp)
cpp_file = "test_SAMPLES_2D.cpp"
executable_file = "test_SAMPLES_2D"

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

# Function to load 2D data from a text file
def load_data(file_path):
    data = np.loadtxt(file_path)  # Load data directly from the text file
    return data[:, 0], data[:, 1]  # Return x and y

# Chemin vers le fichier Test_Echantillon.txt
data_file = 'Test_Echantillon.txt'

# Charger les échantillons
data_x, data_y = load_data(data_file)

# Conversion en coordonnées polaires
theta = np.arctan2(data_y, data_x)
theta = np.mod(theta + 2 * np.pi, 2 * np.pi)  # Convertir en [0, 2π]


# Test KS pour vérifier si theta suit une distribution uniforme sur [0, 2π]
statistic_theta, p_value_theta = kstest(theta, 'uniform', args=(0, 2 * np.pi))

if p_value_theta < 0.05:
    print("La distribution de θ n'est pas uniforme.")
else:
    print("La distribution de θ est uniforme.")

# Calculer la densité de probabilité pour l'angle θ
plt.hist(theta, bins=50, density=True, alpha=0.5, label='Densité de θ')
plt.xlabel("θ (radians)")
plt.ylabel("Densité")
plt.title("Histogramme de la distribution de θ")
plt.legend()
plt.show()