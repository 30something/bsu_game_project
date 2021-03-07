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
set(REQUIRED_LIBS Core Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Widgets)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -O3")

set(SOURCES main.cpp src/view.cpp src/view.h
        src/main_window.cpp src/main_window.h src/menu.cpp src/menu.h
        src/model.cpp src/model.h src/controller.cpp src/controller.h
        src/car.cpp src/car.h images.qrc helpers/vec2f.cpp helpers/vec2f.h src/wheel.h)


add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
