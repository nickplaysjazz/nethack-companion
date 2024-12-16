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

std::vector<int> Sokoban::get_win_size() {
    return {sizey, sizex};
}

WINDOW *Sokoban::get_my_win() {
    return my_sokoban_window;
}

void Sokoban::set_my_win(WINDOW* new_win) {
    my_sokoban_window = new_win;
}

void Sokoban::open() {
    my_sokoban_window = newwin(sizey, sizex, 0, 0);
    box(my_sokoban_window, 0, 0);
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
    std::string esc_msg = "Esc) Exit";

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

int Sokoban::sokoban_action_handler(MainMenu & main_menu, Savefile & my_save, int ch) {
    // TODO bug where anything other than ESC causes softlock
    // sokoban menu
    bool is_running = true;
    while (is_running) {
        if (ch == 27) {
            is_running = false;
            close();

            main_menu.open_menu();
            std::string file_title = main_menu.get_filetitle();
            main_menu.render_menu(file_title, my_save);
            wrefresh(main_menu.get_my_win());

            return 1;
        } else if (ch >= int('a') && ch <= int('h')) {
            // open sokoban levels
            (void) ch;
        }
    }

    return 0;
}