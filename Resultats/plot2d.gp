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

# forcer l'étendue de la colorbar. A changer selon les cas.
set cbrange [0:1]

# force la mise à l'échelle des axes.
set size ratio -1

# si affichage 3D, force l'étendue de l'axe des z. A changer selon les cas.
set zrange [0:1]
set xrange [-1:1]
set yrange [-1:1]
# si affichage 3D, fixe le point de vue. A changer selon les cas.
set view 48,132

do for [i = 0:49] {
    t=i*0.01
    # si sauvegarde en png, force le nom du fichier. A commenter sinon.
    # %05d force à écrire le nombre avec 5 chiffres et ajouter des 0 si besoin.
    set output "Frame-".sprintf("%d", i).".png"
    set title "t = ".sprintf("%f", t)." s"." (i = ".sprintf("%d", i).")"
    show title
    ## fait un affichage 2D en couleur
    plot "solution_t_".i.".txt" u 1:2:5 palette with image
    # fait un affichage en 3D et en couleur
    #splot "solution_t_".i.".txt" u 1:2:5 w l palette 
    ## A décommenter si affichage classique, et à adapter pour gérer la vitesse d'affichage
    # pause 0.01
}
