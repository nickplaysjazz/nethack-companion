cmake_minimum_required(VERSION 3.10)

project(NetHack_Companion VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wno-unused-parameter")

add_executable(${PROJECT_NAME} ${SOURCES} ${CMAKE_SOURCE_DIR}/assets/resources.rc)

if (MSYS OR MINGW)
    message(STATUS "Detected MSYS2/MinGW environment — linking with ncursesw")
    target_link_libraries(${PROJECT_NAME} ncursesw)
elseif (WIN32)
    message(STATUS "Detected native Windows environment — linking with ncursesw (Windows build)")
    target_link_libraries(${PROJECT_NAME} ncursesw)
elseif (UNIX)
    message(STATUS "Detected Unix-like system — linking with ncurses")
    target_link_libraries(${PROJECT_NAME} ncurses)
else()
    message(WARNING "Unknown platform — defaulting to ncurses")
    target_link_libraries(${PROJECT_NAME} ncurses)
endif()


if (EXISTS "C:/")
    message(STATUS "Windows-like filesystem: installing to Start Menu")
    message("${CMAKE_BINARY_DIR}")
    install(CODE "
        string(REPLACE \"\\\\\" \"\\\\\\\\\" escapedAppData \$ENV{APPDATA})
        string(REPLACE \"/c/\" \"C:/\" winBinaryDir ${CMAKE_BINARY_DIR})
        execute_process(
            COMMAND powershell -Command \"
                $shell = New-Object -ComObject WScript.Shell;
                $shortcut = $shell.CreateShortcut('\${escapedAppData}/Microsoft/Windows/Start Menu/Programs/NetHack Companion.lnk');
                $shortcut.TargetPath = '\${winBinaryDir}/NetHack_Companion.exe';
                $shortcut.Save();
            \"
        )
    ")
elseif (EXISTS "~/.local/share/applications")
    message(STATUS "Linux-like filesystem: installing to ~/.local/share/application")
    configure_file("${CMAKE_SOURCE_DIR}/assets/desktop.in" "${CMAKE_SOURCE_DIR}/assets/NetHack_Companion.desktop" @ONLY)
    install(PROGRAMS "${CMAKE_SOURCE_DIR}/assets/NetHack_Companion.desktop" DESTINATION ~/.local/share/applications)
endif()