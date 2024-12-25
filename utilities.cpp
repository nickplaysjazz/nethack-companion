#include <algorithm>
#include <array>
#include <ncurses/curses.h>
#include <string>
#include <vector>

#include "utilities.h"

std::string ascii_title = 
                        "                                       nickplaysjazz's                                        \n"
                        " _   _      _   _   _            _       ____                                  _             \n"
                        "| \\ | | ___| |_| | | | __ _  ___| | __  / ___|___  _ __ ___  _ __   __ _ _ __ (_) ___  _ __   \n"
                        "|  \\| |/ _ \\ __| |_| |/ _` |/ __| |/ / | |   / _ \\| '_ ` _ \\| '_ \\ / _` | '_ \\| |/ _ \\| '_ \\  \n"
                        "| |\\  |  __/ |_|  _  | (_| | (__|   <  | |__| (_) | | | | | | |_) | (_| | | | | | (_) | | | | \n"
                        "|_| \\_|\\___|\\__|_| |_|\\__,_|\\___|_|\\_\\  \\____\\___/|_| |_| |_| .__/ \\__,_|_| |_|_|\\___/|_| |_| \n"
                        "                                                            |_|                               ";

int count_newlines(const std::string & input_string) {
    int num_newlines = std::count(input_string.begin(), input_string.end(), '\n');

    return num_newlines;
}

std::string num_to_alphabet(int input_num) {
    switch (input_num) {
        case 0: return "a";
        case 1: return "b";
        case 2: return "c";
        case 3: return "d";
        case 4: return "e";
        case 5: return "f";
        case 6: return "g";
        case 7: return "h";
        case 8: return "i";
        case 9: return "j";
        case 10: return "k";
        case 11: return "l";
        case 12: return "m";
        case 13: return "n";
        case 14: return "o";
        case 15: return "p";
        case 16: return "q";
        case 17: return "r";
        case 18: return "s";
        case 19: return "t";
        case 20: return "u";
        case 21: return "v";
        case 22: return "w";
        case 23: return "x";
        case 24: return "y";
        case 25: return "z";
        default: return "!! ERROR !!";
    }
}

char keycode_to_char(int keycode) {
    switch (keycode) {
        case int('a'): return 'a';
        case int('b'): return 'b';
        case int('c'): return 'c';
        case int('d'): return 'd';
        case int('e'): return 'e';
        case int('f'): return 'f';
        case int('g'): return 'g';
        case int('h'): return 'h';
        case int('i'): return 'i';
        case int('j'): return 'j';
        case int('k'): return 'k';
        case int('l'): return 'l';
        case int('m'): return 'm';
        case int('n'): return 'n';
        case int('o'): return 'o';
        case int('p'): return 'p';
        case int('q'): return 'q';
        case int('r'): return 'r';
        case int('s'): return 's';
        case int('t'): return 't';
        case int('u'): return 'u';
        case int('v'): return 'v';
        case int('w'): return 'w';
        case int('x'): return 'x';
        case int('y'): return 'y';
        case int('z'): return 'z';

        case int('A'): return 'A';
        case int('B'): return 'B';
        case int('C'): return 'C';
        case int('D'): return 'D';
        case int('E'): return 'E';
        case int('F'): return 'F';
        case int('G'): return 'G';
        case int('H'): return 'H';
        case int('I'): return 'I';
        case int('J'): return 'J';
        case int('K'): return 'K';
        case int('L'): return 'L';
        case int('M'): return 'M';
        case int('N'): return 'N';
        case int('O'): return 'O';
        case int('P'): return 'P';
        case int('Q'): return 'Q';
        case int('R'): return 'R';
        case int('S'): return 'S';
        case int('T'): return 'T';
        case int('U'): return 'U';
        case int('V'): return 'V';
        case int('W'): return 'W';
        case int('X'): return 'X';
        case int('Y'): return 'Y';
        case int('Z'): return 'Z';

        case int('0'): return '0';
        case int('1'): return '1';
        case int('2'): return '2';
        case int('3'): return '3';
        case int('4'): return '4';
        case int('5'): return '5';
        case int('6'): return '6';
        case int('7'): return '7';
        case int('8'): return '8';
        case int('9'): return '9';

        case 32: return ' '; 
        case 33: return '!';
        case 63: return '?'; //
        case 64: return '@';
        case 35: return '#';
        case 36: return '$';
        case 37: return '%';
        case 94: return '^';
        case 38: return '&'; 
        case 42: return '*'; //
        case 40: return '(';
        case 41: return ')';
        case 95: return '_';
        case 45: return '-';
        case 43: return '+';
        case 61: return '=';
        case 91: return '[';
        case 93: return ']';
        case 123: return '{';
        case 125: return '}';
        case 124: return '|'; //
        case 92: return '\\'; //
        case 58: return ':'; //
        case 59: return ';';
        case 39: return '\'';
        case 34: return '"'; //
        case 60: return '<'; //
        case 62: return '>'; //
        case 44: return ',';
        case 46: return '.'; //
        case 47: return '/'; //
        case 96: return '`';
        case 126: return '~';

        default: return ' ';
    }
}

std::vector<int> legal_special_characters = {32,33,35,36,37,38,39,40,41,43,44,45,59,61,64,91,93,94,95,96,123,125,126};
std::vector<int> notes_special_characters = {32,33,63,64,35,36,37,94,38,42,40,41,95,45,43,61,91,93,123,125,124,92,58,59,39,34,60,62,44,46,47,96,126};

// important intrinsics & extrinsics
std::vector<std::string> properties_list = {
    //	"aggravate monster",
    //	"amphibiousness",
    "cold resistance",
    //	"conflict",
    "disintegration resist.",
    "fire resistance",
    //	"food appraisal",
    //	"hunger",
    "infravision",
    "invisible",
    //	"jumping",
    "levitation",
    "magic resistance",
    "magic cancellation",
    "poison resistance",
    "polymorph control",
    "polymorphitis",
    "protection",
    //	"protection from shape changers",
    "reflection",
    "regeneration",
    "searching",
    "see invisible",
    "shock resistance",
    "sleep resistance",
    "speed",
    "stealth",
    "telepathy",
    "teleport control",
    "teleportitis",
    //	"unbreathing",
    "warning"
};

std::array<int, 16> item_base_prices = {8, 20, 30, 50, 60, 80, 100, 150, 175, 200, 250, 300, 400, 500, 600, 700};

std::vector<std::vector<std::string>> items_by_prices = {
    {"Armor:",
     "     elven boots",
     "     kicking boots"},
    {"Scrolls:",
     "     identify"},
    {"Armor:",
     "     fumble boots",
     "     levitation boots"},
    {"Armor:",
     "     jumping boots",
     "     speed boots",
     "     water walking boots",
     "     cloak of protection",
     "Scrolls:",
     "     light",
     "Potions:", 
     "     booze",
     "     fruit juice",
     "     see invisible", 
     "     sickness"},
    {"Armor:", 
     "     cloak of invisibility",
     "     cloak of magic resistance",
     "Scrolls:",
     "     enchant weapon"},
    {"Scrolls:",
     "     enchant armor",
     "     remove curse"},
    {"Scrolls:",
     "     confuse monster",
     "     destroy armor",
     "     fire",
     "     food detection",
     "     gold detection",
     "     magic mapping",
     "     scare monster",
     "     teleportation", 
     "Potions:",
     "     confusion",
     "     extra healing",
     "     hallucination",
     "     healing",
     "     restore ability",
     "     sleeping",
     "Rings:",
     "     adornment",
     "     hunger",
     "     protection",
     "     protection from shape changers",
     "     stealth",
     "     sustain ability",
     "     warning",
     "Wands:",
     "     light",
     "     nothing",
     "Spellbooks:",
     "     force bolt",
     "     protection", 
     "     detect monsters",
     "     light",
     "     sleep",
     "     jumping",
     "     healing",
     "     knock"},
     {"Potions:",
     "     blindness",
     "     gain energy", 
     "     invisibility",
     "     monster detection", 
     "     object detection",
     "Rings:",
     "     aggravate monster",
     "     cold resistance",
     "     gain constitution",
     "     gain strength", 
     "     increase accuracy",
     "     increase damage", 
     "     invisibility", 
     "     poison resistance", 
     "     see invisibile",
     "     shock resistance",
     "Wands:",
     "     aggravate monster",
     "     cold resistance",
     "     gain constitution",
     "     gain strength", 
     "     increase accuracy", 
     "     increase damage",
     "     invisibility",
     "     poison resistance",
     "     see invisible", 
     "     shock resistance"},
     {"Wands:",
     "     cold",
     "     fire",
     "     lightning", 
     "     sleep"},
     {"Scrolls:",
     "     amnesia",
     "     create monster",
     "     earth", 
     "     taming", 
     "Potions:",
     "     enlightenment",
     "     full healing", 
     "     levitation",
     "     polymorph",
     "     speed",
     "Rings:",
     "     fire resistance",
     "     free action", 
     "     levitation", 
     "     regeneration", 
     "     searching",
     "     slow digestion", 
     "     teleportation",
     "Wands:", 
     "     fire resistance",
     "     free action", 
     "     levitation",
     "     regeneration",
     "     searching", 
     "     slow digestion",
     "     teleportation",
     "Spellbooks:",
     "     drain life",
     "     magic missile",
     "     create monster", 
     "     detect food", 
     "     confuse monster", 
     "     slow monster", 
     "     cure blindness",
     "     wizard lock"},
     {"Potions:",
     "     acid",
     "     oil"},
     {"Scrolls:",
     "     charging",
     "     genocide",
     "     punishment",
     "     stinking cloud",
     "Potions:",
     "     charging",
     "     genocide", 
     "     punishment",
     "     stinking cloud",
     "Rings:",
     "     conflict",
     "     polymorph",
     "     polymorph control",
     "     teleport control",
     "Spellbooks:",
     "     remove curse",
     "     clairvoyance",
     "     detect unseen",
     "     identify",
     "     cause fear",
     "     charm monster",
     "     haste self",
     "     cure sickness",
     "     extra healing",
     "     stone to flesh"},
     {"Spellbooks:",
     "     cone of cold",
     "     fireball",
     "     detect treasure",
     "     invisibility",
     "     levitation",
     "     restore ability"},
     {"Wands:",
     "     death",
     "     wishing",
     "Spellbooks:",
     "     magic mapping",
     "     dig"},
     {"Spellbooks:",
     "     create familiar",
     "     turn undead",
     "     teleport away",
     "     polymorph"},
     {"Spellbooks:",
     "     finger of death",
     "     cancellation"}
};

std::vector<std::string> xp_to_level = {
    "Lvl 1    0", "Lvl 2    20", "Lvl 3    40", "Lvl 4    80", "Lvl 5    160", "Lvl 6    320", "Lvl 7    640", "Lvl 8    1,280", "Lvl 9    2,560", "Lvl 10   5,120", 
    "Lvl 11   10,000", "Lvl 12   20,000", "Lvl 13   40,000", "Lvl 14   80,000", "Lvl 15   160,000", "Lvl 16   320,000", "Lvl 17   640,000", "Lvl 18   1,280,000", 
    "Lvl 19   2,560,000", "Lvl 20   5,120,000", "Lvl 21   10,000,000", "Lvl 22   20,000,000", "Lvl 23   30,000,000", "Lvl 24   40,000,000", "Lvl 25   50,000,000", 
    "Lvl 26   60,000,000", "Lvl 27   70,000,000", "Lvl 28   80,000,000", "Lvl 29   90,000,000", "Lvl 30   100,000,000"
};

std::vector<std::string> engrave_list = {
    "A few ice cubes drop from the wand. ........................... cold",
    "A lit field surrounds you! .................................... light",
    "Gravel flies up from the floor! ............................... digging",
    "Lightning arcs from the wand. You are blinded by the flash! ... lightning",
    "No message or effect. ......................................... locking",
    "                                                                nothing ",
    "                                                                opening ",
    "                                                                probing ",
    "                                                                secret door detection ",
    "                                                                undead turning ",
    "                                                                wand is cancelled (x:-1) ",
    "The <floor> is riddled by bullet holes! ....................... magic missile",
    "The bugs on the <floor> slow down! ............................ slow monster",
    "The bugs on the <floor> speed up! ............................. speed monster",
    "The bugs on the <floor> stop moving! .......................... death",
    "                                                                sleep",
    "The engraving now reads: <random message> * ................... polymorph",
    "The engraving on the <floor> vanishes! * ...................... cancellation",
    "                              (if existing engraving is burned) cold",
    "                                                                make invisible",
    "                        (engraving is moved elsewhere in level) teleportation",
    "The wand is too worn out to engrave. .......................... wand is exhausted (x:0)",
    "The wand unsuccessfully fights your attempt to write! ......... striking",
    "",
    "                          * No message if no existing engraving ",
    "        Note that wands of digging, fire, and lightning self-ID "
    //"This <wand> is a wand of digging! ............................. digging",
    //"This <wand> is a wand of fire! ................................ fire",
    //"This <wand> is a wand of lightning! ........................... lightning",
};

std::vector<std::string> sokoban_1a = {
    "-------- ------ ",
    "|<|>...---....| ",
    "|^|-.00....0..| ",
    "|^||..00|.0.0.| ",
    "|^||....|.....| ",
    "|^|------0----| ",
    "|^|    |......| ",
    "|^------......| ",
    "|..^^^^0000...| ",
    "|..-----......| ",
    "----   -------- "
};

std::vector<std::string> sokoban_1b = {
    "------  ----- ",
    "|....|  |...| ",
    "|.0..----.0.| ",
    "|.0......0..| ",
    "|..--->---0.| ",
    "|---------.---",
    "|..^^^<|.....|",
    "|..----|0....|",
    "--^|   |.0...|",
    " |^-----.0...|",
    " |..^^^^0.0..|",
    " |..----------",
    " ----         "
};

std::vector<std::string> sokoban_2a = {
" ----          -----------",
"--.>--------   |.........|",
"|..........|   |.........|",
"|.0-----0-.|   |.........|",
"|..|...|.0.|   |....<....|",
"|.0.0....0-|   |.........|",
"|.0..0..|..|   |.........|",
"|.----0.--.|   |.........|",
"|..0...0.|.--  |.........|",
"|.---0-...0.------------.|",
"|...|..0-.0.^^^^^^^^^^^^.|",
"|..0......----------------",
"-----..|..|               ", 
"    -------               "
};

std::vector<std::string> sokoban_2b = {
"-----------       -----------",
"|....|....---     |.........|",
"|..00|00...>|     |.........|",
"|.....0...---     |.........|",
"|....|....|       |....<....|",
"|-.---------      |.........|",
"|..0.|.....|      |.........|",
"|.00.|0.0.0|      |.........|",
"|..0.....0.|      |.........|",
"|.000|0..0.----------------.|",
"|....|..0.0.^^^^^^^^^^^^^^^.|",
"-----------------------------"
};

std::vector<std::string> sokoban_3a = {
"  --------          ",  
"---.|....|          ",   
"|...0....|----------", 
"|.-.00-00|.|.......|", 
"|.00-......|.......|", 
"|.-..0.|...|.......|", 
"|....-0--0-|...<...|", 
"|..00..0...|.......|", 
"|.--...|...|.......|", 
"|....-0|---|.......|", 
"---..0.-----------.|", 
"  |..0>^^^^^^^^^^^.|", 
"  ------------------"
};

std::vector<std::string> sokoban_3b = {
"--------------------",
"|........|...|.....|",
"|.00..-00|.-.|.....|",
"|..|.0.0.|00.|.....|",
"|-.|..-..|.-.|..<..|",
"|...--.......|.....|",
"|...|.0.-...-|.....|", 
"|.0.|0.|...--|.....|", 
"|-0.|..-----------.|", 
"|..0....^^^^^^^^^^.|", 
"|...|.>-------------", 
"--------            "
};

std::vector<std::string> sokoban_4a = {
"--------------------------",
"|>......^^^^^^^^^^^^^^^^.|",
"|.......----------------.|",
"-------.------         |.|",
" |...........|         |.|",
" |.0.0.0.0.0.|         |.|",
"--------.----|         |.|",
"|...0.0..0.0.|         |.|",
"|...0........|         |.|",
"-----.--------   ------|.|",
" |..0.0.0...|  --|.....|.|",
" |.....0....|  |.......|.|",
" |.0.0...0.--  |-|.....|.|",
"-------.----   |<........|",
"|..0.....|     |-|.....|--",
"|........|     |.......|  ",
"|...------     --|.....|  ",
"-----            -------  "
};

std::vector<std::string> sokoban_4b = {
"  ------------------------",
"  |..^^^^^^^^^^^^^^^^^^..|",
"  |..-------------------.|",
"----.|    -----        |.|",
"|..|0--  --...|        |.|",
"|.....|--|.0..|        |.|",
"|.00..|..|..0.|        |.|",
"--..00|...00.--        |.|",
" |0..0...|0..|   ------|.|",
" |.00.|..|..0| --|.....|.|",
" |.0.0---|.0.| |.......|.|",
" |.......|..-- |-|.....|.|",
" ----.0..|.--  |<........|",
"    ---.--.|   |-|.....|--",
"     |.0...|   |.......|  ",
"     |>.|..|   --|.....|  ",
"     -------     -------  ",
};