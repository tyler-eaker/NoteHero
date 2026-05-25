cmake_minimum_required(VERSION 3.20)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(NoteHero CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    midifile
    GIT_REPOSITORY https://github.com/craigsapp/midifile.git
    GIT_TAG master
)
FetchContent_MakeAvailable(midifile)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
    rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG main
)
FetchContent_MakeAvailable(rlimgui)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.14.1
)
FetchContent_MakeAvailable(spdlog)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    src/Engine.cpp
    src/States.cpp
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${rlimgui_SOURCE_DIR}/rlImGui.cpp
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    ${imgui_SOURCE_DIR}
    ${midifile_SOURCE_DIR}/include
    ${rlimgui_SOURCE_DIR}
    external/fmod/inc
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(FMOD_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/lib/x64/fmod_vc.lib")
    set(FMOD_DLL "${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/lib/x64/fmod.dll")
else()
    set(FMOD_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/lib/x86/fmod_vc.lib")
    set(FMOD_DLL "${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/lib/x86/fmod.dll")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    midifile
    spdlog::spdlog
    ${FMOD_LIB}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${FMOD_DLL}"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)