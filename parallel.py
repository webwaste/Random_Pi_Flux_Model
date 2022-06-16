import multiprocessing as mp
import subprocess as sp
import numpy as np
import math
import time


def dos(H, E, eta, dim):
    G = np.linalg.inv((E + eta*(1j))*np.identity(dim) - H)
    #print("E: %.2f"%E);
    return -(np.trace(G).imag)/(math.pi)

def main():
    N = 1000;  #no of partion in dos plotting axis.
    N_it = 150; #number of iteration.
    DOS = np.zeros((N_it,N));
    for i in range(N_it):
        sp.call("./cpp_executables/rand_pi_flux_generator");
        sp.call("./cpp_executables/gauge_fixer");
        sp.call("./cpp_executables/ham_constructor");
    
        H = np.loadtxt("Data/Hamiltonian.mat", dtype = float);
        dim = H.shape[0];
        eta = 0.01
        E = np.linspace(-4.5,4.5,N)
        pool = mp.Pool(mp.cpu_count())
        DOS[i] = pool.starmap(dos, [(H,En,eta,dim) for En in E])
        pool.close();
        print("iteration: ",i+1);

    DOS_avg = np.sum(DOS,axis=0)/N_it;

    file = open("Data/parallel_dos.dat", "w");
    for i in range(N):
            file.write(str(E[i])+" "+str(DOS_avg[i])+"\n");
    
    file.close();

#    np.savetxt('Data/parallel_dos.dat',DOS_avg,delimiter='\n')
    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print(int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

