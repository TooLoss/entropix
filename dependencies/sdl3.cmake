include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
    FIND_PACKAGE_ARGS NAMES SDL3
)

FetchContent_MakeAvailable(SDL3)
