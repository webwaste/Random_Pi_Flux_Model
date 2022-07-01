import multiprocessing as mp
import subprocess as sp
import numpy as np
from tqdm import tqdm
import time
import math
import time
import json
import os
import glob


def eigen_dumper(i):
    print("i: ",i);
    proc_id = mp.current_process().pid
    sp.run(["./cpp_executables/rand_pi_flux_generator",str(proc_id)]);
    sp.run(["./cpp_executables/gauge_fixer",str(proc_id)]);
    sp.run(["./cpp_executables/ham_constructor",str(proc_id)]);

    H = np.loadtxt("Data/"+str(proc_id)+"Hamiltonian.mat", dtype = float);
    #deleting the unnecessary files
    for filename in glob.glob("Data/"+str(proc_id)+"*"):
        os.remove(filename);

    return np.linalg.eigvalsh(H);


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

    n_proc_max = mp.cpu_count();
    pool = mp.Pool(2);

#    for i in tqdm(range(N_samp), desc="Progress: ", ascii=False,ncols=75):
#    for i in range(N_samp):
    EIG = pool.map(eigen_dumper,range(N_samp));

    pool.close()
    pool.join()

    os.makedirs("Data/"+str(Lx)+"X"+str(Ly), exist_ok=True);
    np.save("Data/"+str(Lx)+"X"+str(Ly)+"/eigen_val_"+str(Lx)+"_"+str(Ly)+"_"+str(p),EIG)

    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print("Time taken: ",int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

