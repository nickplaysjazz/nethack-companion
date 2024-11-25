#ifndef PLAYMAP_H
#define PLAYMAP_H

#include <ncurses/ncurses.h>

class GameMap 
{
    private: 
        int id;
        void init_map(int maxy, int maxx);

    public: 
        int **map;
        int sizey, sizex;
        int totrow, totcol; 
        WINDOW *play_win;

        //typedef bool (Menu::*ActionHandlerType)(int); 
        //ActionHandlerType action_handler = &Menu::menu_action_handler;

        // constructor 
        GameMap(int _id, int _totrow, int _totcol, int _sizey, int _sizex);
        // default constructor with no parameters is required for compilation when GameMap is passed as a parameter to a class in another file
        GameMap();
        void update_map(int maxy, int maxx);
};

#endif