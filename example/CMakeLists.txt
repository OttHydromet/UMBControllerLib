if(WIN32)
    cmake_minimum_required(VERSION 3.21)
else()
    cmake_minimum_required(VERSION 3.1)
endif()
project(UmbControllerTest)

set(SOURCES
    UmbCtrlTest.cpp)

set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set(SOURCES ${SOURCES}
        ComWin.cpp
        win/serialport/SerialPort.cpp)

    set(INCLUDES ${INCLUDES}
        win
        win/pthread
        win/serialport)
elseif(UNIX)
    set(SOURCES ${SOURCES}
        ComLinux.cpp)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

target_link_libraries(${PROJECT_NAME} PRIVATE UmbControllerLib)
if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message("Build using MSVC compiler")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 -D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -D_CRT_SECURE_NO_WARNINGS")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message("Build using GNU compiler")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")
endif()

if(WIN32)
    # copy required DLLs to output folder
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()
