add_executable(Starter main.cpp
        include/game.h
        src/game.cpp
        include/player.h
        src/player.cpp
        include/constants.h
        include/sensor.h
        src/sensor.cpp
        include/physical_object.h)

target_link_libraries(Starter PUBLIC SFML::Graphics SFML::Audio box2d::box2d)