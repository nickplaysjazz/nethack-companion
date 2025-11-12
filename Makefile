all:
	g++ -Wall -Wextra -Werror -o NetHack_Companion.exe src/*.cpp -I/include/*.h -lncurses -Wno-unused-parameter -std=c++17
