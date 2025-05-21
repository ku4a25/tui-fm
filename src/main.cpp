#include "fm.hpp"
#include <ncurses.h>

void F::r() {
    int c;
    di();
    while ((c = getch())) {
        if (cm) {
            if (c == 10 || c == KEY_ENTER) {
                hc(); ci.clear(); cm = false;
            } else if (c == 27) {
                ci.clear(); cm = false;
            } else if (c == KEY_BACKSPACE || c == 127) {
                if (!ci.empty()) ci.pop_back();
            } else {
                ci += static_cast<char>(c);
            }
        } else {
            switch (c) {
                case KEY_UP:
                    if (si > 0) si--;
                    if (si < so) so--;
                    break;
                case KEY_DOWN:
                    if (si < f_e.size() - 1) si++;
                    if (si >= so + (LINES - 4)) so++;
                    break;
                case KEY_RIGHT:
                    if (!f_e.empty()) {
                        auto& x = f_e[si];
                        if (x.is_directory()) l(x.path().string());
                        else sf(x.path());
                    }
                    break;
                case KEY_LEFT:
                    if (!fs::path(p).parent_path().empty())
                        l(fs::path(p).parent_path().string());
                    break;
                case ':':
                    cm = true;
                    ci.clear();
                    break;
            }
        }
        di();
    }
}

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    noecho();
    curs_set(TRUE);
    keypad(stdscr, TRUE);

    F f(fs::current_path().string());
    f.r();

    endwin();
    return 0;
}
