import multiprocessing as mp
import subprocess as sp
import numpy as np
from tqdm import tqdm
import math
import time
import json
import os

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
    p = config["Probability"]

    EIG = np.load("Data/"+str(Lx)+"X"+str(Ly)+"/eigen_val_"+str(Lx)+"_"+str(Ly)+"_"+str(p)+".npy")[0:int(N_samp)];
    DOS = np.zeros((N_samp,N_dos)); 
    E = np.linspace(-4,4,N_dos);

    for i in tqdm(range(N_samp),desc="Progress",ascii=False,ncols=75):
        DOS[i] = dos(EIG[i],eta,E,dim)

    np.save("Data/"+str(Lx)+"X"+str(Ly)+"/raw_dos_"+str(Lx)+"_"+str(Ly)+"_"+str(p),DOS);


    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print("Time taken: ",int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

