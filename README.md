# nethack-companion
A simple ASCII ncurses app to contain useful NetHack character information between runs, updated for NetHack 5.0.

With this app, you can keep track of your character's intrinsics, see a price ID table, take notes, practice Sokoban levels (including flipped & rotated Sokoban levels), and more.

## Downloading
Pre-compiled executables for Windows, Mac, and Linux devices are available on the Release page on GitHub.

## Building from source
Follow these instructions only if you wish to compile an executable yourself. 

1) **Open a terminal.**
    - Windows devices: the NetHack Companion app is easily compiled with a shell such as MSYS2. Download [MSYS2](https://www.msys2.org/) and open the UCRT64 terminal. The package manager [pacman](https://www.msys2.org/docs/package-management/) should be installed.
    - MacOS devices: the default terminal should work. If you do not have it installed, [Homebrew](https://brew.sh/) is the standard package manager for Mac. In the terminal, run `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
    - Linux devices: the default terminal should work. For Debian Linux distributions, use the package manager [apt-get](https://wiki.debian.org/AptCLI). For Arch Linux, use the [pacman](https://www.msys2.org/docs/package-management/) package manager. For Red Hat-based Linux distributions, use the [DNF](https://rpm-software-management.github.io/) package manager.

2) **Install prerequisite packages.**
    - Windows devices: run the command `pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ncurses mingw-w64-ucrt-x86_64-pkg-config make`
    - MacOS devices: run the command `brew install cmake ncurses`
    - Linux devices: using the appropriate package manager, install the prerequisite packages. For apt-get, run `sudo apt update && sudo apt install -y build-essential cmake libncursesw5-dev`

3) **`mkdir build` if the directory does not exist. In the `build` subdirectory, build with `cmake ..` then `make`.**

    This should generate the NetHack_Companion executable.

4) **Optional: run `make install` to add a NetHack Companion shortcut.**

    On Windows, a NetHack Companion shortcut will be added to your Start Menu.

    On Linux, a NetHack Companion will be added to the Menu applet under the Games category.


## Contributing
Bug reports via GitHub's issues feature are welcome. When describing an issue, please include a minimal reproducible example, the expected behavior, and the actual behavior. 

Feature requests are also welcome.

## Acknowledgments 
Special thanks to: 

- C0D3R1N0 : for code review, conceptualization, testing, and asset creation
- saundersresearch : for testing

The FIGlet ASCII font "Standard" was created by Glenn Chappell & Ian Chai 3/93 based on Frank's .sig. The font is used here under a BSD-3-Clause license. For more information, see http://www.figlet.org/. 

The icon file nhc_icon.xpm utilizes modified tile files from the vanilla NetHack source code. These file are modified and used under the NetHack General Public License, a copy of which is included in the /assets/ directory as NH_LICENSE.

### To-Do
Beta release: 
- Pre-compiled binaries available via GitHub releases feature
- Icon not appearing on binaries? 

Suggested ideas: 
- Checklist: user can add items and check them off
- Intrinsics improvements: add'l uncommon intrinsics not now included (protection from shape changers, aggravate monsters, amphibiousness, conflict, food appraisal, hunger, jumping, unbreathing)
- Notes section improvements: functioning delete key, word bumps to next line when reaching end of line, typing/deleting before a set of words moves words, vertical scrolling. Consider using ncurses text widgets here.
- Sink ring ID table
- Help button with "?" that shows controls
- File handling improvements: ability to change filename, removing prepended spaces in file names, prevent overwriting of file names, include VAL-DWA-LAW-etc. notation somewhere (could also pregen intrinsics from this?)
- Input improvements: right now, lowercase & uppercase letters are handled separately
- Prayer timeout counter with % chance of success