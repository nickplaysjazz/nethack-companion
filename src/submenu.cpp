#ifdef _WIN32
#include <ncurses/ncurses.h>
#elif __linux__
#include <ncurses.h>
#elif __APPLE__
#include <ncurses.h>
#endif

#include <iostream>

#include "../include/menu.h"
#include "../include/savefile.h"
#include "../include/submenu.h"
#include "../include/utilities.h"

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

std::vector<int> MainMenu::get_main_menu_size() {
    return {sizey, sizex};
}

void MainMenu::render_menu() {
    // necessary but this version is not used
    return;
}

void MainMenu::render_menu(std::string file_title, Savefile & my_save) {
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
    my_main_menu_intrinsics_box = subwin(my_win, 30, 30, 2, 0);
    box(my_main_menu_intrinsics_box, 0, 0);
    mvwaddch(my_main_menu_intrinsics_box, 0, 0, ACS_LTEE);
    mvwaddch(my_main_menu_intrinsics_box, 0, 29, ACS_TTEE);
    mvwaddch(my_main_menu_intrinsics_box, 29, 0, ACS_LLCORNER);
    mvwaddch(my_main_menu_intrinsics_box, 29, 29, ACS_BTEE);
    std::string intrinsics_title = "INTRINSICS i)";
    wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
    mvwaddstr(my_main_menu_intrinsics_box, 1, 15 - intrinsics_title.length()/2, intrinsics_title.c_str());
    wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));

    for (int i = 0; i < (int)properties_list.size(); ++i) {
        if (my_save.get_intrinsics()[i] >= 1) {
            wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
        }
        mvwaddstr(my_main_menu_intrinsics_box, 3+i, 5, properties_list[i].c_str());
        if (i == 7) {
            // magic cancellation
            std::string mc_num = " " + std::to_string(my_save.get_intrinsics()[i]);
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 23, mc_num.c_str());
        } else if (i == 18) {
            // speed
            std::string speed_num = " " + std::to_string(my_save.get_intrinsics()[i]);
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 10, speed_num.c_str());
        } else if (i == 11) {
            // protection
            std::string prot_num = " " + std::to_string(my_save.get_intrinsics()[i]);
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 15, prot_num.c_str());
        }
        if (my_save.get_intrinsics()[i] >= 1) {
            wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));
        }
        waddstr(my_main_menu_intrinsics_box, ((std::string)(" ")).c_str());
    } 

    // notes
    my_main_menu_notes_box = subwin(my_win, 30, 30, 2, 80);
    box(my_main_menu_notes_box, 0, 0);
    mvwaddch(my_main_menu_notes_box, 0, 0, ACS_TTEE);
    mvwaddch(my_main_menu_notes_box, 0, 29, ACS_RTEE);
    mvwaddch(my_main_menu_notes_box, 29, 0, ACS_BTEE);
    mvwaddch(my_main_menu_notes_box, 29, 29, ACS_LRCORNER);
    std::string notes_title = "NOTES n)";
    wattron(my_main_menu_notes_box, COLOR_PAIR(5));
    mvwaddstr(my_main_menu_notes_box, 1, 15 - notes_title.length()/2, notes_title.c_str());
    wattroff(my_main_menu_notes_box, COLOR_PAIR(5));

    std::vector<char> notes_text = my_save.get_notes(); 
    int i = 0;
    for (int x = 1; x <= 28; ++x) {
        for (int y = 2; y <= 28; ++y) {
            mvwaddch(my_main_menu_notes_box, y, x, notes_text[i]); 
            ++i;
        }
    }

    // price ID
    my_main_menu_price_ID_box = subwin(my_win, 23, 52, 2, 29);
    box(my_main_menu_price_ID_box, 0, 0); 
    mvwaddch(my_main_menu_price_ID_box, 0, 0, ACS_TTEE);
    mvwaddch(my_main_menu_price_ID_box, 0, 51, ACS_TTEE);
    mvwaddch(my_main_menu_price_ID_box, 22, 0, ACS_LTEE);
    mvwaddch(my_main_menu_price_ID_box, 22, 51, ACS_RTEE);
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

    // monster list
    std::string monster_str = "m) MONSTER EDIBILITY";
    wattron(my_win, COLOR_PAIR(3));
    mvwaddstr(my_win, 26, 31, monster_str.c_str());
    wattroff(my_win, COLOR_PAIR(3));

    // sokoban
    std::string sokoban_str = "s) SOKOBAN PRACTICE";
    wattron(my_win, COLOR_PAIR(3));
    mvwaddstr(my_win, 27, 31, sokoban_str.c_str());
    wattroff(my_win, COLOR_PAIR(3));

    // xp
    std::string xp_str = "x) XP TO LVL";
    wattron(my_win, COLOR_PAIR(3));
    mvwaddstr(my_win, 28, 31, xp_str.c_str());
    wattroff(my_win, COLOR_PAIR(3));

    // wand engrave
    std::string engrave_str = "z) WAND ENGRAVE ID";
    wattron(my_win, COLOR_PAIR(3));
    mvwaddstr(my_win, 29, 31, engrave_str.c_str());
    wattroff(my_win, COLOR_PAIR(3));

    // armor ID
    std::string armor_ID_str = "a) ARMOR ID";
    wattron(my_win, COLOR_PAIR(3));
    mvwaddstr(my_win, 26, 56, armor_ID_str.c_str());
    wattroff(my_win, COLOR_PAIR(3));

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
        if (my_save.get_intrinsics()[option_count] >= 1) {
            wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
        }
        mvwaddstr(my_main_menu_intrinsics_box, 3+option_count, 1, num_to_alphabet(option_count).c_str());
        waddstr(my_main_menu_intrinsics_box, ") "); 
        mvwaddstr(my_main_menu_intrinsics_box, 3+option_count, 5, it->c_str());
        if (option_count == 7) {
            // magic cancellation
            std::string mc_num = " " + std::to_string(my_save.get_intrinsics()[option_count]);
            mvwaddstr(my_main_menu_intrinsics_box, 3+option_count, 23, mc_num.c_str());
        } else if (option_count == 18) {
            //speed
            std::string speed_num = " " + std::to_string(my_save.get_intrinsics()[option_count]);
            mvwaddstr(my_main_menu_intrinsics_box, 3+option_count, 10, speed_num.c_str());
        } else if (option_count == 11) {
            // protection
            std::string prot_num = " " + std::to_string(my_save.get_intrinsics()[option_count]);
            mvwaddstr(my_main_menu_intrinsics_box, 3+option_count, 15, prot_num.c_str());
        }
        if (my_save.get_intrinsics()[option_count] >= 1) {
            wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));
            wattroff(my_main_menu_intrinsics_box, A_STANDOUT);
        }
        waddstr(my_main_menu_intrinsics_box, ((std::string)(" ")).c_str());
        ++option_count;
    }

    wrefresh(my_main_menu_intrinsics_box);
}

void MainMenu::render_intrinsics_menu_on(Savefile & my_save) {
    // highlight those already selected
    for (int i = 0; i < (int)properties_list.size(); ++i) {
        if (my_save.get_intrinsics()[i] >= 1) {
            wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
            wattron(my_main_menu_intrinsics_box, A_STANDOUT);
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 1, num_to_alphabet(i).c_str());
            waddstr(my_main_menu_intrinsics_box, ")  "); 
            if (i == 7) {
                // magic cancellation
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 1, ((std::string)("H/h)")).c_str());
                std::string mc_num = " " + std::to_string(my_save.get_intrinsics()[i]);
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 23, mc_num.c_str());
            } else if (i == 18) {
                // speed
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 1, ((std::string)("S/s)")).c_str());
                std::string speed_num = " " + std::to_string(my_save.get_intrinsics()[i]);
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 10, speed_num.c_str());
            } else if (i == 11) {
                // protection
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 1, ((std::string)("L/l)")).c_str());
                std::string prot_num = " " + std::to_string(my_save.get_intrinsics()[i]);
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 15, prot_num.c_str());
                wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));
                wattroff(my_main_menu_intrinsics_box, A_STANDOUT);
                waddstr(my_main_menu_intrinsics_box, ((std::string)" ").c_str());
                wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
                wattron(my_main_menu_intrinsics_box, A_STANDOUT);
            }
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 5, properties_list[i].c_str());
            wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));
            wattroff(my_main_menu_intrinsics_box, A_STANDOUT);
        } else {
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 1, num_to_alphabet(i).c_str());
            waddstr(my_main_menu_intrinsics_box, ")  "); 
            if (i == 7) {
                // magic cancellation
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 1, ((std::string)("H/h)")).c_str());
                std::string mc_num = " " + std::to_string(my_save.get_intrinsics()[i]);
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 23, mc_num.c_str());
            } else if (i == 18) {
                // speed
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 1, ((std::string)("S/s)")).c_str());
                std::string speed_num = " " + std::to_string(my_save.get_intrinsics()[i]);
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 10, speed_num.c_str());
            } else if (i == 11) {
                // protection
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 1, ((std::string)("L/l)")).c_str());
                std::string prot_num = " " + std::to_string(my_save.get_intrinsics()[i]);
                mvwaddstr(my_main_menu_intrinsics_box, 3+i, 15, prot_num.c_str());
            }
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 5, properties_list[i].c_str());
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
        if (my_save.get_intrinsics()[i] >= 1) {
            wattron(my_main_menu_intrinsics_box, COLOR_PAIR(4));
        }
        mvwaddstr(my_main_menu_intrinsics_box, 3+option_count, 1, "    ");
        mvwaddstr(my_main_menu_intrinsics_box, 3+option_count, 5, properties_list[i].c_str());
        if (i == 7) {
            // magic cancellation
            std::string mc_num = " " + std::to_string(my_save.get_intrinsics()[i]);
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 23, mc_num.c_str());
        } else if (i == 18) {
            // speed
            std::string speed_num = " " + std::to_string(my_save.get_intrinsics()[i]);
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 10, speed_num.c_str());
        } else if (i == 11) {
            // protection
            std::string prot_num = " " + std::to_string(my_save.get_intrinsics()[i]);
            mvwaddstr(my_main_menu_intrinsics_box, 3+i, 15, prot_num.c_str());
        }
        if (my_save.get_intrinsics()[i] >= 1) {
            wattroff(my_main_menu_intrinsics_box, COLOR_PAIR(4));
        }
        waddstr(my_main_menu_intrinsics_box, ((std::string)(" ")).c_str());
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
        for (int y = 2; y <= 28; ++y) {
            mvwaddch(my_main_menu_notes_box, y, x, notes_text[i]); 
            ++i;
        }
    }        
    wmove(my_main_menu_notes_box, 2, 1); 

    wrefresh(my_main_menu_notes_box);
}

void MainMenu::render_notes_menu_off() {
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

void MainMenu::render_price_ID_menu_off() {
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

void MainMenu::render_armor_ID_subtable(nlohmann::json & armor) {
    int name_len = 4;
    int AC_len = 2;
    int appearance_len = 10;
    int cost_len = 4;
    int don_doff_len = 8;
    int effect_len = 6;
    int material_len = 8;
    int mc_len = 2;
    int weight_len = 5; 
    for (auto it = armor.begin(); it != armor.end(); ++it) {
        if (it.key() != "random_appearance") {
            if (it.key().size() > name_len) {name_len = it.key().size();}
            // sub items
            for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
                // convert to std::string quite explicitly if needed
                auto &value = *it2;
                std::string str_to_use = "";
                if (value.is_number_integer()) {
                    str_to_use = nlohmann::to_string(value);
                } else {
                    str_to_use = value;
                }
                if (it2.key() == "appearance") {
                    if (str_to_use.size() > appearance_len) {appearance_len = str_to_use.size();}
                } else if (it2.key() == "cost") {
                    if (str_to_use.size() > cost_len) {cost_len = str_to_use.size();}
                } else if (it2.key() == "effect") {
                    if (str_to_use.size() > effect_len) {effect_len = str_to_use.size();}
                } else if (it2.key() == "material") {
                    if (str_to_use.size() > material_len) {material_len = str_to_use.size();}
                } 
            }
        }
    }

    int my_row = 4 + armor.size(); 
    int my_col = 2 + name_len + 1 + AC_len + 1 + appearance_len + 1 + cost_len + 1 + don_doff_len + 1 + effect_len + 1 + material_len + 1 + mc_len + 1 + weight_len + 1;

    std::string first_line = "Random appearances: ";
    first_line.append(armor["random_appearance"]);

    if (first_line.size() + 2 > my_col) {my_col = first_line.size() + 2;}

    WINDOW *popup_table = NULL;
    popup_table = newwin(my_row, my_col, get_main_menu_size()[0]/2 - my_row/2, get_main_menu_size()[1]/2 - my_col/2);
    wattron(popup_table, COLOR_PAIR(2));
    box(popup_table, 0, 0);
    wattroff(popup_table, COLOR_PAIR(2));

    // RENDER HERE
    mvwaddstr(popup_table, 1, 1, first_line.c_str());

    std::string headers = "";
    headers.append(name_len+1,' ').append("AC").append(AC_len-2+1,' ').append("APPEARANCE").append(appearance_len-10+1,' ').append("COST").append(cost_len-4+1,' ');
    headers.append("DON/DOFF").append(don_doff_len-8+1,' ').append("EFFECT").append(effect_len-6+1,' ').append("MATERIAL").append(material_len-8+1,' ').append("MC").append(mc_len-2+1,' ').append("WEIGHT");

    wattron(popup_table, COLOR_PAIR(5));
    mvwaddstr(popup_table, 3, 1, headers.c_str());
    wattroff(popup_table, COLOR_PAIR(5));

    int list_count = 0;
    for (auto it = armor.begin(); it != armor.end(); ++it) {
        if (it.key() != "random_appearance") {
            mvwaddstr(popup_table, 4 + list_count, 1, it.key().c_str());
            for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
                // convert to std::string quite explicitly if needed
                auto &value = *it2;
                std::string str_to_use = "";
                if (value.is_number_integer()) {
                    str_to_use = nlohmann::to_string(value);
                } else {
                    str_to_use = value;
                }
                int col_pos = 1 + name_len + 1;
                if (it2.key() == "AC") {mvwaddstr(popup_table, 4+list_count, col_pos, str_to_use.c_str());}
                col_pos = col_pos + AC_len + 1;
                if (it2.key() == "appearance") {mvwaddstr(popup_table, 4+list_count, col_pos, str_to_use.c_str());}
                col_pos = col_pos + appearance_len + 1;
                if (it2.key() == "cost") {mvwaddstr(popup_table, 4+list_count, col_pos, str_to_use.c_str());}
                col_pos = col_pos + cost_len + 1;
                if (it2.key() == "don/doff") {mvwaddstr(popup_table, 4+list_count, col_pos, str_to_use.c_str());}
                col_pos = col_pos + don_doff_len + 1;
                if (it2.key() == "effect") {mvwaddstr(popup_table, 4+list_count, col_pos, str_to_use.c_str());}
                col_pos = col_pos + effect_len + 1;
                if (it2.key() == "material") {mvwaddstr(popup_table, 4+list_count, col_pos, str_to_use.c_str());}
                col_pos = col_pos + material_len + 1;
                if (it2.key() == "MC") {mvwaddstr(popup_table, 4+list_count, col_pos, str_to_use.c_str());}
                col_pos = col_pos + mc_len + 1;
                if (it2.key() == "weight") {mvwaddstr(popup_table, 4+list_count, col_pos, str_to_use.c_str());}
            }
            ++list_count;
        }
    }

    wrefresh(popup_table);

    // loop window
    bool running_loop = true;
    std::vector<int> exit_buttons = {27, 32};
    while (running_loop) {
        int ch1 = getch();
        if (std::find(exit_buttons.begin(), exit_buttons.end(), ch1) != exit_buttons.end()) { 
            werase(popup_table);
            wrefresh(popup_table);
            delwin(popup_table);
            running_loop = false;
            return; 
        } 
    }
    return;
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
    wattron(my_win, COLOR_PAIR(3));
    for (int i = 0; i < title_lines; ++i) {
        std::string line = title_to_print.substr(0, title_to_print.find("\n"));
        title_to_print.erase(0, title_to_print.find("\n") + ((std::string)"\n").length());
        mvwaddstr(my_win, (int)(my_row/2 -2 - title_lines + i), (int)((my_col - line.length())/2), line.c_str());
    }
    wattroff(my_win, COLOR_PAIR(3));
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
