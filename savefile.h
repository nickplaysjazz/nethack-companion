#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <vector>

#include "utilities.h"

class Savefile {
    private:
        std::vector<int> intrinsics;

    public:
        Savefile();
        std::vector<int> get_intrinsics();
        void set_intrinics(std::vector<int> new_intrinsics);
};

#endif