#include <functional>
#include <csignal>
#include <iostream>
#include <ncurses\ncurses.h>
#include <vector>

#include "io.h"
#include "input_handlers.h"
#include "menu.h"
#include "gamemap.h"
#include "savefile.h"
#include "submenu.h"
#include "utilities.h"

int totrow, totcol;

void save_and_exit(int signal_number) {
    // this is where we handle saving and quitting, even abnormally
   // std::cout << "\nInterrupt signal (" << signal_number << ") received.";
}

int main() {
    // Start curses
	initscr();
    // Do not print characters that are input by user
    noecho(); 
    // Enable keypad and extended keys
    keypad(stdscr, true); 
    // Make flashing cursor invisible
    curs_set(0);

    // Initalize colors
    if (has_colors() == false) 
    {
        endwin();
        std::cout<<"\nYour terminal does not support color!";
        return 1; 
    }
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    // Catch early termination by closing window
    signal(SIGTERM, save_and_exit);
    // Catch early termination by ctrl-c 
    signal(SIGINT, save_and_exit);

    // Read in file names now
    std::vector<std::string> character_filenames = get_filenames("data");

    // TODO load savefiles?

    // Initialize a GameMap. This will be blank for now
    // in NetHack there are 32 rows; 82 col for main screen and +38 for sidebar
    totrow = 32; 
    totcol = 110;
    GameMap PlayMap(
        0, totrow, totcol, totrow, totcol
    );
   
    // Initialize necessary submenus now
    WINDOW *my_profile_menu_win = NULL;
    ProfileMenu profile_menu(
        my_profile_menu_win, PlayMap.get_map_tot_row_col()[0], PlayMap.get_map_tot_row_col()[1], 0, 0, ascii_title, character_filenames, 27
    );

    WINDOW *my_main_menu_win = NULL;
    MainMenu main_menu(
        my_main_menu_win, PlayMap.get_map_tot_row_col()[0], PlayMap.get_map_tot_row_col()[1], 0, 0, "", std::vector<std::string> {""}, 27
    );

    profile_menu.open_menu();
	refresh();

    // GAME LOOP
    bool is_running = true;
    int action_handler = 0;
    while (is_running) {
        // Check for input
        int ch = getch();

        // state machine
        switch (action_handler) {
            case 0:
                // profile menu
                action_handler = profile_menu_action_handler(profile_menu, main_menu, ch); 
                break;
            case 1:
                // main menu
                action_handler = main_menu_action_handler(main_menu, profile_menu, ch);
                break; 
            case 99:
                // quit
                save_and_exit(0);
                is_running = false;
                break;
        }
    }

	return 0;
}