#ifndef SUBMENU_H
#define SUBMENU_H

#include "gamemap.h"
#include "menu.h"

class ProfileMenu : public Menu {
    public: 
        ProfileMenu(
            const GameMap & _play_map,
            int _sizey, 
            int _sizex, 
            int _locy, 
            int _locx, 
            const std::string & _menu_name, 
            const std::vector<std::string> & _options_list, 
            int _close_button
        );
        void render_menu() override;
        bool menu_action_handler(int ch) override;
};

// class IntrinsicMenu
// {
//     private:
//         int sizey, sizex, locy, locx;
//         WINDOW *my_win;  

//     public: 
//         IntrinsicMenu(int _sizey, int _sizex, int _locy, int _locx);
//         void open_menu();
//         void close_menu();
//         //bool menu_action_handler(); 
// };

#endif