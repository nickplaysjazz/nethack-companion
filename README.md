# nethack-companion
ASCII-based NetHack companion app to contain useful character information between runs

## Installation

To use the NetHack Companion, you must build the files from source. You must first install [ncurses](https://invisible-mirror.net/archives/ncurses/). Then, compile using the following command (it is necessary that the flag "-lncursesw" is at the END of the list of flags):

```bash
g++ -o main.exe *.cpp -lncursesw
```

## TO DO
- FIX closing Menu with action handler. Need to fix how action handler should switch between different MenuActionHandlers whenever you want. 
- Handle resizing window (this might be impossible with PDCurses, need to look into this)
- Is not currently loading & saving data, but will create/delete files
- Journals: intrinsics, notes, ascension kit (user-defined?),
- Notes: message lookup, dangerous creatures (user-defined?), xp to level up, wand engraving, ring sink, shop lookup
- Date of run (?)

## Acknowledgments 
The FIGlet ASCII font "Standard" was created by Glenn Chappell & Ian Chai 3/93 based on Frank's .sig. The font is used here under a BSD-3-Clause license. For more information, see http://www.figlet.org/. 