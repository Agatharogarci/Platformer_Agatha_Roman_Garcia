add_executable(Starter main.cpp
        include/game.h
        src/game.cpp
        include/player.h
        src/player.cpp
        include/constants.h
        include/sensor.h
        src/sensor.cpp
        include/physical_object.h
        src/physical_object.cpp
        include/contact.h
        include/enemy.h
        src/enemy.cpp
        include/menu.h
        src/menu.cpp
        include/health.h
        src/health.cpp
        include/game_over.h
        src/game_over.cpp
        include/win.h
        src/win.cpp
        include/settings.h
        include/win_flag.h
        src/win_flag.cpp
)

target_link_libraries(Starter PUBLIC SFML::Graphics SFML::Audio box2d::box2d)