set(TARGET networking_tests)

set(SOURCES
    main.cpp
    http_request.cpp
)

set(LIBRARIES
    gtest::gtest

    networking
)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})

add_test(NAME ${TARGET} COMMAND ${TARGET})
