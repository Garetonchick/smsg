cmake_minimum_required(VERSION 3.16)
project(Smsg LANGUAGES CXX)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create main executable
add_executable(smsg src/main.cpp src/util.cpp) 

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

#gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(my_test src/tests/test.cpp src/util.cpp)
target_link_libraries(my_test ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(my_test ${JSONCPP_LIBRARIES})
gtest_discover_tests(my_test)

# Add root of includes
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Setup clang-tidy 
set_target_properties(
    smsg
    PROPERTIES
        CXX_CLANG_TIDY "clang-tidy"
)

# Copy app files to build dir
# Copy the contents of a directory to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/app/
     DESTINATION ${CMAKE_BINARY_DIR}/
     FILES_MATCHING PATTERN "*")
