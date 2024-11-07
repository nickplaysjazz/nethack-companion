#ifndef MENU_H
#define MENU_H

#include <ncurses/ncurses.h>
#include <string>
#include <vector>

// Menu is the DEFAULT behavior for any Menu. SubMenu inherits from Menu and overrides functions. 
class Menu {
    private: 
        std::string menu_name;
        int sizey, sizex, locy, locx;
        std::vector<std::string> options_list; 
        std::string exit_msg; 
        int justify;        // 0 is top-left, 1 is middle-center
        int close_button; 
        WINDOW *my_win; 
        int totrow = 32;
        int totcol = 110;

    public: 
        Menu(
            const std::string & _menu_name, 
            int _sizey, 
            int _sizex, 
            int _locy, 
            int _locx, 
            const std::vector<std::string> & _options_list, 
            const std::string & _exit_msg, 
            int _justify = 0,
            int _close_button = 27
        );
        void open_menu();
        void close_menu();
        bool menu_action_handler(Menu & parent_menu);
};

#endif