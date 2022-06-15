#!/bin/sh

#This is to automate the process of running the codes sequentially.
echo 
echo "####################################"
./cpp_executables/rand_pi_flux_generator 8 8 50 
echo "Random pi-flux generation done."
./cpp_executables/gauge_fixer
echo "Gauge fixed."
./cpp_executables/ham_constructor
echo "Hamiltonian construction done."
time ./cpp_executables/dos
echo "DOS computation done."
gnuplot plotter.p
echo "DOS graph plotting done."
echo "####################################"
echo 


