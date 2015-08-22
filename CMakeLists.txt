cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME tris)
project(${PROJECT_NAME})

find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES}  ${CMAKE_CURRENT_BINARY_DIR})

include_directories(StruttureDati)
include_directories(Utils)
include_directories(Game)
include_directories(Gui)
include_directories(Gui/DialogUI)
include_directories(Gui/Widget)
include_directories(Gui/Widget/Decorators)
include_directories(ApplicationManager)

file(GLOB StruttureDati_CPP StruttureDati/*.cpp)
file(GLOB StruttureDati_H StruttureDati/*.h)

file(GLOB Utility_CPP Utils/*.cpp)
file(GLOB Utility_H Utils/*.h)

file(GLOB Game_CPP Game/*.cpp)
file(GLOB Game_H Game/*.h)

file(GLOB_RECURSE Gui_CPP  Gui/*.cpp)
file(GLOB_RECURSE Gui_H Gui/*.h)

file(GLOB Manager_CPP ApplicationManager/*.cpp)
file(GLOB Manager_H ApplicationManager/*.h)

qt4_wrap_cpp(tris_MOC ${StruttureDati_H} ${Utility_H} ${Game_H} ${Gui_H} ${Manager_H})

add_executable(${PROJECT_NAME} main.cpp GameFactory.cpp ${tris_MOC} ${StruttureDati_CPP} ${Utility_CPP} ${Game_CPP} ${Gui_CPP} ${Manager_CPP})
target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})