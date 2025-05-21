cmake_minimum_required(VERSION  3.22.1)
project(NumericalMethodsInCpp)

set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

include(FetchContent)
FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git GIT_TAG df8e9e16110b305479a875399cee13daa0ccadd9)
FetchContent_MakeAvailable(glad)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        # docking-latest
        GIT_TAG docking
)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/sdl)

## Find dependencies
find_package(OpenGL)
find_package(glfw3 REQUIRED)

add_executable(NumericalMethodsInCpp main.cpp)

target_include_directories(NumericalMethodsInCpp
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(NumericalMethodsInCpp
        # PRIVATE project_warnings
        # Added SDL2::SDL2 and imgui here.
        PUBLIC SDL3::SDL3 imgui)



