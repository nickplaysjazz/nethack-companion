#include <iostream>
#include <ncurses/ncurses.h>
#include <string>

#include "input_handlers.h"
#include "io.h"
#include "submenu.h"
#include "utilities.h"

bool profile_menu_action_handler(ProfileMenu & profile_menu, int ch) {
    switch (ch) {
        case 330: // Delete key 
        {
            std::vector<int> progress_buttons_list {};
            for (int i = 0; i < (int)profile_menu.get_options_list().size(); ++i) {
                progress_buttons_list.push_back(int('a') + i);
            }
            WINDOW *my_delwin = NULL;
            int result = profile_menu.create_popup(
                profile_menu,
                my_delwin,
                "While file do you want to delete?",
                profile_menu.get_options_list(),
                progress_buttons_list,
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

            return true;
            break;
            // // prepare Delete window
            // WINDOW *my_delwin;
            // std::string title_to_print = "Which file do you want to delete?"; 
            // std::vector<std::string> options_list = profile_menu.get_options_list();
            // int my_row = 4 + options_list.size(); 
            // int my_col = 0;
            // for (int j = 0; j < (int)options_list.size(); ++j) {
            //     if ((int)options_list[j].length() + 3 > my_col) {my_col = (int)options_list[j].length();}
            // }
            // if ((int)title_to_print.length() > my_col) {my_col = (int)title_to_print.length();}
            // my_col = my_col + 2; 

            // my_delwin = newwin(my_row, my_col, profile_menu.get_size()[0]/2 - my_row/2, profile_menu.get_size()[1]/2 - my_col/2);
            // box(my_delwin, 0, 0);
            // mvwaddstr(my_delwin, 1, 1, title_to_print.c_str());
            // int option_count = 0;
            // for (std::vector<std::string>::const_iterator it = options_list.begin(); it != options_list.end(); ++it) {
            //     mvwaddstr(my_delwin, 3 + option_count, 1, num_to_alphabet(option_count).c_str());
            //     waddstr(my_delwin, ") "); 
            //     waddstr(my_delwin, it->c_str());
            //     ++option_count;
            // }

            // // render Delete window
            // wrefresh(my_delwin);

            // // loop Delete window
            // bool is_inner_loop_running = true;
            // while (is_inner_loop_running) {
            //     int ch1 = getch();
            //     if (ch1 == 27 || ch1 == 32) { // escape
            //         werase(my_delwin);
            //         wrefresh(my_delwin);
            //         delwin(my_delwin);
            //         touchwin(profile_menu.get_my_win());
            //         refresh();
            //         wrefresh(profile_menu.get_my_win());
            //         is_inner_loop_running = false;
            //     } else if (ch1 >= int('a') && ch1 <= int('z')) {
            //         if (ch1 - int('a') < (int)options_list.size()) {
            // *************************************************************
            //             WINDOW *my_confirm_win;
            //             std::string my_confirm_txt = "Are you sure you want to delete " + options_list[ch1-int('a')] + " ? y/n";
            //             my_confirm_win = newwin(3, (int)my_confirm_txt.length()+2, profile_menu.get_size()[0]/2 - 1/2, profile_menu.get_size()[1]/2 - (int)my_confirm_txt.length()/2);
            //             box(my_confirm_win, 0, 0);
            //             mvwaddstr(my_confirm_win, 1, 1, my_confirm_txt.c_str());

            //             wrefresh(my_confirm_win);

            //             int ch2 = getch();
            //             int inner_second_loop_running = true;
            //             while (inner_second_loop_running) {
            //                 if (ch2 == int('y')) {
            //                     delete_file(get_filepaths("data")[ch1-int('a')]);
            //                     profile_menu.set_options_list(get_filenames("data"));
            //                     werase(profile_menu.get_my_win());
            //                     profile_menu.render_menu();
            //                     wrefresh(profile_menu.get_my_win());
            //                 }
                            
            //                 if (ch2 == int('n') || ch2 == int('y') || ch2 == 27 || ch2 == 32) {
            //                     werase(my_confirm_win);
            //                     delwin(my_confirm_win);
            //                     werase(my_delwin);
            //                     delwin(my_delwin);
            //                     touchwin(profile_menu.get_my_win());
            //                     refresh();
            //                     wrefresh(profile_menu.get_my_win());
            //                     is_inner_loop_running = false;
            //                     inner_second_loop_running = false;
            //                 }
            //             }
            //         }
            //     }
            // }
        }
        case 10: // enter
            return true;
            break;
        case 27: // escape
            std::cout<<"test: esc has been hit, goodbye"<<std::endl;
            return false; 
            break;
        default:
            return true;
            break;
    } 
}