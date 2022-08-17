#g++ -ljsoncpp cpp_program_files/rand_pi_flux_generator.cpp -o cpp_executables/rand_pi_flux_generator
g++ -ljsoncpp cpp_program_files/single_pi_flux_generator.cpp -o cpp_executables/single_pi_flux_generator
#g++ cpp_program_files/gauge_fixer.cpp -o cpp_executables/gauge_fixer
##g++ cpp_program_files/ham_constructor.cpp -o cpp_executables/ham_constructor
#g++ -ljsoncpp cpp_program_files/eigval_generator.cpp -llapack -o cpp_executables/eigval_generator
g++ -ljsoncpp cpp_program_files/eigstate_generator.cpp -llapack -o cpp_executables/eigstate_generator
#g++ -ljsoncpp cpp_program_files/wave_data_gen.cpp -o cpp_executables/wave_data_gen
#g++ -ljsoncpp cpp_program_files/wavefunc_ang_dep_analyzer.cpp -o cpp_executables/wavefunc_ang_dep_analyzer
g++ -ljsoncpp cpp_program_files/low_enrg_state_gen.cpp -llapack -o cpp_executables/low_enrg_state_gen
#g++ cpp_program_files/dos.cpp -o cpp_executables/dos
