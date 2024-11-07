#ifndef SUBMENU_H
#define SUBMENU_H

class IntrinsicMenu
{
    private:
        int sizey, sizex, locy, locx;
        WINDOW *my_win;  

    public: 
        IntrinsicMenu(int _sizey, int _sizex, int _locy, int _locx);
        void open_menu();
        void close_menu();
        //bool menu_action_handler(); 
};

#endif