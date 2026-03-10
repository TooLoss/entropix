add_library(sand_lib STATIC 
    core/World.cpp 
    render/TerminalRender.cpp
    cells/Cell.cpp
)

target_include_directories(sand_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(Threads REQUIRED)
target_link_libraries(sand_lib PRIVATE Threads::Threads)

add_executable(SandApp main.cpp)
target_link_libraries(SandApp PRIVATE sand_lib)
