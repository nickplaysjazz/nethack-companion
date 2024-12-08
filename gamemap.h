#ifndef PLAYMAP_H
#define PLAYMAP_H

#include <ncurses/ncurses.h>
#include <vector>

class GameMap 
{
    private: 
        int id;
        void init_map(int maxy, int maxx);
        int sizey, sizex;
        int totrow, totcol; 

    public: 
        int **map;
        WINDOW *play_win;

        // constructor 
        GameMap(int _id, int _totrow, int _totcol, int _sizey, int _sizex);
        // default constructor with no parameters is required for compilation when GameMap is passed as a parameter to a class in another file
        GameMap();
        void update_map(int maxy, int maxx);
        std::vector<int> get_map_size();
        std::vector<int> get_map_tot_row_col();
};

#endif