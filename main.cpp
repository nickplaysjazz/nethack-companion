#include <iostream>
#include <ncurses\ncurses.h>
#include <vector>

#include "io.h"
#include "menu.h"
#include "playmap.h"
#include "submenu.h"
#include "utilities.h"

int totrow, totcol;

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

    // Read in file names now
    std::vector<std::string> character_filenames = get_filenames("data");

    // TODO handle this better
    character_filenames.push_back("Create New Character");
    character_filenames.push_back("Delete Character"); 

    // Initialize background GameMap called PlayMap
    // The GameMap defines the total area of the app, but otherwise really shouldn't change
    totrow = 31;
    totcol = 110; //82 for main screen, +38 for sidebar
    GameMap PlayMap(
        0, totrow, totcol, totrow, totcol
    );
   
    Menu profile_menu(
        ascii_title, totrow, totcol, 0, 0, character_filenames, "Esc) Exit", 1, 27
    );

    Menu main_menu(
        "Options", totrow, totcol, 0, 0, std::vector<std::string> {"Intrinsics"}, "Esc) Switch Profile", 1, 27
    );

    profile_menu.open_menu();
	refresh();

    // GAME LOOP BELOW 
    bool is_running = true;
    while (is_running) {
        // Check for input
        int ch = getch();

        // Handle inputs
        switch (ch) {
            case 27:
                // escape button
                is_running = false; 
                endwin();
                break; 
            case 97:
                // a 
                main_menu.open_menu(); 
                is_running = main_menu.menu_action_handler(profile_menu);
                break; 
        }
    }

	return 0;
}