echo zello>input.bin; clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp -lboost_iostreams && ./a.out