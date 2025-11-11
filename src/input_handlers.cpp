#include <algorithm>
#include <iostream>

#ifdef _WIN32
#include <ncurses/ncurses.h>
#elif __linux__
#include <ncurses.h>
#endif

#include <string>
#include <vector>

#include "../include/input_handlers.h"
#include "../include/io.h"
#include "../include/sokoban.h"
#include "../include/submenu.h"
#include "../include/utilities.h"

int main_menu_action_handler(MainMenu & main_menu, ProfileMenu & profile_menu, Sokoban & my_sokoban, Savefile & my_save, int ch) {
    if (ch == 27) {
        // escape
        main_menu.close_menu();
        profile_menu.open_menu();
        profile_menu.render_menu();

        my_save.flip_active_state();
        save_file(my_save.get_filename(), my_save);
        my_save.clear();

        return 0;
    } else if (ch == int('i')) {
        // intrinsics
        properties_menu_action_handler(main_menu, my_save);
    } else if (ch == int('n')) {
        // notes
        notes_menu_action_handler(main_menu, my_save);
    } else if (ch == int('p')) {
        // price ID
        price_ID_menu_action_handler(main_menu, my_save);
    } else if (ch == int('s')) {
        // sokoban
        main_menu.close_menu();
        my_sokoban.init_game();

        return 2;
    } else if (ch == int('x')) {
        // xp level
        WINDOW * my_xp_window = NULL;
        main_menu.create_popup_long(
            main_menu,
            my_xp_window, 
            xp_to_level,
            {},
            {}
        );
    } else if (ch == int('z')) {
        // wand engrave
        WINDOW *my_engrave_win = NULL;
        main_menu.create_popup_long(
            main_menu,
            my_engrave_win,
            engrave_list,
            {},
            {}
        );
    } else if (ch == int('m')) {
        // monster lookup
        WINDOW *my_monster_lookup = NULL;
        main_menu.create_table_filter(
            main_menu,
            my_monster_lookup,
            "Enter monster name: ",
            monster_list,
            {27}
        );
    }
    return 1; 
}

int profile_menu_action_handler(ProfileMenu & profile_menu, MainMenu & main_menu, Savefile & my_savefile, int ch) {
    int num_options = (int)profile_menu.get_options_list().size();
    std::vector<int> progress_buttons;
    for (int i = 0; i < num_options; ++i) {
        progress_buttons.push_back(int('a') + i); 
    }

    if (ch == 330) // Delete key 
    {
        WINDOW *my_delwin = NULL;
        int result = profile_menu.create_popup(
            profile_menu,
            my_delwin,
            "While file do you want to delete?",
            profile_menu.get_options_list(),
            progress_buttons,
            std::vector<int> {27, 32}
        );

        if (result != -1) {
            WINDOW *my_confirm_window = NULL;
            int result2 = profile_menu.create_popup(
                profile_menu,
                my_confirm_window,
                "Are you sure you want to delete " + profile_menu.get_options_list()[result - int('a')] + " ? y/n",
                std::vector<std::string> {},
                std::vector<int> {int('y')},
                std::vector<int> {27, 32, int('n')}
            );

            if (result2 != -1) {
                delete_file(get_filepaths("data")[result-int('a')]);
                profile_menu.set_options_list(get_filenames("data"));
                werase(profile_menu.get_my_win());
                profile_menu.render_menu();
                wrefresh(profile_menu.get_my_win());
            }
        }
        return 0;
    } else if (ch == 10) { // enter
        if (get_filenames("data").size() >= 10) {
            WINDOW *my_too_many_windows = NULL;
            int result = profile_menu.create_popup(
                profile_menu,
                my_too_many_windows,
                "You have reached the max number of files. Please delete some and try again.",
                std::vector<std::string> {},
                std::vector<int> {},
                std::vector<int> {27, 32, int('n'), int('y'), 10, 8, KEY_BACKSPACE}
            );
            (void) result;
            return 0;
        }
        WINDOW *my_file_name_prompt = NULL;
        std::string filename = profile_menu.create_text_prompt(
            profile_menu,
            my_file_name_prompt,
            "What is the name of your new file?",
            std::vector<int> {10},
            std::vector<int> {27}
        );

        if (filename != "" && !std::all_of(filename.begin(),filename.end(),isspace)) {
            create_file(filename);
        }
        profile_menu.set_options_list(get_filenames("data"));
        werase(profile_menu.get_my_win());
        profile_menu.render_menu();
        wrefresh(profile_menu.get_my_win());
        
        return 0;
    } else if (ch == 27) { // escape
        WINDOW *my_goodbye_win;
        std::string exit_msg = "Press any key to exit...";
        my_goodbye_win = newwin(3, exit_msg.length()+2, profile_menu.get_size()[0]/2 - 1/2, profile_menu.get_size()[1]/2 - exit_msg.length()/2);
        wattron(my_goodbye_win, COLOR_PAIR(2));
        box(my_goodbye_win, 0, 0);
        wattroff(my_goodbye_win, COLOR_PAIR(2));
        mvwaddstr(my_goodbye_win, 1, 1, exit_msg.c_str());

        // render window
        wrefresh(my_goodbye_win);
        return 99; 
    } else if (std::find(progress_buttons.begin(), progress_buttons.end(), ch) != progress_buttons.end()) {
        profile_menu.close_menu();
        try_load_file((profile_menu.get_options_list()[ch - int('a')]).append(".dat"), my_savefile);

        main_menu.open_menu();
        main_menu.render_menu(profile_menu.get_options_list()[ch - int('a')], my_savefile);
        wrefresh(main_menu.get_my_win());

        return 1;
    } else {
        return 0;
    }
}

int properties_menu_action_handler(MainMenu & main_menu, Savefile & my_save) {
    main_menu.render_intrinsics_menu_default(my_save);

    int num_options = (int)properties_list.size();
    std::vector<int> properties_buttons;
    for (int i = 0; i < num_options; ++i) {
        properties_buttons.push_back(int('a') + i); 
    }

    // intrinsics submenu
    bool is_inner_loop_running = true;
    while (is_inner_loop_running) {
        main_menu.render_intrinsics_menu_on(my_save);

        int ch1 = getch();

        if (ch1 == 27) {
            main_menu.render_intrinsics_menu_off(my_save);

            is_inner_loop_running = false;
        } else if (std::find(properties_buttons.begin(), properties_buttons.end(), ch1) != properties_buttons.end() || (ch1 == int('S')) || (ch1 == int('H')) || (ch1 == int('L'))) {
            std::vector<int> save_intrinsics = my_save.get_intrinsics();

            // Finding the index of val
            std::vector<int>::iterator it = find(properties_buttons.begin(), properties_buttons.end(), ch1);
            int index = it - properties_buttons.begin();
            if (ch1 == int('S')) {
                index = 18;
            } else if (ch1 == int('H')) {
                index = 7;
            } else if (ch1 == int('L')) {
                index = 11; 
            }

            if (index == 18) {
                if (ch1 == int('S')) {
                    if (save_intrinsics[index] > 0) {
                        --save_intrinsics[index];
                    }
                } else if (ch1 == int('s')) {
                    if (save_intrinsics[index] < 2) {
                        ++save_intrinsics[index];
                    }
                }
            } else if (index == 7) {
                if (ch1 == int('H')) {
                    if (save_intrinsics[index] > 0) {
                        --save_intrinsics[index];
                    }
                } else if (ch1 == int('h')) {
                    if (save_intrinsics[index] < 3) {
                        ++save_intrinsics[index];
                    }
                }
            } else if (index == 11) {
                if (ch1 == int('L')) {
                    if (save_intrinsics[index] > 0) {
                        --save_intrinsics[index];
                    }
                } else if (ch1 == int('l')) {
                    if (save_intrinsics[index] < 99) {
                        ++save_intrinsics[index];
                    }
                }
            } else {
                if (save_intrinsics[index] == 0) {
                    save_intrinsics[index] = 1;
                } else {
                    save_intrinsics[index] = 0;
                }
            }

            my_save.set_intrinics(save_intrinsics);
        }
    }

    return 1;
}

int notes_menu_action_handler(MainMenu & main_menu, Savefile & my_save) {
    main_menu.render_notes_menu_on(my_save);
    
    int xpos = 1;
    int ypos = 2;
    bool is_inner_loop_running = true;
    wmove(main_menu.get_my_main_menu_notes_box(), ypos, xpos); 

    while (is_inner_loop_running) {
        // Make flashing cursor visible again
        curs_set(1);

        int ch1 = getch();

        if (ch1 == 27) {
            // Make flashing cursor invisible
            curs_set(0);

            std::vector<char> notes_panel; 
            for (int x = 1; x <= 28; ++x) {
                for (int y = 2; y <= 28; ++y) {
                    wmove(main_menu.get_my_main_menu_notes_box(), y, x); 
                    char current_ch = winch(main_menu.get_my_main_menu_notes_box());
                    notes_panel.push_back(current_ch); 
                }
            }        
            my_save.set_notes(notes_panel); 

            main_menu.render_notes_menu_off(my_save);

            is_inner_loop_running = false;
        } else if ((ch1 >= int('a') && ch1 <= int('z')) || (ch1 >= int('A') && ch1 <= int('Z')) || (ch1 >= int('0') && ch1 <= int('9')) || (ch1 == 32) || (std::find(notes_special_characters.begin(), notes_special_characters.end(), ch1) != notes_special_characters.end())) {
            if (xpos+1 <= 29) {
                waddch(main_menu.get_my_main_menu_notes_box(), keycode_to_char(ch1));
                wrefresh(main_menu.get_my_main_menu_notes_box());
                ++xpos;
            } 
        } else if (ch1 == KEY_BACKSPACE || ch1 == 8) {
            // backspace
            if (xpos-1 >= 1) {
                mvwaddch(main_menu.get_my_main_menu_notes_box(), ypos, xpos-1, ' ');
                --xpos;
                wmove(main_menu.get_my_main_menu_notes_box(), ypos, xpos); 
                wrefresh(main_menu.get_my_main_menu_notes_box()); 
            } else if (ypos - 1 >= 2) {
                xpos = 29;
                --ypos;
                wmove(main_menu.get_my_main_menu_notes_box(), ypos, xpos); 
                wrefresh(main_menu.get_my_main_menu_notes_box());
            }
        } else if (ch1 == 330) {
            // delete 
            
        } else if (ch1 == 10) {
            // enter
            if (ypos+1 <= 28) {
                ++ypos;
                xpos = 1;
                wmove(main_menu.get_my_main_menu_notes_box(), ypos, xpos); 
                wrefresh(main_menu.get_my_main_menu_notes_box());
            }
        } else if (ch1 == 258) {
            //down arrow
            if (ypos+1 <= 28) {
                ++ypos;
                wmove(main_menu.get_my_main_menu_notes_box(), ypos, xpos); 
                wrefresh(main_menu.get_my_main_menu_notes_box());
            }
        } else if (ch1 == 259) {
            //up arrow
            if (ypos-1 >= 2) {
                --ypos;
                wmove(main_menu.get_my_main_menu_notes_box(), ypos, xpos); 
                wrefresh(main_menu.get_my_main_menu_notes_box());
            }
        } else if (ch1 == 260) {
            //left arrow
            if (xpos-1 >= 1) {
                --xpos;
                wmove(main_menu.get_my_main_menu_notes_box(), ypos, xpos); 
                wrefresh(main_menu.get_my_main_menu_notes_box());
            }
        } else if (ch1 == 261) {
            //right arrow
            if (xpos+1 <= 29) {
                ++xpos;
                wmove(main_menu.get_my_main_menu_notes_box(), ypos, xpos); 
                wrefresh(main_menu.get_my_main_menu_notes_box());
            }
        }
    }

    return 1; 
}

int price_ID_menu_action_handler(MainMenu & main_menu, Savefile & my_save) {
    main_menu.render_price_ID_menu_on(my_save);
    
    bool is_inner_loop_running = true;
    while (is_inner_loop_running) {
        int ch1 = getch();

        if (ch1 == 27) {
            // escape
            main_menu.render_price_ID_menu_off(my_save);

            is_inner_loop_running = false;
        } else if (ch1 == 259 || ch1 == 261) {
            // up or right arrow
            int current_cha = my_save.get_charisma(); 
            if (current_cha < 25) {
                ++current_cha;
                my_save.set_charisma(current_cha);

                std::string charisma_ch = std::to_string(my_save.get_charisma());
                if (charisma_ch.size() != 2) {
                    charisma_ch = " " + charisma_ch;
                }
                mvwaddstr(main_menu.get_my_main_menu_price_ID_box(), 3, 19, charisma_ch.c_str());
                main_menu.render_prices(my_save); 
            }
        } else if (ch1 == 258 || ch1 == 260) {
            // down or left arrow
            int current_cha = my_save.get_charisma(); 
            if (current_cha > 3) {
                --current_cha;
                my_save.set_charisma(current_cha);

                std::string charisma_ch = std::to_string(my_save.get_charisma());
                if (charisma_ch.size() != 2) {
                    charisma_ch = " " + charisma_ch;
                }

                mvwaddstr(main_menu.get_my_main_menu_price_ID_box(), 3, 19, charisma_ch.c_str());
                main_menu.render_prices(my_save); 
            }
        } else if (ch1 == 10) {
            // enter
            my_save.flip_is_being_duped();
            if (my_save.get_is_being_duped() == true) {
                std::string print_yes = "YES";
                mvwaddstr(main_menu.get_my_main_menu_price_ID_box(), 4, 19, print_yes.c_str());
            } else {
                std::string print_no = "NO ";
                mvwaddstr(main_menu.get_my_main_menu_price_ID_box(), 4, 19, print_no.c_str());       
            }
            main_menu.render_prices(my_save); 
        } else if (ch1 >= int('a') && ch1 <= int('p')) {
            WINDOW *my_long_popup = NULL;
            
            std::vector<int> buttons = {};
            std::vector<int> buttons2 = {};
            main_menu.create_popup_long(
                main_menu, 
                my_long_popup,
                items_by_prices[ch1 - int('a')],
                {},
                {}
            );
        }
    }
    return 1; 
}