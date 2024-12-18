#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <ncurses/ncurses.h>

#include "savefile.h"
#include "submenu.h"

class Player
{
    private: 
        int posx, posy;
        WINDOW* play_window;
        std::array<std::string, 11> play_map;

    public:
        // constructor
        Player(WINDOW* _play_window, std::array<std::string, 11> & _play_map, int _initx, int _inity);
        Player();

        void pl_move(int dy, int dx); 
        void render();

        std::vector<int> get_yx();
        std::array<std::string, 11>& get_map();

        void set_yx(int newy, int newx);
};

class Sokoban 
{
    private: 
        int sizey, sizex;
        WINDOW *my_sokoban_window;
        WINDOW *my_level_select = NULL;
        WINDOW *my_sokoban_msg = NULL;
        WINDOW *my_sokoban_play = NULL;
        Player player;

    public: 
        // constructor 
        Sokoban(WINDOW *_my_sokoban_window, int _sizey, int _sizex);

        void open(); 
        void close();
        
        int sokoban_action_handler(MainMenu & main_menu, Savefile & my_save, int ch); 
        void render_level_select_menu();
        void enter_level(int lvl_id);
        void render_game_map();
        void sokoban_play_handler();

        std::vector<int> get_win_size();
        WINDOW * get_my_win();
        Player& get_my_player();

        void set_my_win(WINDOW* new_win);
        void set_my_player(Player & my_player);
};

#endif