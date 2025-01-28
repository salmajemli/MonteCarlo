# Fichier : plot.gp
# Script Gnuplot pour afficher des graphiques 1D dans une boucle temporelle

# Définir la palette de couleurs pour une colorbar (non utilisée en 1D ici, mais conservée pour cohérence)
set palette defined ( 0 '#F7FBFF',\
                      1 '#DEEBF7',\
                      2 '#C6DBEF',\
                      3 '#9ECAE1',\
                      4 '#6BAED6',\
                      5 '#4292C6',\
                      6 '#2171B5',\
                      7 '#084594' )

# Pour générer des PNG
set terminal png size 800,600 enhanced font "Arial,12"

# Fixer les axes (à adapter en fonction de vos données)
set xrange [-1:1]        # Étendue des x (temps, colonne 1)
set yrange [0:2]        # Étendue des y (valeurs u, colonne 5)

# Ajouter une grille pour la lisibilité
set grid

# Définir une boucle pour afficher les frames
do for [i = 0:100] {
    # Calculer l'instant temporel
    t = i * 0.01

    # Définir le fichier de sortie PNG
    set output "Frame-".sprintf("%05d", i).".png"

    # Ajouter un titre dynamique au graphique
    set title "t = ".sprintf("%.2f", t)." s (i = ".sprintf("%d", i).")"

    # Tracer la courbe en 1D avec les colonnes 1 (temps) et 5 (valeurs)
    plot "solution_t_".i.".txt" using 1:5 with lines lw 2 lc rgb "blue" title "u(t)"

    # Pause pour affichage interactif (décommenter si besoin)
    # pause 0.01
}
