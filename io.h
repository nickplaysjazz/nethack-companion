#ifndef IO_H
#define IO_H

#include <string>

std::vector<std::string> get_filenames(const std::string & dirname);
int load_file(const std::string & filename);
int save_file(const std::string & filename);

#endif