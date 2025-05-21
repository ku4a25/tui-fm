#include "fm.hpp"
#include <algorithm>
#include <fstream>
#include <filesystem>

F::F(const std::string& x) : p(x) {
    l(x);
}

void F::apf() {
    f_e.clear();
    for (const auto& i : e) {
        std::string n = i.path().filename().string();
        if (filter.empty() || n.find(filter) != std::string::npos)
            f_e.push_back(i);
    }
}

void F::l(const std::string& x) {
    e.clear();
    p = x;
    si = 0;
    so = 0;

    try {
        for (const auto& i : fs::directory_iterator(p)) e.push_back(i);
        std::sort(e.begin(), e.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
            if (a.is_directory() != b.is_directory()) return a.is_directory();
            return a.path().filename().string() < b.path().filename().string();
        });
    } catch (...) { e.clear(); }

    apf();
}

void F::d() {
    if (f_e.empty()) return;
    fs::path x = f_e[si].path();
    try {
        if (fs::is_directory(x)) fs::remove_all(x);
        else fs::remove(x);
    } catch (...) {}
    l(p);
}

void F::rn(const std::string& n) {
    if (f_e.empty()) return;
    fs::path o = f_e[si].path();
    fs::path nw = o.parent_path() / n;
    try {
        fs::rename(o, nw);
    } catch (...) {}
    l(p);
}

void F::cp(const std::string& dest) {
    if (f_e.empty()) return;
    fs::path src = f_e[si].path();
    fs::path dst = fs::path(dest) / src.filename();
    try {
        if (fs::is_directory(src))
            fs::copy(src, dst, fs::copy_options::recursive);
        else
            fs::copy(src, dst);
    } catch (...) {}
    l(p);
}

void F::mv(const std::string& dest) {
    if (f_e.empty()) return;
    fs::path src = f_e[si].path();
    fs::path dst = fs::path(dest) / src.filename();
    try {
        fs::rename(src, dst);
    } catch (...) {}
    l(p);
}
