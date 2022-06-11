This repository contains the codes for solving random pi-flux model. 

----------------------------------------------------------------------
Programs in the root folders: 

[gauge_fixer.cpp] Takes a lattice configuration file as input where the plaquettes states are given and return a lattice configuration file where the edge states (Z's) are consistent with the plaquettes configuration. 

[ham_constructor.cpp] Takes a lattice configuration file as input with appropriate edges and plaquettes configuration and return the Hamiltonian matrix in single particle basis. 

[dos.cpp] Computes the density of states for a given hamiltonian for a predefined energy range.

[plotter.p] gnuplot script file for plotting the density of states. 

----------------------------------------------------------------------
Header files: 

[lattice.h] Contains the lattice class. 
[supl_func.h] Contains the silly functions that are required to keep the codes clean.
[matrix.h] Contains the matrix class. So far matrix class has not been used. Eigen package will be used most probably. 

----------------------------------------------------------------------
Data files: 
[rand_pi_flux.lat] Lattice configuration after defining the pi-flux-configuration.
[fixed_gauge.lat]  Lattice configuration after computing the consistent edge states.
[Hamiltonian.mat]  Hamiltonian matrix for a given plaquettes configuration.
[dos.dat]          list of density of states for different energies.
[dos_plot.pdf]     Plot of density of states.
