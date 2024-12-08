#ifndef INPUT_HANDLERS_H
#define INPUT_HANDLERS_H

#include "savefile.h"
#include "submenu.h"

int profile_menu_action_handler(ProfileMenu & profile_menu, MainMenu & main_menu, Savefile & my_savefile, int ch);
int main_menu_action_handler(MainMenu & main_menu, ProfileMenu & profile_menu, Savefile & my_savefile, int ch); 

int properties_menu_action_handler(MainMenu & main_menu, Savefile & my_save);
int notes_menu_action_handler(MainMenu & main_menu, Savefile & my_save);

#endif