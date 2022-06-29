import multiprocessing as mp
import subprocess as sp
import numpy as np
from tqdm import tqdm
import math
import time
import json
import os


def main():
    #Reading json files.
    config_file = open("config.json",'r');
    config = json.load(config_file);
    N_samp = config["No_of_sampling"];
    N_dos = config["DOS_partitions"];
    Lx = int(config["Lx"])
    Ly = int(config["Ly"])
    p = config["Probability"];
    l_lim = config["lower_energy_limit_of_dos"]
    u_lim = config["upper_energy_limit_of_dos"]

    DOS = np.loadtxt("Data/"+str(Lx)+"X"+str(Ly)+"/raw_dos_"+str(Lx)+"_"+str(Ly)+"_"+str(p)+".dat")[0:int(N_samp)];
    DOS_avg = np.sum(DOS,axis=0)/N_samp;
    DOS_var = np.sum(np.square(DOS),axis=0)/N_samp - np.square(DOS_avg);
    E = np.linspace(l_lim,u_lim,N_dos);
    file = open("Data/"+str(Lx)+"X"+str(Ly)+"/dos_"+str(Lx)+"_"+str(Ly)+"_"+str(p)+".dat", "w");
    for i in tqdm(range(N_dos),desc="Progress: ", ascii=False, ncols=75):
            file.write(str(E[i])+" "+str(DOS_avg[i])+" "+str(np.sqrt(DOS_var[i])/np.sqrt(N_samp-1))+"\n");
    
    file.close();

    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print("Time taken: ",int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

