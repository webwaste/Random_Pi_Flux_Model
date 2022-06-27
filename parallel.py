import multiprocessing as mp
import subprocess as sp
import numpy as np
import math
import time
import json


def dos(H, E, eta, dim):
    G = np.linalg.inv((E + eta*(1j))*np.identity(dim) - H)/dim
    #print("E: %.2f"%E);
    return -(np.trace(G).imag)/(math.pi)

def main():
    #Rading the json files 
    config_file = open("config.json",'r');
    config = json.load(config_file);
    N = config["DOS_partitions"];  #no of partion in dos plotting axis.
    N_it = config["No_of_sampling"];  #no of partion in dos plotting axis.

    DOS = np.zeros((N_it,N));
    for i in range(N_it):
        sp.call("./cpp_executables/rand_pi_flux_generator");
        sp.call("./cpp_executables/gauge_fixer");
        sp.call("./cpp_executables/ham_constructor");
    
        H = np.loadtxt("Data/Hamiltonian.mat", dtype = float);
        dim = H.shape[0];
        eta = 0.005
        E = np.linspace(-4,4,N)
        pool = mp.Pool(mp.cpu_count())
        DOS[i] = pool.starmap(dos, [(H,En,eta,dim) for En in E])
        pool.close();
        print("iteration: ",i+1);

    np.savetxt("Data/dos_raw_matrix.dat",DOS,fmt="%s")

#    DOS_avg = np.sum(DOS,axis=0)/N_it;
#    DOS_var = np.sum(np.square(DOS),axis=0)/N_it - np.square(DOS_avg);
#
#    file = open("Data/parallel_dos.dat", "w");
#    for i in range(N):
#            file.write(str(E[i])+" "+str(DOS_avg[i])+" "+str(np.sqrt(DOS_var[i])/np.sqrt(N-1))+"\n");
#    
#    file.close();

    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print(int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

