import multiprocessing as mp
import subprocess as sp
import numpy as np
import math
import time
import json


def main():
    #Reading json files.
    config_file = open("config.json",'r');
    config = json.load(config_file);
    N_it = config["No_of_sampling"];
    N = config["DOS_partitions"];
    
    DOS = np.loadtxt("Data/dos_raw_matrix.dat")[0:300];
    DOS_avg = np.sum(DOS,axis=0)/N_it;
    DOS_var = np.sum(np.square(DOS),axis=0)/N_it - np.square(DOS_avg);
    E = np.linspace(-4,4,N);
    file = open("Data/parallel_dos_300.dat", "w");
    for i in range(N):
            file.write(str(E[i])+" "+str(DOS_avg[i])+" "+str(np.sqrt(DOS_var[i])/np.sqrt(N-1))+"\n");
    
    file.close();

    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print(int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

