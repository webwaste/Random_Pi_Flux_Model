import multiprocessing as mp
import subprocess as sp
import numpy as np
from scipy.sparse.linalg import eigsh
from tqdm import tqdm
import time
import math
import time
import json
import os


def main():
    #Rading the json files 
    config_file = open("config.json",'r');
    config = json.load(config_file);

    N_samp = config["No_of_sampling"];  #no of partion in dos plotting axis.
    Lx = config["Lx"];
    Ly = config["Ly"];
    p = config["Probability"];

    dim = Lx*Ly;
    EIG = np.zeros((N_samp,dim));

    os.makedirs("Data/"+str(Lx)+"X"+str(Ly), exist_ok=True);

    for i in tqdm(range(N_samp), desc="Progress: ", ascii=False,ncols=75):
        sp.call("./cpp_executables/rand_pi_flux_generator");
        sp.call("./cpp_executables/gauge_fixer");
        #sp.call("./cpp_executables/ham_constructor");
        sp.call("./cpp_executables/eigval_generator");

        EIG[i] =  np.loadtxt("Data/temp.eig", dtype = float);

    
        #H = np.loadtxt("Data/Hamiltonian.mat", dtype = float);
        #EIG[i] = np.linalg.eigvalsh(H);

    np.save("Data/"+str(Lx)+"X"+str(Ly)+"/eigen_val_"+str(Lx)+"_"+str(Ly)+"_"+str(p),EIG)

    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print("Time taken: ",int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

