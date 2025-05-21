
// mk.cpp
#include "mk.hpp"
#include <fstream>
#include <sys/stat.h>
#include <cstring>

void mf(const char* p) {
    std::ofstream f(p);
    f.close();
}

void md(const char* p) {
    mkdir(p, 0755);
}
