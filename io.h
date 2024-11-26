#ifndef IO_H
#define IO_H

#include <string>

void delete_file(const std::string & filename);
std::vector<std::string> get_filenames(const std::string & dirname);
std::vector<std::string> get_filepaths(const std::string & dirname);
int load_file(const std::string & filename);
int save_file(const std::string & filename);

#endif