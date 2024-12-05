#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <vector>

#include "utilities.h"

class Savefile {
    private:
        std::vector<bool> intrinsics;
        bool is_active_save = false;
        std::string filename; 

    public:
        Savefile();

        void clear();

        std::vector<bool> get_intrinsics();
        std::string get_filename();

        void set_filename(std::string & new_filename);
        void set_intrinics(std::vector<bool> & new_intrinsics);

        void flip_active_state();
        bool is_active();
};

#endif