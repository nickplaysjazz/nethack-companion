#include <ncurses/ncurses.h>

#include "submenu.h"

IntrinsicMenu::IntrinsicMenu(int _sizey, int _sizex, int _locy, int _locx) {
    sizey = _sizey;
    sizex = _sizex;
    locy = _locy;
    locx = _locx;
}

void IntrinsicMenu::open_menu() {
    my_win = newwin(sizey, sizex, locy, locx);
}

void IntrinsicMenu::close_menu() {
    werase(my_win);
    wrefresh(my_win);
    delwin(my_win);
} 

bool IntrinsicMenu::menu_action_handler() {
    while (true) {
        int ch = getch();
        // switch (ch):
            // TODO
    }
}