cmake_minimum_required(VERSION 3.16)
project(mk2d_demo CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Busca SFML; si no está, lo trae con FetchContent ---
set(SFML_MIN_VER 2.5)
find_package(SFML ${SFML_MIN_VER} COMPONENTS graphics window system audio CONFIG QUIET)
if(NOT SFML_FOUND)
  message(STATUS "SFML no encontrado, descargando SFML 2.6.1 con FetchContent...")
  include(FetchContent)
  FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
  )
  FetchContent_MakeAvailable(SFML)
endif()


# --- Fetch ImGui-SFML (brings ImGui too) ---
include(FetchContent)
FetchContent_Declare(
  imgui_sfml
  GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml.git
  GIT_TAG v2.6
)
FetchContent_MakeAvailable(imgui_sfml)

file(GLOB_RECURSE SRC_FILES
  src/Core/*.cpp src/Graphics/*.cpp src/UI/*.cpp
  src/Track/*.cpp src/Entities/*.cpp src/AI/*.cpp src/App.cpp)

add_executable(MarioKart2D ${SRC_FILES})
target_include_directories(MarioKart2D PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(MarioKart2D PRIVATE sfml-graphics sfml-window sfml-system sfml-audio ImGui-SFML::ImGui-SFML)

# Windows: fix unresolved WinMain (LNK2019)
if(WIN32)
  target_link_libraries(MarioKart2D PRIVATE sfml-main)
endif()

# Copy local assets next to the binary after build (if user places them in mk2d_demo/assets)
add_custom_command(TARGET MarioKart2D POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:MarioKart2D>/assets
  COMMENT "Copying assets folder to build output (if present)")
