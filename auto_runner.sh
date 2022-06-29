#!/bin/sh

#This is to automate the process of running the codes for different values of p.
echo 
for p in 0.8 0.82 0.84 0.86 0.88 0.90 0.92 0.94 0.96 0.98 1.0
do
    echo "Probability of plaquettes: "$p
    python plqts_adjstr.py $p
    echo "Number of Plaquettes adjusted."
    echo
    echo "Eigen values are being dumped for each random configuration"
    echo
    python eig_dumper.py
    echo
    echo "Eigen values are being used to calculate density of states."
    echo
    python eig2dos.py
    echo 
    echo "DOS for random configurations are being averaged."
    echo
    python averager.py
    echo

done
echo
echo "Calculation complete"
echo 
