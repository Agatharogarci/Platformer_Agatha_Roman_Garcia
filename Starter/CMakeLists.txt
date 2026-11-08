add_executable(Starter main.cpp
        include/game.h
        src/game.cpp
        include/player.h
        src/player.cpp
        include/constants.h)

target_link_libraries(Starter PUBLIC SFML::Graphics SFML::Audio)