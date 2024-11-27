#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

extern std::string ascii_title; 
int count_newlines(const std::string & input_string);
std::string num_to_alphabet(int input_num);
char keycode_to_char(int keycode); 

extern std::vector<int> legal_special_characters;

#endif 