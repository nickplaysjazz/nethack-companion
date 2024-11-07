#ifndef PLAYMAP_H
#define PLAYMAP_H

#include <ncurses/ncurses.h>

class GameMap 
{
    private: 
        int id;
        int totrow, totcol; 

        void init_map(int maxy, int maxx);

    public: 
        int **map;
        int sizey, sizex;
        WINDOW *play_win;

        // constructor 
        GameMap(int _id, int _totrow, int _totcol, int _sizey, int _sizex);
        void update_map(int maxy, int maxx);
};

#endif