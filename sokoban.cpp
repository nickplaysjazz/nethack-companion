#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "submenu.h"
#include "sokoban.h"

Sokoban::Sokoban(
    WINDOW *_my_sokoban_window,
    int _sizey, 
    int _sizex
) {
    my_sokoban_window = _my_sokoban_window;
    sizey = _sizey;
    sizex = _sizex;
}

WINDOW *Sokoban::get_my_win() {
    return my_sokoban_window;
}

void Sokoban::set_my_win(WINDOW* new_win) {
    my_sokoban_window = new_win;
}


void Sokoban::init_game() {
    // initialize sokoban display
    init_sokoban_windows();
    render_sokoban_command_list();

    // set map to level 1a
    sokoban_map = sokoban_1a;
    
    // place player, & render map/player
    enter_level(0);
}

void Sokoban::init_sokoban_windows() {
    my_sokoban_window = newwin(sizey, sizex, 0, 0);
    my_sokoban_play = subwin(my_sokoban_window, sizey, sizex - 28, 0, 0);
    box(my_sokoban_play, 0, 0);
    my_sokoban_msg = subwin(my_sokoban_window, sizey, 28, 0, sizex - 28);
    box(my_sokoban_msg, 0, 0);
    wrefresh(my_sokoban_window);
}

void Sokoban::close_sokoban_windows() {
    werase(my_sokoban_window);
    wrefresh(my_sokoban_window);
    delwin(my_sokoban_window);
}

void Sokoban::render_sokoban_command_list() {
    std::vector<std::string> lvl_list = {"a) Level 1a", "b) Level 1b", "c) Level 2a", "d) Level 2b", "e) Level 3a", "f) Level 3b", "g) Level 4a", "h) Level 4b"};
    // std::string title = "Select a level:";
    std::string esc_msg = "Esc) Exit";

    // my_level_select = subwin(my_sokoban_window, 12+2, title.length() + 2, sizey/2 - 6, sizex/2 - title.length()/2);
    // wattron(my_level_select, COLOR_PAIR(2));
    // box(my_level_select, 0, 0);
    // wattroff(my_level_select, COLOR_PAIR(2));
    // mvwaddstr(my_level_select, 1, 1, title.c_str());

    for (int i = 0; i < (int)lvl_list.size(); ++i) {
        mvwaddstr(my_sokoban_msg, i+3, lvl_list[i].size()/2, lvl_list[i].c_str());
    }

    mvwaddstr(my_sokoban_msg, 12, esc_msg.size()/2, esc_msg.c_str());

    wrefresh(my_sokoban_msg);
}

void Sokoban::render_player() {
    mvwaddch(my_sokoban_play, player_pos[0], player_pos[1], '@');
    wrefresh(my_sokoban_play);
}

void Sokoban::render_game_map() {
    for (int i = 0; i < (int)sokoban_map.size(); ++i) {
        mvwaddstr(my_sokoban_play, sizey/2 - (int)sokoban_map.size()/2 + i, sizex/2 - sokoban_map[i].length()/2 - 28/2, sokoban_map[i].c_str());
    }
    wrefresh(my_sokoban_play);
}

void Sokoban::enter_level(int lvl_id) {
    // render game map
    render_game_map();

    // move player to stairway and render
    if (lvl_id == 0) {
        player_pos = {12, 36};
    }
    render_player();

}

void Sokoban::attempt_player_move(int dy, int dx) {
    // check for legal movement here
    std::vector<char> walls = {'-','|'};
    int map_y = player_pos[0] - sizey/2 + (int)sokoban_map.size()/2;
    int map_x = player_pos[1] - sizex/2 + 28/2 + sokoban_map[0].length()/2; 

    // can't move into walls
    if ((char)sokoban_map[map_y+dy][map_x+dx] == '^' || std::find(walls.begin(), walls.end(), (char)sokoban_map[map_y+dy][map_x+dx]) != walls.end()) {
        return;
    }

    // can't move diagonally through boulders
    if ((abs(dx) + abs(dy) == 2) && (((char)sokoban_map[map_y+dy][map_x] == '0' || std::find(walls.begin(), walls.end(), (char)sokoban_map[map_y+dy][map_x]) != walls.end()) && ((char)sokoban_map[map_y][map_x+dx] == '0' || std::find(walls.begin(), walls.end(), (char)sokoban_map[map_y][map_x+dx]) != walls.end()))) {
        return;
    }

    // boulder
    if ((char)sokoban_map[map_y+dy][map_x+dx] == '0') {
        // cannot move boulders diagonally
        if (abs(dx) + abs(dy) == 2) {
            return;
        }
        
        // check if wall or boulder is beyond
        if (((char)sokoban_map[map_y+2*dy][map_x+2*dx] == '0') || (std::find(walls.begin(), walls.end(), (char)sokoban_map[map_y+2*dy][map_x+2*dx]) != walls.end())) {
            return;
        } 

        // check if pit is beyond
        if ((char)sokoban_map[map_y+2*dy][map_x+2*dx] == '^') {
            sokoban_map[map_y+2*dy][map_x+2*dx] = '.';
            sokoban_map[map_y+dy][map_x+dx] = '.';
            player_pos[0] = player_pos[0] + dy;
            player_pos[1] = player_pos[1] + dx;
            return;
        }

        // otherwise push boulder
        sokoban_map[map_y+dy][map_x+dx]= '.';
        sokoban_map[map_y+2*dy][map_x+2*dx] = '0';
    } 

    player_pos[0] = player_pos[0] + dy;
    player_pos[1] = player_pos[1] + dx;

    // check for exiting level
    
}

int Sokoban::sokoban_action_handler(MainMenu & main_menu, Savefile & my_save, int ch) {
    bool is_running = true;
    while (is_running) {
        if (ch == 27) {
            close_sokoban_windows();

            main_menu.open_menu();
            std::string file_title = main_menu.get_filetitle();
            main_menu.render_menu(file_title, my_save);
            wrefresh(main_menu.get_my_win());

            is_running = false;
            return 1;
        } else if (ch >= int('a') && ch <= int('h')) {
            // werase(my_level_select);
            // wrefresh(my_level_select);
            // delwin(my_level_select);

            // change levels here!!       

            // once we have exited sokoban, render level select menu again
            //render_level_select_menu();
        } else if (ch == 258) {
            attempt_player_move(1, 0); 
            render_game_map();
            render_player();
        } else if (ch == 259) {
            attempt_player_move(-1, 0); 
            render_game_map();
            render_player();
        } else if (ch == 260) {
            attempt_player_move(0, -1); 
            render_game_map();
            render_player();
        } else if (ch == 261) {
            attempt_player_move(0, 1); 
            render_game_map();
            render_player();
        } else if (ch == 339) {
            attempt_player_move(-1, 1); 
            render_game_map();
            render_player();
        } else if (ch == 338) {
            attempt_player_move(1, 1);
            render_game_map();
            render_player();
        } else if (ch == 360) {
            attempt_player_move(1, -1);
            render_game_map();
            render_player();
        } else if (ch == 262) {
            attempt_player_move(-1, -1);
            render_game_map();
            render_player();
        }
        ch = getch();
    }

    return -1;
}

