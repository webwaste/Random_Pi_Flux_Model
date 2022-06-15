import multiprocessing as mp
import numpy as np
import math
import time


def dos(H, E, eta, dim):
    G = np.linalg.inv((E + eta*(1j))*np.identity(dim) - H)
    print("E: %.2f"%E);
    return -(np.trace(G).imag)/(math.pi)

def main():
    H = np.loadtxt("Data/Hamiltonian.mat", dtype = float);
    np.savetxt('Data/H.mat',H,delimiter=' ')
    dim = H.shape[0];
    eta = 0.01
    E = np.linspace(-4.5,4.5,3000)
    pool = mp.Pool(mp.cpu_count())
    DOS = pool.starmap(dos, [(H,En,eta,dim) for En in E])
    pool.close();


    np.savetxt('DOS.dat',DOS,delimiter='\n')
    
tic = time.time()
if __name__ == "__main__":
    main()
    t = time.time() - tic; 
    
    print(int(t//3600), " hours ",(t%3600)//60, " minutes ", (t%3600)%60, "seconds" )

