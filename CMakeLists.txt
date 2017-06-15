cmake_minimum_required (VERSION 3.8)

project (HyperConsole CXX)

set (CXX_FLAGS_EXTRA "-std=c++14")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    #set (CMAKE_CXX_COMPILER "clang++")
endif ()

set (CMAKE_MACOSX_RPATH 1)

# Set some nicer output dirs.
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Add path for custom CMake modules.
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

include_directories (${CMAKE_SOURCE_DIR}/include)

message (STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message (STATUS "System processor: ${CMAKE_SYSTEM_PROCESSOR}")
message (STATUS "System version: ${CMAKE_SYSTEM_VERSION}")

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build. Options are 'Debug' and 'Release'."
        FORCE
    )
endif ()

string (TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)

message (STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set (HYPER_LINK_FLAGS_ "$ENV{LDFLAGS}")

#string (REGEX REPLACE "^ +" "" HYPER_LINK_FLAGS ${HYPER_LINK_FLAGS_})

set (CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set (CMAKE_CXX_FLAGS_DEBUG   "-g3 -ggdb -fno-inline -Wextra -Wno-unused-parameter -DDEBUG ${CXX_FLAGS_EXTRA}")
set (CMAKE_CXX_FLAGS_RELEASE "-O3 -fomit-frame-pointer ${CXX_FLAGS_EXTRA}")

enable_testing ()

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (test)

