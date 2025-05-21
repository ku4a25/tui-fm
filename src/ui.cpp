#include "fm.hpp"
#include <fstream>
#include <ncurses.h>

void F::di() {
    clear();
    attron(A_BOLD);
    mvprintw(0, 0, "Path: %s", p.c_str());
    attroff(A_BOLD);

    int m = LINES - 4;
    for (int i = 0; i < m && (i + so) < f_e.size(); ++i) {
        int ix = i + so;
        std::string n = f_e[ix].path().filename().string();
        if (f_e[ix].is_directory()) {
            attron(COLOR_PAIR(2));
            n += "/";
        } else {
            attron(COLOR_PAIR(1));
        }

        if (ix == si) attron(A_REVERSE);
        mvprintw(i + 2, 2, "%s", n.c_str());
        if (ix == si) attroff(A_REVERSE);
        attroff(COLOR_PAIR(1));
        attroff(COLOR_PAIR(2));
    }

    if (cm) {
        mvprintw(LINES - 2, 0, ":%s", ci.c_str());
        move(LINES - 2, ci.length() + 1);
    } else {
        mvprintw(LINES - 2, 0, "Press ':' for command (e.g., :q, :d, :r <name>, :f query)");
    }

    refresh();
}

void F::sh() {
    clear();
    mvprintw(1, 2, "Spaghetti help page");
    mvprintw(3, 2, "Navigation:");
    mvprintw(4, 4, "Up/Down   - Move");
    mvprintw(5, 4, "Left      - Back");
    mvprintw(6, 4, "Right     - Enter/View");

    mvprintw(8, 2, "Commands:");
    mvprintw(9, 4, ":q         - Quit");
    mvprintw(10, 4, ":d         - Delete");
    mvprintw(11, 4, ":r <name>  - Rename");
    mvprintw(12, 4, ":cp <dest> - Copy");
    mvprintw(13, 4, ":mv <dest> - Move");
    mvprintw(14, 4, ":f <str>   - Filter");
    mvprintw(15, 4, ":clear     - Clear filter");
    mvprintw(16, 4, ":help      - Help");

    mvprintw(18, 2, "Press any key...");
    refresh();
    getch();
}

void F::sf(const fs::path& pth) {
    clear();
    mvprintw(0, 0, "Viewing: %s (press key to exit)", pth.filename().c_str());

    std::ifstream f(pth);
    std::string line;
    int r = 2;
    while (std::getline(f, line) && r < LINES - 1)
        mvprintw(r++, 2, "%.*s", COLS - 4, line.c_str());

    refresh();
    getch();
}
