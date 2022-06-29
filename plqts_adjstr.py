import sys
import json

config_file=open("config.json",'r');
config=json.load(config_file);
config_file.close();

Lx = config["Lx"];
Ly = config["Ly"];
p = float(sys.argv[1]);
N_plqts = int(p*Lx*Ly);

if N_plqts%2==1:
    N_plqts+=1;

config["No_of_plaquettes"]=N_plqts;
config["Probability"]=p;

config_file=open("config.json",'w');
json.dump(config,config_file,indent=4);
config_file.close();
    



