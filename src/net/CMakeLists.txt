set(TARGET networking)

set(SOURCES
    socket.cpp
)

set(LIBRARIES)

if(WIN32)
    list(APPEND LIBRARIES
        Ws2_32
    )
endif()

add_library(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})
