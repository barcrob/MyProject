cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME tris)
project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE Debug)

set(QT_QMAKE_EXECUTABLE /usr/local/Trolltech/Qt-4.8.7/bin/qmake)

find_package(Qt4 REQUIRED)
if (NOT ${QT4_FOUND} STREQUAL "YES" AND NOT STREQUAL "TRUE")
	message(FATAL_ERROR "Package Qt4 required configure enviroment variable!")
	exit()
endif(NOT ${QT4_FOUND} STREQUAL "YES" AND NOT STREQUAL "TRUE")

include_directories(${QT_INCLUDES}  ${CMAKE_CURRENT_BINARY_DIR})

include_directories(StruttureDati)
include_directories(Utils)
include_directories(Game/public)
include_directories(Game/src)
include_directories(Gui)
include_directories(Gui/DialogUI)
include_directories(Gui/Widget)
include_directories(Gui/Widget/Decorators)
include_directories(ApplicationManager)

file(GLOB StruttureDati_CPP StruttureDati/*.cpp)
file(GLOB StruttureDati_H StruttureDati/*.h)

file(GLOB Utility_CPP Utils/*.cpp)
file(GLOB Utility_H Utils/*.h)

file(GLOB_RECURSE Game_CPP Game/*.cpp)
file(GLOB_RECURSE Game_H Game/*.h)

file(GLOB_RECURSE Gui_CPP  Gui/*.cpp)
file(GLOB_RECURSE Gui_H Gui/*.h)

file(GLOB Manager_CPP ApplicationManager/*.cpp)
file(GLOB Manager_H ApplicationManager/*.h)

qt4_wrap_cpp(tris_MOC ${StruttureDati_H} ${Utility_H} ${Game_H} ${Gui_H} ${Manager_H})

add_executable(${PROJECT_NAME} main.cpp ${tris_MOC} ${StruttureDati_CPP} ${Utility_CPP} ${Game_CPP} ${Gui_CPP} ${Manager_CPP})
target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})