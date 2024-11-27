#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> get_filenames(const std::string & dirname) {
    std::filesystem::path file_directory =  std::filesystem::current_path().append(dirname) ; 
    std::vector<std::string> filename_list; 
    for (const auto & file : std::filesystem::directory_iterator(file_directory)) {
        std::string filename = file.path().string(); 
        filename = filename.substr(filename.find(dirname) + dirname.length() + 1);
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

int load_file(const std::string & filename) {
    std::string line;
    std::ifstream my_file (filename);
    if (my_file.is_open()) {
        while (getline(my_file, line)) {
            std::cout<<line<<"\n";
        }
        my_file.close();
        return 0;
    } else {
        return 1; 
    }
    return 0; 
}

int save_file(const std::string & filename) {
    std::ofstream my_file;
    my_file.open(filename); 
    if (my_file.is_open()) {
        my_file<<"\ntesting write to a file";
        my_file.close();
        return 0;
    } else {
        return 1;
    }
}

int create_file(const std::string & filename) {
    std::ofstream my_file;
    std::filesystem::path file_directory =  std::filesystem::current_path().append("data") ; 
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