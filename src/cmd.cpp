#include "fm.hpp"
#include <ncurses.h>

void F::hc() {
    if (ci == "q") {
        endwin();
        exit(0);
    } else if (ci == "d") {
        d();
    } else if (ci == "help") {
        sh();
    } else if (ci == "clear") {
        filter.clear();
        apf();
    } else if (ci.substr(0, 2) == "r ") {
        rn(ci.substr(2));
    } else if (ci.substr(0, 3) == "cp ") {
        cp(ci.substr(3));
    } else if (ci.substr(0, 3) == "mv ") {
        mv(ci.substr(3));
    } else if (ci.substr(0, 2) == "f ") {
        filter = ci.substr(2);
        apf();
    }
}
