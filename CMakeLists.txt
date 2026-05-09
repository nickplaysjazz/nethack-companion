cmake_minimum_required(VERSION 3.11)

# Might need to include RC for windows icon
project(NetHack_Companion VERSION 1.0.0 LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

# nlohmann_json package
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

# add resource file to the sources list if on Windows/MSYS
if(WIN32 OR MSYS)
    list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/resources.rc")
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

# add assets folder as directory to get nhc_icon.ico
if(WIN32 OR MSYS)
    target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/assets")
endif()

# Copy assets folder to build directory
# Kind of a workaround for now
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
    COMMENT "Copying assets to build directory"
)

# Static linking -- needed to avoid .dll issues on Windows
if(WIN32)
    add_definitions(-DNCURSES_STATIC)
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
    set(PKG_CONFIG_ARGN "--static")
endif()

# and finally some necessary linking for ncurses
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