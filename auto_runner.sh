#!/bin/sh

#This is to automate the process of running the codes sequentially.
echo 
echo "####################################"
./rand_pi_flux_generator 8 8 26 
echo "Random pi-flux generation done."
./gauge_fixer
echo "Gauge fixed."
./ham_constructor
echo "Hamiltonian construction done."
./dos
echo "DOS computation done."
gnuplot plotter.p
echo "DOS graph plotting done."
echo "####################################"
echo 


