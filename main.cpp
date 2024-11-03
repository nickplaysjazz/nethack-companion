#include <iostream>
#include <ncurses\ncurses.h>
#include <vector>

#include "io.h"
#include "utilities.h"

int totrow, totcol;

// GameMap is a placeholder for the background
class GameMap 
{
    private: 
        int id;

        void init_map(int maxy, int maxx) {
            // define the map array
            map = new int*[maxy];
            for (int i = 0; i < maxy; ++i) {
                map[i] = new int[maxx];
                for (int j = 0; j < maxx; ++j) 
                    map[i][j] = '^' - 0;
            }
            
            // define map
            for (int i = 0; i < maxy; ++i) {
                for (int j = 0; j < maxx; ++j) { 
                    if ((i > 0 && i < maxy - 1) && (j > 0 && j < maxx - 1)) {
                        map[i][j] = '.' - 0;
                    }
                }
            }

            update_map(sizey, sizex);
            refresh();
        }

    public: 
        int **map;
        int sizey, sizex;
        WINDOW *play_win;

        // constructor 
        GameMap(int _id, int _sizey, int _sizex) {
            id = _id;
            sizey = _sizey;
            sizex = _sizex;
            play_win = newwin(totrow, totcol, 0, 0);
            init_map(sizey, sizex);
        }

        void update_map(int maxy, int maxx) {
            wattron(play_win, COLOR_PAIR(1));
            box(play_win, 0, 0);
            for (int i = 0; i < maxy; ++i) {
                for (int j = 0; j < maxx; ++j) { 
                    if ((i > 0 && i < maxy - 1) && (j > 0 && j < maxx - 1)) {
                        mvwaddch(play_win, i, j, (char)map[i][j]);
                    }
                }
            }
            wattroff(play_win, COLOR_PAIR(1));
            wrefresh(play_win);
        }
};

class Menu {
    private: 
        std::string menu_name;
        int sizey, sizex, locy, locx;
        std::vector<std::string> options_list; 
        std::string exit_msg; 
        int justify;        // 0 is top-left, 1 is middle-center
        int close_button; 
        WINDOW *my_win; 

    public: 
        // constructor
        Menu(const std::string & _menu_name, int _sizey, int _sizex, int _locy, int _locx, const std::vector<std::string> & _options_list, const std::string & _exit_msg, int _justify = 0, int _close_button = 27) {
            menu_name = _menu_name;
            sizey = _sizey;
            sizex = _sizex;
            locy = _locy;
            locx = _locx;
            options_list = _options_list;
            exit_msg = _exit_msg;
            justify = _justify; 
            close_button = _close_button;
        }

        void open_menu() {
            // TODO check for options being too long for size of screen
            my_win = newwin(sizey, sizex, locy, locx);
            if (justify == 0) {
                // top-left
                int title_lines = count_newlines(menu_name);
                std::string title_to_print = menu_name; 
                for (int i = 0; i < title_lines; ++i) {
                    std::string line = title_to_print.substr(0, title_to_print.find("\n"));
                    title_to_print.erase(0, title_to_print.find("\n") + ((std::string)"\n").length());
                    mvwaddstr(my_win, 1 + i, 1, line.c_str());
                }
                int option_count = 0;
                for (std::vector<std::string>::const_iterator it = options_list.begin(); it != options_list.end(); ++it) {
                    mvwaddstr(my_win, 2 + title_lines + option_count, 1, num_to_alphabet(option_count).c_str());
                    waddstr(my_win, ") "); 
                    waddstr(my_win, it->c_str());
                    ++option_count;
                }
                mvwaddstr(my_win, 3 + title_lines + option_count, 1, exit_msg.c_str());
            } else if (justify == 1) {
                // centered
                int title_lines = count_newlines(menu_name);
                std::string title_to_print = menu_name; 
                for (int i = 0; i < title_lines; ++i) {
                    std::string line = title_to_print.substr(0, title_to_print.find("\n"));
                    title_to_print.erase(0, title_to_print.find("\n") + ((std::string)"\n").length());
                    mvwaddstr(my_win, (int)(totrow/2 -2 - title_lines + i), (int)((totcol - line.length())/2), line.c_str());
                }
                int option_count = 0;
                for (std::vector<std::string>::const_iterator it = options_list.begin(); it != options_list.end(); ++it) {
                    mvwaddstr(my_win, (int)(totrow/2 + option_count), (int)(totcol/2 - 5), num_to_alphabet(option_count).c_str());
                    waddstr(my_win, ") "); 
                    waddstr(my_win, it->c_str());
                    ++option_count;
                }
                mvwaddstr(my_win, (int)(totrow/2 + 1 + title_lines + option_count), (int)(totcol/2 - 5), exit_msg.c_str());
            } 
            box(my_win, 0, 0);
            wrefresh(my_win);
        }

        void close_menu() {
            werase(my_win);
            wrefresh(my_win);
            delwin(my_win);
        }

        // returns true if still running game, false if quitting game
        bool menu_action_handler() {
            while (true) {
                int ch = getch();
                if (ch == close_button) {
                    // closing button
                    close_menu();
                    return true;
                } 
            }
        }
};


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

    totrow = 32;
    totcol = 110; //82 for main screen, +38 for sidebar

    // Read in file names now
    std::vector<std::string> character_filenames = get_filenames("data");

    // Initialize background GameMap called PlayMap
    // The GameMap defines the total area of the app, but otherwise really shouldn't change
    GameMap PlayMap(
        0, totrow, totcol
    );
   
    Menu profile_menu(
        ascii_title, totrow, totcol, 0, 0, character_filenames, "", 1
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
            default:
                refresh();
                break;
        }
    }

	return 0;
}