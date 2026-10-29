add_executable(Starter main.cpp
        include/game.h
        src/game.cpp)

target_link_libraries(Starter PUBLIC SFML::Graphics)