# nethack-companion
ASCII-based NetHack companion app to contain useful character information between runs

## Installation

To use the NetHack Companion, you must build the files from source. You must first install [ncurses](https://invisible-mirror.net/archives/ncurses/) using MinGW for Windows. Then, compile using the following command (it is necessary that the flag "-lncursesw" is at the END of the list of flags):

```bash
g++ -o main.exe *.cpp -lncursesw
```

## TO DO
- Handle resizing window (this might be impossible with PDCurses, need to look into this)
- Ability to create a checklist? 
- Notes section: better handling (delete key, word wrap-around, typing before a set of words pushes those words, etc.). Could even do vertical scrolling. We can also allow periods, colons, etc here, just not in filenames.  
- Various menus: message lookup, dangerous creatures (user-defined?), xp to level up, wand engraving, ring sink, shop lookup
- Price list by charisma. Better handling of runoff into second window (can't see heading, can't go backwards)
- Date of run (?)
- Input file improvements: Checksum on input file, Binary file for inputs instead, maybe json? Need to use istream 
- Make it so that you cannot create a file with solely spaces
- Hit ? at any time and a menu appears with controls
- Change filename, perhaps with VAL-DWA-LAW etc notation. Could also pregen intrinsics from this? 

## Acknowledgments 
The FIGlet ASCII font "Standard" was created by Glenn Chappell & Ian Chai 3/93 based on Frank's .sig. The font is used here under a BSD-3-Clause license. For more information, see http://www.figlet.org/. 