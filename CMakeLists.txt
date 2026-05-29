cmake_minimum_required(VERSION 3.16)
project(Backtester LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for the project
include_directories(${CMAKE_SOURCE_DIR}/scr)

# --- Fetch nlohmann/json ---
include(FetchContent)

# ⚠️ Required by nlohmann_json (modern CMake policies)
set(CMAKE_POLICY_DEFAULT_CMP0081 NEW)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)

# Disable tests to reduce build overhead
set(BUILD_TESTING OFF CACHE BOOL "Disable tests for nlohmann_json")

FetchContent_MakeAvailable(nlohmann_json)

# Add executable
add_executable(data_processor ${CMAKE_SOURCE_DIR}/scr/data_processor.cpp)

# Link json library
target_link_libraries(data_processor PRIVATE nlohmann_json::nlohmann_json)