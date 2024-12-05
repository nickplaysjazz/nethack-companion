#include <algorithm>
#include <iostream>
#include <ncurses/ncurses.h>
#include <string>
#include <vector>

#include "input_handlers.h"
#include "io.h"
#include "submenu.h"
#include "utilities.h"

int main_menu_action_handler(MainMenu & main_menu, ProfileMenu & profile_menu, Savefile & my_save, int ch) {
    if (ch == 27) {
        // escape
        main_menu.close_menu();
        profile_menu.open_menu();
        profile_menu.render_menu();

        my_save.flip_active_state();
        save_file(my_save.get_filename(), my_save);
        my_save.clear();

        return 0;
    } else if (ch == int('p')) {
        // intrinsics
        std::string intrinsics_title = "PROPERTIES p)";
        WINDOW *intrinsics_box = main_menu.get_my_main_menu_intrinsics_box();

        wattron(intrinsics_box, COLOR_PAIR(4));
        wattron(intrinsics_box, A_STANDOUT);
        mvwaddstr(intrinsics_box, 1, intrinsics_title.length()/2, intrinsics_title.c_str());
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
                wattron(intrinsics_box, A_STANDOUT);
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

        // intrinsics submenu
        bool is_inner_loop_running = true;
        while (is_inner_loop_running) {
            // highlight those already selected
            for (int i = 0; i < (int)properties_buttons.size(); ++i) {
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

            int ch1 = getch();

            if (ch1 == 27) {
                wattron(intrinsics_box, COLOR_PAIR(4));
                mvwaddstr(intrinsics_box, 1, intrinsics_title.length()/2, intrinsics_title.c_str());
                wattroff(intrinsics_box, COLOR_PAIR(4));

                int option_count = 0;
                for (std::vector<std::string>::const_iterator it = properties_list.begin(); it != properties_list.end(); ++it) {
                    mvwaddstr(intrinsics_box, 3+option_count, 1, "   ");
                    waddstr(intrinsics_box, it->c_str());
                    ++option_count;
                }

                wrefresh(intrinsics_box);

                is_inner_loop_running = false;
            } else if (std::find(properties_buttons.begin(), properties_buttons.end(), ch1) != properties_buttons.end()) {
                std::vector<bool> save_intrinsics = my_save.get_intrinsics();

                // Finding the index of val
                std::vector<int>::iterator it = find(properties_buttons.begin(), properties_buttons.end(), ch1);
                int index = it - properties_buttons.begin();

                if (save_intrinsics[index] == 0) {
                    save_intrinsics[index] = 1;
                } else {
                    save_intrinsics[index] = 0;
                }

                my_save.set_intrinics(save_intrinsics);
            }
        }

        return 1;
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
        main_menu.open_menu();
        main_menu.render_menu(profile_menu.get_options_list()[ch - int('a')]);
        wrefresh(main_menu.get_my_win());

        try_load_file((profile_menu.get_options_list()[ch - int('a')]).append(".dat"), my_savefile);

        return 1;
    } else {
        return 0;
    }
}