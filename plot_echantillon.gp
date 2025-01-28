# Nom du fichier de données
set datafile separator whitespace  # Séparateur : espace ou tabulation (modifiable selon vos données)
datafile = "Test_Echantillon.txt"

# Titre et étiquettes
set title "Affichage 2D des positions" font "Helvetica,14"
set xlabel "Position X" font "Helvetica,12"
set ylabel "Position Y" font "Helvetica,12"

# Style des points
set style line 1 lc rgb "#0060ad" pt 7 ps 1.5  # Couleur bleue, point de style 7, taille 1.5

# Affichage des données
plot datafile using 1:2 with points linestyle 1 title "Positions"
