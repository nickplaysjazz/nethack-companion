#include <ncurses/ncurses.h>

#include "gamemap.h"

GameMap::GameMap(int _id, int _totrow, int _totcol, int _sizey, int _sizex) {
    id = _id;
    totrow = _totrow;
    totcol = _totcol; 
    sizey = _sizey;
    sizex = _sizex;
    play_win = newwin(totrow, totcol, 0, 0);
    init_map(sizey, sizex);
}

GameMap::GameMap() {}

void GameMap::init_map(int maxy, int maxx) {
    // define the map array
    map = new int*[maxy];
    for (int i = 0; i < maxy; ++i) {
        map[i] = new int[maxx];
        for (int j = 0; j < maxx; ++j) 
            map[i][j] = '^' - 0;
    }
    
    // the "map" is just empty squares. 
    // we aren't really using GameMap as a map. We just need something to draw windows on top of. 
    for (int i = 0; i < maxy; ++i) {
        for (int j = 0; j < maxx; ++j) { 
            if ((i > 0 && i < maxy - 1) && (j > 0 && j < maxx - 1)) {
                map[i][j] = '.' - 0;
            }
        }
    }

    update_map(sizey, sizex);
    refresh();
}

void GameMap::update_map(int maxy, int maxx) {
    wattron(play_win, COLOR_PAIR(1));
    box(play_win, 0, 0);
    for (int i = 0; i < maxy; ++i) {
        for (int j = 0; j < maxx; ++j) { 
            if ((i > 0 && i < maxy - 1) && (j > 0 && j < maxx - 1)) {
                mvwaddch(play_win, i, j, (char)map[i][j]);
            }
        }
    }
    wattroff(play_win, COLOR_PAIR(1));
    wrefresh(play_win);
}
