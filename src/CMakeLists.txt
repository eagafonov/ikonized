set(ikonized_SRCS
    main.cpp)

add_executable(ikonized ${ikonized_SRCS})

install(TARGETS ikonized DESTINATION ${DESTDIR}/bin)
