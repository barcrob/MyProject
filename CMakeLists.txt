cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME tris)
project(${PROJECT_NAME})

find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES}  ${CMAKE_CURRENT_BINARY_DIR})

include_directories(StruttureDati)
include_directories(Utils)
include_directories(Game)

file(GLOB StruttureDati_CPP StruttureDati/*.cpp)
file(GLOB StruttureDati_H StruttureDati/*.h)

file(GLOB Utility_CPP Utils/*.cpp)
file(GLOB Utility_H Utils/*.h)

file(GLOB Game_CPP Game/*.cpp)
file(GLOB Game_H Game/*.h)

qt4_automoc(${StruttureDati_CPP} ${Utility_CPP} ${Game_CPP})

add_executable(${PROJECT_NAME} main.cpp GameFactory.cpp ${StruttureDati_CPP} ${Utility_CPP} ${Game_CPP})
target_link_libraries(${PROJECT_NAME} ${QT_QTCORE_LIBRARY})