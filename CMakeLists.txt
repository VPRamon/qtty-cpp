cmake_minimum_required(VERSION 3.15)
project(qtty_cpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Cargo for building Rust library
find_program(CARGO_BIN cargo REQUIRED)

# Paths to qtty-ffi
set(QTTY_SUBMODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qtty)
set(QTTY_FFI_INCLUDE_DIR ${QTTY_SUBMODULE_DIR}/qtty-ffi/include)
set(QTTY_ARTIFACT_DIR ${QTTY_SUBMODULE_DIR}/target/release)

# Platform-specific library paths
if(APPLE)
    set(QTTY_LIBRARY_PATH ${QTTY_ARTIFACT_DIR}/libqtty_ffi.dylib)
elseif(WIN32)
    set(QTTY_LIBRARY_PATH ${QTTY_ARTIFACT_DIR}/qtty_ffi.dll)
    set(QTTY_IMPORT_LIBRARY ${QTTY_ARTIFACT_DIR}/qtty_ffi.dll.lib)
else()
    set(QTTY_LIBRARY_PATH ${QTTY_ARTIFACT_DIR}/libqtty_ffi.so)
endif()

# Build qtty-ffi via Cargo
add_custom_target(
    build_qtty_ffi
    COMMAND ${CARGO_BIN} build -p qtty-ffi --release
    WORKING_DIRECTORY ${QTTY_SUBMODULE_DIR}
    BYPRODUCTS ${QTTY_LIBRARY_PATH}
    COMMENT "Building qtty-ffi library via Cargo"
    VERBATIM
)

# Import qtty-ffi as a library target
add_library(qtty_ffi SHARED IMPORTED GLOBAL)
set_target_properties(qtty_ffi PROPERTIES IMPORTED_LOCATION ${QTTY_LIBRARY_PATH})
if(WIN32)
    set_target_properties(qtty_ffi PROPERTIES IMPORTED_IMPLIB ${QTTY_IMPORT_LIBRARY})
endif()
add_dependencies(qtty_ffi build_qtty_ffi)

# Header-only C++ wrapper library
add_library(qtty_cpp INTERFACE)
target_include_directories(qtty_cpp INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${QTTY_FFI_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(qtty_cpp INTERFACE qtty_ffi)

# Set RPATH for runtime library location
if(APPLE)
    set(_qtty_rpath "@loader_path/../qtty/target/release")
elseif(UNIX)
    set(_qtty_rpath "$ORIGIN/../qtty/target/release")
endif()

# Google Test integration
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Examples
add_executable(demo examples/demo.cpp)
target_link_libraries(demo PRIVATE qtty_cpp)
if(DEFINED _qtty_rpath)
    set_target_properties(demo PROPERTIES 
        BUILD_RPATH ${_qtty_rpath}
        INSTALL_RPATH ${_qtty_rpath}
    )
endif()

# Test executables with Google Test
add_executable(test_ffi tests/test_ffi.cpp)
target_link_libraries(test_ffi PRIVATE qtty_cpp GTest::gtest_main)
if(DEFINED _qtty_rpath)
    set_target_properties(test_ffi PROPERTIES 
        BUILD_RPATH ${_qtty_rpath}
        INSTALL_RPATH ${_qtty_rpath}
    )
endif()

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(test_ffi)

# Installation rules
install(DIRECTORY include/qtty 
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)

install(DIRECTORY ${QTTY_FFI_INCLUDE_DIR}/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Generate unit files (if needed)
add_custom_target(
    gen_units
    COMMAND ${CARGO_BIN} run -p qtty-ffi --bin gen_units
    WORKING_DIRECTORY ${QTTY_SUBMODULE_DIR}
    COMMENT "Generating unit files"
    VERBATIM
)
