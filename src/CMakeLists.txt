set(TARGET networking)

set(SOURCES
    net/socket.cpp
)

set(INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(LIBRARIES
    Ws2_32
)

add_library(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE ${INCLUDE})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})

set(UTILITY main)

set(UTILITY_SOURCES
    main.cpp
)

set(UTILITY_INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(LIBRARIES
    ${TARGET}
)

add_executable(${UTILITY} ${UTILITY_SOURCES})
target_include_directories(${UTILITY} PRIVATE ${UTILITY_INCLUDE})
target_link_libraries(${UTILITY} PRIVATE ${TARGET})
