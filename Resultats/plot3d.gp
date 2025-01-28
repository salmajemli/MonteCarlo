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

# si affichage 3D, fixe l'étendue de l'axe des z. A changer selon les cas.
set zrange [-1:1]
set xrange [-1:1]
set yrange [-1:1]
set trange [0:1] # Ajout d'une plage pour les valeurs de u
# si affichage 3D, fixe le point de vue. A changer selon les cas.
set view 48,132

do for [i = 0:49] {
    t = i * 0.01
    # si sauvegarde en png, force le nom du fichier. A commenter sinon.
    set output "Frame-".sprintf("%d", i).".png"
    set title "t = ".sprintf("%f", t)." s (i = ".sprintf("%d", i).")"
    show title
    # Traçage de u en fonction de x, y et z
    splot "solution_t_".i.".txt" u 1:2:3:5 with points palette
    # ou pour une visualisation en surface
    # splot "solution_t_".i.".txt" u 1:2:3:5 with pm3d palette
    # pause 0.01 # A décommenter si vous souhaitez une pause entre les images
}