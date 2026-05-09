#include "../include/terminal.h"
#include <cstdio>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void set_terminal_size() {
    const int COLS = 110;
    const int ROWS = 32;

#ifdef _WIN32
    HWND console = GetConsoleWindow();
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFO cfi;
    COORD fontSize;
    RECT r;
    
    GetWindowRect(console, &r);
    if (GetCurrentConsoleFont(hOut, FALSE, &cfi))
        fontSize = GetConsoleFontSize(hOut, cfi.nFont);

    // Set buffer and window size
    COORD bufferSize = {COLS, ROWS};
    SetConsoleScreenBufferSize(hOut, bufferSize);
    
    SMALL_RECT windowSize = {0, 0, COLS - 1, ROWS - 1};
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
    
    // Resize the window itself (adding offsets for decorations)
    MoveWindow(console, r.left, r.top, fontSize.X * (COLS + 5), fontSize.Y * (ROWS + 3), TRUE);

#else
    // Linux and macOS: use ANSI escape sequence to resize terminal
    // Format: ESC ] 0 ; title BEL is for title, but we use CSI 8 for terminal size
    // CSI 8 ; rows ; cols t
    printf("\033[8;%d;%dt", ROWS, COLS);
    fflush(stdout);
#endif
}
