#ifndef SOKOBAN_H
#define SOKOBAN_H


#ifdef _WIN32
#include <ncurses/ncurses.h>
#elif __linux__
#include <ncurses.h>
#elif __APPLE__
#include <ncurses.h>
#endif

#include "savefile.h"
#include "submenu.h"


class Sokoban 
{
    private: 
        int sizey, sizex;
        WINDOW *my_sokoban_window;
        WINDOW *my_level_select = NULL;
        WINDOW *my_sokoban_msg = NULL;
        WINDOW *my_sokoban_play = NULL;
        //Player player;
        std::vector<int> player_pos = {0,0};
        int current_lvl_id = 0;
        bool is_flip_horiz = false;
        bool is_flip_vert = false;

        int turn_count = 0;

        std::vector<std::string> sokoban_map;

    public: 
        // constructor 
        Sokoban(WINDOW *_my_sokoban_window, int _sizey, int _sizex);

        void init_game();
        void init_sokoban_windows(); 
        void close_sokoban_windows();
        void render_sokoban_command_list(int lvl_id);

        int sokoban_action_handler(MainMenu & main_menu, Savefile & my_save, int ch); 
        void enter_level(int lvl_id);
        void render_game_map();
        void render_player();

        void attempt_player_move(int dy, int dx);

        WINDOW * get_my_win();

        void set_my_win(WINDOW* new_win);

};

#endif