all:
	g++ -Wall -Wextra -Werror -o NetHack_Companion.exe src/*.cpp -I/include/*.h -lncursesw -Wno-unused-parameter -std=c++17
