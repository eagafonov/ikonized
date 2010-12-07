cmake_minimum_required(VERSION 2.6)
project(ikonized)
find_package(KDE4 4.3.2 REQUIRED)

add_subdirectory(src)
add_subdirectory(skins)

message(" * Install prefix is ${CMAKE_INSTALL_PREFIX}")
message(" * KIO libs: ${KDE4_KIO_LIBS}")
message(" * KDE UI libs: ${KDE4_KDEUI_LIBS}")


