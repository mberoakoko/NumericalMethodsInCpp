message(STATUS "Fetching SDL ...")
include(FetchContent)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-3.2.0
)

FetchContent_MakeAvailable(SDL3)