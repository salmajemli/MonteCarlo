#!/usr/bin/python3
# -*- coding: iso-8859-1 -*-

import os
import subprocess


def run_test(test_dir, executable_name):
    """
    Exécute un cas test dans le dossier donné.
    - test_dir : répertoire contenant les fichiers pour le cas test.
    - executable_name : nom de l'exécutable généré par le makefile.
    """
    # Vérifier si le répertoire existe
    if not os.path.exists(test_dir):
        print(f"Erreur : Le répertoire {test_dir} n'existe pas.")
        return

    # Changer vers le répertoire de test
    os.chdir(test_dir)

    try:
        # Étape 1 : Compilation avec make
        print(f"Compilation en cours dans {test_dir}...")
        result = subprocess.run(["make"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode != 0:
            print(f"Erreur lors de la compilation dans {test_dir} :")
            print(result.stderr)
            return
        else:
            print(f"Compilation reussie dans {test_dir}.")

        # Vérifier si l'exécutable a été généré
        if not os.path.exists(executable_name):
            print(f"Erreur : L'exécutable '{executable_name}' n'a pas été généré dans {test_dir}. Vérifiez votre makefile.")
            return

        # Étape 2 : Exécution de l'application
        print(f"Execution de ./{executable_name} dans {test_dir}...")
        result = subprocess.run([f"./{executable_name}"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode != 0:
            print(f"Erreur lors de l'exécution dans {test_dir} :")
            print(result.stderr)
            return

        # Affichage des résultats
        print(f"Sortie du programme dans {test_dir} :")
        print(result.stdout)

    except FileNotFoundError as e:
        print(f"Erreur : {e}")
    except Exception as e:
        print(f"Une erreur inattendue est survenue dans {test_dir} : {e}")
    finally:
        # Revenir au répertoire parent
        os.chdir("..")


if __name__ == "__main__":
    # Liste des tests avec leurs répertoires et exécutables
    tests = [
        {"test_dir": "advection", "executable_name": "advection"},
        {"test_dir": "absorption_transport", "executable_name": "absorption"},
        {"test_dir": "diffusion_limit", "executable_name": "diffusion"},
    ]

    # Exécution de chaque test
    for test in tests:
        run_test(test["test_dir"], test["executable_name"])
