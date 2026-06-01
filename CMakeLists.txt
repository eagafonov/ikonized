cmake_minimum_required(VERSION 3.16)
project(ikonized)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(Qt5 REQUIRED COMPONENTS Widgets Svg X11Extras)
find_package(KF5 REQUIRED COMPONENTS WindowSystem GlobalAccel I18n XmlGui WidgetsAddons Config)

add_subdirectory(src)
add_subdirectory(skins)

message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
