set(TARGET networking_tests)

set(SOURCES
    main.cpp
)

set(LIBRARIES
    gtest::gtest

    networking
)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})

enable_testing()
add_test(NAME ${TARGET} COMMAND ${TARGET})
