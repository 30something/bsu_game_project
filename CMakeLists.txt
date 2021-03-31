cmake_minimum_required(VERSION 3.10)
project(Death_Rally)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON) # Enable Qt MOC compiler
set(CMAKE_AUTORCC ON) # Enable Qt resources compiler
set(CMAKE_AUTOUIC ON) # Enable Qt UI compiler

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\")")
endif ()

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Widgets Multimedia)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Widgets Multimedia)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Widgets Qt5::Multimedia)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -O3")

set(SOURCES main.cpp
        src/View/view.cpp
        "src/Main window/main_window.cpp"
        src/Menu/menu.cpp
        src/GameCore/GameController.cpp
        src/EventsController/EventsController.cpp
        src/GameCore/car.cpp
        src/helpers/vec2f.cpp
        src/GameCore/wheel.cpp
        src/Menu/pause_menu.cpp
        src/Menu/small_exit_window.cpp
        src/helpers/line.cpp
        src/GameCore/map.cpp
        src/View/engine.cpp
        src/View/engine.h
        )

set(RESOURCES
        images.qrc
        map_data.qrc
        sounds.qrc)

add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
