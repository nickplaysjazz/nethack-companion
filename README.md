# nethack-companion
ASCII ncurses-based NetHack companion to contain useful character information between runs. 

The app will save/load profiles with your characters' intrinsics, a price ID table, a notes section, and a Sokoban practice. 

## Installation

Currently, the NetHack Companion has only been tested on Windows devices. There are two options to use this app:

1) Build files from source (RECOMMENDED)
First, install [MinGW-w64] (https://www.mingw-w64.org/). 
Next, install [ncurses](https://invisible-island.net/ncurses/) using MinGW for Windows. 
Then, navigate to the NetHack Companion app installation directory in your cmd terminal, and compile using the following command:

```bash
g++ -o NetHack_Companion.exe *.cpp -lncursesw -Wall
```

To compile the executable to run natively on other Windows systems without others needing to install MinGW or ncurses, the following command may work, but it is still being tested:

```bash
g++ -I/mingw64/include/ncurses -o NetHack_Companion.exe -g *.cpp -lncursesw -L/mingw64/bin -DNCURSES_STATIC
```

2) Download .exe file directly (NOT RECOMMENDED/SUPPORTED - still testing)
First, download the pre-compiled .exe (NOT provided yet, still testing!)
This file has only been reported to run with the .dll files of an ncurses installation present in the working directory of the .exe file. I cannot distribute these .dll files. As such, this installation method is currently not recommended or supported. 
Creating a working .exe file is still in progress. 

## Contributing
Bug reports via GitHub's issues feature are welcome. When describing an issue, please include a minimal reproducible example, the expected behavior, and the actual behavior. 
Feature requests are also welcome.

## Acknowledgments 
Special thanks to Coderino for conceptualization, code review, and testing. 

The FIGlet ASCII font "Standard" was created by Glenn Chappell & Ian Chai 3/93 based on Frank's .sig. The font is used here under a BSD-3-Clause license. For more information, see http://www.figlet.org/. 

## TO DO
Version 1.0: 
- Handle resizing window, or preventing window resizing. (This may be impossible with ncurses, need to look into this)
- New menu accessed in lower middle-left: List of edible/inedible creatures (and add'l effects on eating)
- Better price list handling (if list is too long, it just spills onto a second table. Can we make it the table double-column instead?). 
- New submenu in lower middle-right: Prayer timeout counter with % chance
- Intrinsics improvements: add additional uncommon intrinsics in another menu. Add counters instead of binaries for protection, speed

Stretch goals:
- Checklist -- user can add items and check them off? 
- Better notes section handling (functioning delete key, word bumps to next line when reaching end of line, typing/deleting before a set of words moves words, maybe even vertical scrolling, etc.)
- NetHack message lookup menu (maybe just 'you feel' & 'you hear' messages?)
- Sink ring ID table
- Display start date of run
- Speedrun timer
- Input file improvements (use checksum on input file, use binary file for inputs/maybe json, use istream c++ features)
- Create help button with "?" that shows controls
- Ability to change filename. Chop off prepended spaces in file names. Prevent overwriting of file names. 
- Perhaps name can include the NetHack VAL-DWA-LAW-etc. notation. Could also pregen intrinsics from this? 
- Handle capital keyboard inputs versus lowercase?
- C++ improvements: use constexpr on utilities, use arrays instead of only vectors, double-check passing by copying in functions

