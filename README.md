# Pararllel-Computing-Project
Run the parallel version with these commands in the terminal
mpicc -o output main.c
mpirun -np 4 ./output

Run the serial version with this commands in the terminal
gcc -o output main.c
./output
