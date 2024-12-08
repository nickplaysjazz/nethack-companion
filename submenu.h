#ifndef SUBMENU_H
#define SUBMENU_H

#include "menu.h"
#include "savefile.h"

class MainMenu : public Menu {
    private:
        WINDOW *my_main_menu_intrinsics_box;
        WINDOW *my_main_menu_title_box;
        WINDOW *my_main_menu_notes_box;

    public: 
        MainMenu(
            WINDOW *_my_main_menu_win,
            int _sizey, 
            int _sizex, 
            int _locy, 
            int _locx, 
            const std::string & _menu_name, 
            const std::vector<std::string> & _options_list, 
            int _close_button
        );
        void render_menu(std::string & file_title, Savefile & my_save);
        void render_menu() override;

        void render_intrinsics_menu_default(Savefile & my_save);
        void render_intrinsics_menu_off(Savefile & my_save);
        void render_intrinsics_menu_on(Savefile & my_save);

        void set_my_main_menu_intrinsics_box(WINDOW *win);
        void set_my_main_menu_title_box(WINDOW *win);
        WINDOW *get_my_main_menu_intrinsics_box();
        WINDOW *get_my_main_menu_title_box();
};

class ProfileMenu : public Menu {
    public: 
        ProfileMenu(
            WINDOW *_my_profile_menu_win,
            int _sizey, 
            int _sizex, 
            int _locy, 
            int _locx, 
            const std::string & _menu_name, 
            const std::vector<std::string> & _options_list, 
            int _close_button
        );
        void render_menu() override;
        void set_options_list(std::vector<std::string> new_options_list); 
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