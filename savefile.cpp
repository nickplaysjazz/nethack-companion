// TODO remove
#include <iostream>

#include "savefile.h"
#include "utilities.h"

Savefile::Savefile(
) {
    intrinsics = std::vector<bool> (properties_list.size(), 0);
};

void Savefile::clear() {
    for (int i = 0; i < (int)properties_list.size(); ++i) {
        intrinsics[i] = 0;
    }
    filename = "";
}

std::vector<bool> Savefile::get_intrinsics() {
    return intrinsics;
}

std::string Savefile::get_filename() {
    return filename; 
}

void Savefile::set_filename(std::string & new_filename) {
    filename = new_filename;
}

void Savefile::set_intrinics(std::vector<bool> & new_intrinsics) {
    intrinsics = new_intrinsics;
}

void Savefile::flip_active_state() {
    is_active_save = !is_active_save;
}

bool Savefile::is_active() {
    return is_active_save;
}
