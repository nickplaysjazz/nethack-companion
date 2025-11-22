#ifdef _WIN32
#include <ncurses/ncurses.h>
#include <windows.h>
#elif __linux__
#include <ncurses.h>
#elif __APPLE__
#include <ncurses.h>
#endif

#include <functional>
#include <csignal>
#include <iostream>
#include <vector>

#include "../include/io.h"
#include "../include/input_handlers.h"
#include "../include/menu.h"
#include "../include/gamemap.h"
#include "../include/savefile.h"
#include "../include/sokoban.h"
#include "../include/submenu.h"
#include "../include/utilities.h"

// MUST be global in order to be saved on improper exit
Savefile my_open_save;

void save_and_exit(int signal_number) {
    // this is where we handle saving and quitting, even abnormally
    if (signal_number != 0) {
        std::cout << "\nInterrupt signal (" << signal_number << ") received!" << std::endl;
    }
   
    if (my_open_save.is_active()) {
        save_file(my_open_save.get_filename(), my_open_save);
    }

}

int main() {
    // a weird bug causes Linux, Mac to delay on hitting escape button
    // because ncurses somewhat handles alt key and escape key with the same code
    // instead of waiting to check if two buttons are pressed, in which case it's treated as an "alt" button
    // just have the code move on without checking
    // if you hit escape and another key rapidly afterwards, you might run into it handling it as alt + another key
    // but no big deal
    ESCDELAY = 10;
    int totrow = 32; 
    int totcol = 110;

    // Set the window size
    #ifdef _WIN32
        HWND console = GetConsoleWindow();
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_FONT_INFO cfi;
        COORD fontSize;
        RECT r;
        
        GetWindowRect(console, &r);
        if (GetCurrentConsoleFont(hOut, FALSE, &cfi))
            fontSize = GetConsoleFontSize(hOut, cfi.nFont);

        resizeterm(totrow, totcol);
        // TODO: Magic numbers for 5 & 3? Why??
        MoveWindow(console, r.left, r.top, fontSize.X * (totcol+5), fontSize.Y * (totrow+3), TRUE);
    #endif

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
    // default color
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    // subbox color
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    // character title color, profile page title
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    // properties color
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    // notes color
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    // price ID color
    init_pair(6, COLOR_RED, COLOR_BLACK);
    // sokoban
    //init_pair(7, COLOR_BLUE, COLOR_BLACK);
    // xp 
    //init_pair(8, COLOR_WHITE, COLOR_BLACK);
    // wand engrave
    //init_pair(9, COLOR_MAGENTA, COLOR_BLACK);

    // if needed, create /data/ folder
    create_data_folder();

    // Read in file names now
    std::vector<std::string> character_filenames = get_filenames("data");

    // Read in JSON files now too
    //std::vector<std::string> armor_ID_data = get_json_data();

    // Initialize a GameMap. This will be blank for now
    // in NetHack there are 32 rows; 82 col for main screen and +38 for sidebar
    GameMap PlayMap(
        0, totrow, totcol, totrow, totcol
    );
   
    // Initialize necessary submenus now
    WINDOW *my_profile_menu_win = NULL;
    ProfileMenu profile_menu(
        my_profile_menu_win, totrow, totcol, 0, 0, ascii_title, character_filenames, 27
    );

    WINDOW *my_main_menu_win = NULL;
    MainMenu main_menu(
        my_main_menu_win, totrow, totcol, 0, 0, "", std::vector<std::string> {""}, 27
    );

    // Also initialize Sokoban map
    WINDOW *my_sokoban_win = NULL;
    Sokoban my_sokoban(
        my_sokoban_win, totrow, totcol
    );
    
    // Catch early termination by closing window.
    signal(SIGTERM, save_and_exit);
    // Catch early termination by ctrl-c.
    signal(SIGINT, save_and_exit);

    profile_menu.open_menu();
	refresh();

    // GAME LOOP
    bool is_running = true;
    int action_handler = 0;
    while (is_running) {
        // Check for input
        int ch = getch();

        switch (action_handler) {
            case 0:
                // profile menu
                action_handler = profile_menu_action_handler(profile_menu, main_menu, my_open_save, ch); 
                break;
            case 1:
                // main menu
                action_handler = main_menu_action_handler(main_menu, profile_menu, my_sokoban, my_open_save, ch);
                break; 
            case 2:
                // sokoban
                action_handler = my_sokoban.sokoban_action_handler(main_menu, my_open_save, ch);
                break;
            case 99:
                // quit
                save_and_exit(0);
                endwin();
                is_running = false;
                break;
        }
    }

	return 0;
}