#include <iostream>
#include <ncurses\ncurses.h>

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

    // TODO REMOVE
    printw("Hello World !!!");
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
        }
    }

	return 0;
}