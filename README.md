# nethack-companion
 ASCII-based NetHack companion app to contain useful character information between runs

## Installation

To use the NetHack Companion, you must build the files from source. You must first install [ncurses](https://invisible-mirror.net/archives/ncurses/). Then, compile using the following command (it is necessary that the flag "-lncursesw" is at the END of the list of flags):

```bash
g++ -o main.exe *.cpp -lncursesw
```

## TO DO
- Need generic Menu class from which ProfileMenu, MainMenu, etc. inherit from. Then you can override ActionHandlers, text generation, etc.
- New submenu button handling
- Handle resizing window
- Load and save data between runs, deleting characters
- Journals: intrinsics, notes, ascension kit (user-defined?),
- Notes: message lookup, dangerous creatures (user-defined?), xp to level up, wand engraving, ring sink, shop lookup
- Date of run (?)

## Acknowledgments 
The FIGlet ASCII font "Standard" was created by Glenn Chappell & Ian Chai 3/93 based on Frank's .sig. The font is used here under a BSD-3-Clause license. For more information, see http://www.figlet.org/. 