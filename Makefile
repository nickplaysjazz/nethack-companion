all:
	g++ -Wall -Wextra -Werror -o NetHack_Companion.exe *.cpp -lncursesw -Wno-unused-parameter
