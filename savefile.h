#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <vector>

#include "utilities.h"

class Savefile {
    private:
        std::vector<int> intrinsics;
        bool is_active_save = false;

    public:
        Savefile();

        std::vector<int> get_intrinsics();
        void set_intrinics(std::vector<int> & new_intrinsics);
        void flip_active_state();
        bool is_active();
};

#endif