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

set(ikonized_UIS
    optionsdlg.ui
)

qt5_wrap_ui(ikonized_UI_SRCS ${ikonized_UIS})
qt5_add_resources(ikonized_RC_SRCS ikonized.qrc)

add_executable(ikonized ${ikonized_SRCS} ${ikonized_UI_SRCS} ${ikonized_RC_SRCS})

target_include_directories(ikonized PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(ikonized
    Qt5::Widgets
    Qt5::Svg
    Qt5::X11Extras
    KF5::WindowSystem
    KF5::GlobalAccel
    KF5::I18n
    KF5::XmlGui
    KF5::WidgetsAddons
    KF5::ConfigCore
)

install(TARGETS ikonized DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
