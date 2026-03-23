add_library(sand_lib STATIC 
    core/World.cpp 
    core/CellRegistry.cpp
    core/Game.cpp
    core/GameState.cpp
    render/Camera.cpp
    render/TerminalRender.cpp
    cells/Cell.cpp
    cells/CellVoid.cpp
    cells/CellSand.cpp
    cells/CellAbstractFall.cpp
)

target_include_directories(sand_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(Threads REQUIRED)
target_link_libraries(sand_lib PRIVATE Threads::Threads)

add_executable(entropix main.cpp)
target_link_libraries(entropix PRIVATE sand_lib SDL3::SDL3)
