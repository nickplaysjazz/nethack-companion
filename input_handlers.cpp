#include <algorithm>
#include <iostream>
#include <ncurses/ncurses.h>
#include <string>
#include <vector>

#include "input_handlers.h"
#include "io.h"
#include "submenu.h"
#include "utilities.h"

int main_menu_action_handler(MainMenu & main_menu, ProfileMenu & profile_menu, int ch) {
    if (ch == 27) {
        // escape
        main_menu.close_menu();
        profile_menu.open_menu();
        profile_menu.render_menu();

        return 0;
    }
    return 1; 
}

int profile_menu_action_handler(ProfileMenu & profile_menu, MainMenu & main_menu, int ch) {
    int num_options = (int)profile_menu.get_options_list().size();
    std::vector<int> progress_buttons;
    for (int i = 0; i < num_options; ++i) {
        progress_buttons.push_back(int('a') + i); 
    }

    if (ch == 330) // Delete key 
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
                std::vector<int> {27, 32, int('n'), int('y'), 10, 8}
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

        create_file(filename);
        profile_menu.set_options_list(get_filenames("data"));
        werase(profile_menu.get_my_win());
        profile_menu.render_menu();
        wrefresh(profile_menu.get_my_win());
        
        return 0;
    } else if (ch == 27) { // escape
        WINDOW *my_goodbye_win;
        std::string exit_msg = "Files saved. Press any key to exit...";
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
        main_menu.open_menu();
        main_menu.render_menu(profile_menu.get_options_list()[ch - int('a')]);
        wrefresh(main_menu.get_my_win());

        return 1;
    } else {
        return 0;
    }
}