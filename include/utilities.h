#ifndef UTILITIES_H
#define UTILITIES_H

#include <array>
#include <cctype>
#include <string>

int count_newlines(const std::string & input_string);
std::string num_to_alphabet(int input_num);
char keycode_to_char(int keycode); 
void make_str_lowercase(std::string & input_string);

const extern std::string ascii_title;
const extern std::vector<int> legal_special_characters;
const extern std::vector<int> notes_special_characters;
const extern std::vector<std::string> properties_list;
const extern std::vector<std::string> xp_to_level;
const extern std::vector<std::string> engrave_list;

const extern std::vector<std::string> sokoban_1a;
const extern std::vector<std::string> sokoban_1b;
const extern std::vector<std::string> sokoban_2a;
const extern std::vector<std::string> sokoban_2b;
const extern std::vector<std::string> sokoban_3a;
const extern std::vector<std::string> sokoban_3b;
const extern std::vector<std::string> sokoban_4a;
const extern std::vector<std::string> sokoban_4b;

#endif