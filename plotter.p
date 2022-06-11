set terminal pdf color size 6, 4 font "Helvetica,15"  
filename = sprintf("Data/Density_of_states.dat")
set output sprintf("Data/DOS_plot.pdf")
set title sprintf("η = 0.1") 

set xlabel "Energy (E)"
set ylabel "Density of states"
plot filename u 1:2 w l lc "black" t ""
