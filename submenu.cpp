#include <ncurses/ncurses.h>
#include <iostream>

#include "menu.h"
#include "savefile.h"
#include "submenu.h"
#include "utilities.h"

MainMenu::MainMenu(
    WINDOW *_my_main_menu_win,
    int _sizey, 
    int _sizex, 
    int _locy, 
    int _locx, 
    const std::string & _menu_name, 
    const std::vector<std::string> & _options_list, 
    int _close_button
) {
    my_win = _my_main_menu_win;
    sizey = _sizey;
    sizex = _sizex;
    locy = _locy;
    locx = _locx;
    menu_name = _menu_name;
    options_list = _options_list;
    close_button = _close_button;
};

    void MainMenu::set_my_main_menu_intrinsics_box(WINDOW *win) {
        my_main_menu_intrinsics_box = win;
    }

    void MainMenu::set_my_main_menu_title_box(WINDOW *win) {
        my_main_menu_title_box = win;
    }

    WINDOW *MainMenu::get_my_main_menu_intrinsics_box() {
        return my_main_menu_intrinsics_box;
    }
    
    WINDOW *MainMenu::get_my_main_menu_title_box() {
        return my_main_menu_title_box;
    }

void MainMenu::render_menu() {
    // necessary but this version is not used
    return;
}

void MainMenu::render_menu(std::string & file_title, Savefile & my_save) {
    menu_name = file_title;
    int my_row = sizey;
    (void) my_row;
    int my_col = sizex;
    box(my_win, 0, 0);

    // title
    my_main_menu_title_box = subwin(my_win, 3, my_col, 0, 0);
    box(my_main_menu_title_box, 0, 0);
    wattron(my_main_menu_title_box, COLOR_PAIR(3));
    mvwaddstr(my_main_menu_title_box, 1, my_col/2 - file_title.length()/2, file_title.c_str());
    wattroff(my_main_menu_title_box, COLOR_PAIR(3));
    
    // intrinsics
    my_main_menu_intrinsics_box = subwin(my_win, 23, 30, 2, 0);
    box(my_main_menu_intrinsics_box, 0, 0);
    std::string intrinsics_title = "PROPERTIES p)";
    wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
    mvwaddstr(my_main_menu_intrinsics_box, 1, 15 - intrinsics_title.length()/2, intrinsics_title.c_str());
    wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));

    for (int i = 0; i < (int)properties_list.size(); ++i) {
        if (my_save.get_intrinsics()[i] == 1) {
            wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
        }
        mvwaddstr(my_main_menu_intrinsics_box, 3+i, 4, properties_list[i].c_str());
        if (my_save.get_intrinsics()[i] == 1) {
            wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));
        }
    } 

    // notes
    my_main_menu_notes_box = subwin(my_win, 23, 30, 2, 80);
    box(my_main_menu_notes_box, 0, 0);
    std::string notes_title = "NOTES n)";
    wattron(my_main_menu_notes_box, COLOR_PAIR(5));
    mvwaddstr(my_main_menu_notes_box, 1, 15 - notes_title.length()/2, notes_title.c_str());
    wattroff(my_main_menu_notes_box, COLOR_PAIR(5));
}

void MainMenu::render_intrinsics_menu_default(Savefile & my_save) {
    // render properties menu
    std::string intrinsics_title = "PROPERTIES p)";
    WINDOW *intrinsics_box = get_my_main_menu_intrinsics_box();

    wattron(intrinsics_box, COLOR_PAIR(4));
    wattron(intrinsics_box, A_STANDOUT);
    mvwaddstr(intrinsics_box, 1, 15 - intrinsics_title.length()/2, intrinsics_title.c_str());
    wattroff(intrinsics_box, COLOR_PAIR(4));
    wattroff(intrinsics_box, A_STANDOUT);

    int num_options = (int)properties_list.size();
    std::vector<int> properties_buttons;
    for (int i = 0; i < num_options; ++i) {
        properties_buttons.push_back(int('a') + i); 
    }

    int option_count = 0;
    for (std::vector<std::string>::const_iterator it = properties_list.begin(); it != properties_list.end(); ++it) {
        if (my_save.get_intrinsics()[option_count] == 1) {
            wattron(intrinsics_box, COLOR_PAIR(4));
        }
        mvwaddstr(intrinsics_box, 3+option_count, 1, num_to_alphabet(option_count).c_str());
        waddstr(intrinsics_box, ") "); 
        waddstr(intrinsics_box, it->c_str());
        if (my_save.get_intrinsics()[option_count] == 1) {
            wattroff(intrinsics_box, COLOR_PAIR(4));
            wattroff(intrinsics_box, A_STANDOUT);
        }
        ++option_count;
    }

    wrefresh(intrinsics_box);
}

void MainMenu::render_intrinsics_menu_on(Savefile & my_save) {
    WINDOW * intrinsics_box = get_my_main_menu_intrinsics_box();
    // highlight those already selected
    for (int i = 0; i < (int)properties_list.size(); ++i) {
        if (my_save.get_intrinsics()[i] == 1) {
            wattron(intrinsics_box, COLOR_PAIR(4));
            wattron(intrinsics_box, A_STANDOUT);
            mvwaddstr(intrinsics_box, 3+i, 1, num_to_alphabet(i).c_str());
            waddstr(intrinsics_box, ") "); 
            waddstr(intrinsics_box, properties_list[i].c_str());
            wattroff(intrinsics_box, COLOR_PAIR(4));
            wattroff(intrinsics_box, A_STANDOUT);
        } else {
            mvwaddstr(intrinsics_box, 3+i, 1, num_to_alphabet(i).c_str());
            waddstr(intrinsics_box, ") "); 
            waddstr(intrinsics_box, properties_list[i].c_str());
        }
    }
    wrefresh(intrinsics_box);
}

void MainMenu::render_intrinsics_menu_off(Savefile & my_save) {
    WINDOW *intrinsics_box = get_my_main_menu_intrinsics_box();
    std::string intrinsics_title = "PROPERTIES p)";

    wattron(intrinsics_box, COLOR_PAIR(4));
    mvwaddstr(intrinsics_box, 1, 15 - intrinsics_title.length()/2, intrinsics_title.c_str());
    wattroff(intrinsics_box, COLOR_PAIR(4));

    int option_count = 0;
    for (int i = 0; i < (int)properties_list.size(); ++i) {
        if (my_save.get_intrinsics()[i] == 1) {
            wattron(intrinsics_box, COLOR_PAIR(4));
        }
        mvwaddstr(intrinsics_box, 3+option_count, 1, "   ");
        waddstr(intrinsics_box, properties_list[i].c_str());
        if (my_save.get_intrinsics()[i] == 1) {
            wattroff(intrinsics_box, COLOR_PAIR(4));
        }
        ++option_count;
    }

    wrefresh(intrinsics_box);
}

ProfileMenu::ProfileMenu(
    WINDOW *_my_profile_menu_win,
    int _sizey, 
    int _sizex, 
    int _locy, 
    int _locx, 
    const std::string & _menu_name, 
    const std::vector<std::string> & _options_list, 
    int _close_button = 27
    ) 
{
    my_win = _my_profile_menu_win;
    sizey = _sizey;
    sizex = _sizex;
    locy = _locy;
    locx = _locx;
    menu_name = _menu_name;
    options_list = _options_list;
    close_button = _close_button;
};

void ProfileMenu::render_menu() { 
    int title_lines = count_newlines(menu_name) + 1;
    int my_row = sizey;
    int my_col = sizex; 
    box(my_win, 0, 0);
    std::string title_to_print = menu_name; 
    for (int i = 0; i < title_lines; ++i) {
        std::string line = title_to_print.substr(0, title_to_print.find("\n"));
        title_to_print.erase(0, title_to_print.find("\n") + ((std::string)"\n").length());
        mvwaddstr(my_win, (int)(my_row/2 -2 - title_lines + i), (int)((my_col - line.length())/2), line.c_str());
    }
    int option_count = 0;
    for (std::vector<std::string>::const_iterator it = options_list.begin(); it != options_list.end(); ++it) {
        mvwaddstr(my_win, (int)(my_row/2 + option_count), (int)(my_col/2 - 5), num_to_alphabet(option_count).c_str());
        waddstr(my_win, ") "); 
        waddstr(my_win, it->c_str());
        ++option_count;
    }
    mvwaddstr(my_win,(int)(my_row/2 + 1 + option_count), (int)(my_col/2 - 5), ((std::string)"Enter) Create New Character").c_str());
    mvwaddstr(my_win,(int)(my_row/2 + 2 + option_count), (int)(my_col/2 - 5), ((std::string)"Delete) Delete Character").c_str());
    mvwaddstr(my_win, (int)(my_row/2 + 4 + option_count), (int)(my_col/2 - 5), ((std::string)"Esc) Quit").c_str());
}

void ProfileMenu::set_options_list(std::vector<std::string> new_options_list) {
    options_list = new_options_list;
}
