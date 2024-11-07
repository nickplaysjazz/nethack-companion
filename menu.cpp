#include <ncurses/ncurses.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "menu.h"
#include "gamemap.h"
#include "utilities.h"

Menu::Menu(
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

// constructor with no parameters, this is required for compilation 
Menu::Menu() {}; 

void Menu::open_menu() {
    // TODO need to create ProfileMenu my_win, not the Menu my_win, when this is called. 
    my_win = newwin(sizey, sizex, locy, locx);
    render_menu();
    box(my_win, 0, 0);
    wrefresh(my_win);
}

// This function should ALWAYS be overriden
void Menu::render_menu() {
    throw std::runtime_error("Menu::render_menu() must be overriden!");
}

void Menu::close_menu() {
    werase(my_win);
    wrefresh(my_win);
    delwin(my_win);
}

// This function should ALWAYS be overriden
bool Menu::menu_action_handler(int ch) {
    throw std::runtime_error("Menu::menu_action_handler() must be overriden!");
}



// Menu::Menu(
//     const std::string & _menu_name, 
//     int _sizey, 
//     int _sizex, 
//     int _locy, 
//     int _locx, 
//     const std::vector<std::string> & _options_list, 
//     const std::string & _exit_msg, 
//     int _justify, 
//     int _close_button) 
// {
//     menu_name = _menu_name;
//     sizey = _sizey;
//     sizex = _sizex;
//     locy = _locy;
//     locx = _locx;
//     options_list = _options_list;
//     exit_msg = _exit_msg;
//     justify = _justify; 
//     close_button = _close_button;
// };

// void Menu::open_menu() {
//     // TODO check for options being too long for size of screen
//     my_win = newwin(sizey, sizex, locy, locx);
//     if (justify == 0) {
//         // top-left
//         int title_lines = count_newlines(menu_name) + 1;
//         std::string title_to_print = menu_name; 
//         for (int i = 0; i < title_lines; ++i) {
//             std::string line = title_to_print.substr(0, title_to_print.find("\n"));
//             title_to_print.erase(0, title_to_print.find("\n") + ((std::string)"\n").length());
//             mvwaddstr(my_win, 1 + i, 1, line.c_str());
//         }
//         int option_count = 0;
//         for (std::vector<std::string>::const_iterator it = options_list.begin(); it != options_list.end(); ++it) {
//             mvwaddstr(my_win, 2 + title_lines + option_count, 1, num_to_alphabet(option_count).c_str());
//             waddstr(my_win, ") "); 
//             waddstr(my_win, it->c_str());
//             ++option_count;
//         }
//         mvwaddstr(my_win, 4 + option_count, 1, exit_msg.c_str());
//     } else if (justify == 1) {
//         // centered
//         int title_lines = count_newlines(menu_name) + 1;
//         std::string title_to_print = menu_name; 
//         for (int i = 0; i < title_lines; ++i) {
//             std::string line = title_to_print.substr(0, title_to_print.find("\n"));
//             title_to_print.erase(0, title_to_print.find("\n") + ((std::string)"\n").length());
//             mvwaddstr(my_win, (int)(totrow/2 -2 - title_lines + i), (int)((totcol - line.length())/2), line.c_str());
//         }
//         int option_count = 0;
//         for (std::vector<std::string>::const_iterator it = options_list.begin(); it != options_list.end(); ++it) {
//             mvwaddstr(my_win, (int)(totrow/2 + option_count), (int)(totcol/2 - 5), num_to_alphabet(option_count).c_str());
//             waddstr(my_win, ") "); 
//             waddstr(my_win, it->c_str());
//             ++option_count;
//         }
//         mvwaddstr(my_win, (int)(totrow/2 + 1 + option_count), (int)(totcol/2 - 5), exit_msg.c_str());
//     } 
//     box(my_win, 0, 0);
//     wrefresh(my_win);
// }

// void Menu::close_menu() {
//     werase(my_win);
//     wrefresh(my_win);
//     delwin(my_win);
// }

// // returns true if still running game, false if quitting game
// bool Menu::menu_action_handler(Menu & parent_menu) {
//     while (true) {
//         int ch = getch();
//         if (ch == close_button) {
//             // closing button
//             close_menu();
//             parent_menu.open_menu();
//             return true;
//         }
//     }
// }