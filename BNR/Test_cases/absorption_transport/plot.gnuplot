# permet de définir les couleurs d'affichage
set palette defined ( 0 '#F7FBFF',\
                      1 '#DEEBF7',\
                      2 '#C6DBEF',\
                      3 '#9ECAE1',\
                      4 '#6BAED6',\
                      5 '#4292C6',\
                      6 '#2171B5',\
                      7 '#084594' )

# pour faire des png. Commenter pour un affichage classique.
set terminal png

set xrange [-1:1]  # À adapter si nécessaire
set yrange [-1:1]  # À adapter si nécessaire
set zrange [0:1]  # Ajuster selon les valeurs de votre solution
set cbrange [0:1] # Ajuster selon les valeurs de votre solution
# si affichage 3D, fixe le point de vue. A changer selon les cas.
set view 48,132

do for [i = 0:9] {
    t=i*0.01
    # si sauvegarde en png, force le nom du fichier. A commenter sinon.
    # %05d force à écrire le nombre avec 5 chiffres et ajouter des 0 si besoin.
    set output "solution_n".sprintf("%d", i).".png"
    set title "t = ".sprintf("%f", t)." s"." (i = ".sprintf("%d", i).")"
    show title
    ## fait un affichage 2D en couleur
    plot "sol_ref_t".i.".txt" u 1:2:3 palette with image
    # fait un affichage en 3D et en couleur
    #splot "sol_ref_t".i.".txt" u 1:2:3 w l palette 
    ## A décommenter si affichage classique, et à adapter pour gérer la vitesse d'affichage
    # pause 0.01
}