cmake_minimum_required(VERSION 3.16)
project(Smsg LANGUAGES CXX)

include(FetchContent)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create main executable
add_executable(smsg src/main.cpp src/util.cpp) 

# Cmake modules
# set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

# pthread
find_package(Threads REQUIRED)
target_link_libraries(smsg PRIVATE Threads::Threads)

# openssl
find_package(OpenSSL REQUIRED)
target_link_libraries(smsg PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# jsonlib
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
target_link_libraries(smsg PRIVATE ${JSONCPP_LIBRARIES})
target_include_directories(smsg PRIVATE ${JSONCPP_INCLUDE_DIRS})

# libpqxx
FetchContent_Declare(
  libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  GIT_TAG 7.8.1
)

FetchContent_MakeAvailable(libpqxx)
target_link_libraries(smsg PRIVATE pqxx)
target_include_directories(smsg PRIVATE pqxx)

#gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(my_test src/tests/test.cpp src/util.cpp)
target_link_libraries(my_test ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(my_test ${JSONCPP_LIBRARIES})
target_link_libraries(my_test pqxx)
target_include_directories(my_test PRIVATE ${JSONCPP_INCLUDE_DIRS})
target_include_directories(my_test PRIVATE pqxx)
gtest_discover_tests(my_test)

# Add root of includes
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Setup clang-tidy 
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)

if(CLANG_TIDY_EXECUTABLE)
    message(STATUS "Found clang-tidy")
    set_target_properties(
        smsg
        PROPERTIES
            CXX_CLANG_TIDY "clang-tidy"
    )
else()
    message(WARNING "clang-tidy not found")
endif()

# Setup symbolic link to app directory

set(app_source_directory "${CMAKE_SOURCE_DIR}/app")
set(app_target_directory "${CMAKE_BINARY_DIR}/app") 

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${app_source_directory} ${app_target_directory}
    RESULT_VARIABLE app_symlink_res
)

if(app_symlink_res EQUAL 0)
    message(STATUS "Symbolic link created from ${app_target_directory} to ${app_source_directory}")
else()
    message(FATAL_ERROR "Failed to create symbolic link")
endif()
