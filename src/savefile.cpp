#ifdef _WIN32
#include <ncurses/ncurses.h>
#elif __linux__
#include <curses.h>
#endif

#include "../include/savefile.h"
#include "../include/utilities.h"

Savefile::Savefile(
) {
    intrinsics = std::vector<int> (properties_list.size(), 0);
    notes = std::vector<char> (784, int(' '));
    charisma = 10;
};

void Savefile::clear() {
    for (int i = 0; i < (int)properties_list.size(); ++i) {
        intrinsics[i] = 0;
    }
    filename = "";
    notes = std::vector<char> (784, int(' '));
    charisma = 10;
}

std::vector<int> Savefile::get_intrinsics() {
    return intrinsics;
}

std::string Savefile::get_filename() {
    return filename; 
}

std::vector<char> Savefile::get_notes() {
    return notes; 
}

int Savefile::get_charisma() {
    return charisma;
}

void Savefile::set_filename(std::string & new_filename) {
    filename = new_filename;
}

void Savefile::set_intrinics(std::vector<int> & new_intrinsics) {
    intrinsics = new_intrinsics;
}

void Savefile::set_notes(std::vector<char> & new_notes) {
    notes = new_notes; 
}

void Savefile::set_charisma(int new_charisma) {
    charisma = new_charisma; 
}

void Savefile::flip_active_state() {
    is_active_save = !is_active_save;
}

void Savefile::flip_is_being_duped() {
    is_being_duped = !is_being_duped;
}

void Savefile::set_is_being_duped(bool in) {
    is_being_duped = in;
}

bool Savefile::is_active() {
    return is_active_save;
}

bool Savefile::get_is_being_duped() {
    return is_being_duped;
}
