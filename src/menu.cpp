#include <algorithm>
#include <iostream>         // TODO REMOVE

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#elif __linux__
#include <ncurses.h>
#elif __APPLE__
#include <ncurses.h>
#endif

#include <stdexcept>
#include <string>
#include <vector>

#include "../include/gamemap.h"
#include "../include/menu.h"
#include "../include/utilities.h"

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

    if (my_row < menu_name.get_size()[0]) {
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
    } else {
        // need to subdivide into multiple windows
        int rows_to_get_rid_of = my_row;
        int pos = 0;
        while (rows_to_get_rid_of > 0) {
            std::vector<std::string>::const_iterator first = my_rows.begin() + pos;
            std::vector<std::string>::const_iterator last = my_rows.begin() + pos + std::min(menu_name.get_size()[0] - 2, my_row-2-pos);
            std::vector<std::string> my_new_rows(first, last);

            int my_new_row = my_new_rows.size() + 2; 
            int my_col = 0;
            for (int j = 0; j < (int)my_new_rows.size(); ++j) {
                if ((int)my_new_rows[j].length() > my_col) {my_col = (int)my_new_rows[j].length();}
            }
            my_col = my_col + 2;

            my_popup_name = newwin(my_new_row, my_col, menu_name.get_size()[0]/2 - my_new_row/2, menu_name.get_size()[1]/2 - my_col/2);
            wattron(my_popup_name, COLOR_PAIR(2));
            box(my_popup_name, 0, 0);
            wattroff(my_popup_name, COLOR_PAIR(2));

            int option_count = 0;
            for (std::vector<std::string>::const_iterator it = my_new_rows.begin(); it != my_new_rows.end(); ++it) {
                mvwaddstr(my_popup_name, option_count+1, 1, it->c_str());
                ++option_count;
            }

            // render window
            wrefresh(my_popup_name);

            if ((rows_to_get_rid_of > menu_name.get_size()[0]) || (exit_buttons.empty() && progress_buttons.empty())) {
                // need to continue, or close window entirely
                // any button will close 
                int ch1 = getch();
                (void) ch1; 
                werase(my_popup_name);
                wrefresh(my_popup_name);
                delwin(my_popup_name);
                touchwin(menu_name.get_my_win());
                refresh();
                wrefresh(menu_name.get_my_win());
                if (rows_to_get_rid_of < menu_name.get_size()[0]) {
                    return -1; 
                }
                rows_to_get_rid_of = rows_to_get_rid_of - my_new_row; 
                pos = pos + my_new_row; 
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
        }
    }
    return -1;
}

void Menu::create_table_filter(
    Menu & menu_name,
    WINDOW *my_popup_name,
    std::string my_table_title,
    std::vector<std::vector<std::string>> my_rows,
    std::vector<int> exit_buttons
) {
    // create popup
    int my_row = 4; 
    int my_col = 110;
    my_popup_name = newwin(my_row, my_col, menu_name.get_size()[0]/2 - my_row/2, menu_name.get_size()[1]/2 - my_col/2);
    //wbkgdset(my_popup_name, ' ');

    // loop
    bool is_text_prompt_running = true;
    int xpos = 1;
    std::string input_text = "";
    while (is_text_prompt_running) {
        // make sure that main screen will be redrawn
        touchwin(menu_name.get_my_win());
        touchwin(my_popup_name);
        
        // render as many as possible
        if (input_text != "") {
            // get filter text
            std::vector<std::string> words;
            std::size_t start = 0;
            std::size_t end;
            while ((end = input_text.find(' ', start)) != std::string::npos) {
                std::string return_str = input_text.substr(start, end-start);
                make_str_lowercase(return_str);
                if (return_str != "") {
                    words.push_back(return_str);
                }
                start = end + 1;
            }
            std::string return_str = input_text.substr(start, end-start);
            make_str_lowercase(return_str);
            if (return_str != "") {
                words.push_back(return_str);
            }

            std::string words_str = "";
            for (int i = 0; i < (int)words.size(); ++i) {
                words_str = words_str + words[i];
            }

            // get possible items to display
            std::vector<std::vector<std::string>> display_list;
            for (int i = 0; i < (int)my_rows.size(); ++i) {
                std::string row_str = "";
                for (int j = 0; j < (int)my_rows[i].size(); ++j) {
                    row_str = row_str + my_rows[i][j];
                }
                make_str_lowercase(row_str);

                std::size_t index = row_str.find(words_str);

                if (index != std::string::npos) {
                    display_list.push_back(my_rows[i]);
                }         
            }

            // display possible items
            int num_rows = std::min((int)display_list.size(), 13);
            wresize(my_popup_name, num_rows+5, my_col);
            wattron(my_popup_name, COLOR_PAIR(2));
            box(my_popup_name,0,0);
            wattroff(my_popup_name, COLOR_PAIR(2));
            mvwhline(my_popup_name, 3, 1, 0, my_col-2);
            mvwaddstr(my_popup_name, 1, 1, my_table_title.c_str());
            for (int i = 0; i < num_rows; ++i) {
                wmove(my_popup_name, i+4, 1);
                for (int j = 0; j < (int)display_list[i].size(); ++j) {
                    if (display_list[i][j] == "") {
                        continue;
                    }
                    std::string print_str = display_list[i][j] + " ";
                    if (j == (int)display_list[i].size() - 2) {
                        wattron(my_popup_name, COLOR_PAIR(5));
                    } else if (j == (int)display_list[i].size() - 1) {
                        wattron(my_popup_name, COLOR_PAIR(6));
                    }
                    waddstr(my_popup_name, print_str.c_str());
                    if (j == (int)display_list[i].size() - 2) {
                        wattroff(my_popup_name, COLOR_PAIR(5));
                    } else if (j == (int)display_list[i].size() - 1) {
                        wattroff(my_popup_name, COLOR_PAIR(6));
                    }
                }            
            }
        } else if (input_text == "") {
            int num_rows = 4;
            wresize(my_popup_name, num_rows, my_col);
            wattron(my_popup_name, COLOR_PAIR(2));
            box(my_popup_name,0,0);
            wattroff(my_popup_name, COLOR_PAIR(2));
            mvwaddstr(my_popup_name, 1, 1, my_table_title.c_str());
        }

        // instead of calling wrefresh twice, can prevent a double window update via the following
        wnoutrefresh(menu_name.get_my_win());
        wnoutrefresh(my_popup_name);
        doupdate();

        int ch = getch();
        werase(my_popup_name);
        if (std::find(exit_buttons.begin(), exit_buttons.end(), ch) != exit_buttons.end()) { 
            werase(my_popup_name);
            wrefresh(my_popup_name);
            delwin(my_popup_name);
            touchwin(menu_name.get_my_win());
            refresh();
            wrefresh(menu_name.get_my_win());
            is_text_prompt_running = false;
            return;
        } else if ((ch >= int('a') && ch <= int('z')) || (ch >= int('A') && ch <= int('Z')) || (ch >= int('0') && ch <= int('9')) || (ch == 32) || (std::find(legal_special_characters.begin(), legal_special_characters.end(), ch) != legal_special_characters.end())) {
            if (xpos+1 <= 25) {
                input_text = input_text + keycode_to_char(ch); 
                mvwaddstr(my_popup_name, 2, 1, input_text.c_str());
                ++xpos;
            } 
        } else if (ch == 8 || ch == KEY_BACKSPACE || ch == 127 || ch == int('\b')) {
            if (xpos-1 >= 1) {
                input_text = input_text.substr(0, input_text.size() - 1); 
                mvwaddstr(my_popup_name, 2, 1, input_text.c_str());
                --xpos;
            }
        }
    }
    return;
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
        } else if (ch == 8 || ch == KEY_BACKSPACE || ch == 127 || ch == int('\b')) {
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