#ifndef SAVEFILE_H
#define SAVEFILE_H

#ifdef _WIN32
#include <ncurses/ncurses.h>
#elif __linux__
#include <curses.h>
#elif __APPLE__
#include <ncurses.h>
#endif

#include <vector>

#include "utilities.h"

class Savefile {
    private:
        std::vector<int> intrinsics;
        bool is_active_save = false;
        std::string filename; 
        int charisma;
        bool is_being_duped = false;

        std::vector<char> notes; 

    public:
        Savefile();

        void clear();

        std::vector<int> get_intrinsics();
        std::string get_filename();
        std::vector<char> get_notes(); 
        int get_charisma(); 

        void set_filename(std::string & new_filename);
        void set_intrinics(std::vector<int> & new_intrinsics);
        void set_notes(std::vector<char> & new_notes);
        void set_charisma(int new_charisma);
        void set_is_being_duped(bool in); 

        void flip_active_state();
        void flip_is_being_duped(); 

        bool get_is_being_duped(); 
        bool is_active();
};

#endif