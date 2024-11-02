#include <iostream>
#include <ncurses\ncurses.h>

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
            play_win = newwin(totrow-5, totcol, 0, 0);
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
        std::string options_list; 
        int close_button; 
        WINDOW *my_win; 

    public: 
        // constructor
        Menu(const std::string & _menu_name, int _sizey, int _sizex, int _locy, int _locx, const std::string & _options_list, int _close_button = 27) {
            menu_name = _menu_name;
            sizey = _sizey;
            sizex = _sizex;
            locy = _locy;
            locx = _locx;
            options_list = _options_list;
            close_button = _close_button;
        }

        void open_menu() {
            my_win = newwin(sizey, sizex, locy, locx);
            mvwaddstr(my_win, 1, 1, menu_name.c_str());
            mvwaddstr(my_win, 3, 1, options_list.c_str());
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

    totrow = 30;
    totcol = 75;
    int playrow = totrow-5;
    int playcol = totcol;

    // Initialize background GameMap called PlayMap
    // The GameMap defines the total area of the app, but otherwise really shouldn't change
    GameMap PlayMap(
        0, playrow, playcol
    );

    // Initialize menus
    Menu profile_menu(
        "NETHACK COMPANION", 10, 25, (int)totrow/3, (int)totcol/3, "A: Example A \n Esc: Quit"
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