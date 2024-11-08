#include <ncurses/ncurses.h>
#include <iostream>

#include "submenu.h"
#include "utilities.h"

ProfileMenu::ProfileMenu(
    const GameMap & _play_map,
    int _sizey, 
    int _sizex, 
    int _locy, 
    int _locx, 
    const std::string & _menu_name, 
    const std::vector<std::string> & _options_list, 
    int _close_button = 27
    ) 
{
    play_map = _play_map; 
    sizey = _sizey;
    sizex = _sizex;
    locy = _locy;
    locx = _locx;
    menu_name = _menu_name;
    options_list = _options_list;
    close_button = _close_button;
};

void ProfileMenu::render_menu() {
        int title_lines = count_newlines(menu_name) + 1;
        int my_row = play_map.totrow;
        int my_col = play_map.totcol; 
        std::string title_to_print = menu_name; 
        for (int i = 0; i < title_lines; ++i) {
            std::string line = title_to_print.substr(0, title_to_print.find("\n"));
            title_to_print.erase(0, title_to_print.find("\n") + ((std::string)"\n").length());
            mvwaddstr(my_win, (int)(my_row/2 -2 - title_lines + i), (int)((my_col - line.length())/2), line.c_str());
        }
        int option_count = 0;
        for (std::vector<std::string>::const_iterator it = options_list.begin(); it != options_list.end(); ++it) {
            mvwaddstr(my_win, (int)(my_row/2 + option_count), (int)(my_col/2 - 5), num_to_alphabet(option_count).c_str());
            waddstr(my_win, ") "); 
            waddstr(my_win, it->c_str());
            ++option_count;
        }
        mvwaddstr(my_win,(int)(my_row/2 + 1 + option_count), (int)(my_col/2 - 5), ((std::string)"Enter) Create New Character").c_str());
        mvwaddstr(my_win,(int)(my_row/2 + 2 + option_count), (int)(my_col/2 - 5), ((std::string)"Backspace) Delete Character").c_str());
        mvwaddstr(my_win, (int)(my_row/2 + 4 + option_count), (int)(my_col/2 - 5), ((std::string)"Esc) Quit").c_str());
}

bool ProfileMenu::menu_action_handler(int ch) {
    switch (ch) {
        // todo handle variable case
        case 27:
            // TODO fix closing the right menu, right now it closes the parent Menu window instead of the child ProfileMenu window. 
            // might need to pass the window into close_menu()... 
            //close_menu();
            std::cout<<"test: esc has been hit, goodbye"<<std::endl;
            return false; 
            break;
        default:
            return true;
            break;
    }
}

// IntrinsicMenu::IntrinsicMenu(int _sizey, int _sizex, int _locy, int _locx) {
//     sizey = _sizey;
//     sizex = _sizex;
//     locy = _locy;
//     locx = _locx;
// }

// void IntrinsicMenu::open_menu() {
//     my_win = newwin(sizey, sizex, locy, locx);
// }

// void IntrinsicMenu::close_menu() {
//     werase(my_win);
//     wrefresh(my_win);
//     delwin(my_win);
// } 

// bool IntrinsicMenu::menu_action_handler() {
//     while (true) {
//         int ch = getch();
//         switch (ch):
// 
//     }
// }