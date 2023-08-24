cmake_minimum_required(VERSION 3.16)
project(Smsg LANGUAGES CXX)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create main executable
add_executable(smsg src/main.cpp)

# pthread
find_package(Threads REQUIRED)
target_link_libraries(smsg PRIVATE Threads::Threads)

# Add roots of includes
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

#Setup clang-tidy 
set_target_properties(
    smsg
    PROPERTIES
        CXX_CLANG_TIDY "clang-tidy"
)
