set(ikonized_SRCS
    sizer.cpp
    main.cpp
    ikonized.cpp
    windowinfo.cpp
    mainwindow.cpp
    optionsdlg.cpp
    settings.cpp
    skinsimple.cpp
    skinsvg.cpp
)

KDE4_MOC_HEADERS(
    windowinfo.h
    mainwindow.h
    optionsdlg.h
    settings.h
)

KDE4_ADD_UI_FILES(ikonized_SRCS
    optionsdlg.ui
)

# kde4_automoc( ${ikonized_SRCS} )

add_definitions(-O0 -g)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

KDE4_ADD_EXECUTABLE(ikonized ${ikonized_SRCS})
# add_executable(ikonized ${ikonized_SRCS})
target_link_libraries(ikonized ${KDE4_KDEUI_LIBS})

install(TARGETS ikonized DESTINATION ${DESTDIR}/bin)
