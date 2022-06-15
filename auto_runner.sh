#!/bin/sh

#This is to automate the process of running the codes sequentially.
echo 
echo "####################################"
./rand_pi_flux_generator 32 32 500 
echo "Random pi-flux generation done."
./gauge_fixer
echo "Gauge fixed."
./ham_constructor
echo "Hamiltonian construction done."
#time ./dos
echo "DOS computation done."
#gnuplot plotter.p
echo "DOS graph plotting done."
echo "####################################"
echo 


