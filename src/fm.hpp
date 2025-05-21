#pragma once
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class F {
public:
    std::vector<fs::directory_entry> e;
    std::vector<fs::directory_entry> f_e;
    std::string p;
    int si = 0, so = 0;
    bool cm = false;
    std::string ci;
    std::string filter;

    F(const std::string&);
    void l(const std::string&);
    void d();
    void sh();
    void sf(const fs::path&);
    void rn(const std::string&);
    void hc();
    void r();
    void di();
    void cp(const std::string&);
    void mv(const std::string&);
    void apf();
};
