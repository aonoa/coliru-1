##set -x ; clang++ -std=c++11 -O2 -W -Wall -pedantic -pthread main.cpp  && ./a.out
##set -x ; g++ -std=c++11 -O2 -W -Wall  -Wconversion -pedantic -pthread main.cpp  && ./a.out
##set -x ; g++ -std=c++11 -O2 -W -Wall  -Wconversion -pedantic -pthread main.cpp -S  && cat main.s
##set -x ; gcc -x c -std=gnu99 -O2 -W -Wall -Wextra -pedantic  -pthread main.cpp  && ./a.out
set -x ; clang -x c -std=c99 -O0 -W -Wall -pedantic  -pthread main.cpp  && ./a.out