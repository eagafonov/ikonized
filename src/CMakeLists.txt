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

add_executable(ikonized ${ikonized_SRCS} ${ikonized_UIS} ikonized.qrc)

target_include_directories(ikonized PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(ikonized
    Qt6::Widgets
    Qt6::Svg
    Qt::GuiPrivate
    KF6::WindowSystem
    KF6::GlobalAccel
    KF6::I18n
    KF6::XmlGui
    KF6::WidgetsAddons
    KF6::ConfigCore
)

install(TARGETS ikonized DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
