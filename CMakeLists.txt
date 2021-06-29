cmake_minimum_required(VERSION 3.15)

option(LK_BUILD_EXAMPLES "Build LK example programs" ON)
option(LK_BUILD_TESTS "Build LK unit tests" ON)
option(LK_ENABLE_ASSERT "Keep enabled unless you know what you're doing" ON)
option(LK_ENABLE_STD_EXCEPTION "Make all exceptions inherit from std::exception" OFF)

project(LK
        VERSION 0.2.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
endif ()

add_library(LK SHARED
        include/LK/Version.h src/Version.cpp
        include/LK/Types.h
        include/LK/Meta.h
        include/LK/CString.h src/CString.cpp
        include/LK/Assert.h src/Assert.cpp
        include/LK/UnitTest.h src/UnitTest.cpp
        include/LK/Buffer.h
        include/LK/Algorithms.h
        include/LK/Human.h src/Human.cpp
        include/LK/Array.h
        include/LK/Exception.h src/Exception.cpp)

target_include_directories(LK PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_definitions(LK PRIVATE -DLK_VERSION="${CMAKE_PROJECT_VERSION}" -DLK_BUILDING_DLL)
if (UNIX)
    if (LK_ENABLE_ASSERT)
        target_compile_definitions(LK PRIVATE -DLK_ENABLE_ASSERT=true)
    endif ()
    if (LK_ENABLE_STD_EXCEPTION)
        target_compile_definitions(LK PRIVATE -DLK_ENABLE_STD_EXCEPTION=true)
    endif ()
endif ()

if (LK_BUILD_EXAMPLES)
    add_executable(example1 examples/example1.cpp)
    target_link_libraries(example1 LK)
endif ()
if (LK_BUILD_TESTS)
    add_executable(test_cstring tests/Test_CString.cpp)
    target_link_libraries(test_cstring LK)
    add_executable(test_buffer tests/Test_Buffer.cpp)
    target_link_libraries(test_buffer LK)
    add_executable(test_array tests/Test_Array.cpp)
    target_link_libraries(test_array LK)
endif ()
