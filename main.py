from fonctions import *

Nx , Ny , xmin , xmax , ymin , ymax , Tf , alphaS , alphaT = lire_fichier("data.txt")

dx = ( xmax - xmin )/Nx
dy = (yxmax - ymin )/Ny

# dt = CFL * dx * dy
dt = 0.001

for i in range(Tf/dt):
    #boucle en temps

    if alphaT == 0. and alphaS == 0: 
        #equation de transport

        