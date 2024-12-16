#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <ncurses/ncurses.h>

#include "savefile.h"
#include "submenu.h"

class Sokoban 
{
    private: 
        int sizey, sizex;
        WINDOW *my_sokoban_window;
        WINDOW *my_level_select = NULL;

    public: 
        // constructor 
        Sokoban(WINDOW *_my_sokoban_window, int _sizey, int _sizex);

        void open(); 
        void close();
        
        int sokoban_action_handler(MainMenu & main_menu, Savefile & my_save, int ch); 
        void render_level_select_menu();

        std::vector<int> get_win_size();
        WINDOW * get_my_win();

        void set_my_win(WINDOW* new_win);
};

#endif