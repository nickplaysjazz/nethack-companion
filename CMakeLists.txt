cmake_minimum_required(VERSION 3.11)

project(NetHack_Companion VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/include.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_MakeAvailable(json)
    add_library(nlohmann_json INTERFACE)
    target_include_directories(nlohmann_json INTERFACE ${json_SOURCE_DIR}/include)
endif()

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS "-g")

if(WIN32)
    set(RESOURCE_FILE ${CMAKE_SOURCE_DIR}/assets/resources.rc)
else()
    set(RESOURCE_FILE "")
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCE_FILE})

# Copy assets folder to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets to build directory"
)

if(WIN32)
    add_definitions(-DNCURSES_STATIC)
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
    set(PKG_CONFIG_ARGN "--static")
endif()

find_package(PkgConfig REQUIRED)
if (WIN32 OR MSYS)
    pkg_check_modules(NCURSES REQUIRED ncursesw)
    link_directories(${NCURSES_LIBRARY_DIRS})
else()
    pkg_check_modules(NCURSES REQUIRED ncurses)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${NCURSES_LIBRARIES} 
    nlohmann_json
    $<$<PLATFORM_ID:Windows>:psapi>
)
target_include_directories(${PROJECT_NAME} PRIVATE ${NCURSES_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${NCURSES_CFLAGS_OTHER})
target_link_options(${PROJECT_NAME} PRIVATE ${NCURSES_LDFLAGS_OTHER})

#if (EXISTS "C:/")
#     message(STATUS "Windows-like filesystem: installing to Start Menu")
#     message("${CMAKE_BINARY_DIR}")
#     install(CODE "
#         string(REPLACE \"\\\\\" \"\\\\\\\\\" escapedAppData \$ENV{APPDATA})
#         string(REPLACE \"/c/\" \"C:/\" winBinaryDir ${CMAKE_BINARY_DIR})
#         execute_process(
#             COMMAND powershell -Command \"
#                 $shell = New-Object -ComObject WScript.Shell;
#                 $shortcut = $shell.CreateShortcut('\${escapedAppData}/Microsoft/Windows/Start Menu/Programs/NetHack Companion.lnk');
#                 $shortcut.TargetPath = '\${winBinaryDir}/NetHack_Companion.exe';
#                 $shortcut.Save();
#             \"
#         )
#     ")
# elseif (EXISTS "/home/")
#     message(STATUS "Linux-like filesystem: installing to ~/.local/share/application")
#     configure_file("${CMAKE_SOURCE_DIR}/assets/desktop.in" "${CMAKE_SOURCE_DIR}/assets/NetHack_Companion.desktop" @ONLY)
#     install(PROGRAMS "${CMAKE_SOURCE_DIR}/assets/NetHack_Companion.desktop" DESTINATION ~/.local/share/applications)
# endif()