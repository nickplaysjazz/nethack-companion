#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "savefile.h"

std::vector<std::string> get_filenames(const std::string & dirname) {
        std::filesystem::path file_directory =  std::filesystem::current_path().append(dirname) ; 
        std::vector<std::string> filename_list; 
        for (const auto & file : std::filesystem::directory_iterator(file_directory)) {
            std::string filename = file.path().string(); 
            filename = filename.substr(filename.find(dirname) + dirname.length() + 1);
            std::size_t pos_to_erase = filename.find(".dat");
            // ignore if file is not .dat
            try {
                filename.erase(pos_to_erase);
            } catch (std::out_of_range const&) {
                std::cout<<"Unrecognized file "<<filename<< "!"<<std::endl;
                continue;
            }
            filename_list.push_back(filename);
        }
    return filename_list;
}

std::vector<std::string> get_filepaths(const std::string & dirname) {
    std::filesystem::path file_directory =  std::filesystem::current_path().append(dirname) ; 
    std::vector<std::string> filepath_list; 
    for (const auto & file : std::filesystem::directory_iterator(file_directory)) {
        std::string filename = file.path().string(); 
        filepath_list.push_back(filename);
    }
    return filepath_list;
}

Savefile try_load_file(std::string & filename, Savefile & my_savefile) {
    std::string line;
    std::ifstream my_file (filename);

    std::filesystem::path full_filename =  std::filesystem::current_path().append("data").append(filename); 

    my_file.open(full_filename);
    
    if (my_file.is_open()) {
        if (!std::filesystem::is_empty(full_filename)) {
            int line_no = 0; 
            while (getline(my_file, line)) {
                if (line_no == 0) {
                    // intrinsics
                    std::vector<int> list;

                    for (int i = 0; i < (int)line.length(); ++i) {
                        if (line[i] == '1')  {
                            list.push_back(1);
                        } else if (line[i] == '0') {
                            list.push_back(0);
                        } else if (line[i] == '2') {
                            list.push_back(2);
                        }
                    }

                    my_savefile.set_intrinics(list);
                } else if (line_no == 1) {
                    // notes
                    std::vector<char> notes_l; 
                    for (int i = 0; i < (int)line.length(); ++i) {
                        char cstr = line[i];
                        notes_l.push_back(cstr);
                    }
                    my_savefile.set_notes(notes_l);
                } else if (line_no == 2) {
                    // price ID
                    std::vector<int> price_v;
                    for (int i = 0; i <= (int)line.length(); ++i) {
                        int cstr = line[i];
                        price_v.push_back(cstr);
                    }
                    std::vector<int> digits;
                    for (int i = 0; i <= (int)price_v.size(); ++i) {
                        if (price_v[i] == 0) {
                            break;
                        } 
                        digits.push_back(price_v[i] - int('0'));
                    }

                    if (digits.size() == 1) {
                        int cha = digits[0];
                        my_savefile.set_charisma(cha);
                    } else {
                        int cha = digits[1];
                        if (digits[0] == 2) {
                            cha = cha + 20;
                        } else if (digits[0] == 1) {
                            cha = cha + 10;
                        } else {
                            cha = 0;
                        }
                        my_savefile.set_charisma(cha);
                    }                    
                } else if (line_no == 3) {
                    //being duped
                    bool is_duping;
                    for (int i = 0; i < (int)line.length(); ++i) {
                        if (line[i] == '1')  {
                            is_duping = true;
                        } else if (line[i] == '0') {
                            is_duping = false; 
                        }
                    }
                    my_savefile.set_is_being_duped(is_duping); 
                }
                ++line_no; 
            }
        }
        my_file.close();

        my_savefile.flip_active_state();
        std::string my_loc_name = "data\\";
        my_savefile.set_filename(my_loc_name.append(filename));

        return my_savefile;
    } else {
        throw std::invalid_argument("Cannot open desired file " + filename + "!!");
    }
}

int save_file(const std::string & filename, Savefile & file_to_save) {
    std::ofstream my_file;
    my_file.open(filename, std::ofstream::out | std::ofstream::trunc); 
    if (my_file.is_open()) {
        // intrinsics
        std::vector<int> file_intrinsics = file_to_save.get_intrinsics();
        for (int i = 0; i < (int)properties_list.size(); ++i) {
            my_file<<file_intrinsics[i]<<" ";
        }        
        my_file<<std::endl;
        // notes
        std::vector<char> file_notes = file_to_save.get_notes();
        for (int i = 0; i < (int)file_notes.size(); ++i) {
            my_file<<file_notes[i];
        }
        my_file<<std::endl;
        // price ID
        my_file<<std::to_string(file_to_save.get_charisma());
        my_file<<std::endl;
        // is_duped
        my_file<<file_to_save.get_is_being_duped(); 
        my_file.close();
        return 0;
    } else {
        return 1; 
    }
}

int create_file(std::string filename) {
    std::ofstream my_file;
    std::filesystem::path file_directory =  std::filesystem::current_path().append("data"); 
    filename = filename.append(".dat");
    my_file.open(file_directory.append(filename));
    if (my_file.is_open()) {
        my_file.close();
        return 0; 
    }
    else {
        return 1;
    }
}

void delete_file(const std::string & filename) {
    std::remove(filename.c_str());
}

void create_data_folder() {
    const std::string folderName = "data";
    std::filesystem::path folderPath = folderName;

    if (std::filesystem::exists(folderPath) && std::filesystem::is_directory(folderPath)) {
        return;
    } else {
        std::filesystem::create_directory(folderPath);
    }
}