set(TARGET tcp_echo)

set(SOURCES
    main.cpp
)

set(LIBRARIES
    networking
)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})
