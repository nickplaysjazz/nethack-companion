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

void MainMenu::set_my_main_menu_notes_box(WINDOW *win) {
    my_main_menu_notes_box = win;
}

void MainMenu::set_my_main_menu_price_ID_box(WINDOW *win) {
    my_main_menu_price_ID_box = win;
}

WINDOW *MainMenu::get_my_main_menu_intrinsics_box() {
    return my_main_menu_intrinsics_box;
}

WINDOW *MainMenu::get_my_main_menu_title_box() {
    return my_main_menu_title_box;
}

WINDOW *MainMenu::get_my_main_menu_notes_box() {
    return my_main_menu_notes_box;
}

WINDOW *MainMenu::get_my_main_menu_price_ID_box() {
    return my_main_menu_price_ID_box;
}

std::string MainMenu::get_filetitle() {
    return my_filename;
}

void MainMenu::render_menu() {
    // necessary but this version is not used
    return;
}

void MainMenu::render_menu(std::string & file_title, Savefile & my_save) {
    menu_name = file_title;
    my_filename = file_title;
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
    mvwaddch(my_main_menu_intrinsics_box, 0, 0, ACS_LTEE);
    mvwaddch(my_main_menu_intrinsics_box, 0, 29, ACS_TTEE);
    mvwaddch(my_main_menu_intrinsics_box, 22, 0, ACS_LTEE);
    mvwaddch(my_main_menu_intrinsics_box, 22, 29, ACS_BTEE);
    std::string intrinsics_title = "INTRINSICS i)";
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
    mvwaddch(my_main_menu_notes_box, 0, 0, ACS_TTEE);
    mvwaddch(my_main_menu_notes_box, 0, 29, ACS_RTEE);
    mvwaddch(my_main_menu_notes_box, 22, 0, ACS_BTEE);
    mvwaddch(my_main_menu_notes_box, 22, 29, ACS_RTEE);
    std::string notes_title = "NOTES n)";
    wattron(my_main_menu_notes_box, COLOR_PAIR(5));
    mvwaddstr(my_main_menu_notes_box, 1, 15 - notes_title.length()/2, notes_title.c_str());
    wattroff(my_main_menu_notes_box, COLOR_PAIR(5));

    std::vector<char> notes_text = my_save.get_notes(); 
    int i = 0;
    for (int x = 1; x <= 28; ++x) {
        for (int y = 2; y <= 21; ++y) {
            mvwaddch(my_main_menu_notes_box, y, x, notes_text[i]); 
            ++i;
        }
    }

    // price ID
    my_main_menu_price_ID_box = subwin(my_win, 23, 52, 2, 29);
    box(my_main_menu_price_ID_box, 0, 0); 
    mvwaddch(my_main_menu_price_ID_box, 0, 0, ACS_TTEE);
    mvwaddch(my_main_menu_price_ID_box, 0, 51, ACS_TTEE);
    mvwaddch(my_main_menu_price_ID_box, 23, 0, ACS_BTEE);
    mvwaddch(my_main_menu_price_ID_box, 22, 51, ACS_BTEE);
    std::string price_ID_title = "PRICE ID p)";
    wattron(my_main_menu_price_ID_box, COLOR_PAIR(6));
    mvwaddstr(my_main_menu_price_ID_box, 1, 25 - price_ID_title.length()/2, price_ID_title.c_str());
    wattroff(my_main_menu_price_ID_box, COLOR_PAIR(6));

    std::string price_ID_cha = "             Ch: ";
    mvwaddstr(my_main_menu_price_ID_box, 3, 2, price_ID_cha.c_str());

    std::string charisma_ch = std::to_string(my_save.get_charisma());
    if (charisma_ch.size() != 2) {
        charisma_ch = " " + charisma_ch;
    }
    mvwaddstr(get_my_main_menu_price_ID_box(), 3, 19, charisma_ch.c_str());
    wrefresh(get_my_main_menu_price_ID_box());
    std::string price_ID_being_duped = "    Being duped? ";
    mvwaddstr(my_main_menu_price_ID_box, 4, 2, price_ID_being_duped.c_str());
    std::string price_ID_headings = "  SELL PRICES       BUY PRICES       ITEM LIST";
    mvwaddstr(my_main_menu_price_ID_box, 5, 2, price_ID_headings.c_str());
    std::string delimiters = "                                              ";
    for (int ys = 5; ys <= 21; ++ys) {
        mvwaddch(my_main_menu_price_ID_box, ys, 18, ACS_VLINE);
        mvwaddch(my_main_menu_price_ID_box, ys, 35, ACS_VLINE);
    }

    for (int ys = 6; ys <= 21; ++ys) {
        mvwaddstr(my_main_menu_price_ID_box, ys, 42, "...");
    }

    if (my_save.get_is_being_duped() == true) {
        std::string print_yes = "YES";
        mvwaddstr(get_my_main_menu_price_ID_box(), 4, 19, print_yes.c_str());
    } else {
        std::string print_no = "NO ";
        mvwaddstr(get_my_main_menu_price_ID_box(), 4, 19, print_no.c_str());       
    }

    render_prices(my_save);

    // sokoban, could make this a subwin
    std::string sokoban_str = "s) SOKOBAN PRACTICE";
    wattron(my_win, COLOR_PAIR(7));
    mvwaddstr(my_win, 26, 1, sokoban_str.c_str());
    wattroff(my_win, COLOR_PAIR(7));
}

void MainMenu::render_intrinsics_menu_default(Savefile & my_save) {
    // render properties menu
    std::string intrinsics_title = "INTRINSICS i)";

    wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
    wattron(my_main_menu_intrinsics_box, A_STANDOUT);
    mvwaddstr(my_main_menu_intrinsics_box, 1, 15 - intrinsics_title.length()/2, intrinsics_title.c_str());
    wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));
    wattroff(my_main_menu_intrinsics_box, A_STANDOUT);

    int num_options = (int)properties_list.size();
    std::vector<int> properties_buttons;
    for (int i = 0; i < num_options; ++i) {
        properties_buttons.push_back(int('a') + i); 
    }

    int option_count = 0;
    for (std::vector<std::string>::const_iterator it = properties_list.begin(); it != properties_list.end(); ++it) {
        if (my_save.get_intrinsics()[option_count] == 1) {
            wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
        }
        mvwaddstr(my_main_menu_intrinsics_box, 3+option_count, 1, num_to_alphabet(option_count).c_str());
        waddstr(my_main_menu_intrinsics_box, ") "); 
        waddstr(my_main_menu_intrinsics_box, it->c_str());
        if (my_save.get_intrinsics()[option_count] == 1) {
            wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));
            wattroff(my_main_menu_intrinsics_box, A_STANDOUT);
        }
        ++option_count;
    }

    wrefresh(my_main_menu_intrinsics_box);
}

void MainMenu::render_intrinsics_menu_on(Savefile & my_save) {
    // highlight those already selected
    for (int i = 0; i < (int)properties_list.size(); ++i) {
        if (my_save.get_intrinsics()[i] == 1) {
            wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
            wattron(my_main_menu_intrinsics_box, A_STANDOUT);
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 1, num_to_alphabet(i).c_str());
            waddstr(my_main_menu_intrinsics_box, ") "); 
            waddstr(my_main_menu_intrinsics_box, properties_list[i].c_str());
            wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));
            wattroff(my_main_menu_intrinsics_box, A_STANDOUT);
        } else {
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 1, num_to_alphabet(i).c_str());
            waddstr(my_main_menu_intrinsics_box, ") "); 
            waddstr(my_main_menu_intrinsics_box, properties_list[i].c_str());
        }
    }
    wrefresh(my_main_menu_intrinsics_box);
}

void MainMenu::render_intrinsics_menu_off(Savefile & my_save) {
    std::string intrinsics_title = "INTRINSICS i)";

    wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
    mvwaddstr(my_main_menu_intrinsics_box, 1, 15 - intrinsics_title.length()/2, intrinsics_title.c_str());
    wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));

    int option_count = 0;
    for (int i = 0; i < (int)properties_list.size(); ++i) {
        if (my_save.get_intrinsics()[i] == 1) {
            wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
        }
        mvwaddstr(my_main_menu_intrinsics_box, 3+option_count, 1, "   ");
        waddstr(my_main_menu_intrinsics_box, properties_list[i].c_str());
        if (my_save.get_intrinsics()[i] == 1) {
            wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));
        }
        ++option_count;
    }

    wrefresh(my_main_menu_intrinsics_box);
}

void MainMenu::render_notes_menu_on(Savefile & my_save) {
    std::string notes_title = "NOTES n)";
    wattron(my_main_menu_notes_box, COLOR_PAIR(5));
    wattron(my_main_menu_notes_box, A_STANDOUT);
    mvwaddstr(my_main_menu_notes_box, 1, 15 - notes_title.length()/2, notes_title.c_str());
    wattroff(my_main_menu_notes_box, COLOR_PAIR(5));
    wattroff(my_main_menu_notes_box, A_STANDOUT);

    std::vector<char> notes_text = my_save.get_notes(); 
    int i = 0;
    for (int x = 1; x <= 28; ++x) {
        for (int y = 2; y <= 21; ++y) {
            mvwaddch(my_main_menu_notes_box, y, x, notes_text[i]); 
            ++i;
        }
    }        
    wmove(my_main_menu_notes_box, 2, 1); 

    wrefresh(my_main_menu_notes_box);
}

void MainMenu::render_notes_menu_off(Savefile & my_save) {
    std::string notes_title = "NOTES n)";
    wattron(my_main_menu_notes_box, COLOR_PAIR(5));
    mvwaddstr(my_main_menu_notes_box, 1, 15 - notes_title.length()/2, notes_title.c_str());
    wattroff(my_main_menu_notes_box, COLOR_PAIR(5));

    wrefresh(my_main_menu_notes_box);
}

void MainMenu::render_price_ID_menu_on(Savefile & my_save) {
    std::string price_ID_title = "PRICE ID p)";
    wattron(my_main_menu_price_ID_box, COLOR_PAIR(6));
    wattron(my_main_menu_price_ID_box, A_STANDOUT);
    mvwaddstr(my_main_menu_price_ID_box, 1, 25 - price_ID_title.length()/2, price_ID_title.c_str());
    wattroff(my_main_menu_price_ID_box, A_STANDOUT);
    wattroff(my_main_menu_price_ID_box, COLOR_PAIR(6));

    std::string cha_instr = "(use arrow keys)";
    mvwaddstr(my_main_menu_price_ID_box, 3, 25, cha_instr.c_str());
    std::string dupe_instr = "(use enter key)";
    mvwaddstr(my_main_menu_price_ID_box, 4, 25, dupe_instr.c_str());
    
    for (int ys = 6; ys <= 21; ++ys) {
            mvwaddstr(my_main_menu_price_ID_box, ys, 42, num_to_alphabet(ys - 6).c_str());
            waddstr(my_main_menu_price_ID_box, ") "); 
    }

    // will render in render_prices
    render_prices(my_save); 
}

void MainMenu::render_price_ID_menu_off(Savefile & my_save) {
    std::string price_ID_title = "PRICE ID p)";
    wattron(my_main_menu_price_ID_box, COLOR_PAIR(6));
    mvwaddstr(my_main_menu_price_ID_box, 1, 25 - price_ID_title.length()/2, price_ID_title.c_str());
    wattroff(my_main_menu_price_ID_box, COLOR_PAIR(6));

    std::string cha_instr = "                ";
    mvwaddstr(my_main_menu_price_ID_box, 3, 25, cha_instr.c_str());
    std::string dupe_instr = "               ";
    mvwaddstr(my_main_menu_price_ID_box, 4, 25, dupe_instr.c_str());

    for (int ys = 6; ys <= 21; ++ys) {
        mvwaddstr(my_main_menu_price_ID_box, ys, 42, "...");
    }
    wrefresh(my_main_menu_price_ID_box);
}

void MainMenu::render_prices(Savefile & my_save) {
    // clear old prices
    std::string clear = "          ";
    for (int ys = 0; ys < (int)item_base_prices.size(); ++ys) {
        mvwaddstr(my_main_menu_price_ID_box, 6+ys, 4, clear.c_str());
        mvwaddstr(my_main_menu_price_ID_box, 6+ys, 21, clear.c_str());
    }

    int charisma = my_save.get_charisma();
    float price_mod;
    if (charisma <= 5) {
        price_mod = 2.;
    } else if (charisma <= 7) {
        price_mod = 1.5;
    } else if (charisma <= 10) {
        price_mod = 1. + (1./3.);
    } else if (charisma <= 15) {
        price_mod = 1.;
    } else if (charisma <= 17) {
        price_mod = 3./4.;
    } else if (charisma == 18) {
        price_mod = 2./3.;
    } else {
        price_mod = 1./2.;
    }

    for (int ys = 0; ys < (int)item_base_prices.size(); ++ys) {
        float this_price = ((my_save.get_is_being_duped() * (1./3.)) + (1 - my_save.get_is_being_duped()) * (1./2.)) * item_base_prices[ys];
        mvwaddstr(my_main_menu_price_ID_box, 6+ys, 7 - std::to_string((int)(this_price*(3./4.) + 0.5)).length()/2, std::to_string((int)(this_price*(3./4.) + 0.5)).c_str());
        waddch(my_main_menu_price_ID_box, ',');
        waddstr(my_main_menu_price_ID_box, std::to_string((int)(this_price)).c_str());
    }

    for (int ys = 0; ys < (int)item_base_prices.size(); ++ys) {
        float this_price = price_mod * item_base_prices[ys];
        this_price = (my_save.get_is_being_duped())*(4./3.)*this_price + (1 - my_save.get_is_being_duped())*this_price ;
        int price = (int)this_price;
        mvwaddstr(my_main_menu_price_ID_box, 6+ys, 24 - std::to_string(price).length()/2, std::to_string(price).c_str());
        waddch(my_main_menu_price_ID_box, ',');
        waddstr(my_main_menu_price_ID_box, std::to_string((int)(this_price*(4./3.))).c_str());
    }

    wrefresh(my_main_menu_price_ID_box);
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
