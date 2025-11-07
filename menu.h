#ifndef MENU_H
#define MENU_H


#ifdef _WIN32
#include <ncurses/ncurses.h>
#elif __linux__
#include <ncurses.h>
#endif

#include <string>
#include <vector>

// Menu is the DEFAULT behavior for any SubMenu. SubMenu inherits from Menu and overrides function as needed
class Menu {
    protected: 
        WINDOW *my_win;

        int locy, locx, sizey, sizex;
        std::string menu_name;
        std::vector<std::string> options_list; 
        int close_button; 

    public: 
        Menu(
            WINDOW *_my_menu_win,
            int _sizey, 
            int _sizex, 
            int _locy, 
            int _locx, 
            const std::string & _menu_name, 
            const std::vector<std::string> & _options_list, 
            int _close_button
        );
        Menu();
        void open_menu();
        virtual void render_menu();
        void close_menu();
        int create_popup(
            Menu & menu_name,
            WINDOW *my_popup_name,
            std::string my_popup_title,
            std::vector<std::string> my_options_list,
            std::vector<int> progress_buttons, 
            std::vector<int> exit_buttons
        );
        int create_popup_long(
            Menu & menu_name,
            WINDOW *my_popup_name,
            std::vector<std::string> my_rows,
            std::vector<int> progress_buttons, 
            std::vector<int> exit_buttons
        );
        void create_table_filter(
            Menu & menu_name,
            WINDOW *my_popup_name,
            std::string my_table_title,
            std::vector<std::vector<std::string>> my_rows,
            std::vector<int> exit_buttons
        );
        std::string create_text_prompt(
            Menu & menu_name,
            WINDOW *my_text_prompt_name,
            std::string my_text_prompt_title,
            std::vector<int> progress_buttons, 
            std::vector<int> exit_buttons
        );
        
        std::vector<int> get_location(); 
        WINDOW *get_my_win();
        std::vector<std::string> get_options_list();
        std::vector<int> get_size();
};

#endif