#include <functional>
#include <csignal>
#include <iostream>
#include <ncurses\ncurses.h>
#include <vector>

#include "io.h"
#include "input_handlers.h"
#include "menu.h"
#include "gamemap.h"
#include "submenu.h"
#include "utilities.h"

int totrow, totcol;

void save_and_exit(int signal_number) {
    // this is where we handle saving and quitting when exiting from the terminal abnormally
   std::cout << "\nInterrupt signal (" << signal_number << ") received.";
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

    // Catch early termination by closing window
    signal(SIGTERM, save_and_exit);
    // Catch early termination by ctrl-c 
    signal(SIGINT, save_and_exit);

    // Read in file names now
    // TODO handle if there are too many files to print on screen? Probably just throw an exception
    std::vector<std::string> character_filenames = get_filenames("data");

    // Initialize a GameMap. This will be blank for now
    totrow = 32;    // really there is 32, but some weird bug causes the bottom row to disappear occasionally
    totcol = 110;   //82 for main screen, +38 for sidebar
    GameMap PlayMap(
        0, totrow, totcol, totrow, totcol
    );
   
    // Initialize necessary submenus now
    ProfileMenu profile_menu(
        PlayMap.get_map_tot_row_col()[0], PlayMap.get_map_tot_row_col()[1], 0, 0, ascii_title, character_filenames, 27
    );

    //Menu main_menu(
    //    "Options", totrow, totcol, 0, 0, std::vector<std::string> {"Intrinsics"}, "Esc) Switch Profile", 1, 27
    //);

    //(profile_menu->*action_handler)(0); 

    profile_menu.open_menu();
	refresh();

    // GAME LOOP BELOW 
    bool is_running = true;

    while (is_running) {
        // Check for input
        int ch = getch();

        // handle input. Set is_running false to quit loop, but otherwise will remain true
        is_running = profile_menu_action_handler(profile_menu, ch);
    }

	return 0;
}