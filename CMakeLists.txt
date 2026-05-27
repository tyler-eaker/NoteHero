cmake_minimum_required(VERSION 3.15)
project(NoteHero LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(raylib 
    GIT_REPOSITORY https://github.com/raysan5/raylib.git 
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(spdlog 
    GIT_REPOSITORY https://github.com/gabime/spdlog.git 
    GIT_TAG v1.14.1
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG master
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG main
)
FetchContent_MakeAvailable(rlimgui)

FetchContent_Declare(midifile
    GIT_REPOSITORY https://github.com/craigsapp/midifile.git
    GIT_TAG master
)
FetchContent_MakeAvailable(midifile)

file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/*.h"
)

set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${rlimgui_SOURCE_DIR}/rlImGui.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/inc
    ${imgui_SOURCE_DIR}
    ${rlimgui_SOURCE_DIR}
    ${midifile_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib 
    spdlog::spdlog 
)

if (MSVC)
    set(FMOD_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/lib/x64/fmod_vc.lib")
    set(FMOD_DLL "${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/lib/x64/fmod.dll")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE "${FMOD_LIB}")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${FMOD_DLL}"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)