#ifndef INPUT_HANDLERS_H
#define INPUT_HANDLERS_H

#include "submenu.h"

int profile_menu_action_handler(ProfileMenu & profile_menu, MainMenu & main_menu, int ch);
int main_menu_action_handler(MainMenu & main_menu, ProfileMenu & profile_menu, int ch); 

#endif