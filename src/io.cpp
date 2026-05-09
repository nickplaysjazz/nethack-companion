#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <cstdlib>
#ifdef _WIN32
#include <libloaderapi.h>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#endif
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#include "../include/savefile.h"
#include "../include/embedded_assets.h"

std::filesystem::path get_exe_path() {
    #ifdef _WIN32
    char exeStr[MAX_PATH];
    GetModuleFileNameA(NULL, exeStr, MAX_PATH);

    #elif defined(__linux__)
    char exeStr[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", exeStr, PATH_MAX - 1);
    if (count != -1) exeStr[count] = '\0';
    
    #elif defined(__APPLE__)
    char exeStr[1024];
    uint32_t size = sizeof(exeStr);
    _NSGetExecutablePath(exeStr, &size);
    
    #else
    // unknown platforms
    return std::filesystem::current_path();
    #endif

    return std::filesystem::path(exeStr).parent_path();
}

std::filesystem::path get_data_path() {
    std::filesystem::path dataPath;

    #ifdef _WIN32
    const char* appdata = std::getenv("APPDATA");
    if (appdata != nullptr) {
        dataPath = std::filesystem::path(appdata) / "nethack-companion";
    } else {
        dataPath = std::filesystem::path(std::getenv("USERPROFILE")) / "AppData" / "Roaming" / "nethack-companion";
    }

    #elif defined(__APPLE__)
    const char* home = std::getenv("HOME");
    if (home != nullptr) {
        dataPath = std::filesystem::path(home) / "Library" / "Application Support" / "nethack-companion";
    } else {
        dataPath = std::filesystem::path("/tmp/nethack-companion");
    }

    #elif defined(__linux__)
    const char* xdgDataHome = std::getenv("XDG_DATA_HOME");
    if (xdgDataHome != nullptr) {
        dataPath = std::filesystem::path(xdgDataHome) / "nethack-companion";
    } else {
        const char* home = std::getenv("HOME");
        if (home != nullptr) {
            dataPath = std::filesystem::path(home) / ".local" / "share" / "nethack-companion";
        } else {
            dataPath = std::filesystem::path("/tmp/nethack-companion");
        }
    }

    #else
    // Unknown platform, fallback to current directory
    dataPath = std::filesystem::current_path() / "nethack-companion";
    #endif

    return dataPath;
}

std::filesystem::path get_root_path() {
    return std::filesystem::path(__FILE__).parent_path().parent_path();
}

std::vector<std::string> get_filenames(const std::string & dirname) {
        std::filesystem::path file_directory = get_data_path() / dirname; 
        std::vector<std::string> filename_list; 
        for (const auto & file : std::filesystem::directory_iterator(file_directory)) {
            std::string filename = file.path().string(); 
            filename = filename.substr(filename.find(dirname) + dirname.length() + 1);
            std::size_t pos_to_erase = filename.find(".json");
            // ignore if file is not .json
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

    std::filesystem::path file_directory = get_data_path() / dirname; 
    std::vector<std::string> filepath_list; 
    for (const auto & file : std::filesystem::directory_iterator(file_directory)) {
        std::string filename = file.path().string(); 
        filepath_list.push_back(filename);
    }
    return filepath_list;
}

nlohmann::json get_json_data(const std::string & filename) {
    if (auto embedded_json = embedded_assets::get_embedded_json(filename); !embedded_json.empty()) {
        return nlohmann::json::parse(std::string(embedded_json));
    }

    std::filesystem::path asset_path = get_data_path() / filename;
    return nlohmann::json::parse(std::ifstream(asset_path));
}

void initialize_assets() {
    std::filesystem::path src_assets = get_exe_path() / "assets";
    std::filesystem::path dst_assets = get_data_path() / "assets";
    
    if (!std::filesystem::exists(dst_assets)) {
        try {
            if (!std::filesystem::exists(src_assets)) {
                // JSON assets are embedded into the executable, so missing source assets
                // is not fatal for run-time JSON loading.
                return;
            }

            std::filesystem::copy(src_assets, dst_assets, 
                std::filesystem::copy_options::recursive | 
                std::filesystem::copy_options::overwrite_existing);
            std::cout << "Assets initialized to: " << dst_assets << std::endl;
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Warning: Failed to copy assets: " << e.what() << std::endl;
        }
    }
}

Savefile try_load_file(std::string & filename, Savefile & my_savefile) {
    std::string line;
    std::ifstream my_file (filename);

    std::filesystem::path full_filename = get_data_path() / "data" / filename; 

    my_file.open(full_filename);
    
    if (my_file.is_open()) {
        if (!std::filesystem::is_empty(full_filename)) {
            nlohmann::json data = get_json_data(full_filename.string());

            std::vector<int> intr = data["intrinsics"].get<std::vector<int>>();
            my_savefile.set_intrinics(intr);
            my_savefile.set_charisma(data["charisma"]);
            my_savefile.set_is_being_duped(data["is_being_duped"]);
            std::vector<char> note = data["notes"].get<std::vector<char>>();
            my_savefile.set_notes(note);
            my_savefile.set_active_price_ID(data["active_price_ID"]);
        } else {
            // bandaid fix to prevent crashes on linux & mac
            // for some reason the intrinsics are not initialized properly and so we just hard-code them to be zero
            // this only loads when the file is blank, so we aren't overriding anything
            std::vector<int> n_list (properties_list.size(), 0);
            my_savefile.set_intrinics(n_list);
        }
        my_file.close();

        my_savefile.flip_active_state();
        my_savefile.set_filename(filename);

        return my_savefile;
    } else {
        throw std::invalid_argument("Cannot open desired file " + filename + "!!");
    }
}

int create_file(std::string filename) {
    std::ofstream my_file;
    std::filesystem::path file_directory = get_data_path() / "data"; 
    filename = filename.append(".json");
    my_file.open(file_directory / filename);
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
    std::filesystem::path folderPath = get_data_path() / "data";
    
    if (std::filesystem::exists(folderPath) && std::filesystem::is_directory(folderPath)) {
        return;
    } else {
        std::filesystem::create_directories(folderPath);
    }
}

int save_file_json(const std::string & filename, Savefile & file_to_save) {
    nlohmann::json jsonfile;
    jsonfile["intrinsics"] = file_to_save.get_intrinsics();
    jsonfile["notes"] = file_to_save.get_notes();
    jsonfile["charisma"] = file_to_save.get_charisma();
    jsonfile["is_being_duped"] = file_to_save.get_is_being_duped();
    jsonfile["active_price_ID"] = file_to_save.get_active_price_ID();

    std::ofstream my_file;
    my_file.open(get_data_path() / "data" / filename, std::ofstream::out | std::ofstream::trunc);
    if (my_file.is_open()) {
        my_file << jsonfile;
        my_file.close();
        return 0;
    } else {
        return 1; 
    }
}