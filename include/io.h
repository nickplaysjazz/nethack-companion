#ifndef IO_H
#define IO_H

#include <string>
#include <nlohmann/json.hpp>

#include "savefile.h"

void delete_file(const std::string & filename);
std::vector<std::string> get_filenames(const std::string & dirname);
std::vector<std::string> get_filepaths(const std::string & dirname);
nlohmann::json get_json_data(const std::string & filename);
Savefile try_load_file(std::string & filename, Savefile & my_savefile);
int create_file(std::string filename);
void create_data_folder();

int save_file_json(const std::string & filename, Savefile & file_to_save);

#endif