g++ -ljsoncpp cpp_program_files/rand_pi_flux_generator.cpp -o cpp_executables/rand_pi_flux_generator
g++ cpp_program_files/gauge_fixer.cpp -o cpp_executables/gauge_fixer
#g++ cpp_program_files/ham_constructor.cpp -o cpp_executables/ham_constructor
g++ -ljsoncpp cpp_program_files/eigval_generator.cpp -llapack -o cpp_executables/eigval_generator
#g++ cpp_program_files/dos.cpp -o cpp_executables/dos
