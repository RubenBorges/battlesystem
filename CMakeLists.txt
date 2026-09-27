cmake_minimum_required(VERSION 3.20)
project(battlesystem CXX)

# Force C++26 for modern features
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Process the source subdirectory first
add_subdirectory(src)

# =====================================================================
# INSTALL & DISTRIBUTION TARGETS (dist/)
# =====================================================================

set(DIST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist")

# 1. Install the compiled binary executable
install(TARGETS battlesystem
    RUNTIME DESTINATION "${DIST_DIR}"
)

# 2. Copy the text data assets folder contents
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dat/"
    DESTINATION "${DIST_DIR}/dat"
    FILES_MATCHING PATTERN "*.txt"
)

