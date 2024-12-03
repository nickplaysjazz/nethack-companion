// TODO remove
#include <iostream>

#include "savefile.h"
#include "utilities.h"

Savefile::Savefile(
) {
    intrinsics = std::vector<int> (properties_list.size(), 0);
};

std::vector<int> Savefile::get_intrinsics() {
    return intrinsics;
}

void Savefile::set_intrinics(std::vector<int> & new_intrinsics) {
    intrinsics = new_intrinsics;
}

void Savefile::flip_active_state() {
    is_active_save = !is_active_save;
}

bool Savefile::is_active() {
    return is_active_save;
}
