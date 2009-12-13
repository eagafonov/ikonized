set(ikonized_SRCS
    sizer.cpp
    main.cpp)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

add_executable(ikonized ${ikonized_SRCS})

install(TARGETS ikonized DESTINATION ${DESTDIR}/bin)
