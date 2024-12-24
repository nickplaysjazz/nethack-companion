#ifndef UTILITIES_H
#define UTILITIES_H

#include <array>
#include <string>

extern std::string ascii_title; 
int count_newlines(const std::string & input_string);
std::string num_to_alphabet(int input_num);
char keycode_to_char(int keycode); 

extern std::vector<int> legal_special_characters;
extern std::vector<std::string> properties_list;
extern std::array<int, 16> item_base_prices;
extern std::vector<std::vector<std::string>> items_by_prices; 
extern std::vector<std::string> xp_to_level;

extern std::vector<std::string> sokoban_1a;
extern std::vector<std::string> sokoban_1b;
extern std::vector<std::string> sokoban_2a;
extern std::vector<std::string> sokoban_2b;
extern std::vector<std::string> sokoban_3a;
extern std::vector<std::string> sokoban_3b;
extern std::vector<std::string> sokoban_4a;
extern std::vector<std::string> sokoban_4b;

#endif