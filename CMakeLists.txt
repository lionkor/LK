cmake_minimum_required(VERSION 3.15)

option(LK_BUILD_EXAMPLES "Build LK example programs" ON)
option(LK_BUILD_TESTS "Build LK unit tests" ON)
option(LK_ENABLE_ASSERT "Keep enabled unless you know what you're doing" ON)

project(LK
        VERSION 0.1.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_VERSION 17)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
endif ()

add_library(LK SHARED
        include/LK/Version.h src/Version.cpp
        include/LK/Types.h
        include/LK/Meta.h
        include/LK/CString.h src/CString.cpp
        include/LK/Assert.h
        include/LK/UnitTest.h
        src/UnitTest.cpp)

target_include_directories(LK PUBLIC ${CMAKE_SOURCE_DIR}/include)

if (UNIX)
    target_compile_definitions(LK PRIVATE -DLK_VERSION="${CMAKE_PROJECT_VERSION}" -DLK_BUILDING_DLL)
    if (LK_ENABLE_ASSERT)
        target_compile_definitions(LK PRIVATE -DLK_ENABLE_ASSERT=true)
    endif ()
endif ()

if (LK_BUILD_EXAMPLES)
    add_executable(example1 examples/example1.cpp)
    target_link_libraries(example1 LK)
endif ()
if (LK_BUILD_TESTS)
    add_executable(test_cstring tests/Test_CString.cpp)
    target_link_libraries(test_cstring LK)
endif ()
