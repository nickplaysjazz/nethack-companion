#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <ncurses\curses.h>
#include <vector>

#include "utilities.h"

class Savefile {
    private:
        std::vector<bool> intrinsics;
        bool is_active_save = false;
        std::string filename; 
        int charisma;

        std::vector<char> notes; 

    public:
        Savefile();

        void clear();

        std::vector<bool> get_intrinsics();
        std::string get_filename();
        std::vector<char> get_notes(); 
        int get_charisma(); 

        void set_filename(std::string & new_filename);
        void set_intrinics(std::vector<bool> & new_intrinsics);
        void set_notes(std::vector<char> & new_notes);
        void set_charisma(int new_charisma);

        void flip_active_state();
        bool is_active();
};

#endif