#include "savefile.h"
#include "utilities.h"

Savefile::Savefile(
) {
    intrinsics = std::vector<int> (properties_list.size(), 0);
};

std::vector<int> Savefile::get_intrinsics() {
    return intrinsics;
}

void Savefile::set_intrinics(std::vector<int> new_intrinsics) {
    intrinsics = new_intrinsics;
}