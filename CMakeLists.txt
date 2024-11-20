cmake_minimum_required(VERSION 3.28)


project(qosmit2d 
        VERSION 1.0.0
        LANGUAGES CXX
)

set(mExecutableTargetName qosmit)
set(mExecutableOutputName "Qosmit2D")

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory("dependencies")



file(GLOB_RECURSE mSourceFileList "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${mExecutableTargetName} ${mSourceFileList})
target_include_directories(${mExecutableTargetName} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(${mExecutableTargetName} PUBLIC ImGui-SFML::ImGui-SFML)
target_link_libraries(${mExecutableTargetName} PUBLIC fmt::fmt)
   


set_target_properties(${mExecutableTargetName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set_target_properties(${mExecutableTargetName} PROPERTIES OUTPUT_NAME ${mExecutableOutputName})