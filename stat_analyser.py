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
    for N_samp in np.linspace(100,N_it,10):
        print(N_samp);
        DOS = np.loadtxt("Data/dos_raw_matrix_test.dat")[0:int(N_samp)];
        DOS_avg = np.sum(DOS,axis=0)/N_samp;
        DOS_var = np.sum(np.square(DOS),axis=0)/N_samp - np.square(DOS_avg);
        E = np.linspace(-4,4,N);
        file = open("Data/dos_samp_"+str(N_samp)+".dat", "w");
        for i in range(N):
                file.write(str(E[i])+" "+str(DOS_avg[i])+" "+str(np.sqrt(DOS_var[i])/np.sqrt(N_samp-1))+"\n");
        
        file.close();

    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print(int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

