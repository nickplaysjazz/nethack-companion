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
        }
        case 10: // enter
        {
            if (get_filenames("data").size() >= 10) {
                WINDOW *my_too_many_windows = NULL;
                int result = profile_menu.create_popup(
                    profile_menu,
                    my_too_many_windows,
                    "You have reached the max number of files. Please delete some and try again.",
                    std::vector<std::string> {},
                    std::vector<int> {},
                    std::vector<int> {27, 32, int('n'), int('y'), 10, 8}
                );
                (void) result;
                return true;
                break;
            }
            WINDOW *my_file_name_prompt = NULL;
            std::string filename = profile_menu.create_text_prompt(
                profile_menu,
                my_file_name_prompt,
                "What is the name of your new file?",
                std::vector<int> {10},
                std::vector<int> {27}
            );

            create_file(filename);
            profile_menu.set_options_list(get_filenames("data"));
            werase(profile_menu.get_my_win());
            profile_menu.render_menu();
            wrefresh(profile_menu.get_my_win());
            
            return true;
            break;
        }
        case 27: // escape
            std::cout<<"test: esc has been hit, goodbye"<<std::endl;
            return false; 
            break;
        default:
            return true;
            break;
    } 
}