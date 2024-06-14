add_compile_definitions(LIB_EXPORTS)

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

add_library(${TARGET} SHARED ${SOURCES})
target_link_libraries(${TARGET} PRIVATE ${LIBRARIES})
