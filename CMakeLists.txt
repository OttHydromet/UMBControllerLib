cmake_minimum_required(VERSION 3.1)
project(UmbControllerLib VERSION 0.4.0)

option(ENABLE_EXAMPLES "Build examples" ON)

set(LIB_NAME ${PROJECT_NAME})
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    # Raspberry Pi / ARM
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(LIB_NAME lib${LIB_NAME}Arm_32)
    else()
        set(LIB_NAME lib${LIB_NAME}Arm_64)
    endif()
else()
    # Intel
    if(UNIX)
        set(LIB_NAME lib${LIB_NAME})
    endif()
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        # x86
        set(LIB_NAME ${LIB_NAME}_32)
    endif()
endif()


if(UNIX)
    set(LIB_NAME ${LIB_NAME}.a)
else()
    set(LIB_NAME ${LIB_NAME}.lib)
endif()


add_library(${PROJECT_NAME} STATIC IMPORTED)
set_property(TARGET ${PROJECT_NAME} PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/${LIB_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)


if(ENABLE_EXAMPLES)
    add_subdirectory(example)
endif()
