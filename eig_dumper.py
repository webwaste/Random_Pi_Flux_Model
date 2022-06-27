import multiprocessing as mp
import subprocess as sp
import numpy as np
import math
import time
import json


def eig(H):
    return np.linalg.eig(H)[0];

def main():
    #Rading the json files 
    config_file = open("config.json",'r');
    config = json.load(config_file);

    N_samp = config["No_of_sampling"];  #no of partion in dos plotting axis.
    Lx = config["Lx"];
    Ly = config["Ly"];

    dim = Lx*Ly;
    EIG = np.zeros((N_samp,dim));

    for i in range(N_samp):
        sp.call("./cpp_executables/rand_pi_flux_generator");
        sp.call("./cpp_executables/gauge_fixer");
        sp.call("./cpp_executables/ham_constructor");
    
        H = np.loadtxt("Data/Hamiltonian.mat", dtype = float);
        EIG[i] = eig(H);
        print("Sampling: ",i+1);

    np.savetxt("Data/eigen_val_"+str(Lx)+"_"+str(Ly)+".dat",EIG,fmt="%s")

    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print(int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

