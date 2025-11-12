# nethack-companion
A simple ASCII ncurses app to contain useful NetHack character information between runs.  

With this app, you can keep track of your characters' intrinsics, see a price ID table, take notes, practice Sokoban levels (including 3.7 flips/rotations), and more.

## Installation

On Windows devices, the NetHack Companion app is most easily compiled with a shell such as [MSYS2](https://www.msys2.org/). Linux and Mac users should be able to use their default terminal. 

The NetHack Companion uses CMake for consistent building. 

1) Install necessary prerequisite packages.

Install the following using a package manager such as [pacman](https://www.msys2.org/docs/package-management/) for MSYS2 and Arch Linux, [brew](https://brew.sh/) for Mac, or [apt-get](https://wiki.debian.org/AptCLI) on Debian Linux.
- A C/C++ compiler such as [gcc](https://www.gcc.gnu.org/) or [Clang](https://www.clang.llvm.org/).
- The [make](https://www.gnu.org/software/make) command.
- The [cmake](https://www.cmake.org/) command.
- The [ncurses](https://invisible-island.net/ncurses/) package.
- The [ncurses-dev](https://invisible-island.net/ncurses/) package.

2) Build the executable 

Navigate to the NetHack Companion app installation directory in your terminal, and build with the following commands:
```cmake .```
```make```

This should generate the NetHack_Companion executable.

## Contributing
Bug reports via GitHub's issues feature are welcome. When describing an issue, please include a minimal reproducible example, the expected behavior, and the actual behavior. 
Feature requests are also welcome.

## Acknowledgments 
Special thanks to: 

C0D3R1N0 : for code review, conceptualization, and testing

saundersresearch : for testing

The FIGlet ASCII font "Standard" was created by Glenn Chappell & Ian Chai 3/93 based on Frank's .sig. The font is used here under a BSD-3-Clause license. For more information, see http://www.figlet.org/. 

## TO DO
Version 1.0: 
- Handle resizing window, or preventing window resizing. (This may be impossible with ncurses, need to look into this)
- Better price list handling (if list is too long, it just spills onto a second table. Can we make it the table double-column instead?). 
- New submenu in lower middle-right: Prayer timeout counter with % chance
- Intrinsics improvements: add additional uncommon intrinsics in another menu (protection from shape changers, aggravate monsters, amphibiousness, conflict, food appraisal, hunger, jumping, unbreathing)

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
- Edible monster improvements (a little bit cleaner interface, maybe deliberately show a specific word/symbol when something is safe to eat)
