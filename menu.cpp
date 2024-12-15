#include <algorithm>
#include <ncurses/ncurses.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "gamemap.h"
#include "menu.h"
#include "utilities.h"

Menu::Menu(
    WINDOW *_my_menu_win,
    int _sizey, 
    int _sizex, 
    int _locy, 
    int _locx, 
    const std::string & _menu_name, 
    const std::vector<std::string> & _options_list, 
    int _close_button = 27
    ) 
{
    my_win = _my_menu_win;
    sizey = _sizey;
    sizex = _sizex;
    locy = _locy;
    locx = _locx;
    menu_name = _menu_name;
    options_list = _options_list;
    close_button = _close_button;
};

// constructor with no parameters, this is required for compilation 
Menu::Menu() {}; 

void Menu::open_menu() {
    my_win = newwin(sizey, sizex, locy, locx);
    render_menu();
    wrefresh(my_win);
}

// This function should ALWAYS be overriden
void Menu::render_menu() {
    throw std::runtime_error("Menu::render_menu() must be overriden!");
}

void Menu::close_menu() {
    werase(my_win);
    wrefresh(my_win);
    delwin(my_win);
}

std::vector<int> Menu::get_location() {
    return std::vector<int> {locy, locx};
}

WINDOW *Menu::get_my_win() {
    return my_win;
}

std::vector<std::string> Menu::get_options_list() {
    return options_list; 
}

std::vector<int> Menu::get_size() {
    return std::vector<int> {sizey, sizex};
}

int Menu::create_popup(
    Menu & menu_name,
    WINDOW *my_popup_name,
    std::string my_popup_title,
    std::vector<std::string> my_options_list,
    std::vector<int> progress_buttons, 
    std::vector<int> exit_buttons
) {
    int my_row = 4 + my_options_list.size(); 
    if (my_options_list.size() == 0) {
        my_row--; 
    }
    int my_col = 0;
    for (int j = 0; j < (int)my_options_list.size(); ++j) {
        if ((int)my_options_list[j].length() + 3 > my_col) {my_col = (int)my_options_list[j].length();}
    }
    if ((int)my_popup_title.length() > my_col) {my_col = (int)my_popup_title.length();}
    my_col = my_col + 2;

    // TODO graphical bug when title name is max number of characters.  

    my_popup_name = newwin(my_row, my_col, menu_name.get_size()[0]/2 - my_row/2, menu_name.get_size()[1]/2 - my_col/2);
    wattron(my_popup_name, COLOR_PAIR(2));
    box(my_popup_name, 0, 0);
    wattroff(my_popup_name, COLOR_PAIR(2));
    mvwaddstr(my_popup_name, 1, 1, my_popup_title.c_str());
    int option_count = 0;
    for (std::vector<std::string>::const_iterator it = my_options_list.begin(); it != my_options_list.end(); ++it) {
        mvwaddstr(my_popup_name, 3 + option_count, 1, num_to_alphabet(option_count).c_str());
        waddstr(my_popup_name, ") "); 
        waddstr(my_popup_name, it->c_str());
        ++option_count;
    }

    // render window
    wrefresh(my_popup_name);

    // loop window
    bool is_inner_loop_running = true;
    while (is_inner_loop_running) {
        int ch1 = getch();
        if (std::find(exit_buttons.begin(), exit_buttons.end(), ch1) != exit_buttons.end()) { 
            werase(my_popup_name);
            wrefresh(my_popup_name);
            delwin(my_popup_name);
            touchwin(menu_name.get_my_win());
            refresh();
            wrefresh(menu_name.get_my_win());
            is_inner_loop_running = false;
            return -1; 
        } else if (std::find(progress_buttons.begin(), progress_buttons.end(), ch1) != progress_buttons.end()) {
            return ch1;  
        }
    }
    return -1;
}

int Menu::create_popup_long(
    Menu & menu_name,
    WINDOW *my_popup_name,
    std::vector<std::string> my_rows,
    std::vector<int> progress_buttons, 
    std::vector<int> exit_buttons
) {
    int my_row = my_rows.size() + 2; 
    int my_col = 0;
    for (int j = 0; j < (int)my_rows.size(); ++j) {
        if ((int)my_rows[j].length() > my_col) {my_col = (int)my_rows[j].length();}
    }
    my_col = my_col + 2;

    my_popup_name = newwin(my_row, my_col, menu_name.get_size()[0]/2 - my_row/2, menu_name.get_size()[1]/2 - my_col/2);
    wattron(my_popup_name, COLOR_PAIR(2));
    box(my_popup_name, 0, 0);
    wattroff(my_popup_name, COLOR_PAIR(2));
    int option_count = 0;
    for (std::vector<std::string>::const_iterator it = my_rows.begin(); it != my_rows.end(); ++it) {
        mvwaddstr(my_popup_name, option_count+1, 1, it->c_str());
        ++option_count;
    }

    // render window
    wrefresh(my_popup_name);

    if (exit_buttons.empty() && progress_buttons.empty()) {
        // any button will close 
        int ch1 = getch();
        (void) ch1; 
        werase(my_popup_name);
        wrefresh(my_popup_name);
        delwin(my_popup_name);
        touchwin(menu_name.get_my_win());
        refresh();
        wrefresh(menu_name.get_my_win());
        return -1; 
    } else {
        // loop window
        int ch1 = getch(); 
        bool is_inner_loop_running = true;
        while (is_inner_loop_running) {
            
            if (std::find(exit_buttons.begin(), exit_buttons.end(), ch1) != exit_buttons.end()) { 
                werase(my_popup_name);
                wrefresh(my_popup_name);
                delwin(my_popup_name);
                touchwin(menu_name.get_my_win());
                refresh();
                wrefresh(menu_name.get_my_win());
                is_inner_loop_running = false;
                return -1; 
            } else if (std::find(progress_buttons.begin(), progress_buttons.end(), ch1) != progress_buttons.end()) {
                return ch1;  
            }
        }
    }

    return -1;
}

std::string Menu::create_text_prompt(
    Menu & menu_name,
    WINDOW *my_text_prompt_name,
    std::string my_text_prompt_title,
    std::vector<int> progress_buttons, 
    std::vector<int> exit_buttons
) {
    // create popup
    int my_row = 4; 
    int my_col = 2 + (int)my_text_prompt_title.length();
    my_text_prompt_name = newwin(my_row, my_col, menu_name.get_size()[0]/2 - my_row/2, menu_name.get_size()[1]/2 - my_col/2);
    wattron(my_text_prompt_name, COLOR_PAIR(2));
    box(my_text_prompt_name, 0, 0);
    wattroff(my_text_prompt_name, COLOR_PAIR(2));
    mvwaddstr(my_text_prompt_name, 1, 1, my_text_prompt_title.c_str());

    // render
    wrefresh(my_text_prompt_name);

    // loop
    bool is_text_prompt_running = true;
    int xpos = 1;
    std::string return_string = ""; 
    while (is_text_prompt_running) {
        int ch = getch();
        if (std::find(exit_buttons.begin(), exit_buttons.end(), ch) != exit_buttons.end()) { 
            werase(my_text_prompt_name);
            wrefresh(my_text_prompt_name);
            delwin(my_text_prompt_name);
            touchwin(menu_name.get_my_win());
            refresh();
            wrefresh(menu_name.get_my_win());
            is_text_prompt_running = false;
            return "";
        } else if (std::find(progress_buttons.begin(), progress_buttons.end(), ch) != progress_buttons.end()) {
            werase(my_text_prompt_name);
            wrefresh(my_text_prompt_name);
            delwin(my_text_prompt_name);
            touchwin(menu_name.get_my_win());
            refresh();
            wrefresh(menu_name.get_my_win());
            is_text_prompt_running = false;
            return return_string;
        } else if ((ch >= int('a') && ch <= int('z')) || (ch >= int('A') && ch <= int('Z')) || (ch >= int('0') && ch <= int('9')) || (ch == 32) || (std::find(legal_special_characters.begin(), legal_special_characters.end(), ch) != legal_special_characters.end())) {
            if (xpos+1 <= (int)my_text_prompt_title.length()+1) {
                mvwaddch(my_text_prompt_name, 2, xpos, keycode_to_char(ch));
                return_string = return_string + keycode_to_char(ch); 
                wrefresh(my_text_prompt_name);
                ++xpos;
            } 
        } else if (ch == 8) {
            if (xpos-1 >= 1) {
                mvwaddch(my_text_prompt_name, 2, xpos-1, ' ');
                wrefresh(my_text_prompt_name);
                return_string = return_string.substr(0, return_string.size() - 1); 
                --xpos;
            }
        }
    }
    return "";
}