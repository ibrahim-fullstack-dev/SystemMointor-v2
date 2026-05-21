cmake_minimum_required(VERSION 3.15)
project(SystemMonitorAgent VERSION 2.0.0 LANGUAGES CXX)

# ===========================================================================
# 1. C++ Modern Standards & Build Safety Constraints
# ===========================================================================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enforce clean out-of-source builds to prevent artifact pollution
set(CMAKE_DISABLE_IN_SOURCE_BUILDS ON)

# ===========================================================================
# 2. Dynamic Assembly of Shared Source Files (OS-Independent)
# ===========================================================================

# Automatically captures config, core processors, and isolated math handlers
# (e.g., src/logic/hardwares/*.cpp and src/logic/network/*.cpp)
file(GLOB_RECURSE COMMON_SOURCES
    "src/config/*.cpp"
    "src/logic/*.cpp"
)

# Append local development entry point explicitly
list(APPEND COMMON_SOURCES "src/main.cpp")

# ===========================================================================
# 3. Platform-Specific Aggregation (Link-Time Substitution)
# ===========================================================================

if(WIN32)
    message(STATUS " [OS DETECTED] Configuring target build for Windows OS...")
    
    # Automatically tracks windows/hardwares/ and windows/network/ implementation sets
    file(GLOB_RECURSE OS_SPECIFIC_SOURCES "src/data_access/windows/*.cpp")
    
    add_compile_definitions(PLATFORM_WINDOWS)
    
    # Link Windows native sub-systems:
    # - pdh: performance counters
    # - ws2_32: socket communications
    # - psapi: process status information utilities
    set(PLATFORM_LIBS pdh ws2_32 psapi)

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS " [OS DETECTED] Configuring target build for Linux OS...")
    
    # Automatically tracks linux/hardwares/ and linux/network/ implementation sets
    file(GLOB_RECURSE OS_SPECIFIC_SOURCES "src/data_access/linux/*.cpp")
    
    add_compile_definitions(PLATFORM_LINUX)

    # Linux requires explicit threading runtime hooks
    find_package(Threads REQUIRED)
    set(PLATFORM_LIBS Threads::Threads)

else()
    message(FATAL_ERROR " [ERROR] Unsupported Operating System! Only Windows and Linux are supported.")
endif()

# ===========================================================================
# 4. Binary Generation, Include Configurations, and Linking
# ===========================================================================

# Compile common components paired with targeted platform-specific DAL assets
add_executable(${PROJECT_NAME} ${COMMON_SOURCES} ${OS_SPECIFIC_SOURCES})

# Establish the single source of truth header path mapping
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link hardware telemetry access libraries
if(PLATFORM_LIBS)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LIBS})
endif()

# ===========================================================================
# 5. Strict Code Quality Controls and Compiler Warning Triggers
# ===========================================================================

if(MSVC)
    # /W4: rigorous warnings, /WX: treat warnings as blocking build errors
    # /wd4996: bypasses legacy deprecated warnings regarding standard secure C string routines
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4996) 
else()
    # High-grade warning flags utilized by standard GCC / Clang frameworks
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()