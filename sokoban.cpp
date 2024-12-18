#include <array>
#include <string>
#include <iostream> // TODO REMOVE

#include "submenu.h"
#include "sokoban.h"

Player::Player(WINDOW* _play_window, std::array<std::string, 11> & _play_map, int _initx, int _inity) {
    posx = _initx;
    posy = _inity;
    play_window = _play_window;
    play_map = _play_map;

    render();
};

Player::Player() {};

std::vector<int> Player::get_yx() {
    return {posy, posx};
}

std::array<std::string, 11>& Player::get_map() {
    return play_map;
}

void Player::set_yx(int newy, int newx) {
    posx = newx;
    posy = newy;
}

void Player::pl_move(int dy, int dx) {
    // check for legal movement here
    set_yx(posy+dy, posx+dx);

    render();
}

void Player::render() {
    mvwaddch(play_window, posy, posx, '@');
    wrefresh(play_window);
}

Sokoban::Sokoban(
    WINDOW *_my_sokoban_window,
    int _sizey, 
    int _sizex
) {
    my_sokoban_window = _my_sokoban_window;
    sizey = _sizey;
    sizex = _sizex;
}

std::vector<int> Sokoban::get_win_size() {
    return {sizey, sizex};
}

WINDOW *Sokoban::get_my_win() {
    return my_sokoban_window;
}

Player& Sokoban::get_my_player() {
    return player;
}

void Sokoban::set_my_win(WINDOW* new_win) {
    my_sokoban_window = new_win;
}

void Sokoban::set_my_player(Player & my_player) {
    player = my_player;
}

void Sokoban::open() {
    my_sokoban_window = newwin(sizey, sizex, 0, 0);
    my_sokoban_play = subwin(my_sokoban_window, sizey, sizex - 28, 0, 0);
    box(my_sokoban_play, 0, 0);
    my_sokoban_msg = subwin(my_sokoban_window, sizey, 28, 0, sizex - 28);
    box(my_sokoban_msg, 0, 0);
    wrefresh(my_sokoban_window);

    render_level_select_menu();
}

void Sokoban::close() {
    werase(my_sokoban_window);
    wrefresh(my_sokoban_window);
    delwin(my_sokoban_window);
}

void Sokoban::render_level_select_menu() {
    std::vector<std::string> lvl_list = {"a) Level 1a", "b) Level 1b", "c) Level 2a", "d) Level 2b", "e) Level 3a", "f) Level 3b", "g) Level 4a", "h) Level 4b"};
    std::string title = "Select a level:";
    std::string esc_msg = "Enter) Exit";

    my_level_select = subwin(my_sokoban_window, 12+2, title.length() + 2, sizey/2 - 6, sizex/2 - title.length()/2);
    wattron(my_level_select, COLOR_PAIR(2));
    box(my_level_select, 0, 0);
    wattroff(my_level_select, COLOR_PAIR(2));
    mvwaddstr(my_level_select, 1, 1, title.c_str());

    for (int i = 0; i < (int)lvl_list.size(); ++i) {
        mvwaddstr(my_level_select, i+3, 3, lvl_list[i].c_str());
    }

    mvwaddstr(my_level_select, 12, 3, esc_msg.c_str());

    wrefresh(my_level_select);
}

void Sokoban::render_game_map() {
    for (int i = 0; i < (int)sokoban_1a.size(); ++i) {
        mvwaddstr(my_sokoban_play, 16 - (int)sokoban_1a.size()/2 + i, 41 - sokoban_1a[i].length()/2, sokoban_1a[i].c_str());
    }
}

void Sokoban::enter_level(int lvl_id) {
    (void) lvl_id;

    render_game_map();

    // command list render

}

void Sokoban::sokoban_play_handler() {
    bool is_running = true;
    while (is_running) {
        int ch1 = getch();
        render_game_map();
        if (ch1 == 27) {
            return;
        } else if (ch1 == 258) {
            get_my_player().pl_move(1, 0); 
        } else if (ch1 == 259) {
            get_my_player().pl_move(-1, 0); 
        } else if (ch1 == 260) {
            get_my_player().pl_move(0, -1); 
        } else if (ch1 == 261) {
            get_my_player().pl_move(0, 1); 
        } else if (ch1 == 339) {
            get_my_player().pl_move(-1, 1); 
        } else if (ch1 == 338) {
            get_my_player().pl_move(1, 1);
        } else if (ch1 == 360) {
            get_my_player().pl_move(1, -1);
        } else if (ch1 == 262) {
            get_my_player().pl_move(-1, -1);
        }
        
        else {
            continue;
        }
    }
}

int Sokoban::sokoban_action_handler(MainMenu & main_menu, Savefile & my_save, int ch) {
    // sokoban menu
    if (ch == 10) {
        close();

        main_menu.open_menu();
        std::string file_title = main_menu.get_filetitle();
        main_menu.render_menu(file_title, my_save);
        wrefresh(main_menu.get_my_win());

        return 1;
    } else if (ch >= int('a') && ch <= int('h')) {
        // open sokoban levels
        enter_level(0);

        werase(my_level_select);
        wrefresh(my_level_select);
        delwin(my_level_select);

        Player my_player(
            my_sokoban_play, sokoban_1a, 36, 12
        );
        set_my_player(my_player);
        render_game_map();
        my_player.render();

        sokoban_play_handler();

        render_level_select_menu();

        return 2; 
    } else {
        return 2;
    }

    return -1;
}

