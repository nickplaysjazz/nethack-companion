#include "submenu.h"
#include "sokoban.h"

Sokoban::Sokoban(
    int _sizey, 
    int _sizex
    //MainMenu & _main_menu,
    //Savefile & _my_save
) {
    sizey = _sizey;
    sizex = _sizex;
    //main_menu = _main_menu;
    //my_save = _my_save;
}

void Sokoban::open() {
    // sokoban action handler
    int in = getch(); 
    (void) in;
}

int Sokoban::sokoban_action_handler(int ch) {
    if (ch == 27) {
        //main_menu.open_menu();
        //std::string file_title = main_menu.get_filetitle(); 
        //main_menu.render_menu(file_title, my_save);
        //wrefresh(main_menu.get_my_win());
        return 0;
    }
    return 0;
}