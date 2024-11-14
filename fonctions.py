
#Lecture des variables
def lire_fichier(nom_fichier):
    
    variables = {
        "Nx": None, "Ny": None, "xmin": None, "xmax": None, "ymin": None, "ymax": None,
        "Tf": None, "alphaS": None, "alphaT": None   ## ajouter param en fin de ligne 
    }
    
    # Ouvrir le fichier
    try:
        with open(nom_fichier, "r") as file:
            # Lire chaque ligne et extraire les valeurs
            for line in file:
                line = line.strip()  # Supprimer les espaces blancs
                if line:
                    # Séparer par '=' et enlever les espaces
                    key, value = [x.strip() for x in line.split('=')]
                    
                    # Assigner la valeur correcte en fonction du type
                    if key in ["Nx", "Ny"]:
                        variables[key] = int(value)
                    elif key in ["xmin", "xmax", "ymin", "ymax", "Tf", "alphaS", "alphaT"]:
                        variables[key] = float(value)
                    ## ajouter param en fin de ligne selon son type
    except FileNotFoundError:
        print("Erreur lors de l'ouverture du fichier.")
        exit(1)

    Nx = variables["Nx"]
    Ny = variables["Ny"]
    xmin = variables["xmin"]
    xmax = variables["xmax"]
    ymin = variables["ymin"]
    ymax = variables["ymax"]
    Tf = variables["Tf"]
    alphaS = variables["alphaS"]
    alphaT = variables["alphaT"]
    ## ajouter param en fin de ligne 

    # Retourner les valeurs sous forme de dictionnaire
    ## ajouter param en fin de ligne 
    return Nx , Ny , xmin , xmax , ymin , ymax , Tf , alphaS , alphaT