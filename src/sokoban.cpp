#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../include/submenu.h"
#include "../include/sokoban.h"

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
    current_lvl_id = 0;
    init_sokoban_windows();
    render_sokoban_command_list(current_lvl_id);

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

void Sokoban::render_sokoban_command_list(int lvl_id) {
    std::string cmd_title = "SOKOBAN PRACTICE";
    std::string lvl_select = "Select level:";
    std::vector<std::string> lvl_list = {"1) Level 1a", "2) Level 1b", "3) Level 2a", "4) Level 2b", "5) Level 3a", "6) Level 3b", "7) Level 4a", "8) Level 4b"};
    std::vector<std::string> flip_list = {"r) Reverse (horiz.)", "f) Flip (vert.)"};
    std::string esc_msg = "Esc) Exit";

    wattron(my_sokoban_msg, COLOR_PAIR(3));
    mvwaddstr(my_sokoban_msg, 1, cmd_title.size()/2 - 2, cmd_title.c_str());
    wattroff(my_sokoban_msg, COLOR_PAIR(3));

    mvwaddstr(my_sokoban_msg, 4, 1, lvl_select.c_str());
    for (int i = 0; i < (int)lvl_list.size(); ++i) {
        if (lvl_id == i) {
            wattron(my_sokoban_msg, A_STANDOUT);
        }
        mvwaddstr(my_sokoban_msg, i+5, lvl_list[i].size()/2 + 2, lvl_list[i].c_str());
        if (lvl_id == i) {
            wattroff(my_sokoban_msg, A_STANDOUT);
        }
    }

    for (int i = 0; i < (int)flip_list.size(); ++i) {
        if ((is_flip_horiz == true && i == 0) || (is_flip_vert == true && i == 1)) {
            wattron(my_sokoban_msg, A_STANDOUT);
        }
        mvwaddstr(my_sokoban_msg, 15+i, 7, flip_list[i].c_str());
        if ((is_flip_horiz == true && i == 0) || (is_flip_vert == true && i == 1)) {
            wattroff(my_sokoban_msg, A_STANDOUT);
        }
    }

    mvwaddstr(my_sokoban_msg, 29, esc_msg.size()/2 + 1, esc_msg.c_str());

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
    // do not refresh play window, since rendering the player always occurs next & refreshes map!

    std::string turn_msg = "Turns: " + std::to_string(turn_count);
    mvwaddstr(my_sokoban_play, 1, sizex - 30 - turn_msg.length(), turn_msg.c_str());
}

void Sokoban::enter_level(int lvl_id) {
    //update cmd window
    render_sokoban_command_list(lvl_id);

    // delete previous map
    werase(my_sokoban_play);
    box(my_sokoban_play, 0, 0);

    // render game map
    render_game_map();

    // move player to stairway and render
    for (int i = 0; i < (int)sokoban_map.size(); ++i) {
        for (int j = 0; j < (int)sokoban_map[i].length(); ++j) {
            if (sokoban_map[i][j] == '>') {
                player_pos[0] = i + sizey/2 - (int)sokoban_map.size()/2;
                player_pos[1] = j + sizex/2 - 28/2 - sokoban_map[0].length()/2;
            }
        }
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
            ++turn_count;
            return;
        }
        // otherwise push boulder
        sokoban_map[map_y+dy][map_x+dx]= '.';
        sokoban_map[map_y+2*dy][map_x+2*dx] = '0';
    } 
    ++turn_count;
    player_pos[0] = player_pos[0] + dy;
    player_pos[1] = player_pos[1] + dx;
    // check for exiting level?
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
        } else if (ch >= int('1') && ch <= int('8') || (ch == int('r')) || (ch == int('f'))) {
            // change level
            turn_count = 0;
            if (ch == int('r')) {
                is_flip_horiz = !is_flip_horiz;
            } else if (ch == int('f')) {
                is_flip_vert = !is_flip_vert;
            }
            if (ch >= int('1') && ch <= int('8')) {
                current_lvl_id = ch - int('1');
            }
            if (current_lvl_id == 0) {
                sokoban_map = sokoban_1a;
            } else if (current_lvl_id == 1) {
                sokoban_map = sokoban_1b;
            } else if (current_lvl_id == 2) {
                sokoban_map = sokoban_2a;
            } else if (current_lvl_id== 3) {
                sokoban_map = sokoban_2b;
            } else if (current_lvl_id== 4) {
                sokoban_map = sokoban_3a;
            } else if (current_lvl_id== 5) {
                sokoban_map = sokoban_3b;
            } else if (current_lvl_id == 6) {
                sokoban_map = sokoban_4a;            
            } else if (current_lvl_id == 7) {
                sokoban_map = sokoban_4b;
            } 
            if (is_flip_vert) {
                std::reverse(sokoban_map.begin(), sokoban_map.end());
            }
            if (is_flip_horiz) {
                for (int i = 0; i < (int)sokoban_map.size(); ++i) {
                    std::reverse(sokoban_map[i].begin(), sokoban_map[i].end());
                }
            }
            enter_level(current_lvl_id);
        } else if (ch == 258 || ch == int('j')) {
            attempt_player_move(1, 0); 
            render_game_map();
            render_player();
        } else if (ch == 259 || ch == int('k')) {
            attempt_player_move(-1, 0); 
            render_game_map();
            render_player();
        } else if (ch == 260 || ch == int('h')) {
            attempt_player_move(0, -1); 
            render_game_map();
            render_player();
        } else if (ch == 261 || ch == int('l')) {
            attempt_player_move(0, 1); 
            render_game_map();
            render_player();
        } else if (ch == 339 || ch == int('u')) {
            attempt_player_move(-1, 1); 
            render_game_map();
            render_player();
        } else if (ch == 338 || ch == int('n')) {
            attempt_player_move(1, 1);
            render_game_map();
            render_player();
        } else if (ch == 360 || ch == int('b')) {
            attempt_player_move(1, -1);
            render_game_map();
            render_player();
        } else if (ch == 262 || ch == int('y')) {
            attempt_player_move(-1, -1);
            render_game_map();
            render_player();
        } 
        ch = getch();
    }
    return -1;
}

