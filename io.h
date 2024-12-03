#ifndef IO_H
#define IO_H

#include <string>

#include "savefile.h"

void delete_file(const std::string & filename);
std::vector<std::string> get_filenames(const std::string & dirname);
std::vector<std::string> get_filepaths(const std::string & dirname);
Savefile try_load_file(const std::string & filename, Savefile & my_savefile);
int save_file(const std::string & filename, Savefile & file_to_save);
int create_file(std::string filename);

#endif