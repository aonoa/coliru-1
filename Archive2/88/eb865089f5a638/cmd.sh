set -x; clang++ -O3 -std=c++1y -stdlib=libc++ -Wall -Wextra -pedantic main.cpp -o a.out && ./a.out
g++ -O3  -std=gnu++1y -Wall -Wextra -pedantic-errors  main.cpp -o a.out && ./a.out