set -x ; g++-4.8 -std=c++11 -O3 -fopenmp -Wall -pedantic -pthread main.cpp && OMP_NUM_THREADS=10 ./a.out