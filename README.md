# Résolution de l'équation de Boltzmann par méthode Monte-Carlo

Ce projet résout l'équation de Boltzmann linéaire en utilisant une méthode Monte-Carlo semi-analogue. 

-----------------------------------------------------------

# Pour compiler le code et l'exécuter : 
    make
    ./main

-----------------------------------------------------------


# Les paramètres d'entrée sont modifiables dans le fichier parameters.txt. Ce fichier permet de définir :

    Le nombre de particules (Nmc)    
    Les dimensions du domaine (Dim)
    Le pas du temps (dt)
    L tsemps final de la solution (Tf)
    Les bords du domaine (xmin,xmax,ymin,...)
    Les Coefficients de section efficace pour la diffusion et l'absorption (SigmaS , SigmaT)
    


----------------------------------------------------------

# Résultats:
    Les résultats sont sauvegardés dans le dossier resultats.

---------------------------------------------------------


# Cas tests:
    Pour exécuter les différents tests du code, consultez le dossier BNR. Chaque sous-dossier contient un fichier README expliquant le test correspondant.
