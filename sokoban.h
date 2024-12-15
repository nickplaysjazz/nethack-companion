#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <ncurses/ncurses.h>

#include "savefile.h"
#include "submenu.h"

class Sokoban 
{
    private: 
        int sizey, sizex;
        ///MainMenu & main_menu;
        //Savefile & my_save;

    public: 
        // constructor 
        Sokoban(int _sizey, int _sizex);

        void open(); 
        int sokoban_action_handler(int ch); 
};

#endif