include(FetchContent)

set(SFML_VERSION 2.6.2)
set(IMGUI_VERSION 1.87)
set(IMGUI_SFML_VERSION 2.6)
set(FMT_VERSION 11.0.2)


FetchContent_Declare(
    fmt
    URL "https://github.com/fmtlib/fmt/archive/refs/tags/${FMT_VERSION}.zip"
)


FetchContent_Declare(
    SFML
    URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)

FetchContent_Declare(
    imgui
    URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
)


FetchContent_Declare(
    imgui-sfml
    URL "https://github.com/SFML/imgui-sfml/archive/refs/tags/v${IMGUI_SFML_VERSION}.zip"
)



# fmt
FetchContent_MakeAvailable(fmt)


# SFML
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

# Dear ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)

FetchContent_MakeAvailable(imgui-sfml)