# Data file name
set datafile separator whitespace  # Separator: space or tabulation (modifiable according to your data)
datafile = "Test_Echantillon.txt"

# Title and labels
set title "3D Display of Positions" font "Helvetica,14"
set xlabel "Position X" font "Helvetica,12"
set ylabel "Position Y" font "Helvetica,12"
set zlabel "Position Z" font "Helvetica,12"

# Adjusting the Z position to avoid overlap on the Z axis (by adding an offset)
set zrange [0:10]  # Adjust the range of Z-axis if necessary

# Style of points
set style line 1 lc rgb "#0060ad" pt 7 ps 1.5  # Blue color, point style 7, size 1.5

# Displaying 3D data (shifting the Z positions if needed)
splot datafile using 1:2:(column(3) + 2) with points linestyle 1 title "Positions"

