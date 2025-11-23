#ifdef _WIN32
#include <ncurses/ncurses.h>
#elif __linux__
#include <ncurses.h>
#elif __APPLE__
#include <ncurses.h>
#endif

#include <algorithm>
#include <array>
#include <cctype>
#include <string>
#include <vector>

#include "../include/utilities.h"

const std::string ascii_title = 
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
    if (input_num >= 0 && input_num <= 25)
        return std::string(1, static_cast<char>(input_num+97));
    else
        return "!! ERROR !!";
}

char keycode_to_char(int keycode) {
    return static_cast<char>(keycode);
}

void make_str_lowercase(std::string & input_string) {
    std::transform(input_string.begin(), input_string.end(), input_string.begin(), [](unsigned char c){ return std::tolower(c); });
}

const std::vector<int> legal_special_characters = {
    32,33,35,36,37,38,39,40,41,43,44,45,59,61,64,91,93,94,95,96,123,125,126
};
const std::vector<int> notes_special_characters = {
    32,33,63,64,35,36,37,94,38,42,40,41,95,45,43,61,91,93,123,125,124,92,58,59,39,34,60,62,44,46,47,96,126
};

// important intrinsics & extrinsics
const std::vector<std::string> properties_list = {
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

const std::vector<std::string> xp_to_level = {
    "Lvl 1    0",
    "Lvl 2    20",
    "Lvl 3    40",
    "Lvl 4    80",
    "Lvl 5    160",
    "Lvl 6    320",
    "Lvl 7    640",
    "Lvl 8    1,280",
    "Lvl 9    2,560",
    "Lvl 10   5,120",
    "Lvl 11   10,000",
    "Lvl 12   20,000",
    "Lvl 13   40,000",
    "Lvl 14   80,000",
    "Lvl 15   160,000",
    "Lvl 16   320,000",
    "Lvl 17   640,000",
    "Lvl 18   1,280,000",
    "Lvl 19   2,560,000",
    "Lvl 20   5,120,000",
    "Lvl 21   10,000,000",
    "Lvl 22   20,000,000",
    "Lvl 23   30,000,000",
    "Lvl 24   40,000,000",
    "Lvl 25   50,000,000",
    "Lvl 26   60,000,000",
    "Lvl 27   70,000,000",
    "Lvl 28   80,000,000",
    "Lvl 29   90,000,000",
    "Lvl 30   100,000,000"
};

const std::vector<std::string> engrave_list = {
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

const std::vector<std::string> sokoban_1a = {
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

const std::vector<std::string> sokoban_1b = {
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

const std::vector<std::string> sokoban_2a = {
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

const std::vector<std::string> sokoban_2b = {
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

const std::vector<std::string> sokoban_3a = {
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

const std::vector<std::string> sokoban_3b = {
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

const std::vector<std::string> sokoban_4a = {
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

const std::vector<std::string> sokoban_4b = {
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
    "     -------     -------  "
};