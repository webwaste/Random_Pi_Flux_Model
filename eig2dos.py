import multiprocessing as mp
import subprocess as sp
import numpy as np
import math
import time
import json

def dos(EigenVl, eta, E,dim):
    #En is a  
    #E is a numpy array
    dos = np.zeros(np.size(E));
    for En in EigenVl:
        dos += eta*np.reciprocal(((E - En)**2 + eta**2)*(np.pi))
    return dos/dim
        

def main():
    #Reading json files.
    config_file = open("config.json",'r');
    config = json.load(config_file);
    N_samp = config["No_of_sampling"];
    N_dos = config["DOS_partitions"];
    eta = config["eta"]
    Lx = config["Lx"]
    Ly = config["Ly"]
    dim = Lx*Ly

    EIG = np.loadtxt("Data/eigen_val.dat")[0:int(N_samp)];
    print("Eig: ",np.shape(EIG));
    DOS = np.zeros((N_samp,N_dos)); 
    print("dos: ",np.shape(DOS));
    print("dos[0]: ",np.shape(DOS[0]));
    E = np.linspace(-4,4,N_dos);
    print("E: ",np.shape(E));

    for i in range(N_samp):
        print("sampling no: ",i);
#        pool = mp.Pool(mp.cpu_count());
#        DOS[i] += pool.starmap(dos,[(En, eta, E) for En in EIG[i]])
        DOS[i] = dos(EIG[i],eta,E,dim)

    np.savetxt("Data/dos_raw_matrix_test.dat",DOS,fmt="%s");


    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print(int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

