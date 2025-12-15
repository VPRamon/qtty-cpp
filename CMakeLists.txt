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

# Generate C++ unit wrappers from qtty_ffi.h
find_package(Python3 COMPONENTS Interpreter REQUIRED)
set(QTTY_FFI_HEADER ${QTTY_FFI_INCLUDE_DIR}/qtty_ffi.h)
set(GENERATED_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qtty/units/length.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qtty/units/time.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qtty/units/angular.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qtty/units/mass.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qtty/units/power.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qtty/literals.hpp
)

add_custom_command(
    OUTPUT ${GENERATED_HEADERS}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/gen_cpp_units.py
    DEPENDS ${QTTY_FFI_HEADER} ${CMAKE_CURRENT_SOURCE_DIR}/gen_cpp_units.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating C++ unit wrappers from qtty_ffi.h"
    VERBATIM
)

add_custom_target(
    gen_cpp_units
    DEPENDS ${GENERATED_HEADERS}
)

# Build qtty-ffi via Cargo
add_custom_target(
    build_qtty_ffi
    COMMAND ${CARGO_BIN} build -p qtty-ffi --release
    WORKING_DIRECTORY ${QTTY_SUBMODULE_DIR}
    BYPRODUCTS ${QTTY_LIBRARY_PATH}
    DEPENDS gen_cpp_units
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
set(TEST_FFI_SOURCES
    tests/main.cpp
    tests/fixtures.hpp
    tests/test_length.cpp
    tests/test_time.cpp
    tests/test_angular.cpp
    tests/test_mass.cpp
    tests/test_power.cpp
    tests/test_derived.cpp
    tests/test_operations.cpp
    tests/test_dimension_safety.cpp
    tests/test_precision.cpp
)

add_executable(test_ffi ${TEST_FFI_SOURCES})
target_link_libraries(test_ffi PRIVATE qtty_cpp GTest::gtest)
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

# Install the qtty_ffi shared library
install(FILES ${QTTY_LIBRARY_PATH}
    DESTINATION lib
)

# Install CMake config files for find_package support
include(CMakePackageConfigHelpers)

# Create the config file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/qtty_cppConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/qtty_cppConfig.cmake
    INSTALL_DESTINATION lib/cmake/qtty_cpp
)

# Create the version file
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/qtty_cppConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install the config and version files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/qtty_cppConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/qtty_cppConfigVersion.cmake
    DESTINATION lib/cmake/qtty_cpp
)

# Export targets
install(TARGETS qtty_cpp
    EXPORT qtty_cppTargets
    INCLUDES DESTINATION include
)

install(EXPORT qtty_cppTargets
    FILE qtty_cppTargets.cmake
    NAMESPACE qtty::
    DESTINATION lib/cmake/qtty_cpp
)

# Generate unit files (if needed)
add_custom_target(
    gen_units
    COMMAND ${CARGO_BIN} run -p qtty-ffi --bin gen_units
    WORKING_DIRECTORY ${QTTY_SUBMODULE_DIR}
    COMMENT "Generating unit files"
    VERBATIM
)
