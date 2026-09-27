# Source and header setups
set(SOURCES
    battlesystem.cpp
    damageengine.cpp
    actor.cpp
    #log.cpp
    datamanager.cpp
    statistics.cpp
    #graph.cpp
    atbsystem.cpp
    priorityqueue.cpp
)
set(HEADERPATHS
    include/damageengine.hpp
    include/statistics.hpp
    include/actor.hpp
   # include/graph.hpp
   # include/log.hpp
    include/datamanager.hpp
    include/atbsystem.hpp
    include/priorityqueue.hpp
    )

add_executable(battlesystem ${SOURCES} ${HEADERPATHS})

# =====================================================================
# SYSTEM PACMAN LLAMA LINKING RULES (Arch Linux)
# =====================================================================


# 2. Add search parameters for your local project headers and system-wide headers
target_include_directories(battlesystem PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/include
    /usr/local/include
)

# 3. Explicitly link everything, clean and warning-free
target_link_libraries(battlesystem PRIVATE
    pthread        # POSIX threads
)

# 4. Compiler optimizations
target_compile_options(battlesystem PRIVATE -O3 -Wall -Wextra -march=native)
