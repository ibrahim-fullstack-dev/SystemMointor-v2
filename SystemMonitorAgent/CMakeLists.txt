cmake_minimum_required(VERSION 3.15)
project(SystemMonitorAgent VERSION 2.0.0 LANGUAGES CXX)

# ---------------------------------------------------------------------------
# 1. Set C++ Modern Standards For More Efficient Performance and Consistently.
# ---------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Prevent Output Build Files From Combining with Main Project Code (In-Source Build). 
set(CMAKE_DISABLE_IN_SOURCE_BUILDS ON)

# ---------------------------------------------------------------------------
# 2. Assemble Shared Files Code (Run on all systems without adjusting).
# ---------------------------------------------------------------------------

set(COMMON_SOURCES
    src/main.cpp
    src/config/AgentConfig.cpp
    src/logic/core/MetricsProcessor.cpp
    src/logic/core/WebSocketClient.cpp
    src/logic/hardwares/CPUProcessor.cpp
    src/logic/hardwares/RAMProcessor.cpp
    src/logic/hardwares/NetworkProcessor.cpp
)

# ---------------------------------------------------------------------------
# 3. Smart Direction and filtering System Files (Link Time Substitution).
# ---------------------------------------------------------------------------

if(WIN32)
    message(STATUS " [OS DETECTED] Configuring target build for Windows OS...")
    
    set(OS_SPECIFIC_SOURCES
        src/data_access/windows/CPUReader.cpp
        src/data_access/windows/RAMReader.cpp
        src/data_access/windows/NetworkReader.cpp
    )
    
    add_compile_definitions(PLATFORM_WINDOWS)
    
    # Link Windows Main Required Libraries To Fetch Performance Pointers.
    # ws2_32 is mandatory for WebSockets, pdh for hardware counters.
    set(PLATFORM_LIBS pdh ws2_32)

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS " [OS DETECTED] Configuring target build for Linux OS...")
    
    set(OS_SPECIFIC_SOURCES
        src/data_access/linux/CPUReader.cpp
        src/data_access/linux/RAMReader.cpp
        src/data_access/linux/NetworkReader.cpp
    )
    
    add_compile_definitions(PLATFORM_LINUX)

    # Declaration For Interact With Programming Background Thread, Linux Needs Thread Library 
    find_package(Threads REQUIRED)
    set(PLATFORM_LIBS Threads::Threads)

else()
    message(FATAL_ERROR " [ERROR] Unsupported Operating System! Only Windows and Linux are supported.")
endif()

# ---------------------------------------------------------------------------
# 4. Start Compilation and Link Components.
# ---------------------------------------------------------------------------

# Combine Shared Code With Target System To Produce Actual App.
add_executable(${PROJECT_NAME} ${COMMON_SOURCES} ${OS_SPECIFIC_SOURCES})

# Select include Folder As a Main path
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link System Libraries That Selected In Step 3.
if(PLATFORM_LIBS)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PLATFORM_LIBS})
endif()

# ---------------------------------------------------------------------------
# 5. For guarantee and Code Quality (Warnings) Run Strict Attentives.
# ---------------------------------------------------------------------------

if(MSVC)
    # /W4 fields high warnings, /WX treats them as errors. 
    # /wd4996 prevents blocking on secure CRT functions (like traditional string APIs)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4996) 
else()
    # Strict options for GCC/Clang on Linux
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()