cmake_minimum_required(VERSION 3.10)
project(Death_Rally)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\")")
endif ()

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Widgets Network)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Widgets Qt5::Network)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -O0")

set(SOURCES
        main.cpp
        src/View/view.cpp
        "src/Main window/main_window.cpp"
        src/Menu/menu.cpp
        src/GameCore/game_controller.cpp
        src/EventsController/events_controller.cpp
        src/GameCore/GameObjects/car.cpp
        src/helpers/vec2f.cpp
        src/GameCore/GameObjects/wheel.cpp
        src/Menu/pause_menu.cpp
        src/Menu/small_exit_window.cpp
        src/Menu/settings.cpp
        src/Menu/small_exit_window.cpp
        src/GameCore/game_map.cpp
        src/Menu/game_mode_selector.cpp
        src/Menu/map_selector_tile.cpp
        src/GameCore/weapon_handler.cpp
        src/helpers/json_map_parser.cpp
        src/helpers/physics.cpp
        src/GameCore/GameObjects/bonus.cpp
        src/GameCore/GameObjects/game_object.cpp
        src/GameCore/GameObjects/mine.cpp
        src/GameCore/Behaviors/behavior.cpp
        src/GameCore/Behaviors/first_player_behavior.cpp
        src/GameCore/Behaviors/second_player_behavior.cpp
        src/GameCore/Behaviors/bot_behavior.cpp
        src/GameCore/input_controller.cpp
        src/helpers/pixmap_loader.cpp
        src/Menu/end_game_stats.cpp
        src/View/view_info_updater.cpp
        src/helpers/cars_data.cpp
        src/Network/network_player.cpp
        src/Network/network_room.cpp
        src/Network/player_tile.cpp
        src/Network/network_controller.cpp
        src/helpers/map_data.cpp
        src/GameCore/Behaviors/network_player_behavior.cpp)

set(RESOURCES
        images.qrc
        map_data.qrc
        )

set(SERVER_SOURCES
        src/Server/main.cpp
        src/Network/network_player.cpp
        src/Server/server_controller.cpp
        src/helpers/vec2f.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})
add_executable(Death_Rally_Server ${SERVER_SOURCES})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(Death_Rally_Server ${REQUIRED_LIBS_QUALIFIED})
