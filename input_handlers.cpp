#include <iostream>

#include "input_handlers.h"
#include "menu.h"

bool profile_menu_action_handler(Menu& menu, int ch) {
    switch (ch) {
        // todo handle variable case
        case 27:
            // TODO fix closing the right menu, right now it closes the parent Menu window instead of the child ProfileMenu window. 
            // might need to pass the window into close_menu()... 
            //close_menu();
            std::cout<<"test: esc has been hit, goodbye"<<std::endl;
            return false; 
            break;
        default:
            return true;
            break;
    } 
}