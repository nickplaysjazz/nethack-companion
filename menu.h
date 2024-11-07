#ifndef MENU_H
#define MENU_H

#include <ncurses/ncurses.h>
#include <string>
#include <vector>

#include "gamemap.h"

// Menu is the DEFAULT behavior for any SubMenu. SubMenu inherits from Menu and overrides function as needed
class Menu {
    protected: 
        WINDOW *my_win; 

        GameMap play_map; 
        int sizey, sizex, locy, locx;
        std::string menu_name;
        std::vector<std::string> options_list; 
        int close_button; 

    public: 
        Menu(
            const GameMap & _play_map,
            int _sizey, 
            int _sizex, 
            int _locy, 
            int _locx, 
            const std::string & _menu_name, 
            const std::vector<std::string> & _options_list, 
            int _close_button
        );
        Menu();
        void open_menu();
        virtual void render_menu();
        void close_menu();
        virtual bool menu_action_handler(int ch);
};

#endif