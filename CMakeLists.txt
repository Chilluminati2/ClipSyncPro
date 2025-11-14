# CMakeLists.txt (The TRUE "No More Resources" Version)
cmake_minimum_required(VERSION 3.16)

project(ClipSyncPro LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# We only need AUTOMOC and AUTOUIC. NO AUTORCC.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# The include_directories command is GONE.

add_executable(ClipSyncPro
    src/main.cpp
    src/core/ClipboardManager.cpp
    src/gui/MainWindow.cpp
    src/gui/SystemTray.cpp
    src/storage/HistoryManager.cpp
    win32_resource.rc # This is ONLY for the .exe icon now.
)

# This is for the C++ compiler and is correct.
target_include_directories(ClipSyncPro PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(ClipSyncPro PRIVATE Qt6::Core Qt6::Widgets)